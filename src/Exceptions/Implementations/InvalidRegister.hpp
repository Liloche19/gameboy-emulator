#pragma once

#include "Exceptions/Implementations/AException.hpp"
#include <format>

namespace gmb
{
    class InvalidRegisterException final : public AException {
        public:
            explicit InvalidRegisterException(const std::string& message) : AException(std::format("Invalid register exception: {}", message)) {}
            ~InvalidRegisterException() = default;
    };
}
