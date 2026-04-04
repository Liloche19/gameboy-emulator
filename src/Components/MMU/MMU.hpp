#pragma once

#include "Data/MemByte.hpp"
#include <array>
#include <cstdint>
#include <string>

namespace gmb
{
    constexpr std::size_t MEMORY_SIZE = UINT16_MAX + 1;
    using Address = std::uint16_t;

    class MMU final {
        public:
            explicit MMU();
            ~MMU();

            MemByte operator[](Address address);

            void loadGame(const std::string& filename);
            std::string getGameName();

        private:
            std::array<std::uint8_t, MEMORY_SIZE> memory_{0};
    };
}
