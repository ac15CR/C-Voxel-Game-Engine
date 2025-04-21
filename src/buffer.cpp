#include "buffer.h"

#include <cstddef>
#include <cstdint>
#include <span>

#include "auto_release.h"
#include "opengl.h"

namespace game
{

Buffer::Buffer(std::uint32_t size)
        :buffer_{0u, [](auto buffer) { ::glDeleteBuffers(1, &buffer); }}
{
    ::glCreateBuffers(1, &buffer_);
    ::glNamedBufferStorage(buffer_, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
}

void Buffer::write(std::span<const std::byte> data, std::size_t offset) const
{
    ::glNamedBufferSubData(buffer_, offset, data.size(), data.data());
}

::GLuint Buffer::native_handle() const
{
    return buffer_;
}
}