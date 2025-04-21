#pragma once

#include "opengl.h"
#include "auto_release.h"

namespace game
{
class Sampler
{
public:
    Sampler();

    ::GLuint native_handle() const;
private:
    AutoRelease<GLuint> handle_;
};
}
