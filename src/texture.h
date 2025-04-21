#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include "auto_release.h"
#include "opengl.h"

namespace game
{
class Texture
{
public:
    Texture(std::span<const std::byte> data, std::uint32_t width, std::uint32_t height);

    ::GLuint native_handle() const;
private:
    AutoRelease<::GLuint> handle_;
};
}
