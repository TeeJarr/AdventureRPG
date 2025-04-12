#pragma once
#include "Entity.hpp"
#include <sys/types.h>

class Player : public Entity
{
  public:
  Player();
  void Move();

  private: // private functions
  bool CheckScreenBounds() const;

  private: // member variables
  u_int8_t m_speed = 5;
};
