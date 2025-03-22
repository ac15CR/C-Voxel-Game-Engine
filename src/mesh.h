#pragma once

#include "auto_release.h"
#include "opengl.h"

namespace game
{

class Mesh
{
public:
    Mesh();

    void bind() const;

    static void unbind();
private:
    AutoRelease<::GLuint> vao_;
    AutoRelease<::GLuint> vbo_;
};

}