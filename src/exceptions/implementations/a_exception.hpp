#include "exceptions/i_exception.hpp"
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
            AException(std::string message);

        private:
            std::string message_;
    };
}
