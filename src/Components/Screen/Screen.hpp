#pragma once

#include "Components/MMU/MMU.hpp"
#include <array>

namespace gmb
{
    constexpr unsigned int SCREEN_WIDTH = 160;
    constexpr unsigned int SCREEN_HEIGHT = 144;

    constexpr unsigned int TARGET_FPS = 60;

    constexpr double TARGET_FRAME_TIME_ = static_cast<double>(1) / TARGET_FPS;

    struct Pixel {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;
    };

    class Screen final {
        public:
            explicit Screen(MMU& mmu);
            ~Screen();

            void tryRefresh();
            void drawGame();
            bool isOpen();
            void setGameName(const std::string& name);

        private:
            std::array<Pixel, SCREEN_WIDTH * SCREEN_HEIGHT> framebuffer_;
            MMU& mmu_;
            double next_refresh_time_{0};
    };
}
