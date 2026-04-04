#include "./CPU.hpp"
#include "Components/MMU/MMU.hpp"
#include "Data/MemTypes.hpp"
#include "Data/TByte.hpp"
#include "Exceptions/Implementations/InvalidRegister.hpp"
#include "Exceptions/Implementations/UnknownInstruction.hpp"
#include "Exceptions/Implementations/InvalidCondition.hpp"
#include "Instructions/Instructions.hpp"
#include <algorithm>
#include <cstdint>
#include <print>

gmb::CPU::CPU(gmb::MMU& mmu) : mmu_(mmu) {
    instructions_.push_back({NOOP, [this](std::uint8_t opcode) {noop(opcode);}});
    instructions_.push_back({JP_IMM16, [this](std::uint8_t opcode) {jp_imm16(opcode);}});
    instructions_.push_back({INC_R8, [this](std::uint8_t opcode) {inc_r8(opcode);}});
    instructions_.push_back({DEC_R8, [this](std::uint8_t opcode) {dec_r8(opcode);}});
    instructions_.push_back({LD_R8_R8, [this](std::uint8_t opcode) {ld_r8_r8(opcode);}});
    instructions_.push_back({LD_R16_IMM16, [this](std::uint8_t opcode) {ld_r16_imm16(opcode);}});
    instructions_.push_back({SUB_A_R8, [this](std::uint8_t opcode) {sub_a_r8(opcode);}});
    instructions_.push_back({SBC_A_R8, [this](std::uint8_t opcode) {sbc_a_r8(opcode);}});
    instructions_.push_back({LD_R8_IMM8, [this](std::uint8_t opcode) {ld_r8_imm8(opcode);}});
    instructions_.push_back({JR_IMM8, [this](std::uint8_t opcode) {jr_imm8(opcode);}});
    instructions_.push_back({CPL, [this](std::uint8_t opcode) {cpl(opcode);}});
    instructions_.push_back({JR_COND_IMM8, [this](std::uint8_t opcode) {jr_cond_imm8(opcode);}});
    instructions_.push_back({LD_R16MEM_A, [this](std::uint8_t opcode) {ld_r16mem_a(opcode);}});
    instructions_.push_back({INC_R16, [this](std::uint8_t opcode) {inc_r16(opcode);}});
    instructions_.push_back({CALL_IMM16, [this](std::uint8_t opcode) {call_imm16(opcode);}});
    instructions_.push_back({XOR_A_R8, [this](std::uint8_t opcode) {xor_a_r8(opcode);}});
    instructions_.push_back({DI, [this](std::uint8_t opcode) {di(opcode);}});
    instructions_.push_back({EI, [this](std::uint8_t opcode) {ei(opcode);}});
}

gmb::CPU::~CPU() {
}

void gmb::CPU::step() {
    std::uint8_t opcode = mmu_[registers_.PC];
    if constexpr (debug_mode_enabled) {
        std::println("Executing {:#02X} at {:#04X}...", opcode, registers_.PC);
    }
    execute(opcode);
    return;
}

void gmb::CPU::executeCB(std::uint8_t opcode) {
    registers_.PC++;
    cycles_ += ADDRESS_ACCESS_CYCLE;
    auto instruction = std::ranges::find_if(cb_instructions_, [opcode](const auto& p) {
        return (opcode & p.first.mask_arg)  == p.first.mask_op;
    });
    if (instruction == instructions_.end())
        throw UnknownInstructionException(std::format("No cb instruction match the opcode: {:#08b} / {:#02X}", opcode, opcode));
    instruction->second(opcode);
    cb_instruction_ = false;
    return;
}

void gmb::CPU::execute(std::uint8_t opcode) {
    if (cb_instruction_)
        return executeCB(opcode);

    registers_.PC++;
    cycles_ += ADDRESS_ACCESS_CYCLE;
    auto instruction = std::ranges::find_if(instructions_, [opcode](const auto& p) {
        return (opcode & p.first.mask_arg) == p.first.mask_op;
    });
    if (instruction == instructions_.end())
        throw UnknownInstructionException(std::format("No instruction match the opcode: {:#08b} / {:#02X}", opcode, opcode));
    IMEStatus next_ime = ime_ == IMEStatus::WAIT ? IMEStatus::TRUE : ime_;
    instruction->second(opcode);
    ime_ = next_ime;
    return;
}

