#include "EntityHandler.hpp"
#include "Collectable.hpp"

void EntityHandler::Updates(Map& map, Player& player) {
  // Update the mobs
  MobSpawnCheck(map);
  for (Mob* mob : Mobs) {
    mob->Update(player);
  }
  HandleMobs(map);

  // Update Collectables
  HandleCollectables(map, player);
}

void EntityHandler::Draw() const {
  for (Collectable* collectable : Collectables) {
    collectable->Draw();
  }

  for (Mob* mob : Mobs) {
    mob->Draw();
  }
}

void EntityHandler::HandleMobs(Map& map) {
  unsigned int DeadMobs = 0;
  std::vector<int> MobIndex;
  std::vector<Mob*> deleteQueue;
  int index = 0;
  for (Mob* mob : Mobs) {
    if (mob->Die()) {
      MobIndex.push_back(index);
      deleteQueue.push_back(mob);
      DeadMobs++;

      float mob_bounds_x = mob->Bounds.x / map.MapWidth;
      float mob_bounds_y = mob->Bounds.y / map.MapHeight;

      int random_val = GetRandomValue(1, 4);
      float coinX, coinY;
      for (int i = 0; i < random_val; i++) {
        coinX = GetRandomValue(mob_bounds_x * 0.9, mob_bounds_x * 1.1);
        coinY = GetRandomValue(mob_bounds_y * 0.9, mob_bounds_y * 1.1);

        if (coinX + Window::TILE_SIZE > map.MapWidth + Window::TILE_SIZE) {
          coinX = map.MapWidth;
          std::cout << coinX << std::endl;
        }
        if (coinX < 0) coinX = 0;
        if (coinY + Window::TILE_SIZE > map.MapHeight + Window::TILE_SIZE) {
          coinY = map.MapHeight;
          std::cout << coinY << std::endl;
        }
        if (coinY < 0) coinY = 0;

        Collectable* coin = new Collectable({coinX, coinY});
        Collectables.push_back(coin);
        std::cout << coin->bounds.x << ", " << coin->bounds.y << std::endl;
      }
    }
    index++;
  }

  for (int i : MobIndex) {
    Mobs.erase(Mobs.begin() + i);
  }
}

void EntityHandler::HandleCollectables(Map& map, Player& player) {
  // TODO: impliment despawning for the coins after enough time
  int CoinsCollected = 0;
  std::vector<int> CoinIndex;
  std::vector<Collectable*> deleteQueue;
  int index = 0;
  for (Collectable* coin : Collectables) {
    if (coin->Collect(&player)) {
      CoinIndex.push_back(index);
      deleteQueue.push_back(coin);
      CoinsCollected++;
    }
    index++;
  }
  for (int i : CoinIndex) {
    Collectables.erase(Collectables.begin() + i);
  }
}

void EntityHandler::MobSpawnCheck(Map& map) {
  m_MobSpawnCheckRate -= GetFrameTime();
  if (m_MobSpawnCheckRate <= 0 && Mobs.size() < m_MobCap) {
    int random_val = GetRandomValue(0, 100);
    if (random_val <= m_MobSpawnChance) {
      int mob_spawned = GetRandomValue(0, 2);
      Mob* mob =
          new Mob(mob_spawned, {(float)GetRandomValue(0, map.MapWidth * Window::TILE_SIZE),
                                (float)GetRandomValue(0, map.MapHeight * Window::TILE_SIZE)});
      Mobs.push_back(mob);
      std::cout << "Mob spawned\n";
    }
    if (Mobs.size() >= m_MobCap) std::cout << "Mob cap full" << std::endl;
    m_MobSpawnCheckRate = 1;
  }
}
