#pragma once
#include "Map.hpp"
#include <raylib.h>

class Player {
  public:
  // Manipulation functions
  void Spawn(Map& map);
  void Update(Map* map);
  void Draw();
  void Move(Map* map);
  void Attack(); // NOTE: Does not buffer attacks so you must time attacks properly
  unsigned int DealDamage() const;
  bool CheckEntityCollision(Map* map);
  bool CheckInvulnerbility();

  // Variable Getters
  unsigned int GetGold() const;
  unsigned int GetCurrentHealth() const;
  unsigned int GetMaxHealth() const;
  unsigned int GetCurrentMana() const;
  unsigned int GetMaxMana() const;
  float GetSpeed() const;
  unsigned int GetHealthRegenAmount() const;
  unsigned int GetManaRegenAmount() const;

  // Setters
  void TakeDamage(unsigned int a_DamageTaken);
  void Heal(unsigned int a_HealAmount);
  void AddGold(int Gold_Amount);
  void UseMana(unsigned int a_ManaAmount);
  void AddMana(unsigned int a_ManaAmount);

  private: // private functions
  void RegenMana();
  void RegenHealth();
  void CheckMapBounds(Rectangle MapBounds);
  void DebugPlayer() const;
  void CheckInCombat();

  public: // public member variable
  Rectangle bounds;
  Rectangle hit_box;
  int PlayerDirection = UP;

  private:
  // Base Health Stats
  unsigned int m_MaxBaseHealth         = 20;
  unsigned int m_CurHealth             = m_MaxBaseHealth;
  float m_BaseHealthRegenSpeed         = 1;
  unsigned int m_BaseHealthRegenAmount = 1;

  // Base Mana Stats
  unsigned int m_BaseMaxMana         = 10;
  unsigned int m_CurMana             = m_BaseMaxMana;
  float m_BaseManaRegenSpeed         = 1;
  unsigned int m_BaseManaRegenAmount = 1;

  // Movement stats
  float m_BaseSpeed = 150; // NOTE: stat in game will show up divided by 10

  // base combat stats
  unsigned int m_BaseDamage = 2;

  private: // Equiped item stats
  unsigned int m_EquipedItemDamage = 4;

  // Collectable Amounts
  unsigned int m_Gold = 0;

  // Timer stats
  float m_InvulnerableTimer = 0.5;
  float AttackTimeSecs      = 0.3;
  float m_CombatTimer       = 5;

  private: // flags
  bool m_inCombat       = false;
  bool m_isAttacking    = false;
  bool m_isInvulnerable = false;
  Color m_Color         = RED;
  enum Direction { UP = -1, DOWN = 1, LEFT = -2, RIGHT = 2 };
};
