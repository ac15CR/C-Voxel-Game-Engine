#pragma once

#include <format>
#include <string_view>

#include "auto_release.h"
#include "exception.h"
#include "opengl.h"

namespace game
{
enum class ShaderType
{
    VERTEX, FRAGMENT
};

class Shader
{
public:
    Shader(std::string_view source, ShaderType type);

    ShaderType type() const;

    ::GLuint native_handle() const;

private:
    AutoRelease<::GLuint> handle_;
    ShaderType type_;
};
}

template<>
struct std::formatter<game::ShaderType>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::ShaderType &obj, std::format_context &ctx) const
    {
        switch (obj) {
                using enum game::ShaderType;
            case VERTEX:
                return std::format_to(ctx.out(), "VERTEX");
            case FRAGMENT:
                return std::format_to(ctx.out(), "FRAGMENT");
            default: ;
        }
        throw game::Exception("Unknown shader type: {}", std::to_underlying(obj));
    }
};
