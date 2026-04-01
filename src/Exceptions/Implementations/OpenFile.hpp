#pragma once

#include "Exceptions/Implementations/AException.hpp"
#include <format>

namespace gmb
{
    class OpenFileException final : public AException {
        public:
            explicit OpenFileException(const std::string& message) : AException(std::format("Open file exception: {}", message)) {}
            ~OpenFileException() = default;
    };
}
