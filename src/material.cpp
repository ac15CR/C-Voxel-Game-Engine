#include "material.h"
#include "auto_release.h"
#include "error.h"
#include "opengl.h"
#include "shader.h"

namespace game
{
Material::Material(const Shader &vertex_shader, const Shader &fragment_shader)
{
    ensure(vertex_shader.type() == ShaderType::VERTEX, "shader is not a vertex shader");
    ensure(fragment_shader.type() == ShaderType::FRAGMENT, "shader is not a fragment shader");

    handle_ = AutoRelease<::GLuint>{::glCreateProgram(), ::glDeleteProgram};
    ensure(handle_, "failed to create opengl program");

    ::glAttachShader(handle_, vertex_shader.native_handle());
    ::glAttachShader(handle_, fragment_shader.native_handle());
    ::glLinkProgram(handle_);
}

GLuint Material::native_handle() const
{
    return handle_;
}
}
