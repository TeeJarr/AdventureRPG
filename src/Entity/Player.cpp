#include "Player.hpp"
#include "Config.hpp"
#include "Map.hpp"
#include "raylib.h"
#include <iostream>

void Player::Spawn(Map& map) {
  bounds = {(float)map.MapWidth * Window::TILE_SIZE / 2.0f,
            (float)map.MapHeight * Window::TILE_SIZE / 2.0f, (float)Window::TILE_SIZE,
            (float)Window::TILE_SIZE};
  m_speed *= Window::SCALE;
}

void Player::Draw() const {
  DrawRectangleRec(bounds, RED);
  isAttacking ? DrawRectangleRec(hit_box, WHITE) : DrawRectangleRec({}, BLACK);
}

void Player::Update(Map& map) {
  Move(map);
  Attack();
}

void Player::Attack() {
  if (IsKeyPressed(KEY_X) && !isAttacking) {
    isAttacking = true;
  };
  if (isAttacking) {
    if (PlayerDirection == LEFT) {
      hit_box = {bounds.x - (float)Window::TILE_SIZE, bounds.y, (float)Window::TILE_SIZE,
                 (float)Window::TILE_SIZE};
    } else if (PlayerDirection == RIGHT) {
      hit_box = {bounds.x + (float)Window::TILE_SIZE, bounds.y, (float)Window::TILE_SIZE,
                 (float)Window::TILE_SIZE};
    } else if (PlayerDirection == UP) {
      hit_box = {bounds.x, bounds.y - (float)Window::TILE_SIZE, (float)Window::TILE_SIZE,
                 (float)Window::TILE_SIZE};
    } else if (PlayerDirection == DOWN) {
      hit_box = {bounds.x, bounds.y + (float)Window::TILE_SIZE, (float)Window::TILE_SIZE,
                 (float)Window::TILE_SIZE};
    }
    AttackTimeSecs -= 2 * GetFrameTime();
  }
  if (isAttacking && AttackTimeSecs <= 0) {
    isAttacking    = false;
    AttackTimeSecs = 0.5;
  }
}

void Player::Move(Map& map) {
  if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_A)) {
    bounds.x -= m_speed * GetFrameTime();
    PlayerDirection = LEFT;
    if (Debug::DEBUG_PLAYER) {
      DebugPlayer();
    }
  } else if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D)) {
    bounds.x += m_speed * GetFrameTime();
    PlayerDirection = RIGHT;
    if (Debug::DEBUG_PLAYER) {
      DebugPlayer();
    }
  }
  if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_W)) {
    bounds.y -= m_speed * GetFrameTime();
    PlayerDirection = UP;
    if (Debug::DEBUG_PLAYER) {
      DebugPlayer();
    }
  } else if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) || IsKeyDown(KEY_S)) {
    bounds.y += m_speed * GetFrameTime();
    PlayerDirection = DOWN;
    if (Debug::DEBUG_PLAYER) {
      DebugPlayer();
    }
  }
  CheckMapBounds(
      {0, 0, (float)map.MapWidth * Window::TILE_SIZE, (float)map.MapHeight * Window::TILE_SIZE});
}

void Player::CheckMapBounds(Rectangle MapBounds) {
  if (bounds.x <= MapBounds.x) {
    bounds.x = MapBounds.x;
  } else if (bounds.x + bounds.width >= MapBounds.width) {
    bounds.x = MapBounds.width - bounds.width;
  }

  if (bounds.y <= MapBounds.y) {
    bounds.y = MapBounds.y;
  } else if (bounds.y + bounds.height >= MapBounds.height) {
    bounds.y = MapBounds.height - bounds.height;
  }
}

void Player::AddGold(int Gold_Amount) { m_Gold += Gold_Amount; }
unsigned int Player::GetGold() const { return m_Gold; }

// DEBUG FUNCTIONS
void Player::DebugPlayer() const {
  const char* direction;
  switch (PlayerDirection) {
    case UP   : direction = "UP"; break;
    case DOWN : direction = "DOWN"; break;
    case RIGHT: direction = "RIGHT"; break;
    case LEFT : direction = "LEFT"; break;
  }
  std::cout << "Player Direction: " << direction << std::endl;
}
