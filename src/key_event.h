#pragma once

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
