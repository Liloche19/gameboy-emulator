#pragma once

#include <cstdint>
#include <vector>

namespace gmb
{
    constexpr std::size_t MEMORY_SIZE = UINT16_MAX + 1;

    class MMU final {
        public:
            MMU();
            ~MMU();

            std::uint8_t& operator[](std::uint16_t address);

        private:
            std::vector<std::uint8_t> memory_;
    };
}
