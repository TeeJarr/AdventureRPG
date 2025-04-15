#pragma once
#include "Config.hpp"
#include "raylib.h"

// TODO: Make the Tile Load a Texture from a file
class Tile {
  public:
  Tile(Color a_Color) : TileColor(a_Color) {}
  void Draw(Vector2 TilePos) const {
    DrawRectangleRec({TilePos.x, TilePos.y, (float)Window::TILE_SIZE, (float)Window::TILE_SIZE},
                     TileColor);
  }
  // void UpdateTileSize() {Bounds}

  private:
  Texture2D texture; // TODO: impliment the actual texture here
  Color TileColor;
  Rectangle Bounds;
};
