#pragma once
#include "AudioHandler.hpp"
#include "Camera/CameraHandler.hpp"
#include "EntityHandler.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "UI/UI.hpp"
#include <raylib.h>

class Engine {
  public:
  Engine();

  private:
  void Update();
  void Draw();
  void Init();
  void DrawUI();
  void CleanUp();

  private: // Included Objects
  CameraHandler m_Camera;
  UI m_UI;
  Player m_Player;
  Map m_Map;
  EntityHandler m_Entities;
  AudioHandler m_Audio;
};
