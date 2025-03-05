#pragma once

#include <cstdint>

#define NOMINMAX

#include <Windows.h>
#include "auto_release.h"

namespace game
{
class Window
{
public:
    Window(std::uint32_t width, std::uint32_t height);
    ~Window() = default;

    Window(const Window &) = delete;
    auto operator=(const Window &) -> Window & = delete;

    Window(Window &&) noexcept = default;
    auto operator=(Window &&) noexcept -> Window & = default;

    auto running() const -> bool;

private:
    AutoRelease<::HWND, nullptr> window_;
    AutoRelease<::HDC> dc_;
    ::WNDCLASSA wc_;
};
}