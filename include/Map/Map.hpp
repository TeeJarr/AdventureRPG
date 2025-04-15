#pragma once
#include "Config.hpp"
#include "Tile.hpp"
#include "raylib.h"
#include <vector>

class Map {
  public:
  void LoadMap(/* const char* filepath */) {
    isMapLoaded = true;
    m_HeightMap = PopulateMap();
  }
  void UnloadMap() { m_HeightMap.clear(); }
  void DrawMap() const {
    if (!isMapLoaded) {
      return;
    }

    for (std::vector y_tiles : m_HeightMap) {
      int y = 0;
      for (std::vector x_tiles : m_HeightMap) {
        int x = 0;
        for (float TileHeight : x_tiles) {
          if (TileHeight < 0.3f) {
            Water.Draw({(float)x * Window::TILE_SIZE, (float)y * Window::TILE_SIZE});
          } else if (TileHeight < 0.6f) {
            Grass.Draw({(float)x * Window::TILE_SIZE, (float)y * Window::TILE_SIZE});
          } else if (TileHeight < 0.9f) {
            Stone.Draw({(float)x * Window::TILE_SIZE, (float)y * Window::TILE_SIZE});
          }
          x++;
        }
        y++;
      }
    }
  }

  public:
  float MapWidth;
  float MapHeight;

  private:
  std::vector<std::vector<float>> PopulateMap() {
    MapHeight            = 50;
    MapWidth             = 40;
    Image HeightMapImage = GenImagePerlinNoise(MapWidth * Window::TILE_SIZE,
                                               MapHeight * Window::TILE_SIZE, 0, 0, 0.5f);
    std::vector<std::vector<float>> heightMap(MapHeight, std::vector<float>(MapWidth));
    for (int y = 0; y < MapHeight; y++) {
      for (int x = 0; x < MapWidth; x++) {
        Color color  = GetImageColor(HeightMapImage, x * Window::TILE_SIZE, y * Window::TILE_SIZE);
        float height = (float)color.r / 255.0f;
        heightMap[y][x] = height;
      }
    }
    UnloadImage(HeightMapImage);
    return heightMap;
  }

  private:
  bool isMapLoaded = false;
  std::vector<std::vector<float>> m_HeightMap;
  Tile Grass = Tile(GREEN);
  Tile Stone = Tile(LIGHTGRAY);
  Tile Water = Tile(BLUE);
  Tile Dirt  = Tile(BROWN);
};
