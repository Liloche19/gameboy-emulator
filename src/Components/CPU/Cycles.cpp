#include "./Cycles.hpp"

gmb::MCycle::MCycle(CycleType cycles) : cycles_(cycles) {
}

gmb::MCycle::~MCycle() {
}

gmb::CycleType gmb::MCycle::operator++(int) {
    CycleType cycles = cycles_;
    cycles_++;
    return cycles;
}
