#pragma once

#include <cstdint>

#include "auto_release.h"
#include "opengl.h"
#include "buffer.h"

namespace game
{
class Mesh
{
public:
    Mesh();

    void bind() const;

    static void unbind();

    std::uint32_t index_count() const;

    std::uintptr_t index_offset() const;

private:
    AutoRelease<::GLuint> vao_;
    Buffer vbo_;
    std::uint32_t index_count_;
    std::uintptr_t index_offset_;
};
}
