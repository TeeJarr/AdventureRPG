#include "Camera/CameraHandler.hpp"
#include "EntityHandler.hpp"
#include <raylib.h>

void CameraHandler::Init(Player& player) {
  m_Camera.offset   = {Window::SCREEN_SIZE.x / 2.0f, Window::SCREEN_SIZE.y / 2.0f};
  m_Camera.target   = {player.bounds.x + 20, player.bounds.y + 20};
  m_Camera.rotation = 0.0f;
  m_Camera.zoom     = 1;
}

void CameraHandler::Update(Player& player) {
  m_Camera.target = {player.bounds.x + 20, player.bounds.y + 20};
}

void CameraHandler::DrawCameraObjects(Player& player, EntityHandler& entities, Map& map) {
  BeginMode2D(m_Camera);
  map.DrawMap();
  entities.Draw();
  player.Draw();
  EndMode2D();
}
