#include "./Gameboy.hpp"
#include <print>

gmb::Gameboy::Gameboy() : cpu_(mmu_) {
}

gmb::Gameboy::~Gameboy() {
}

void gmb::Gameboy::run(const std::string& filename) {
    mmu_.loadGame(filename);
    game_name_ = mmu_.getGameName();
    std::println("Starting {}...", game_name_);
    while (up_) {
        cpu_.step();
    }
    return;
}
