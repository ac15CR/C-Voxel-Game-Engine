#pragma once

#include <cstdint>
#include <stacktrace>
#include <stdexcept>
#include <string>

namespace game
{
class Exception : public std::runtime_error
{
public:
    Exception(const std::string &what, std::uint32_t skip = 1u);

    std::string stackTrace() const;

private:
    std::stacktrace trace_;
};
}

template<>
struct std::formatter<game::Exception>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::Exception &obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}\n{}", obj.what(), obj.stackTrace());
    }
};