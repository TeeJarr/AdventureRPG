#include "UI/UI.hpp"
#include "Player.hpp"
#include <raylib.h>

void UI::DrawUI(Player& player) const {
  DrawHUD(player);
  DrawDebug(player);
}

void UI::DrawDebug(Player& player) const {
  if (Debug::DEBUG_PERFORMANCE) {
    DrawFPS(Window::SCREEN_SIZE.x * 0.01f, Window::SCREEN_SIZE.y * 0.01f);
    DrawText(std::to_string(GetFrameTime()).c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.03f, 20, GREEN);
    DrawText((std::to_string(player.GetGold()) + " Gold").c_str(), Window::SCREEN_SIZE.x * 0.01f,
             Window::SCREEN_SIZE.y * 0.97f, 20, WHITE);
  }
}
