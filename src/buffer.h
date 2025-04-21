#pragma once

#include <span>
#include <cstdint>
#include <cstddef>

#include "opengl.h"
#include "auto_release.h"

namespace game
{
class Buffer
{
public:
    Buffer(std::uint32_t size);

    void write(std::span<const std::byte> data, std::size_t offset) const;

    ::GLuint native_handle() const;

private:
    AutoRelease<::GLuint> buffer_;
};
}