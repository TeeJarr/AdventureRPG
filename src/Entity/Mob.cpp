#include "Mob.hpp"
#include "Config.hpp"
#include "raylib.h"
#include <cmath>

Mob::Mob(u_int8_t a_Mob_Flag, Vector2 a_SpawnLocation) { SpawnMob(a_Mob_Flag, a_SpawnLocation); }

void Mob::Update(Player& player) {
  PathFinding(player);
  if (CheckCollisionRecs(player.hit_box, Bounds)) TakeDamage(player);
  if (CheckCollisionRecs(player.bounds, Bounds)) Attack(player);
  if (m_CurHealth <= 0) Die();
}

void Mob::Attack(Player& player) { player.TakeDamage(m_Damage); }
void Mob::TakeDamage(Player& player) { m_CurHealth -= player.DealDamage(); }
bool Mob::Die() { return m_CurHealth <= 0; }

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

void Mob::SpawnMob(u_int8_t a_Mob_Flag, Vector2 a_SpawnLocation) {
  switch (a_Mob_Flag) {
    case ZOMBIE:
      m_AttackSpeed = ZOMBIE_ATTACK_SPEED / 100;
      m_Speed       = ZOMBIE_SPEED;
      m_Damage      = ZOMBIE_DAMAGE;
      m_MaxHealth   = ZOMBIE_HEALTH;
      m_CurHealth   = m_MaxHealth;
      color         = DARKGREEN;
      break;
    case SLIME:
      m_AttackSpeed = SLIME_ATTACK_SPEED / 100;
      m_Speed       = SLIME_SPEED;
      m_Damage      = ZOMBIE_DAMAGE;
      m_MaxHealth   = SLIME_HEALTH;
      m_CurHealth   = m_MaxHealth;
      color         = GREEN;
      break;
    case SKELETON:
      m_AttackSpeed = SKELETON_ATTACK_SPEED / 100;
      m_Speed       = SKELETON_SPEED;
      m_Damage      = SKELETON_DAMAGE;
      m_MaxHealth   = SKELETON_HEALTH;
      m_CurHealth   = m_MaxHealth;
      color         = LIGHTGRAY;
      break;
  }
  Bounds = {a_SpawnLocation.x, a_SpawnLocation.y, (float)Window::TILE_SIZE,
            (float)Window::TILE_SIZE};
}

void Mob::Draw() {
  DrawRectangleRec(Bounds, color);
  DrawRectangleLinesEx(Bounds, 3, WHITE);
}
