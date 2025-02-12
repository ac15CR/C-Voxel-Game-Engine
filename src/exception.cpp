#include "exception.h"

namespace game
{
Exception::Exception(const std::string &what)
        : std::runtime_error{what},
          trace_(std::stacktrace::current())
{
}

std::string Exception::stackTrace() const
{
    return std::to_string(trace_);
}

}