#include "renderer.h"

#include "camera.h"
#include "entity.h"
#include "material.h"
#include "mesh.h"
#include "opengl.h"
#include "scene.h"
#include "buffer_writer.h"

namespace game
{
Renderer::Renderer()
    : camera_buffer_{sizeof(Matrix4) * 2u}
{
}


void Renderer::render(const Camera &camera, const Scene &scene) const
{
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); {
        BufferWriter writer{camera_buffer_};
        writer.write(camera.view());
        writer.write(camera.projection());
    }

    ::glBindBufferBase(GL_UNIFORM_BUFFER, 0, camera_buffer_.native_handle());

    for (const auto *entity : scene.entities) {
        const auto *material = entity->material();
        const auto *mesh = entity->mesh();

        ::glUseProgram(material->native_handle());

        const auto model_uniform = ::glGetUniformLocation(material->native_handle(), "model");
        ::glUniformMatrix4fv(model_uniform, 1, GL_FALSE, entity->model().data());



        mesh->bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 36);
        ::glDrawElements(
            GL_TRIANGLES, mesh->index_count(), GL_UNSIGNED_INT, reinterpret_cast<void *>(mesh->index_offset())
        );
        mesh->unbind();
    }
}
}
