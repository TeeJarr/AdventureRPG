#pragma once
#include "Player.hpp"
#include "raylib.h"

class Mob {
  public:
  Mob(u_int8_t a_Mob_Flag, Vector2 a_SpawnLocation);
  void Update(Player& player);
  void Draw();
  void Attack(Player& player);
  void TakeDamage(Player& player);
  void PathFinding(Player& player);
  void GetMaxHealth() const;
  void GetCurrentHealth() const;
  void GetAttackDamage() const;
  bool Die();
  void SpawnMob(u_int8_t a_Mob_Flag, Vector2 a_SpawnLocation);

  public:
  Rectangle Bounds;

  private: // mob type damage values
  int m_CurHealth;
  u_int16_t m_MaxHealth;
  u_int16_t m_Damage;
  u_int16_t m_Speed;
  u_int16_t m_AttackSpeed;
  Color color;

  enum MobType { ZOMBIE, SKELETON, SLIME };
  enum MobDamage { ZOMBIE_DAMAGE = 5, SKELETON_DAMAGE = 4, SLIME_DAMAGE = 2 };
  enum MobHealth { ZOMBIE_HEALTH = 10, SKELETON_HEALTH = 12, SLIME_HEALTH = 6 };
  enum MobSpeed { ZOMBIE_SPEED = 120, SKELETON_SPEED = 135, SLIME_SPEED = 80 };
  enum MobAttackSpeed { // NOTE: Can't make the value a float
    ZOMBIE_ATTACK_SPEED   = 50,
    SKELETON_ATTACK_SPEED = 50,
    SLIME_ATTACK_SPEED    = 80
  };
};
