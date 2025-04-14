#pragma once

#include <format>

namespace game
{
class MouseEvent
{
public:
    MouseEvent(float delta_x, float delta_y);

    float delta_x() const;

    float delta_y() const;

private:
    float delta_x_;
    float delta_y_;
};
}

template<>
struct std::formatter<game::MouseEvent>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::MouseEvent &obj, std::format_context &ctx) const
    {
       return std::format_to(ctx.out(), "MouseEvent {} {}", obj.delta_x(), obj.delta_y());
    }
};

