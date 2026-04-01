#include "./CPU.hpp"
#include "Components/MMU/MMU.hpp"
#include "Exceptions/Implementations/InvalidRegister.hpp"
#include "Exceptions/Implementations/UnknownInstruction.hpp"
#include "Instructions/Instructions.hpp"
#include <algorithm>
#include <cstdint>

gmb::CPU::CPU(gmb::MMU& mmu) : mmu_(mmu) {
    instructions_.push_back({NOOP, [this](std::uint8_t opcode) {noop(opcode);}});
    instructions_.push_back({JP_IMM16, [this](std::uint8_t opcode) {jp_imm16(opcode);}});
    instructions_.push_back({INC_R8, [this](std::uint8_t opcode) {inc_r8(opcode);}});
}

gmb::CPU::~CPU() {
}

void gmb::CPU::step() {
    std::uint8_t opcode = mmu_[registers_.PC];
    execute(opcode);
    return;
}

void gmb::CPU::executeCB(std::uint8_t opcode) {
    auto instruction = std::ranges::find_if(cb_instructions_, [opcode](const auto& p) {
        return (opcode & p.first.mask_arg)  == p.first.mask_op;
    });
    if (instruction == instructions_.end())
        throw UnknownInstructionException(std::format("No cb instruction match the opcode: {:#08b} / {:#02X}", opcode, opcode));
    instruction->second(opcode);
    registers_.PC += instruction->first.size;
    cycles_ += instruction->first.cycle;
    cb_instruction_ = false;
    return;
}

void gmb::CPU::execute(std::uint8_t opcode) {
    if (cb_instruction_)
        return executeCB(opcode);

    auto instruction = std::ranges::find_if(instructions_, [opcode](const auto& p) {
        return (opcode & p.first.mask_arg) == p.first.mask_op;
    });
    if (instruction == instructions_.end())
        throw UnknownInstructionException(std::format("No instruction match the opcode: {:#08b} / {:#02X}", opcode, opcode));
    instruction->second(opcode);
    registers_.PC += instruction->first.size;
    cycles_ += instruction->first.cycle;
    return;
}

std::uint8_t& gmb::CPU::getRegisterR8(std::uint8_t reg) {
    switch (reg) {
        case 0b000: return registers_.B;
        case 0b001: return registers_.C;
        case 0b010: return registers_.D;
        case 0b011: return registers_.E;
        case 0b100: return registers_.H;
        case 0b101: return registers_.L;
        case 0b110: cycles_ += (12 - INC_R8.cycle); return mmu_[registers_.HL];
        case 0b111: return registers_.A;
        default: throw InvalidRegisterException(std::format("Could not find a 8 bit register for value {:#b}", reg));
    }
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
