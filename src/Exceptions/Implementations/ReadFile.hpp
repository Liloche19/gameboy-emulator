#pragma once

#include "Exceptions/Implementations/AException.hpp"
#include <format>

namespace gmb
{
    class ReadFileException final : public AException {
        public:
            explicit ReadFileException(const std::string& message) : AException(std::format("Read file exception: {}", message)) {}
            ~ReadFileException() = default;
    };
}
