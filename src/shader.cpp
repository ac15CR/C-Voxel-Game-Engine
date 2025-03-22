#include "shader.h"
#include "auto_release.h"
#include "error.h"
#include "exception.h"
#include "opengl.h"

namespace
{
::GLenum to_native(const game::ShaderType type)
{
    switch (type) {
            using enum game::ShaderType;
        case VERTEX:
            return GL_VERTEX_SHADER;
        case FRAGMENT:
            return GL_FRAGMENT_SHADER;
    }
    throw game::Exception("Unknown shader type: {}", std::to_underlying(type));
}
}

namespace game
{
Shader::Shader(std::string_view source, ShaderType type)
    : handle_{},
      type_(type)
{
    handle_ = AutoRelease<::GLuint>{::glCreateShader(to_native(type)), ::glDeleteShader};

    const ::GLchar *strings[] = {source.data()};
    const ::GLint lengths[] = {static_cast<::GLint>(source.length())};

    ::glShaderSource(handle_, 1, strings, lengths);
    ::glCompileShader(handle_);

    ::GLint result;
    ::glGetShaderiv(handle_, GL_COMPILE_STATUS, &result);
    ensure(result, "failed to compile shader {}", type);
}

ShaderType Shader::type() const
{
    return type_;
}

::GLuint Shader::native_handle() const
{
    return handle_;
}

}
