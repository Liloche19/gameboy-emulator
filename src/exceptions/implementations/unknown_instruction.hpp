#pragma once

#include "./a_exception.hpp"

namespace gmb
{
    class UnknownInstructionException : public AException {
        public:
            UnknownInstructionException(const std::string& message) : AException("Unknown instruction exception: " + message){}
            ~UnknownInstructionException();
    };
}
