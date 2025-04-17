#pragma once
#include "Collectable.hpp"
#include "Mob.hpp"
#include <vector>

struct EntityHandler {
  std::vector<Mob*> Mobs;
  std::vector<Collectable*> Collectables;

  void HandleMobs(Map& map);
  void HandleCollectables(Map& map, Player& player);
  void MobSpawnCheck(Map& map);

  void Updates(Map& map, Player& player);
  void Draw() const;

  // Mob Values Checks
  float m_MobSpawnCheckRate     = 5;
  unsigned int m_MobSpawnChance = 30;
  unsigned int m_MobCap;
};
