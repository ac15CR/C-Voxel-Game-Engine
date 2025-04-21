#include "mesh.h"

#include <ranges>

#include "auto_release.h"
#include "opengl.h"
#include "vertex_data.h"
#include "buffer.h"
#include "buffer_writer.h"

namespace
{
constexpr game::VertexData vertex_data[] =
{
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},   // 0
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},   // 1
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},   // 2
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},   // 3
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},   // 4
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},   // 5
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},   // 6
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},   // 7
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},   // 8
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},   // 9
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},   //10
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},   //11
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},   //12
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},   //13
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},   //14
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},   //15
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},   //16
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},   //17
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},   //18
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},   //19
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},   //20
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},   //21
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}},   //22
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}},   //23
};

constexpr GLuint indices[] =
{
    0,  1,  2,  2,  3,  0,
    4,  5,  6,  6,  7,  4,
    8,  9, 10, 10, 11,  8,
   12, 13, 14, 14, 15, 12,
   16, 17, 18, 18, 19, 16,
   20, 21, 22, 22, 23, 20
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
    ::glVertexArrayAttribFormat(vao_, 1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, uv));

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
