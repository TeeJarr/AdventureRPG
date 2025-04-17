#pragma once
#include "Config.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>

class Collectable {
  public:
  Collectable(Vector2 a_Pos) {
    bounds = {a_Pos.x * Window::TILE_SIZE, a_Pos.y * Window::TILE_SIZE, (float)Window::TILE_SIZE,
              (float)Window::TILE_SIZE};
    if (bounds.x >= a_Pos.x + Window::TILE_SIZE) {
      bounds.x -= Window::TILE_SIZE;
    }
    if (bounds.y >= a_Pos.y + Window::TILE_SIZE) {
      bounds.y -= Window::TILE_SIZE;
    }
    Value = GetRandomValue(1, 20);
    std::cout << "Coin Created\n";
  }
  // Collectable(Player* player);
  ~Collectable() { std::cout << "Collectable Destroyed\n"; }
  void Draw() const {
    DrawRectangleRec(bounds, color);
    DrawRectangleLinesEx(bounds, 3, WHITE);
  }

  bool Collect(Player* player, void (*func)()) {
    if (CheckCollisionRecs(player->bounds, bounds)) {
      func();
      return true;
    } else {
      return false;
    }
  }

  bool Collect(Player* player) {
    if (CheckCollisionRecs(player->bounds, bounds)) {
      player->AddGold(Value);
      return true;
    } else {
      return false;
    }
  }
  // color setter
  void SetColor(Color a_Color) { color = a_Color; }

  public: // public variables
  Rectangle bounds;

  private:
  unsigned int Value;
  Color color = GOLD;
};
