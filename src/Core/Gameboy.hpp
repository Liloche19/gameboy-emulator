#pragma once

#include "Components/MMU/MMU.hpp"
#include "Components/CPU/CPU.hpp"
#include <string>

namespace gmb
{
    class Gameboy final {
        public:
            explicit Gameboy();
            ~Gameboy();

            void run(const std::string& filename);

        private:
            void loadGame(const std::string& filename);

            MMU mmu_;
            CPU cpu_;
            bool up_{true};
    };
}
