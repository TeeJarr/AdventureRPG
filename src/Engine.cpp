#include "Engine.hpp"
#include "Collectable.hpp"
#include "Config.hpp"
#include "raylib.h"
#include <string>

Engine::Engine() {
  InitWindow(Window::SCREEN_SIZE.x, Window::SCREEN_SIZE.y, "Game");
  SetTargetFPS(144);
  InitCamera();
  map.LoadMap();
  Collectable* coin = new Collectable(
      {(float)GetRandomValue(0, map.MapWidth), (float)GetRandomValue(0, map.MapHeight)});
  coin_arr.push_back(coin);
  player.Spawn(map);
  while (!WindowShouldClose()) {
    Update();
    Draw();
  }

  CleanUp();
}

void Engine::CleanUp() { CloseWindow(); }

void Engine::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  CameraActors(); // draw all elements that are affected by the camera
  DrawUI();       // draw all of the static UI elements on the screen
  EndDrawing();
}

void Engine::CameraActors() {
  BeginMode2D(camera);
  // TODO: Draw the map to the screen
  map.DrawMap();
  for (Collectable* coin : coin_arr) {
    coin->Draw();
  }
  player.Draw();
  // TODO: Draw other Entities to the screen
  EndMode2D();
}

void Engine::DrawUI() {
  if (Debug::DEBUG_PERFORMANCE) {
    DrawFPS(Window::SCREEN_SIZE.x * 0.01f, Window::SCREEN_SIZE.y * 0.01f);
    DrawText(std::to_string(GetFrameTime()).c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.03f, 20, GREEN);
    DrawText((std::to_string(player.GetGold()) + " Gold").c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.97f, 20, WHITE);
  }
}

void Engine::Update() {
  player.Update(map);
  camera.target = {player.bounds.x + 20, player.bounds.y + 20};
  HandleCollectables();
}

void Engine::InitCamera() {
  camera.offset   = {Window::SCREEN_SIZE.x / 2.0f, Window::SCREEN_SIZE.y / 2.0f};
  camera.target   = {player.bounds.x + 20, player.bounds.y + 20};
  camera.rotation = 0.0f;
  camera.zoom     = 1;
}

void Engine::HandleCollectables() {
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
  for (Collectable* coin : deleteQueue) {
    delete coin;
  }
  for (int i = 0; i < CoinsCollected; i++) {
    float coinX       = (float)GetRandomValue(0, map.MapWidth);
    float coinY       = (float)GetRandomValue(0, map.MapHeight);
    Collectable* coin = new Collectable({coinX, coinY});
    coin_arr.push_back(coin);
    std::cout << coin->bounds.x << ", " << coin->bounds.y << std::endl;
  }
}
