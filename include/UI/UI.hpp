#pragma once
#include "Config.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <raygui.h>

class UI {
  public:
  // functions
  void DrawUI(Player& player) const;

  // HUD
  void DrawHUDBackground() const;
  void DrawHUD(Player& player) const;
  float GetCurrentMana(Player& player) const;
  void DrawBars(Player& player) const;
  float GetCurrentHealth(Player& player) const;
  void DrawCurrentGold(Player& player) const;
  void DrawActiveItems(Player& player) const;

  // DEBUG
  void DrawDebug(Player& player) const;

  // UI Variables
  Color HUDColorBg      = ColorAlpha(BLACK, 0.55f);
  float HealthBarLength = Window::SCREEN_SIZE.x * 0.3f;
  float HealthBarHeight = Window::SCREEN_SIZE.y * 0.03f;
};
