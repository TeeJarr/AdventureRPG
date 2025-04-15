#pragma once
#include "Config.hpp"
#include "Tile.hpp"
#include "raylib.h"
#include <iostream>
#include <utility>
#include <vector>

class Map {
  public:
  void LoadMap(/* const char* filepath */) {
    isMapLoaded = true;
    m_HeightMap = PopulateMap();
  }

  void UnloadMap() { m_HeightMap.clear(); }

  std::pair<Tile, Rectangle> GetTile(Vector2 EntityBounds) {
    int x                = EntityBounds.x / Window::TILE_SIZE;
    int y                = EntityBounds.y / Window::TILE_SIZE;
    float Tile_Height    = m_HeightMap[y][x];
    Rectangle TileBounds = {(float)x * Window::TILE_SIZE, (float)y * Window::TILE_SIZE,
                            (float)Window::TILE_SIZE, (float)Window::TILE_SIZE};

    if (Tile_Height < 0.3f) {
      return {Water, TileBounds};
    } else if (Tile_Height < 0.35) {
      return {Dirt, TileBounds};
    } else if (Tile_Height < 0.6f) {
      return {Grass, TileBounds};
    } else if (Tile_Height < 0.9f) {
      return {Stone, TileBounds};
    }
    return {Air, TileBounds};
  }

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
          } else if (TileHeight < 0.35) {
            Dirt.Draw({(float)x * Window::TILE_SIZE, (float)y * Window::TILE_SIZE});
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
  enum Terrain {
    LAND,     // Can Pass Through
    MOUNTAIN, // Need tools to pass through
    WATER,    // Need Tools to pass thorugh
    AIR,      // Can pass through
  };

  private:
  std::vector<std::vector<float>> PopulateMap() {
    MapHeight            = 50;
    MapWidth             = 40;
    int OffsetX          = GetRandomValue(0, 2048);
    int OffsetY          = GetRandomValue(0, 2048);
    Image HeightMapImage = GenImagePerlinNoise(
        MapWidth * Window::TILE_SIZE, MapHeight * Window::TILE_SIZE, OffsetX, OffsetY, 1.0f);
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
  Tile Air   = Tile({255, 255, 255, 0}, AIR);
  Tile Grass = Tile(GREEN, LAND);
  Tile Stone = Tile(LIGHTGRAY, MOUNTAIN);
  Tile Water = Tile(BLUE, WATER);
  Tile Dirt  = Tile(BROWN, LAND);
};
