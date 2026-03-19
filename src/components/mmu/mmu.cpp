#include "./mmu.hpp"
#include "exceptions/implementations/out_of_range_exception.hpp"

gmb::MMU::MMU() : memory_(MEMORY_SIZE, 0) {
}

gmb::MMU::~MMU() {
}

std::uint8_t& gmb::MMU::operator[](std::uint16_t address) {
    if (address > memory_.size())
        throw OutOfRangeException("Requested address is out of range!");
    return memory_[address];
}
