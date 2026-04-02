#include "./CPU.hpp"
#include "Instructions/Instructions.hpp"
#include <cstdint>

void gmb::CPU::noop(std::uint8_t opcode) {
    (void) opcode;
}


void gmb::CPU::ld_r16_imm16(std::uint8_t opcode) {
    std::uint16_t val = (mmu_[registers_.PC + 1] << 8) | mmu_[registers_.PC + 2];
    std::uint8_t reg = (opcode ^ LD_R16_IMM16.mask_op) >> 4;
    getRegisterR16(reg) = val;
}

void gmb::CPU::jp_imm16(std::uint8_t opcode) {
    (void) opcode;
    std::uint16_t address = (mmu_[registers_.PC + 1] << 8) | mmu_[registers_.PC + 2];
    registers_.PC = address - JP_IMM16.size;
}


void gmb::CPU::inc_r8(std::uint8_t opcode) {
    std::uint8_t register_code = (opcode ^ INC_R8.mask_op) >> 3;
    if (register_code == 0b110)
        cycles_ += ADDRESS_ACCESS_CYCLE;
    getRegisterR8(register_code)++;
    setFlagN(false);
}

void gmb::CPU::ld_r8_r8(std::uint8_t opcode) {
    std::uint8_t r_src = (opcode ^ LD_R8_R8.mask_op) & 0b00000111;
    std::uint8_t r_dest = ((opcode ^ LD_R8_R8.mask_op) & 0b00111000) >> 3;
    getRegisterR8(r_dest) = getRegisterR8(r_src);
}
