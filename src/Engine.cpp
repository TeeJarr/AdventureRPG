#include "Engine.hpp"
#include "Collectable.hpp"
#include "Config.hpp"
#include "Mob.hpp"
#include "raylib.h"
#include <string>

Engine::Engine() {
  InitWindow(Window::SCREEN_SIZE.x, Window::SCREEN_SIZE.y, "Game");
  // SetTargetFPS(144);
  LoadMusic();
  InitCamera();
  map.LoadMap();
  player.Spawn(map);
  while (!WindowShouldClose()) {
    Update();
    Draw();
  }

  CleanUp();
}

void Engine::LoadMusic() {
  InitAudioDevice();
  music = LoadMusicStream("../../sound/music/music.mp3");
  PlayMusicStream(music);
}

void Engine::CleanUp() {
  CloseWindow();
  UnloadMusicStream(music);
  CloseAudioDevice();
}

void Engine::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  CameraActors(); // draw all elements that are affected by the camera
  DrawUI();       // draw all of the static UI elements on the screen
  EndDrawing();
}

void Engine::CameraActors() {
  BeginMode2D(camera);
  map.DrawMap();
  for (Collectable* coin : coin_arr) {
    coin->Draw();
  }
  for (Mob* mob : mob_arr) {
    mob->Draw();
  }
  player.Draw();
  EndMode2D();
}

void Engine::DrawUI() {
  float HealthBarLength = Window::SCREEN_SIZE.x * 0.3f;
  float HealthBarHeight = Window::SCREEN_SIZE.y * 0.05f;
  float CurrentHealthBar =
      HealthBarLength * ((float)player.GetCurrentHealth() / player.GetMaxHealth());

  DrawRectangleRec({Window::SCREEN_SIZE.x * 0.02f, Window::SCREEN_SIZE.y * 0.01f, CurrentHealthBar,
                    HealthBarHeight},
                   RED);
  DrawRectangleLinesEx({Window::SCREEN_SIZE.x * 0.02f, Window::SCREEN_SIZE.y * 0.01f,
                        HealthBarLength, HealthBarHeight},
                       4, WHITE);

  if (Debug::DEBUG_PERFORMANCE) {
    DrawFPS(Window::SCREEN_SIZE.x * 0.01f, Window::SCREEN_SIZE.y * 0.01f);
    DrawText(std::to_string(GetFrameTime()).c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.03f, 20, GREEN);
    DrawText((std::to_string(player.GetGold()) + " Gold").c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.97f, 20, WHITE);
  }
}

void Engine::Update() {
  UpdateMusicStream(music);
  player.Update(&map);
  camera.target = {player.bounds.x + 20, player.bounds.y + 20};
  MobSpawnCheck();
  HandleCollectables();
  // HACK: Move mob stuff into own function
  for (Mob* mob : mob_arr) {
    mob->Update(player);
  }
  HandleMobs();
}

void Engine::InitCamera() {
  camera.offset   = {Window::SCREEN_SIZE.x / 2.0f, Window::SCREEN_SIZE.y / 2.0f};
  camera.target   = {player.bounds.x + 20, player.bounds.y + 20};
  camera.rotation = 0.0f;
  camera.zoom     = 1;
}

void Engine::HandleMobs() {
  int DeadMobs = 0;
  std::vector<int> MobIndex;
  std::vector<Mob*> deleteQueue;
  int index = 0;
  for (Mob* mob : mob_arr) {
    if (mob->Die()) {
      MobIndex.push_back(index);
      deleteQueue.push_back(mob);
      DeadMobs++;

      float mob_bounds_x = mob->Bounds.x / map.MapWidth;
      float mob_bounds_y = mob->Bounds.y / map.MapHeight;

      int random_val = GetRandomValue(1, 4);
      float coinX, coinY;
      for (int i = 0; i < random_val; i++) {
        coinX = GetRandomValue(mob_bounds_x * 0.9, mob_bounds_x * 1.1);
        coinY = GetRandomValue(mob_bounds_y * 0.9, mob_bounds_y * 1.1);

        if (coinX + Window::TILE_SIZE > map.MapWidth + Window::TILE_SIZE) {
          coinX = map.MapWidth;
          std::cout << coinX << std::endl;
        }
        if (coinX < 0) coinX = 0;
        if (coinY + Window::TILE_SIZE > map.MapHeight + Window::TILE_SIZE) {
          coinY = map.MapHeight;
          std::cout << coinY << std::endl;
        }
        if (coinY < 0) coinY = 0;

        Collectable* coin = new Collectable({coinX, coinY});
        coin_arr.push_back(coin);
        std::cout << coin->bounds.x << ", " << coin->bounds.y << std::endl;
      }
    }
    index++;
  }

  for (int i : MobIndex) {
    mob_arr.erase(mob_arr.begin() + i);
  }
}

void Engine::HandleCollectables() {
  // TODO: impliment despawning for the coins after enough time
  int CoinsCollected = 0;
  std::vector<int> CoinIndex;
  std::vector<Collectable*> deleteQueue;
  int index = 0;
  for (Collectable* coin : coin_arr) {
    if (coin->Collect(&player)) {
      CoinIndex.push_back(index);
      deleteQueue.push_back(coin);
      CoinsCollected++;
    }
    index++;
  }
  for (int i : CoinIndex) {
    coin_arr.erase(coin_arr.begin() + i);
  }
}

void Engine::MobSpawnCheck() {
  m_MobSpawnCheckRate -= GetFrameTime();
  if (m_MobSpawnCheckRate <= 0) {
    int random_val = GetRandomValue(0, 100);
    if (random_val <= m_MobSpawnChance) {
      Mob* zombie = new Mob(0, {(float)GetRandomValue(0, map.MapWidth * Window::TILE_SIZE),
                                (float)GetRandomValue(0, map.MapHeight * Window::TILE_SIZE)});
      mob_arr.push_back(zombie);
      std::cout << "Mob spawned\n";
    }
    m_MobSpawnCheckRate = 1;
  }
}
