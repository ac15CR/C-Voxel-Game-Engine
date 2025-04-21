#include "mesh.h"

#include <ranges>

#include "auto_release.h"
#include "opengl.h"
#include "vertex_data.h"
#include "buffer.h"
#include "buffer_writer.h"

namespace
{
constexpr game::VertexData vertex_data[] = {
    {{-0.5f, -0.5f, 0.5f,}, {1.0f, 0.0f, 0.0f,}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f,}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f,}},
    {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.0f,}},
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f,}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0}},
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}}
};

constexpr GLuint indices[] = {
    0, 1, 2,
    2, 3, 0,
    1, 5, 6,
    6, 2, 1,
    5, 4, 7,
    7, 6, 5,
    4, 0, 3,
    3, 7, 4,
    4, 5, 1,
    1, 0, 4,
    3, 2, 6,
    6, 7, 3
};
}


namespace game
{
Mesh::Mesh()
    : vao_{0u, [](auto vao) { ::glDeleteVertexArrays(1, &vao); }}
    , vbo_{sizeof(vertex_data) + sizeof(indices)}
    , index_count_(static_cast<std::uint32_t>(std::ranges::distance(indices)))
    , index_offset_(sizeof(vertex_data))
{

    {
        BufferWriter writer{vbo_};
        writer.write(vertex_data);
        writer.write(indices);
    }
    ::glCreateVertexArrays(1, &vao_);
    ::glVertexArrayVertexBuffer(vao_, 0, vbo_.native_handle(), 0, sizeof(VertexData));
    ::glVertexArrayElementBuffer(vao_, vbo_.native_handle());

    ::glEnableVertexArrayAttrib(vao_, 0);
    ::glEnableVertexArrayAttrib(vao_, 1);

    ::glVertexArrayAttribFormat(vao_, 0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
    ::glVertexArrayAttribFormat(vao_, 1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, color));

    ::glVertexArrayAttribBinding(vao_, 0, 0);
    ::glVertexArrayAttribBinding(vao_, 1, 0);
};

void Mesh::bind() const
{
    ::glBindVertexArray(vao_);
}

void Mesh::unbind()
{
    ::glBindVertexArray(0);
}

std::uint32_t Mesh::index_count() const
{
    return index_count_;
}

std::uintptr_t Mesh::index_offset() const
{
    return index_offset_;
}

}
