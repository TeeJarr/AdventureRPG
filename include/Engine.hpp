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
  void HandleMobs();
  void MobSpawnCheck();
  void LoadMusic();

  private: // enviorment variables
  float m_MobSpawnCheckRate     = 5;
  unsigned int m_MobSpawnChance = 30;

  private:
  Camera2D camera;
  Music music;
  Player player;
  Map map;
};
