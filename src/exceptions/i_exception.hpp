#pragma once

#include <exception>

namespace gmb
{
    class IException : public std::exception {
        public:
            ~IException() = default;

            const char* what() const noexcept override = 0;
    };
}
