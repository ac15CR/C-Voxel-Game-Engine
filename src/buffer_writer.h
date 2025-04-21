#pragma once

#include <span>
#include <cstdint>

#include "buffer.h"

namespace game
{
class BufferWriter
{
public:
    BufferWriter(const Buffer &buffer)
            : buffer_(buffer),
              offset_{}
    {
    }

    // Obscure array size deduction template
    template<class T, std::size_t N>
    auto write(const T (&data)[N])
    {
        buffer_.write({reinterpret_cast<const std::byte *>(data), sizeof(T) * N}, offset_);
        offset_ += sizeof(T) * N;
    }

private:
    const Buffer &buffer_;
    std::uint32_t offset_;
};
}