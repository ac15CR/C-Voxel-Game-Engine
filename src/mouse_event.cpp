#include "mouse_event.h"

namespace game
{
MouseEvent::MouseEvent(const float delta_x, const float delta_y)
    : delta_x_(delta_x)
    , delta_y_(delta_y)
{
}

float MouseEvent::delta_x() const
{
    return delta_x_;
}

float MouseEvent::delta_y() const
{
    return delta_y_;
}
}