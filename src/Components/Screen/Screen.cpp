#include "./Screen.hpp"
#include <format>
#include <raylib.h>

gmb::Screen::Screen(MMU& mmu) : mmu_(mmu) {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gameboy");
    next_refresh_time_ = GetTime() + TARGET_FRAME_TIME_;
}

gmb::Screen::~Screen() {
    CloseWindow();
}

void gmb::Screen::tryRefresh() {
    if (GetTime() > next_refresh_time_) {
        drawGame();
    }
}

bool gmb::Screen::isOpen() {
    return !WindowShouldClose();
}

void gmb::Screen::setGameName(const std::string& name) {
    SetWindowTitle(std::format("Gameboy: {}", name).c_str());
}

void gmb::Screen::drawGame() {
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Text", 0, 0, 20, RAYWHITE);

    EndDrawing();
}