gmb::MemByte gmb::CPU::getRegisterR8(std::uint8_t reg) {
    switch (reg) {
        case 0b000: return MemByte{TByte<RegisterType>{registers_.B}};
        case 0b001: return MemByte{TByte<RegisterType>{registers_.C}};
        case 0b010: return MemByte{TByte<RegisterType>{registers_.D}};
        case 0b011: return MemByte{TByte<RegisterType>{registers_.E}};
        case 0b100: return MemByte{TByte<RegisterType>{registers_.H}};
        case 0b101: return MemByte{TByte<RegisterType>{registers_.L}};
        case 0b110: cycles_ += ADDRESS_ACCESS_CYCLE; return mmu_[registers_.HL];
        case 0b111: return MemByte{TByte<RegisterType>{registers_.A}};
        default: throw InvalidRegisterException(std::format("Could not find a 8 bit register for value {:#b}", reg));
    }
}

std::uint16_t& gmb::CPU::getRegisterR16(std::uint8_t reg) {
    switch (reg) {
        case 0b00: return registers_.BC;
        case 0b01: return registers_.DE;
        case 0b10: return registers_.HL;
        case 0b11: return registers_.SP;
        default: throw InvalidRegisterException(std::format("Could not find a 16 bit register for value {:#b}", reg));
    }
}

gmb::MemByte gmb::CPU::getR16memRegister(std::uint8_t reg) {
    std::uint16_t old_reg_value = 0;
    cycles_ += ADDRESS_ACCESS_CYCLE;
    switch (reg) {
        case 0b00: return mmu_[registers_.BC];
        case 0b01: return mmu_[registers_.DE];
        case 0b10: old_reg_value = registers_.HL++; return mmu_[old_reg_value];
        case 0b11: old_reg_value = registers_.HL--; return mmu_[old_reg_value];
        default: throw InvalidRegisterException(std::format("Could not find a r16mem register for value {}", reg));
    }
}

std::uint8_t gmb::CPU::getImm8() {
    std::uint8_t byte = mmu_[registers_.PC++];
    cycles_ += ADDRESS_ACCESS_CYCLE;
    return byte;
}

std::uint16_t gmb::CPU::getImm16() {
    std::uint16_t data = getImm8();
    data |= getImm8() << 8;
    return data;
}

void gmb::CPU::setFlagZ(bool val) {
    if (val)
        registers_.F |= 0b10000000;
    else
        registers_.F &= 0b01111111;
}

void gmb::CPU::setFlagN(bool val) {
    if (val)
        registers_.F |= 0b01000000;
    else
        registers_.F &= 0b10111111;
}

void gmb::CPU::setFlagH(bool val) {
    if (val)
        registers_.F |= 0b00100000;
    else
        registers_.F &= 0b11011111;
}

void gmb::CPU::setFlagC(bool val) {
    if (val)
        registers_.F |= 0b00010000;
    else
        registers_.F &= 0b11101111;
}

bool gmb::CPU::getFlagZ() {
    return static_cast<bool>(registers_.F & 0b10000000);
}

bool gmb::CPU::getFlagN() {
    return static_cast<bool>(registers_.F & 0b01000000);
}

bool gmb::CPU::getFlagH() {
    return static_cast<bool>(registers_.F & 0b00100000);
}

bool gmb::CPU::getFlagC() {
    return static_cast<bool>(registers_.F & 0b00010000);
}

bool gmb::CPU::isConditionTrue(std::uint8_t condition) {
    switch (condition) {
        case 0b00: return !getFlagZ();
        case 0b01: return getFlagZ();
        case 0b10: return !getFlagC();
        case 0b11: return getFlagC();
        default: throw InvalidConditionException(std::format("Unknown condition {}", condition));
    }
}
