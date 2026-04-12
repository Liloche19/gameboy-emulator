#pragma once

#include "Exceptions/Implementations/AException.hpp"
#include <format>

namespace gmb
{
    class InvalidConditionException final : public AException {
        public:
            explicit InvalidConditionException(const std::string& message) : AException(std::format("Invalid condition exception: {}", message)) {}
            ~InvalidConditionException() = default;
    };
}
