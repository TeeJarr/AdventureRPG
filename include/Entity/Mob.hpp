#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <vector>

class Mob {
  public:
  Mob(unsigned int a_Mob_Flag, Vector2 a_SpawnLocation);
  // ~Mob();
  void Update(Player& player);
  void Draw();
  void Attack(Player& player);
  void TakeDamage(Player& player);
  void PathFinding(Player& player);
  void GetMaxHealth() const;
  void GetCurrentHealth() const;
  void GetAttackDamage() const;
  bool Die();

  public:
  Rectangle Bounds;

  private: // mob type damage values
  int m_CurHealth;
  unsigned int m_MaxHealth;
  unsigned int m_Damage;
  unsigned int m_Speed;
  unsigned int m_AttackSpeed;
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

inline std::vector<Mob*> mob_arr;
