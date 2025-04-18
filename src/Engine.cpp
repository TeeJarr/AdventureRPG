#include "Engine.hpp"
#include "Config.hpp"
#include "raylib.h"

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
  m_UI.DrawUI(m_Player);
  EndDrawing();
}

void Engine::Update() {
  m_Audio.PlayMusic();
  m_Player.Update(m_Map);
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

void Engine::DrawUI() {}
