#pragma once
#include "Config.hpp"
#include "raylib.h"

// TODO: Make the Tile Load a Texture from a file
class Tile {
  public:
  Tile(Color a_Color, unsigned int a_TerrainFlag)
      : TileColor(a_Color), TerrainFlag(a_TerrainFlag) {}
  void Draw(Vector2 TilePos) const {
    DrawRectangleRec({TilePos.x, TilePos.y, (float)Window::TILE_SIZE, (float)Window::TILE_SIZE},
                     TileColor);
  }
  unsigned int GetTerrainFlag() const { return TerrainFlag; }
  // void UpdateTileSize() {Bounds}
  Rectangle GetBounds() const { return Bounds; }

  private:
  Texture2D texture; // TODO: impliment the actual texture here
  Color TileColor;
  Rectangle Bounds;
  u_int8_t TerrainFlag;
};
