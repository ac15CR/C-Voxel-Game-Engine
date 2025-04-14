#pragma once

#include <format>

#include "key.h"

namespace game
{
class KeyEvent
{
public:
    KeyEvent(Key key, KeyState state);

    Key key() const;
    KeyState state() const;

private:
    Key key_;
    KeyState state_;
};
}

template<>
struct std::formatter<game::KeyEvent>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::KeyEvent &obj, std::format_context &ctx) const
    {
       return std::format_to(ctx.out(), "KeyEvent {} {}", obj.key(), obj.state());
    }
};
