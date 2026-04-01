#include "./Gameboy.hpp"
#include "Exceptions/Implementations/OpenFile.hpp"
#include "Exceptions/Implementations/ReadFile.hpp"
#include <format>
#include <fstream>
#include <ios>

gmb::Gameboy::Gameboy() : cpu_(mmu_) {
}

gmb::Gameboy::~Gameboy() {
}

void gmb::Gameboy::loadGame(const std::string& filename) {
    auto file = std::ifstream(filename, std::ios::binary | std::ios::ate);
    if (!file)
        throw OpenFileException(std::format("Error opening {} file!", filename));
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::uint8_t* mem = &mmu_[0];
    if (!file.read((char*)mem, size))
        throw ReadFileException(std::format("Error reading {} file!", filename));
}

void gmb::Gameboy::run(const std::string& filename) {
    loadGame(filename);
    while (up_) {
        cpu_.step();
    }
    return;
}
