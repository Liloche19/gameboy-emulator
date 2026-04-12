#include "./MMU.hpp"
#include "Data/MemTypes.hpp"
#include "Data/MemByte.hpp"
#include "Exceptions/Implementations/OutOfRange.hpp"
#include "Exceptions/Implementations/OpenFile.hpp"
#include "Exceptions/Implementations/ReadFile.hpp"
#include <fstream>
#include <ios>
#include <span>

gmb::MMU::MMU() {
}

gmb::MMU::~MMU() {
}

gmb::MemByte gmb::MMU::operator[](Address address) {
    if (address >= memory_.size())
        throw OutOfRangeException(std::format("Address {:#04X} is out of range!", address));
    return MemByte{TByte<RAMType>{memory_[address]}};
}

void gmb::MMU::loadGame(const std::string& filename) {
    auto file = std::ifstream(filename, std::ios::binary | std::ios::ate);
    if (!file)
        throw OpenFileException(std::format("Error opening {} file!", filename));
    std::streamsize size = file.tellg();
    if (static_cast<std::size_t>(size) >= MEMORY_SIZE)
        throw ReadFileException(std::format("Can't read {} file, it's size is too large!", filename));
    file.seekg(0, std::ios::beg);
    std::uint8_t* mem = &memory_[0];
    if (!file.read(reinterpret_cast<char*>(mem), size))
        throw ReadFileException(std::format("Error reading {} file!", filename));
}

std::string gmb::MMU::getGameName() {
    auto gamename_zone = std::span(memory_).subspan(GAMENAME_START_ADDRESS, GAMENAME_END_ADDRESS - GAMENAME_START_ADDRESS + 1);
    return std::string(reinterpret_cast<const char*>(gamename_zone.data()), gamename_zone.size());
}
