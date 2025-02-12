#pragma once

#include <stacktrace>
#include <stdexcept>
#include <string>

namespace game
{
class Exception : public std::runtime_error
{
public:
    Exception(const std::string &what);

    std::string stackTrace() const;

private:
    std::stacktrace trace_;
};
}