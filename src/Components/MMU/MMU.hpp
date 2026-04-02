#pragma once

#include "Data/TByte.hpp"
#include <array>
#include <cstdint>
#include <string>

namespace gmb
{
    constexpr std::size_t MEMORY_SIZE = UINT16_MAX + 1;

    class MMU final {
        public:
            explicit MMU();
            ~MMU();

            MemByte operator[](std::uint16_t address);

            void loadGame(const std::string& filename);

        private:
            std::array<std::uint8_t, MEMORY_SIZE> memory_{0};
    };
}
