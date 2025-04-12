#include "Engine.hpp"
#include "Window.hpp"
#include <iostream>
#include <raylib.h>

Engine::Engine() {
  InitWindow(Window::SCREEN_SIZE.x, Window::SCREEN_SIZE.y, "Window");
  SetTargetFPS(Window::FPS);
  InitCamera();

  Loop();
}

void Engine::Loop() {
  while (!WindowShouldClose()) {
    Update();
    Draw();
  }
}

void Engine::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  // entity section
  BeginMode2D(camera);
  player.Draw();
  EndMode2D();
  // ui section
  DrawUI();
  EndDrawing();
}

void Engine::Update() {
  std::cout << player.GetPos().x << " " << player.GetPos().y << std::endl;
  // update entities
  player.Move();
  Camera();
  // update ui
}

void Engine::Camera() {
  // camera follows the player
  camera.target = {player.GetPos().x + 20, player.GetPos().y + 20};
}

void Engine::DrawUI() {
  if (CONFIG::DEBUG) {
    DrawFPS(Window::SCREEN_SIZE.x * 0.01, Window::SCREEN_SIZE.y * 0.01);
  }
  // Draw HP Bar
  // Draw Mana Bar
  // Draw Active Items
  // Draw Current Money
}

void Engine::InitCamera() {
  // initializes camera on the center of the screen with default zoom and rotation
  camera.target   = {0, 0}; // make centered on the player character once that is implimented
  camera.offset   = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera.zoom     = 1.0f;
  camera.rotation = 0.0f;
}

void Engine::CleanUp() {
  CloseWindow();
}
