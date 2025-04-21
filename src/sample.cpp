#include "sampler.h"

#include "opengl.h"
#include "auto_release.h"

namespace game
{
Sampler::Sampler()
    : handle_{0u, [](auto sampler) { ::glDeleteSamplers(1, &sampler); }}
{
    ::glCreateSamplers(1, &handle_);
}

::GLuint Sampler::native_handle() const
{
    return handle_;
}
}
