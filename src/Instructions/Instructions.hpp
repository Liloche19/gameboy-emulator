#pragma once

#include <cstdint>
#include <string_view>

namespace gmb
{
    struct Instruction {
        std::string_view name;
        std::uint8_t mask_op;
        std::uint8_t mask_arg;
    };

    constexpr std::size_t ADDRESS_ACCESS_CYCLE = 4;

    // misc instructions
    constexpr Instruction NOOP = {"NOOP", 0b00000000, 0b11111111};
    constexpr Instruction CB = {"CB", 0b11001011, 0b11111111};
    constexpr Instruction CPL = {"CPL", 0b00101111, 0b11111111};
    constexpr Instruction DI = {"DI", 0b11110011, 0b11111111};
    constexpr Instruction EI = {"EI", 0b11111011, 0b11111111};

    // call instructions
    constexpr Instruction CALL_IMM16 = {"CALL IMM16", 0b11001101, 0b11111111};

    // jump instructions
    constexpr Instruction JP_IMM16 = {"JP IMM16", 0b11000011, 0b11111111};
    constexpr Instruction JR_IMM8 = {"JR IMM8", 0b00011000, 0b11111111};
    constexpr Instruction JR_COND_IMM8 = {"JR COND IMM8", 0b00100000, 0b11100111};

    // r16 instructions
    // ld instructions
    constexpr Instruction LD_R16_IMM16 = {"LD R16 IMM16", 0b00000001, 0b11001111};
    constexpr Instruction LD_R16MEM_A = {"LD R16MEM A", 0b00000010, 0b11001111};
    constexpr Instruction LD_A_R16MEM = {"LD A R16MEM", 0b00001010, 0b11001111};
    constexpr Instruction LD_IMM16_SP = {"LD IMM16 SP", 0b00001000, 0b11111111};
    // inc/dec instructions
    constexpr Instruction INC_R16 = {"INC R16", 0b00000011, 0b11001111};
    constexpr Instruction DEC_R16 = {"DEC R16", 0b00001011, 0b11001111};
    // HL operations
    constexpr Instruction ADD_HL_R16 = {"ADD HL R16", 0b00001001, 0b11001111};

    // r8 instructions
    // ld instructions
    constexpr Instruction LD_R8_IMM8 = {"LD R8 IMM8", 0b00000110, 0b11000111};
    constexpr Instruction LD_R8_R8 = {"LD R8 R8", 0b01000000, 0b11000000};
    // arithmetic instructions
    constexpr Instruction SUB_A_R8 = {"SUB A R8", 0b10010000, 0b11111000};
    constexpr Instruction SBC_A_R8 = {"SBC A R8", 0b10011000, 0b11111000};
    // inc/dec instructions
    constexpr Instruction INC_R8 = {"INC R8", 0b00000100, 0b11000111};
    constexpr Instruction DEC_R8 = {"DEC R8", 0b00000101, 0b11000111};

    // binary operations
    constexpr Instruction XOR_A_R8 = {"XOR A R8", 0b10101000, 0b11111000};
}
