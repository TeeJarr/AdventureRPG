#include "Config.hpp"
#include "UI/UI.hpp"
#include "raylib.h"
#include <string>

void UI::DrawHUD(Player& player) const {
  DrawHUDBackground();     // Draws the background to the HUD
  DrawCurrentGold(player); // Draws the players gold
  DrawBars(player);        // Draw the health and mana bars
  DrawActiveItems(player); //  Draw the players active items
}

void UI::DrawHUDBackground() const {
  Rectangle hud_back = {Window::SCREEN_SIZE.x * 0.005f, Window::SCREEN_SIZE.y * 0.005f,
                        Window::SCREEN_SIZE.x * 0.55f, Window::SCREEN_SIZE.y * 0.09f};
  DrawRectangleRounded(hud_back, 0.2f, 5, HUDColorBg);
}

void UI::DrawActiveItems(Player& player) const {
  // TODO: impliment the get active items from the player
  // TODO: get icons for the items
  Rectangle item_1_bounds = {(Window::SCREEN_SIZE.x * 0.012f + HealthBarLength) +
                                 (Window::SCREEN_SIZE.x * 0.015f),
                             Window::SCREEN_SIZE.y * 0.0180f, Window::SCREEN_SIZE.x * 0.035f,
                             Window::SCREEN_SIZE.x * 0.035f};
  Rectangle item_2_bounds = {item_1_bounds.x * 1.15f, item_1_bounds.y, item_1_bounds.width,
                             item_1_bounds.height};
  DrawRectangleRoundedLinesEx({item_1_bounds}, 0.3f, 5, 2, WHITE);
  DrawRectangleRoundedLinesEx(item_2_bounds, 0.3f, 5, 2, WHITE);
}

void UI::DrawCurrentGold(Player& player) const {
  const char* gold  = ("Gold: " + std::to_string(player.GetGold())).c_str();
  float text_height = MeasureTextEx(GetFontDefault(), gold, 56, 1).y;
  Vector2 gold_pos  = {Window::SCREEN_SIZE.x * 0.425f,
                       Window::SCREEN_SIZE.y * 0.052f - text_height / 2.0f};
  DrawTextEx(GetFontDefault(), gold, gold_pos, 56.0f, 1.0f, WHITE);
}

void UI::DrawBars(Player& player) const {
  // Health Bar
  DrawRectangleRec({Window::SCREEN_SIZE.x * 0.015f, Window::SCREEN_SIZE.y * 0.015f,
                    GetCurrentHealth(player), HealthBarHeight},
                   RED);
  DrawRectangleLinesEx({Window::SCREEN_SIZE.x * 0.015f, Window::SCREEN_SIZE.y * 0.015f,
                        HealthBarLength, HealthBarHeight},
                       4, WHITE);
  // Mana Bar
  DrawRectangleRec({Window::SCREEN_SIZE.x * 0.015f, Window::SCREEN_SIZE.y * 0.055f,
                    GetCurrentMana(player), HealthBarHeight},
                   BLUE);
  DrawRectangleLinesEx({Window::SCREEN_SIZE.x * 0.015f, Window::SCREEN_SIZE.y * 0.055f,
                        HealthBarLength, HealthBarHeight},
                       4, WHITE);
}

float UI::GetCurrentHealth(Player& player) const {
  return HealthBarLength * ((float)player.GetCurrentHealth() / player.GetMaxHealth());
}
float UI::GetCurrentMana(Player& player) const {
  return HealthBarLength * ((float)player.GetCurrentMana() / player.GetMaxMana());
}
