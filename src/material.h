#pragma once

#include "auto_release.h"
#include "opengl.h"
#include "shader.h"

namespace game
{

class Material
{
public:
    Material(const Shader &vertex_shader, const Shader &fragment_shader);
    ::GLuint native_handle() const;

private:
    AutoRelease<::GLuint> handle_;
};

}