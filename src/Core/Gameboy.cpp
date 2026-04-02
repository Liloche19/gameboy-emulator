#include "./Gameboy.hpp"

gmb::Gameboy::Gameboy() : cpu_(mmu_) {
}

gmb::Gameboy::~Gameboy() {
}

void gmb::Gameboy::run(const std::string& filename) {
    mmu_.loadGame(filename);
    while (up_) {
        cpu_.step();
    }
    return;
}
