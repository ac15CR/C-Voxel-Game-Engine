#include "texture.h"

#include <cstddef>
#include <cstdint>
#include <span>

#define STBI_ONLY_PNG // TODO: does this work
#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb/stb_image.h"

#include "error.h"
#include "opengl.h"

namespace game
{
Texture::Texture(std::span<const std::byte> data, std::uint32_t width, std::uint32_t height)
    : handle_{0u, [](auto texture) { ::glDeleteTextures(1, &texture); }}
{
    auto w = static_cast<int>(width);
    auto h = static_cast<int>(height);
    auto num_channels = int{4};

    auto raw_data = std::unique_ptr<::stbi_uc, decltype(&::stbi_image_free)>(
        ::stbi_load_from_memory(
            reinterpret_cast<const stbi_uc *>(data.data()), static_cast<int>(data.size()), &w, &h, &num_channels, 0
        ),
        ::stbi_image_free
    );

    ensure(raw_data, "failed to load texture data");
    ensure(static_cast<std::uint32_t>(w) == width, "width mismatch");
    ensure(static_cast<std::uint32_t>(h) == height, "height mismatch");
    ensure(num_channels == 4, "expected 4 channels");

    ::glCreateTextures(GL_TEXTURE_2D, 1, &handle_);

    ::glTextureStorage2D(handle_, 1, GL_RGBA8, width, height);
    ::glTextureSubImage2D(handle_, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, raw_data.get());
}

::GLuint Texture::native_handle() const
{
    return handle_;
}
}
