#include "exception.h"

#include <cstdint>

namespace game
{
Exception::Exception(const std::string &what, std::uint32_t skip)
        : std::runtime_error{what},
          trace_(std::stacktrace::current(skip))
{
}

std::string Exception::stackTrace() const
{
    return std::to_string(trace_);
}

}