#pragma once

#include "Exceptions/IException.hpp"
#include <string>

namespace gmb
{
    class AException : public IException {
        public:
            ~AException() = default;

            const char* what() const noexcept override final {
                return message_.c_str();
            }

        protected:
            explicit AException(const std::string& message) : message_(message) {}

        private:
            std::string message_;
    };
}
