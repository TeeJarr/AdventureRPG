#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include <raylib.h>

class Engine {
  public:
  Engine();
  void Loop();
  void CleanUp();

  private:
  void Update();
  void Draw();
  void CameraActors();
  void DrawUI();
  void InitCamera();
  void HandleCollectables();

  private:
  Camera2D camera;
  Player player;
  Map map;
};
