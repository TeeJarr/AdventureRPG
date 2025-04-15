#pragma once
#include <raylib.h>
#include <sys/types.h>

namespace Debug {
  inline bool DEBUG_PERFORMANCE = true;
  inline bool DEBUG_PLAYER      = false;
} // namespace Debug
namespace Window {
  inline Vector2 BASE_RES       = {640, 360};
  inline u_int8_t SCALE         = 3;
  inline unsigned int TILE_BASE = 16;
  inline unsigned int TILE_SIZE = TILE_BASE * SCALE;
  inline Vector2 SCREEN_SIZE    = {BASE_RES.x * SCALE, BASE_RES.y* SCALE};
} // namespace Window
