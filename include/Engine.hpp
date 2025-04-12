#pragma once
#include "Player.hpp"
#include <raylib.h>
#include <sys/types.h>

class Engine
{
  public:
  Engine();
  void Loop();
  void CleanUp();

  private:
  void Update();
  void Draw();
  void Camera();
  void DrawUI();

  void InitCamera();

  private:
  Camera2D camera = {0};
  Player player;
};

namespace CONFIG
{
  inline bool DEBUG = true;
}
