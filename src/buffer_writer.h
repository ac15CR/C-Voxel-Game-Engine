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
        : buffer_(buffer)
        , offset_{}
    {
    }

    template<class T>
    void write(const T &obj) requires std::is_trivially_copyable_v<T>
    {
        auto spn = std::span<const T>{&obj, 1};
        write(spn);
    }

    // Obscure array size deduction template
    template<class T, std::size_t N>
    void write(const T (&data)[N])
    {
        buffer_.write({reinterpret_cast<const std::byte *>(data), sizeof(T) * N}, offset_);
        offset_ += sizeof(T) * N;
    }

    template<class T>
    void write(std::span<const T> data)
    {
        buffer_.write(std::as_bytes(data), offset_);
        offset_ += data.size_bytes();
    }

private:
    const Buffer &buffer_;
    std::size_t offset_;
};
}
