#pragma once

#include <cstdint>
#include <optional>

#define NOMINMAX

#include <Windows.h>
#include "auto_release.h"
#include "event.h"

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

    std::optional<Event> pump_event() const;

    void swap() const;

private:
    AutoRelease<::HWND, nullptr> window_;
    AutoRelease<::HDC> dc_;
    ::WNDCLASSA wc_;
};
}
