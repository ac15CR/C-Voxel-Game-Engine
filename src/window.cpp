#include "window.h"

#include <cstdint>
#include <print>
#include <stdexcept>

#define NOMINMAX

#include <Windows.h>

#include "auto_release.h"


namespace
{
auto g_running = true;

auto CALLBACK window_proc(::HWND hWnd, ::UINT Msg, ::WPARAM wParam, ::LPARAM lParam) -> ::LRESULT
{
    switch (Msg) {
        case WM_CLOSE:
            g_running = false;
            break;
        case WM_KEYDOWN:
            std::println("key down");
            break;
    };

    return ::DefWindowProcA(hWnd, Msg, wParam, lParam);
}
}

namespace game
{
Window::Window(std::uint32_t width, std::uint32_t height)
        : window_({}),
          wc_({})
{
    wc_ = {.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC, .lpfnWndProc = window_proc, .hInstance =::GetModuleHandleA(
            nullptr), .lpszClassName = "window class",};

    if (::RegisterClassA(&wc_) == 0) {
        throw std::runtime_error{"failed to register window class"};
    }

    ::RECT rect{.left={}, .top = {}, .right=static_cast<int>(width), .bottom = static_cast<int>(height)};

    if (::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false) == 0) {
        throw std::runtime_error{"failed to resize window"};
    }

    window_ = {::CreateWindowExA(0, wc_.lpszClassName, "game window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                 rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wc_.hInstance,
                                 nullptr), ::DestroyWindow};

    ::ShowWindow(window_, SW_SHOW);
    ::UpdateWindow(window_);
}

auto Window::running() const -> bool
{
    auto message = ::MSG{};
    while (::PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&message);
        ::DispatchMessageA(&message);
    }
    return g_running;
}

}