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

    struct Flags {
        bool Z;
        bool N;
        bool H;
        bool C;
    };

    class CPU final {
        public:
            explicit CPU(MMU& mmu);
            ~CPU();

            void step();

        private:
            void execute(std::uint8_t opcode);
            void executeCB(std::uint8_t opcode);

            void noop(std::uint8_t opcode);
            void ld_r16_imm16(std::uint8_t opcode);
            void ld_r16mem_a(std::uint8_t opcode);
            void ld_a_r16mem(std::uint8_t opcode);

            Registers registers_{.AF = 0, .BC = 0, .DE = 0, .HL = 0, .SP = 0, .PC = 0};
            Flags flags_{.Z = 0, .N = 0, .H = 0, .C = 0};
            bool cb_instruction_{false};
            std::size_t cycles_{0};
            MMU& mmu_;
            std::vector<std::pair<Instruction, std::function<void (std::uint8_t opcode)>>> instructions_;
            std::vector<std::pair<Instruction, std::function<void (std::uint8_t opcode)>>> cb_instructions_;
    };
}
