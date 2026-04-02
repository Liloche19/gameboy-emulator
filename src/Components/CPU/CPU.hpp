#pragma once

#include "Components/MMU/MMU.hpp"
#include "Instructions/Instructions.hpp"
#include <cstdint>
#include <functional>
#include <vector>

namespace gmb
{
    struct Registers {
        struct {
            union {
                struct {std::uint8_t F; std::uint8_t A;};
                std::uint16_t AF;
            };
        };
        struct {
            union {
                struct {std::uint8_t C; std::uint8_t B;};
                std::uint16_t BC;
            };
        };
        struct {
            union {
                struct {std::uint8_t E; std::uint8_t D;};
                std::uint16_t DE;
            };
        };
        struct {
            union {
                struct {std::uint8_t L; std::uint8_t H;};
                std::uint16_t HL;
            };
        };
        std::uint16_t SP;
        std::uint16_t PC;
    };

    class CPU final {
        public:
            explicit CPU(MMU& mmu);
            ~CPU();

            void step();

        private:
            void execute(std::uint8_t opcode);
            void executeCB(std::uint8_t opcode);

            void setFlagZ(bool val);
            void setFlagN(bool val);
            void setFlagH(bool val);
            void setFlagC(bool val);

            bool getFlagZ();
            bool getFlagN();
            bool getFlagH();
            bool getFlagC();

            std::uint8_t& getRegisterR8(std::uint8_t opcode);
            std::uint16_t& getRegisterR16(std::uint8_t opcode);

            void noop(std::uint8_t opcode);
            void cpl(std::uint8_t opcode);

            void jp_imm16(std::uint8_t opcode);
            void jr_imm8(std::uint8_t opcode);

            void ld_r16_imm16(std::uint8_t opcode);

            void ld_r8_r8(std::uint8_t opcode);
            void ld_r8_imm8(std::uint8_t opcode);
            void sub_a_r8(std::uint8_t opcode);
            void sbc_a_r8(std::uint8_t opcode);
            void inc_r8(std::uint8_t opcode);
            void dec_r8(std::uint8_t opcode);

            Registers registers_{.AF = 0x01B0, .BC = 0x0013, .DE = 0x00D8, .HL = 0x014D, .SP = 0xFFFE, .PC = 0x0100};
            bool cb_instruction_{false};
            std::size_t cycles_{0};
            MMU& mmu_;
            std::vector<std::pair<Instruction, std::function<void (std::uint8_t opcode)>>> instructions_;
            std::vector<std::pair<Instruction, std::function<void (std::uint8_t opcode)>>> cb_instructions_;
    };
}
