#include "UI/UI.hpp"
#include "Player.hpp"
#include <raylib.h>

void UI::DrawUI(Player& player) const {
  DrawHUD(player);
  DrawDebug(player);
}

void UI::DrawDebug(Player& player) const {
  if (Debug::DEBUG_PERFORMANCE) {
    Rectangle debug_bounds = {GetScreenWidth() * 0.92f, GetScreenHeight() * 0.004f,
                              GetScreenWidth() * 0.06f, GetScreenHeight() * 0.050f};
    DrawRectangleRounded(debug_bounds, 0.2f, 5, HUDColorBg);
    DrawFPS(Window::SCREEN_SIZE.x * 0.93f, Window::SCREEN_SIZE.y * 0.01f);
    DrawText(std::to_string(GetFrameTime()).c_str(), Window::SCREEN_SIZE.x * 0.93f,
             Window::SCREEN_SIZE.y * 0.03f, 20, GREEN);
  }
}
