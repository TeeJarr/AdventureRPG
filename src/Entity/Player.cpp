#include "Player.hpp"
#include "Config.hpp"
#include "Map.hpp"
#include "raylib.h"
#include <iostream>

void Player::Spawn(Map& map) {
  bounds = {(float)map.MapWidth * Window::TILE_SIZE / 2.0f,
            (float)map.MapHeight * Window::TILE_SIZE / 2.0f, (float)Window::TILE_SIZE,
            (float)Window::TILE_SIZE};
  m_BaseSpeed *= Window::SCALE;
}

void Player::Draw() {
  m_isInvulnerable ? DrawRectangleRec(bounds, BLACK) : DrawRectangleRec(bounds, RED);
  m_inCombat ? DrawRectangleLinesEx(bounds, 3, WHITE) : void();
  m_isAttacking ? DrawRectangleRec(hit_box, WHITE) : void();
}

void Player::Update(Map& map) {
  Move(map);
  Attack();
  CheckInvulnerbility();
  CheckInCombat();
  RegenHealth();
}

void Player::Attack() {
  if (IsKeyPressed(KEY_X) && !m_isAttacking) {
    m_isAttacking = true;
  };
  if (m_isAttacking) {
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
  if (m_isAttacking && AttackTimeSecs <= 0) {
    m_isAttacking  = false;
    AttackTimeSecs = 0.5;
  }
}

u_int16_t Player::DealDamage() const { return m_EquipedItemDamage; }

float Player::GetSpeed() const {
  float speed = m_BaseSpeed;
  // FIXME: incriment through equiped items for any increases
  return speed;
}

void Player::Move(Map& map) {
  float delta               = GetSpeed() * GetFrameTime();
  Rectangle original_bounds = bounds;
  bool move_left            = (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT));
  bool move_right           = (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT));
  bool move_up              = (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN));
  bool move_down            = (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP));

  if (move_left) {
    bounds.x -= delta;
    PlayerDirection = LEFT;
  } else if (move_right) {
    bounds.x += delta;
    PlayerDirection = RIGHT;
  }
  if (CheckEntityCollision(map)) bounds.x = original_bounds.x;
  if (move_up) {
    bounds.y -= delta;
    PlayerDirection = UP;
  } else if (move_down) {
    bounds.y += delta;
    PlayerDirection = DOWN;
  }
  if (CheckEntityCollision(map)) bounds.y = original_bounds.y;
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

bool Player::CheckEntityCollision(Map& map) {
  Rectangle TempBounds        = bounds;
  Vector2 TopLeft             = {TempBounds.x, TempBounds.y};
  Vector2 BottomLeft          = {TempBounds.x, TempBounds.y + TempBounds.height};
  Vector2 TopRight            = {TempBounds.x + TempBounds.width, TempBounds.y};
  Vector2 BottomRight         = {TempBounds.x + TempBounds.width, TempBounds.y + TempBounds.height};
  std::vector<Vector2> points = {TopLeft, TopRight, BottomLeft, BottomRight};

  for (const Vector2& point : points) {
    auto [Tile, TileBounds] = map.GetTile(point);
    int flag                = Tile.GetTerrainFlag();
    if (flag != map.LAND && flag != map.AIR && CheckCollisionPointRec(point, TileBounds)) {
      return true;
    }
  }

  return false;
}

void Player::AddGold(u_int16_t Gold_Amount) { m_Gold += Gold_Amount; }
u_int16_t Player::GetGold() const { return m_Gold; }

u_int16_t Player::GetMaxHealth() const { return m_MaxBaseHealth; } // FIXME: add health bonuses
u_int16_t Player::GetCurrentHealth() const { return m_CurHealth; }
void Player::Heal(u_int16_t a_HealAmount) {
  m_CurHealth += a_HealAmount;
  if (m_CurHealth > GetMaxHealth()) {
    m_CurHealth = GetMaxHealth();
  }
}

void Player::TakeDamage(u_int16_t a_DamageAmount) {
  if (!m_isInvulnerable) {
    m_CurHealth -= a_DamageAmount;
    m_isInvulnerable = true;
    m_inCombat       = true;
  }
  if (m_CurHealth <= 0) {
    // impliment death
    std::cout << "You are dead\n";
    m_CurHealth = GetMaxHealth();
  }
}

bool Player::CheckInvulnerbility() {
  if (m_isInvulnerable) {
    m_InvulnerableTimer -= GetFrameTime();
    if (m_isInvulnerable && m_InvulnerableTimer <= 0) {
      m_Color             = RED;
      m_isInvulnerable    = false;
      m_InvulnerableTimer = 0.5;
    }
  }
  return m_isInvulnerable;
}

u_int8_t Player::GetHealthRegenAmount() const {
  unsigned int regen_amount = m_BaseHealthRegenAmount;
  // FIXME: add regen amount buffs
  return regen_amount;
}

void Player::RegenHealth() {
  if (!m_inCombat) {
    m_BaseHealthRegenSpeed -= GetFrameTime();
    if (m_BaseHealthRegenSpeed <= 0) {
      m_BaseHealthRegenSpeed = 1;
      Heal(GetHealthRegenAmount());
    }
  }
}

void Player::CheckInCombat() {
  if (m_inCombat) {
    m_CombatTimer -= GetFrameTime();
  }
  if (m_CombatTimer <= 0) {
    m_CombatTimer = 5;
    m_inCombat    = false;
  }
}

u_int16_t Player::GetCurrentMana() const { return m_CurMana; }
u_int16_t Player::GetMaxMana() const { return m_BaseMaxMana; } // FIXME: impl mana buffs
void Player::RegenMana() {
  // FIXME: fix this function
  AddMana((int)(GetManaRegenAmount() * GetFrameTime()));
}
u_int8_t Player::GetManaRegenAmount() const {
  unsigned int mana_regen = m_BaseManaRegenAmount;
  // FIXME: impliment mana regen speed buffs
  return mana_regen;
}

void Player::UseMana(u_int16_t a_ManaAmount) {
  m_CurMana -= a_ManaAmount;
  if (m_CurMana < 0) {
    m_CurMana = 0;
  }
}
void Player::AddMana(u_int16_t a_ManaAmount) {
  m_CurMana += a_ManaAmount;
  if (m_CurMana > GetMaxMana()) {
    m_CurMana = GetMaxMana();
  }
}

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
