#pragma once

#include "Components/MMU/MMU.hpp"
#include "Components/CPU/CPU.hpp"
#include "Components/Screen/Screen.hpp"
#include <string>

namespace gmb
{
    class Gameboy final {
        public:
            explicit Gameboy();
            ~Gameboy();

            void run(const std::string& filename);

        private:
            MMU mmu_;
            CPU cpu_;
            Screen screen_;
            std::string game_name_{""};
            bool up_{true};
    };
}
