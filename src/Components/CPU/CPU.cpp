#include "./CPU.hpp"
#include "Components/MMU/MMU.hpp"
#include "Exceptions/Implementations/UnknownInstruction.hpp"
#include "Instructions/Instructions.hpp"
#include <algorithm>
#include <cstdint>

gmb::CPU::CPU(gmb::MMU& mmu) : mmu_(mmu) {
    instructions_.push_back({NOOP, [this](std::uint8_t opcode) {noop(opcode);}});
    instructions_.push_back({LD_R16_IMM16, [this](std::uint8_t opcode) {ld_r16_imm16(opcode);}});
    instructions_.push_back({LD_R16MEM_A, [this](std::uint8_t opcode) {ld_r16mem_a(opcode);}});
    instructions_.push_back({LD_A_R16MEM, [this](std::uint8_t opcode) {ld_a_r16mem(opcode);}});
}

gmb::CPU::~CPU() {
}

void gmb::CPU::executeCB(std::uint8_t opcode) {
    auto instruction = std::ranges::find_if(cb_instructions_, [opcode](const auto& p) {
        return ((opcode & p.first.mask_arg) & p.first.mask_op) == p.first.mask_op;
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
        return ((opcode & p.first.mask_arg) & p.first.mask_op) == p.first.mask_op;
    });
    if (instruction == instructions_.end())
        throw UnknownInstructionException(std::format("No instruction match the opcode: {:#08b} / {:#02X}", opcode, opcode));
    instruction->second(opcode);
    registers_.PC += instruction->first.size;
    cycles_ += instruction->first.cycle;
    return;
}

void gmb::CPU::step() {
    std::uint8_t opcode = mmu_[registers_.PC];
    execute(opcode);
    return;
}
