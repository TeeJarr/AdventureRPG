#pragma once
#include "Map.hpp"
#include <raylib.h>

class Player {
  public:
  void Spawn(Map& map);
  void Update(Map* map);
  void Draw() const;
  void Move(Map* map);
  void Attack(); // NOTE: Does not buffer attacks so you must time attacks properly
  void TakeDamage(unsigned int a_DamageTaken);
  void Heal(unsigned int a_HealAmount);
  void AddGold(int Gold_Amount);
  unsigned int GetGold() const;
  bool CheckEntityCollision(Map* map);

  public: // public member variable
  Rectangle bounds;
  Rectangle hit_box;
  int PlayerDirection = UP;

  private: // private functions
  void CheckMapBounds(Rectangle MapBounds);
  void DebugPlayer() const;

  private: // player stats
  unsigned int m_Health = 10;
  unsigned int m_Gold   = 0;

  private: // private member variables
  bool isAttacking     = false;
  float m_speed        = 150;
  float AttackTimeSecs = 0.5;
  enum Direction { UP = -1, DOWN = 1, LEFT = -2, RIGHT = 2 };
};
