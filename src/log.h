#pragma once

#include <format>
#include <source_location>
#include <print>
#include <string_view>

namespace game::log
{
enum class Level
{
    DEBUG,
    INFO,
    WARN,
    FATAL, // ERROR is a macro in windows.h, can't use it
};

template<Level L, class... Args>
struct print
{
    print(
        std::format_string<Args...> msg, Args &&... args,
        const std::source_location &loc = std::source_location::current()
    )
    {
        auto c = '?';
        if constexpr (L == Level::DEBUG) {
            c = 'D';
        } else if constexpr (L == Level::INFO) {
            c = 'I';
        } else if constexpr (L == Level::WARN) {
            c = 'W';
        } else if constexpr (L == Level::FATAL) {
            c = 'E';
        }

        std::println(
            "[{}] {}:{} {}", c, loc.file_name(), loc.line(), std::format(msg, std::forward<Args>(args)...)
        );
    }
};

template<Level L, class... Args>
print(std::format_string<Args...>, Args &&...) -> print<L, Args...>;

template<class... Args>
using debug = print<Level::DEBUG, Args...>;

template<class... Args>
using info = print<Level::INFO, Args...>;

template<class... Args>
using warn = print<Level::WARN, Args...>;

template<class... Args>
using fatal = print<Level::FATAL, Args...>;
}
