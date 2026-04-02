#include "./MMU.hpp"
#include "Data/MemTypes.hpp"
#include "Data/TByte.hpp"
#include "Exceptions/Implementations/OutOfRange.hpp"
#include "Exceptions/Implementations/OpenFile.hpp"
#include "Exceptions/Implementations/ReadFile.hpp"
#include <fstream>
#include <ios>

gmb::MMU::MMU() {
}

gmb::MMU::~MMU() {
}

gmb::MemByte gmb::MMU::operator[](std::uint16_t address) {
    if (address > memory_.size())
        throw OutOfRangeException(std::format("Address {:#04X} is out of range!", address));
    return MemByte{TByte<RAMType>{memory_[address]}};
}

void gmb::MMU::loadGame(const std::string& filename) {
    auto file = std::ifstream(filename, std::ios::binary | std::ios::ate);
    if (!file)
        throw OpenFileException(std::format("Error opening {} file!", filename));
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::uint8_t* mem = &memory_[0];
    if (!file.read((char*)mem, size))
        throw ReadFileException(std::format("Error reading {} file!", filename));
}
