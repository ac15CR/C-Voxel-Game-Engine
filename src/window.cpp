#include "window.h"

#include <Windows.h>
#include <gl/gl.h>

#include "../third_party/opengl/wglext.h"

#include <cstdint>
#include <print>
#include <stdexcept>

#define NOMINMAX

#include "opengl.h"

#include "auto_release.h"
#include "error.h"

#pragma comment(lib, "opengl32.lib") // Makes sure that the opengl32.lib is linked so can use wgl functions

namespace
{
// Draw Runes in the sand (TYPE | NAME)
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB{};

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB{};

auto g_running = true;

void APIENTRY opengl_debug_callback(
    ::GLenum source,
    ::GLenum type,
    ::GLuint id,
    ::GLenum severity,
    ::GLsizei,
    const ::GLchar *message,
    const void *

)
{
    std::println("{} {} {} {} {}", source, type, id, severity, message);
}

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

template<class T>
void resolve_gl_function(T &function, const std::string &name)
{
    const auto address = ::wglGetProcAddress(name.c_str());
    game::ensure(address != nullptr, "failed to get address of wgl function: {}", name);

    function = reinterpret_cast<T>(address);
}

void resolve_wgl_functions(::HINSTANCE instance)
{
    auto wc = ::WNDCLASS{
        .style = CS_HREDRAW | CS_VREDRAW |
                 CS_OWNDC,
        .lpfnWndProc = ::DefWindowProc, .hInstance = instance, .lpszClassName = "dummy window"
    };

    game::ensure(::RegisterClassA(&wc) != 0, "failed to register dummy window");

    auto dummy_window = game::AutoRelease<::HWND>{
        ::CreateWindowExA(
            0, wc.lpszClassName, wc.lpszClassName, 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, nullptr, nullptr, instance, nullptr
        ),
        ::DestroyWindow
    };

    game::ensure(dummy_window, "failed to create dummy window");

    auto dc = game::AutoRelease<::HDC>{
        ::GetDC(dummy_window),
        [&dummy_window](auto dc) { ::ReleaseDC(dummy_window, dc); }
    };

    game::ensure(dc, "failed to get dummy device context");

    auto pdf = ::PIXELFORMATDESCRIPTOR{
        .nSize = sizeof(::PIXELFORMATDESCRIPTOR), .nVersion = 1, .dwFlags =
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA, .cColorBits = 32, .cAlphaBits = 8, .cDepthBits = 24, .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE
    };

    auto pixel_format = ::ChoosePixelFormat(dc, &pdf);

    game::ensure(pixel_format != 0, "failed to choose pixel format");

    game::ensure(::SetPixelFormat(dc, pixel_format, &pdf) == TRUE, "failed to set pixel format");

    const auto context = game::AutoRelease<::HGLRC>{::wglCreateContext(dc), ::wglDeleteContext};

    game::ensure(context, "failed to create wgl context");

    game::ensure(::wglMakeCurrent(dc, context) == TRUE, "failed to make wgl context current");

    // resolve wgl functions
    resolve_gl_function(wglCreateContextAttribsARB, "wglCreateContextAttribsARB");
    resolve_gl_function(wglChoosePixelFormatARB, "wglChoosePixelFormatARB");

    game::ensure(::wglMakeCurrent(dc, 0) == TRUE, "failed to release wgl context");
}
}

void init_opengl(::HDC dc)
{
    // Previously set on dummy window, now do real window and use actual wgl functions
    // PAIRS KEY, VALUE | Like the PIXELFORMATDESCRIPTOR
    int pixel_format_attribs[]{
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, WGL_SUPPORT_OPENGL_ARB, GL_TRUE, WGL_DOUBLE_BUFFER_ARB,
        GL_TRUE, WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB, WGL_PIXEL_TYPE_ARB,
        WGL_TYPE_RGBA_ARB, WGL_COLOR_BITS_ARB, 32, WGL_DEPTH_BITS_ARB, 24, WGL_STENCIL_BITS_ARB,
        8, 0 // null terminated
    };

    auto pixel_format = 0;
    auto num_formats = UINT{};
    ::wglChoosePixelFormatARB(dc, pixel_format_attribs, nullptr, 1, &pixel_format, &num_formats);

    game::ensure(num_formats != 0u, "failed to choose pixel format");

    auto pdf = ::PIXELFORMATDESCRIPTOR{};
    game::ensure(
        ::DescribePixelFormat(dc, pixel_format, sizeof(pdf), &pdf) != 0,
        "failed to describe pixel format"
    ); // fill in pdf with the pixel format
    game::ensure(::SetPixelFormat(dc, pixel_format, &pdf) == TRUE, "failed to set pixel format");

    int gl_attribs[]{
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4, WGL_CONTEXT_MINOR_VERSION_ARB, 6, WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    }; //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0};

    auto context = ::wglCreateContextAttribsARB(dc, nullptr, gl_attribs);
    game::ensure(context != nullptr, "failed to create wgl context");

    game::ensure(::wglMakeCurrent(dc, context) == TRUE, "failed to make wgl context current");
}

void resolve_global_gl_functions()
{
#define RESOLVE(TYPE, NAME) resolve_gl_function(NAME, #NAME);
    FOR_OPENGL_FUNCTIONS(RESOLVE)
}

void setup_debug()
{
    ::glEnable(GL_DEBUG_OUTPUT);
    ::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // makes sure that the callback is called immediately, makes code a bit slower
    ::glDebugMessageCallback(opengl_debug_callback, nullptr);
}

namespace game
{
Window::Window(std::uint32_t width, std::uint32_t height)
    : window_({})
    , dc_({})
    , wc_({})
{
    wc_ = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC, .lpfnWndProc = window_proc, .hInstance = ::GetModuleHandleA(
            nullptr
        ),
        .lpszClassName = "window class",
    };

    ensure(::RegisterClassA(&wc_) != 0, "failed to register window class");

    ::RECT rect{.left = {}, .top = {}, .right = static_cast<int>(width), .bottom = static_cast<int>(height)};

    ensure(::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false) != 0, "failed to resize window rect");

    window_ = {
        ::CreateWindowExA(
            0, wc_.lpszClassName, "game window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wc_.hInstance,
            nullptr
        ),
        ::DestroyWindow
    };

    dc_ = AutoRelease<::HDC>{::GetDC(window_), [this](auto dc) { ::ReleaseDC(window_, dc); }};

    ::ShowWindow(window_, SW_SHOW);
    ::UpdateWindow(window_);

    resolve_wgl_functions(wc_.hInstance);
    init_opengl(dc_);
    resolve_global_gl_functions();
    setup_debug();

    //::glEnable(GL_CULL_FACE); // backface culling
    ::glEnable(GL_DEPTH_TEST);
}

bool Window::running() const
{
    auto message = ::MSG{};
    while (::PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&message);
        ::DispatchMessageA(&message);
    }

    return g_running;
}

void Window::swap() const
{
    ::SwapBuffers(dc_);
}
}
