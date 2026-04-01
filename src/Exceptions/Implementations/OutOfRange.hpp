#pragma once

#include "Exceptions/Implementations/AException.hpp"
#include <format>

namespace gmb
{
    class OutOfRangeException final : public AException {
        public:
            explicit OutOfRangeException(const std::string& message) : AException(std::format("Out of range exception: {}", message)) {}
            ~OutOfRangeException() = default;
    };
}
