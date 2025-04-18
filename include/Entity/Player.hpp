#pragma once
#include "Item.hpp"
#include "Map.hpp"
#include <map>
#include <raylib.h>
#include <string>
#include <sys/types.h>
#include <unordered_map>

class Player {
  public:
  // Manipulation functions
  void Spawn(Map& map);
  void Update(Map& map);
  void Draw();
  void Move(Map& map);
  void Attack(); // NOTE: Does not buffer attacks so you must time attacks properly
  u_int16_t DealDamage() const;
  bool CheckEntityCollision(Map& map);
  bool CheckInvulnerbility();

  // Variable Getters
  u_int16_t GetGold() const;
  u_int16_t GetCurrentHealth() const;
  u_int16_t GetMaxHealth() const;
  u_int16_t GetCurrentMana() const;
  u_int16_t GetMaxMana() const;
  float GetSpeed() const;
  u_int8_t GetHealthRegenAmount() const;
  u_int8_t GetManaRegenAmount() const;

  // inventory functions
  std::map<std::string, std::map<Item, u_int8_t>> GetInventory() const;
  std::map<Item, u_int8_t> GetInventorySlot(std::string a_Key) const;
  void AddItemToInventory(std::string a_Key);

  // Setters
  void TakeDamage(u_int16_t a_DamageTaken);
  void Heal(u_int16_t a_HealAmount);
  void AddGold(u_int16_t Gold_Amount);
  void UseMana(u_int16_t a_ManaAmount);
  void AddMana(u_int16_t a_ManaAmount);

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
  // inventory
  std::map<Item, u_int8_t> m_Weapon;
  std::map<Item, u_int8_t> m_Armor;
  std::map<Item, u_int8_t> m_Magic;
  std::map<Item, u_int8_t> m_Potions;
  std::map<Item, u_int8_t> m_Treasures;
  std::map<Item, u_int8_t> m_Key_Items;
  std ::unordered_map<std::string, std::map<Item, u_int8_t>&> m_Inventory = {
      {"Weapons", m_Weapon},  {"Armor", m_Armor},        {"Magic", m_Magic},
      {"Potions", m_Potions}, {"Treasure", m_Treasures}, {"Key Items", m_Key_Items}};

  // Base Health Stats
  u_int16_t m_MaxBaseHealth         = 20;
  u_int16_t m_CurHealth             = m_MaxBaseHealth;
  float m_BaseHealthRegenSpeed      = 1;
  u_int16_t m_BaseHealthRegenAmount = 1;

  // Base Mana Stats
  u_int16_t m_BaseMaxMana         = 10;
  u_int16_t m_CurMana             = m_BaseMaxMana;
  float m_BaseManaRegenSpeed      = 1;
  u_int16_t m_BaseManaRegenAmount = 1;

  // Movement stats
  float m_BaseSpeed = 150; // NOTE: stat in game will show up divided by 10

  // base combat stats
  u_int8_t m_BaseDamage = 6;

  private: // Equiped item stats
  u_int8_t m_EquipedItemDamage = 0;
  float m_EquipedItemMoveSpeed = 0;

  // Collectable Amounts
  u_int16_t m_Gold = 0;

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
