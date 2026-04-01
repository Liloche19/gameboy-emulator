#include "Core/Gameboy.hpp"
#include "Exceptions/IException.hpp"
#include <iostream>
#include <print>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::println("Bad usage! use -h to get the help.");
        return 1;
    }
    try {
        gmb::Gameboy gameboy;
        gameboy.run(std::string(argv[1]));
    } catch (gmb::IException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
