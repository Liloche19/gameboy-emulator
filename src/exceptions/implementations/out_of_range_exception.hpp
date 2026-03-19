#include "exceptions/implementations/a_exception.hpp"

namespace gmb
{
    class OutOfRangeException final : public AException {
        public:
            OutOfRangeException(std::string message) : AException("Out of range exception: " + message) {};
            ~OutOfRangeException();
    };
}
