#pragma once

#include <format>
#include <string_view>
#include <utility>

#include "auto_release.h"
#include "exception.h"

namespace game
{

template<class ...Args>
void ensure(bool predicate, std::string_view msg, Args &&...args)
{
    if (!predicate) {
        throw Exception(std::vformat(msg, std::make_format_args(std::forward<Args>(args)...)), 2u);
    }
}

template<class T, auto Invalid, class ...Args>
void ensure(AutoRelease<T, Invalid> &obj, std::string_view msg, Args &&...args)
{
    ensure(!!obj, msg, std::forward<Args>(args)...); // REQUIRED DO NOT REMOVE THE !!
}

}