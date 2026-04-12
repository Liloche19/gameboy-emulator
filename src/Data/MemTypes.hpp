#pragma once

#include <cstdint>

#ifdef _DEV_MODE
    constexpr bool debug_mode_enabled = true;
#else
    constexpr bool debug_mode_enabled = false;
#endif

namespace gmb
{
    struct RAMType {
        static std::uint8_t read(const std::uint8_t& data) {
            return data;
        }

        static void write(std::uint8_t& dest, std::uint8_t src) {
            dest = src;
        }
    };

    struct RegisterType {
        static std::uint8_t read(const std::uint8_t& data) {
            return data;
        }

        static void write(std::uint8_t& dest, std::uint8_t src) {
            dest = src;
        }
    };
}
