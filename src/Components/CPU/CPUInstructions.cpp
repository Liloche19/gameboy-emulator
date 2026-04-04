#include "./CPU.hpp"
#include "Components/MMU/MMU.hpp"
#include "Data/MemByte.hpp"
#include "Instructions/Instructions.hpp"
#include <cstdint>

void gmb::CPU::noop(std::uint8_t opcode) {
    (void) opcode;
}

void gmb::CPU::cpl(std::uint8_t opcode) {
    (void) opcode;
    registers_.A = ~registers_.A;
    setFlagN(true);
    setFlagH(true);
}

void gmb::CPU::di(std::uint8_t opcode) {
    (void) opcode;
    ime_ = IMEStatus::FALSE;
}

void gmb::CPU::ei(std::uint8_t opcode) {
    (void) opcode;
    ime_ = IMEStatus::WAIT;
}


void gmb::CPU::jp_imm16(std::uint8_t opcode) {
    (void) opcode;
    registers_.PC = getImm16();
    cycles_ += 4;
}

void gmb::CPU::jr_imm8(std::uint8_t opcode) {
    (void) opcode;
    std::uint8_t offset = getImm8();
    registers_.PC += static_cast<std::int8_t>(offset);
    cycles_ += 4;
}

void gmb::CPU::jr_cond_imm8(std::uint8_t opcode) {
    std::int8_t offset = getImm8();
    if (!isConditionTrue((opcode ^ JR_COND_IMM8.mask_op) >> 3))
        return;
    registers_.PC += offset;
    cycles_ += 4;
}


void gmb::CPU::ld_r16mem_a(std::uint8_t opcode) {
    getR16memRegister((opcode ^ LD_R16MEM_A.mask_op) >> 4) = registers_.A;
}


void gmb::CPU::ld_r16_imm16(std::uint8_t opcode) {
    std::uint16_t val = getImm16();
    getRegisterR16((opcode ^ LD_R16_IMM16.mask_op) >> 4) = val;
}

void gmb::CPU::inc_r16(std::uint8_t opcode) {
    std::uint16_t& val = getRegisterR16((opcode ^ INC_R16.mask_op) >> 4);
    val++;
    cycles_ += 4;
}


void gmb::CPU::ld_r8_r8(std::uint8_t opcode) {
    if (opcode == 0x76)
        return;
    std::uint8_t r_src = (opcode ^ LD_R8_R8.mask_op) & 0b00000111;
    std::uint8_t r_dest = ((opcode ^ LD_R8_R8.mask_op) & 0b00111000) >> 3;
    getRegisterR8(r_dest) = getRegisterR8(r_src);
}

void gmb::CPU::ld_r8_imm8(std::uint8_t opcode) {
    getRegisterR8(((opcode ^ LD_R8_IMM8.mask_op) & 0b00111000) >> 3) = getImm8();
}

void gmb::CPU::sub_a_r8(std::uint8_t opcode) {
    MemByte val = getRegisterR8((opcode ^ SUB_A_R8.mask_op) & 0b00000111);
    setFlagN(true);
    setFlagC(registers_.A < val);
    setFlagH((registers_.A & 0x0F) < (val & static_cast<std::uint8_t>(0x0F)));
    registers_.A -= val;
    setFlagZ(registers_.A == 0);
}

void gmb::CPU::sbc_a_r8(std::uint8_t opcode) {
    MemByte val = getRegisterR8((opcode ^ SBC_A_R8.mask_op) & 0b00000111);
    std::uint8_t carry = getFlagC() ? 1 : 0;
    setFlagN(true);
    setFlagH((registers_.A & 0x0F) < (static_cast<std::uint16_t>(val & static_cast<std::uint8_t>(0x0F)) + carry));
    setFlagC(registers_.A < (static_cast<std::uint16_t>(val) + carry));
    registers_.A -= val + carry;
    setFlagZ(registers_.A == 0);
}

void gmb::CPU::inc_r8(std::uint8_t opcode) {
    std::uint8_t register_code = (opcode ^ INC_R8.mask_op) >> 3;
    MemByte val = getRegisterR8(register_code);
    setFlagH(((val & static_cast<std::uint8_t>(0x0F)) + 1) > 0x0F);
    val++;
    if (register_code == 0b110)
        cycles_ += ADDRESS_ACCESS_CYCLE;
    setFlagN(false);
    setFlagZ(val == 0);
}

void gmb::CPU::dec_r8(std::uint8_t opcode) {
    std::uint8_t register_code = (opcode ^ DEC_R8.mask_op) >> 3;
    MemByte val = getRegisterR8(register_code);
    setFlagH((static_cast<std::int16_t>((val & static_cast<std::uint8_t>(0x0F))) - 1) < 0);
    val--;
    if (register_code == 0b110)
        cycles_ += ADDRESS_ACCESS_CYCLE;
    setFlagN(true);
    setFlagZ(val == 0);
}

void gmb::CPU::call_imm16(std::uint8_t opcode) {
    (void) opcode;
    Address address = getImm16();
    registers_.SP--;
    mmu_[registers_.SP] = static_cast<std::uint8_t>(registers_.PC >> 8);
    cycles_ += ADDRESS_ACCESS_CYCLE;
    registers_.SP--;
    mmu_[registers_.SP] = static_cast<std::uint8_t>(registers_.PC & 0xFF);
    cycles_ += ADDRESS_ACCESS_CYCLE;
    registers_.PC = address;
    cycles_ += ADDRESS_ACCESS_CYCLE;
}

void gmb::CPU::xor_a_r8(std::uint8_t opcode) {
    MemByte byte = getRegisterR8(opcode ^ XOR_A_R8.mask_op);
    registers_.A ^= byte;
    setFlagC(false);
    setFlagH(false);
    setFlagN(false);
    setFlagZ(registers_.A == 0);
}

void gmb::CPU::ldh_imm8_a(std::uint8_t opcode) {
    (void) opcode;
    Address address = 0xFF00 | getImm8();
    mmu_[address] = registers_.A;
    cycles_ += ADDRESS_ACCESS_CYCLE;
}

void gmb::CPU::ldh_a_imm8(std::uint8_t opcode) {
    (void) opcode;
    Address address = 0xFF00 | getImm8();
    registers_.A = mmu_[address];
    cycles_ += ADDRESS_ACCESS_CYCLE;
}
