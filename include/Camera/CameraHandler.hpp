#pragma once
#include "EntityHandler.hpp"
#include "Player.hpp"
#include "raylib.h"

class CameraHandler {
  public:
  void Init(Player& player);
  void Update(Player& player);
  void DrawCameraObjects(Player& player, EntityHandler& entities, Map& map);

  Camera2D m_Camera;
};
