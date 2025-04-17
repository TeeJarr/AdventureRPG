#pragma once
#include "EntityHandler.hpp"
#include "Player.hpp"
#include "raylib.h"

struct CameraHandler {
  void Init(Player& player);
  void Update(Player& player);
  void DrawCameraObjects(Player& player, EntityHandler& entities, Map& map);

  Camera2D m_Camera;
};
