#pragma once

#include <array>
#include <cstdint>

namespace gmb
{
    constexpr std::size_t MEMORY_SIZE = UINT16_MAX + 1;

    class MMU final {
        public:
            explicit MMU();
            ~MMU();

            std::uint8_t& operator[](std::uint16_t address);
            const std::uint8_t& operator[](std::uint16_t address) const;

        private:
            std::array<std::uint8_t, MEMORY_SIZE> memory_{0};
    };
}
