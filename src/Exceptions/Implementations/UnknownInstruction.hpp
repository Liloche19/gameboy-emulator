#pragma once

#include "Exceptions/Implementations/AException.hpp"
#include <format>

namespace gmb
{
    class UnknownInstructionException final : public AException {
        public:
            explicit UnknownInstructionException(const std::string& message) : AException(std::format("Unknown instruction exception: {}", message)){}
            ~UnknownInstructionException() = default;
    };
}
