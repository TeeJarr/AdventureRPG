#include "Engine.hpp"
#include "Config.hpp"
#include "raylib.h"
#include <string>

Engine::Engine() {
  Init();

  while (!WindowShouldClose()) {
    Update();
    Draw();
  }

  CleanUp();
}

void Engine::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  m_Camera.DrawCameraObjects(m_Player, m_Entities, m_Map);
  DrawUI();
  EndDrawing();
}

void Engine::Update() {
  m_Audio.PlayMusic();
  m_Player.Update(&m_Map);
  m_Camera.Update(m_Player);
  m_Entities.Updates(m_Map, m_Player);
}

void Engine::Init() {
  InitWindow(Window::SCREEN_SIZE.x, Window::SCREEN_SIZE.y, "Game");
  m_Audio.Init();
  m_Map.LoadMap();
  m_Player.Spawn(m_Map);
  m_Camera.Init(m_Player);
}

void Engine::CleanUp() {
  m_Audio.UnloadMusic();
  CloseWindow();
}

void Engine::DrawUI() {
  float HealthBarLength = Window::SCREEN_SIZE.x * 0.3f;
  float HealthBarHeight = Window::SCREEN_SIZE.y * 0.05f;
  float CurrentHealthBar =
      HealthBarLength * ((float)m_Player.GetCurrentHealth() / m_Player.GetMaxHealth());

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
    DrawText((std::to_string(m_Player.GetGold()) + " Gold").c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.97f, 20, WHITE);
  }
}
