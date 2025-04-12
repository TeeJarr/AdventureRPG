#include "Player.hpp"
#include "Window.hpp"
#include <raylib.h>

Player::Player() {
  pos  = {Window::SCREEN_SIZE.x / 2.0f, Window::SCREEN_SIZE.y / 2.0f};
  size = {25, 25};
}

void Player::Move() {
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    pos.x -= m_speed;
  } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    pos.x += m_speed;
  }

  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
    pos.y -= m_speed;
  } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
    pos.y += m_speed;
  }
}
