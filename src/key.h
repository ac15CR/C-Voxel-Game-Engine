#pragma once

#include <string_view>
#include <format>

using namespace std::string_view_literals;

namespace game
{
enum class Key
{
    ESC = 0x1B,
    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4A,
    K = 0x4B,
    L = 0x4C,
    M = 0x4D,
    N = 0x4E,
    O = 0x4F,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5A,
};

enum class KeyState
{
    UP,
    DOWN,
};
}

template<>
struct std::formatter<game::Key>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::Key &obj, std::format_context &ctx) const
    {
        auto s = "?"sv;

        switch (obj) {
            using enum game::Key;

            case ESC: s = "ESC"sv; break;
            case A: s = "A"sv; break;
            case B: s = "B"sv; break;
            case C: s = "C"sv; break;
            case D: s = "D"sv; break;
            case E: s = "E"sv; break;
            case F: s = "F"sv; break;
            case G: s = "G"sv; break;
            case H: s = "H"sv; break;
            case I: s = "I"sv; break;
            case J: s = "J"sv; break;
            case K: s = "K"sv; break;
            case L: s = "L"sv; break;
            case M: s = "M"sv; break;
            case N: s = "N"sv; break;
            case O: s = "O"sv; break;
            case P: s = "P"sv; break;
            case Q: s = "Q"sv; break;
            case R: s = "R"sv; break;
            case S: s = "S"sv; break;
            case T: s = "T"sv; break;
            case U: s = "U"sv; break;
            case V: s = "V"sv; break;
            case W: s = "W"sv; break;
            case X: s = "X"sv; break;
            case Y: s = "Y"sv; break;
            case Z: s = "Z"sv; break;
            default: s = "?"sv; break;
        }

        return std::format_to(ctx.out(), "{}", s);
    }
};

template<>
struct std::formatter<game::KeyState>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::KeyState &obj, std::format_context &ctx) const
    {
        switch (obj) {
            using enum game::KeyState;
            case DOWN: return std::format_to(ctx.out(), "DOWN");
            case UP: return std::format_to(ctx.out(), "UP");
            default: return std::format_to(ctx.out(), "UNKNOWN");
        }
    }
};
