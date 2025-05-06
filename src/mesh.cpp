#include "mesh.h"

#include <ranges>

#include "auto_release.h"
#include "buffer.h"
#include "buffer_writer.h"
#include "opengl.h"
#include "vertex_data.h"

namespace
{
constexpr game::VertexData vertex_data[] =
{
    // Front face
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

    // Back face
    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

    // Top face
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    // Bottom face
    {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},

    // Right face
    {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}
};

constexpr GLuint indices[] =
{
    // Front face
    0, 1, 2,
    0, 2, 3,

    // Back face
    4, 5, 6,
    4, 6, 7,

    // Top face
    8, 9, 10,
    8, 10, 11,

    // Bottom face
    12, 13, 14,
    12, 14, 15,

    // Right face
    16, 17, 18,
    16, 18, 19,

    // Left face
    20, 21, 22,
    20, 22, 23

};
}


namespace game
{
Mesh::Mesh()
    : vao_{0u, [](auto vao) { ::glDeleteVertexArrays(1, &vao); }}
    , vbo_{sizeof(vertex_data) + sizeof(indices)}
    , index_count_(static_cast<std::uint32_t>(std::ranges::distance(indices)))
    , index_offset_(sizeof(vertex_data))
{ {
        BufferWriter writer{vbo_};
        writer.write(vertex_data);
        writer.write(indices);
    }
    ::glCreateVertexArrays(1, &vao_);
    ::glVertexArrayVertexBuffer(vao_, 0, vbo_.native_handle(), 0, sizeof(VertexData));
    ::glVertexArrayElementBuffer(vao_, vbo_.native_handle());

    ::glEnableVertexArrayAttrib(vao_, 0);
    ::glEnableVertexArrayAttrib(vao_, 1);
    ::glEnableVertexArrayAttrib(vao_, 2);

    ::glVertexArrayAttribFormat(vao_, 0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
    ::glVertexArrayAttribFormat(vao_, 1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, normal));
    ::glVertexArrayAttribFormat(vao_, 2, 2, GL_FLOAT, GL_FALSE, offsetof(VertexData, uv));

    ::glVertexArrayAttribBinding(vao_, 0, 0);
    ::glVertexArrayAttribBinding(vao_, 1, 0);
    ::glVertexArrayAttribBinding(vao_, 2, 0);
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
