#pragma once

#include <cstdint>

namespace gmb
{
    using CycleType = std::uint64_t;

    class MCycle final {
        public:
            explicit MCycle(CycleType cycles = 0);
            ~MCycle();

            CycleType operator++(int);

        private:
            CycleType cycles_;
    };
}
