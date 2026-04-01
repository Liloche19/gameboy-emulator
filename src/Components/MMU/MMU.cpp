#include "./MMU.hpp"
#include "Exceptions/Implementations/OutOfRange.hpp"

gmb::MMU::MMU() {
}

gmb::MMU::~MMU() {
}

std::uint8_t& gmb::MMU::operator[](std::uint16_t address) {
    if (address > memory_.size())
        throw OutOfRangeException(std::format("Address {:#04X} is out of range!", address));
    return memory_[address];
}
