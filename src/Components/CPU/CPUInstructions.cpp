#include "./CPU.hpp"
#include "Instructions/Instructions.hpp"
#include <cstdint>

void gmb::CPU::noop(std::uint8_t opcode) {
    (void) opcode;
}


void gmb::CPU::jp_imm16(std::uint8_t opcode) {
    (void) opcode;
    std::uint16_t address = (mmu_[registers_.PC + 1] << 8) | mmu_[registers_.PC + 2];
    registers_.PC = address - JP_IMM16.size;
}


void gmb::CPU::inc_r8(std::uint8_t opcode) {
    std::uint8_t register_code = (opcode ^ INC_R8.mask_op) >> 3;
    getRegisterR8(register_code)++;
    setFlagN(false);
}
