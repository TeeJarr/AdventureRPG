#pragma once
#include "Collectable.hpp"
#include "Mob.hpp"
#include <vector>

class EntityHandler {
  public:
  std::vector<Mob*> Mobs;
  std::vector<Collectable*> Collectables;

  void HandleMobs(Map& map);
  void HandleCollectables(Map& map, Player& player);
  void MobSpawnCheck(Map& map);

  void Updates(Map& map, Player& player);
  void Draw() const;

  // Mob Values Checks
  float m_MobSpawnCheckRate = 5;
  u_int8_t m_MobSpawnChance = 30;
  u_int8_t m_MobCap;
};
