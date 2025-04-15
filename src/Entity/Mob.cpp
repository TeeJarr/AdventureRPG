#include "Mob.hpp"
#include "Config.hpp"
#include "raylib.h"
#include <cmath>
#include <cstdlib>

Mob::Mob(unsigned int a_Mob_Flag, Vector2 a_SpawnLocation) {
  switch (a_Mob_Flag) {
    case ZOMBIE:
      m_AttackSpeed = ZOMBIE_ATTACK_SPEED / 100;
      m_Speed       = ZOMBIE_SPEED;
      m_Damage      = ZOMBIE_DAMAGE;
      m_Health      = ZOMBIE_HEALTH;
      color         = DARKGREEN;
      break;
  }

  Bounds = {a_SpawnLocation.x, a_SpawnLocation.y, (float)Window::TILE_SIZE,
            (float)Window::TILE_SIZE};
}

void Mob::Update(Player& player) {
  PathFinding(player);
  // Attack(player);
}

void Mob::PathFinding(Player& player) {
  Vector2 MobCenter    = {Bounds.x + (Bounds.width / 2.0f), Bounds.y + (Bounds.height / 2.0f)};
  Vector2 PlayerCenter = {player.bounds.x + (player.bounds.width / 2.0f),
                          player.bounds.y + (player.bounds.height / 2.0f)};
  Vector2 direction    = {PlayerCenter.x - MobCenter.x, PlayerCenter.y - MobCenter.y};
  float length         = std::sqrt(direction.x * direction.x + direction.y * direction.y);

  if (length < 800) {
    if (length != 0) {
      direction.x /= length;
      direction.y /= length;
    }
    Bounds.x += direction.x * m_Speed * GetFrameTime();
    Bounds.y += direction.y * m_Speed * GetFrameTime();
  }
}

void Mob::Draw() {
  DrawRectangleRec(Bounds, color);
  DrawRectangleLinesEx(Bounds, 3, WHITE);
}
