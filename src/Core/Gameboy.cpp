#include "./Gameboy.hpp"

gmb::Gameboy::Gameboy() : cpu_(mmu_), screen_(mmu_) {
}

gmb::Gameboy::~Gameboy() {
}

void gmb::Gameboy::run(const std::string& filename) {
    mmu_.loadGame(filename);
    game_name_ = mmu_.getGameName();
    screen_.setGameName(game_name_);
    while (up_ && screen_.isOpen()) {
        cpu_.step();
        screen_.tryRefresh();
    }
    return;
}
