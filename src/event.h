#pragma once

#include <variant>

#include "key_event.h"
#include "stop_event.h"

namespace game
{

using Event = std::variant<StopEvent, KeyEvent>;

}