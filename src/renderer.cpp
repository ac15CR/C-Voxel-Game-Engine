#include "renderer.h"

#include "material.h"
#include "opengl.h"

namespace game
{
Renderer::Renderer(Material material)
    : mesh_{}, material_(std::move(material))
{
    ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void Renderer::render() const
{
    ::glClear(GL_COLOR_BUFFER_BIT);

    ::glUseProgram(material_.native_handle());
    mesh_.bind();
    ::glDrawArrays(GL_TRIANGLES, 0, 3);
    mesh_.unbind();
}
}
