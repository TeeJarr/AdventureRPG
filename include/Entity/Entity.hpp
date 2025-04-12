#pragma once
#include <raylib.h>

class Entity
{
  public:
  void Draw() {
    DrawRectangleRec(GetBounds(), RED);
  };
  Rectangle GetBounds() const {
    return (Rectangle){pos.x, pos.y, size.x, size.y};
  }
  Vector2 GetPos() const {
    return pos;
  }

  bool isColliding(Rectangle other) {
    return CheckCollisionRecs(GetBounds(), other);
  }

  protected:
  Vector2 pos;
  Vector2 size;
};
