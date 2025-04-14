#include "key_event.h"

#include "key.h"

namespace game
{
KeyEvent::KeyEvent(const Key key, const KeyState state)
    : key_(key)
    , state_(state)
{
}

Key KeyEvent::key() const
{
    return key_;
}

KeyState KeyEvent::state() const
{
    return state_;
}
}
