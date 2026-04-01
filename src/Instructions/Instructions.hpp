#pragma once

#include <cstdint>
#include <string_view>

namespace gmb
{
    struct Instruction {
        std::string_view name;
        std::size_t cycle;
        std::uint16_t size;
        std::uint8_t mask_op;
        std::uint8_t mask_arg;
    };

    // misc instructions
    constexpr Instruction NOOP = {"NOOP", 4, 1, 0b00000000, 0b11111111};
    constexpr Instruction CB = {"CB", 4, 1, 0b11001011, 0b11111111};

    // jump instructions
    constexpr Instruction JP_IMM16 = {"JP IMM16", 16, 3, 0b11000011, 0b11111111};

    // r16 instructions
    // ld instructions
    constexpr Instruction LD_R16_IMM16 = {"LD R16 IMM16", 12, 3, 0b00000001, 0b11001111};
    constexpr Instruction LD_R16MEM_A = {"LD R16MEM A", 8, 1, 0b00000010, 0b11001111};
    constexpr Instruction LD_A_R16MEM = {"LD A R16MEM", 8, 1, 0b00001010, 0b11001111};
    constexpr Instruction LD_IMM16_SP = {"LD IMM16 SP", 20, 3, 0b00001000, 0b11111111};
    // inc/dec instructions
    constexpr Instruction INC_R16 = {"INC R16", 8, 1, 0b00000011, 0b11001111};
    constexpr Instruction DEC_R16 = {"DEC R16", 8, 1, 0b00001011, 0b11001111};
    // HL operations
    constexpr Instruction ADD_HL_R16 = {"ADD HL R16", 8, 1, 0b00001001, 0b11001111};

    // r8 instructions
    // ld instructions
    constexpr Instruction LD_R8_IMM8 = {"LD R8 IMM8", 8, 1, 0b00000110, 0b11000111};
    constexpr Instruction LD_R8_R8 = {"LD R8 R8", 4, 1, 0b01000000, 0b11000000};
    // inc/dec instructions
    constexpr Instruction INC_R8 = {"INC R8", 4, 1, 0b00000100, 0b11000111};
    constexpr Instruction DEC_R8 = {"DEC R8", 4, 1, 0b00000101, 0b11000111};
}
