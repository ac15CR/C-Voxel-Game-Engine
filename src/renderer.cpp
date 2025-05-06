#include "renderer.h"

#include "buffer_writer.h"
#include "camera.h"
#include "color.h"
#include "entity.h"
#include "material.h"
#include "mesh.h"
#include "opengl.h"
#include "sampler.h"
#include "scene.h"
#include "texture.h"
#include "vector3.h"

namespace
{
struct LightBuffer
{
    alignas(16) game::Color ambient;
    alignas(16) game::Vector3 direction;
    alignas(16) game::Color direction_color;
    alignas(16) game::Vector3 position;
    alignas(16) game::Color point_color;
};
}

namespace game
{
Renderer::Renderer()
    : camera_buffer_{sizeof(Matrix4) * 2u}
      , light_buffer_{sizeof(LightBuffer)}
{
}


void Renderer::render(const Camera &camera, const Scene &scene) const
{
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); {
        BufferWriter writer{camera_buffer_};
        writer.write(camera.view());
        writer.write(camera.projection());
    } {
        const LightBuffer light_buffer{
            scene.ambient,
            scene.directional.direction,
            scene.directional.color,
            scene.point.position,
            scene.point.color
        };
        BufferWriter writer{light_buffer_};
        writer.write(light_buffer);
    }

    ::glBindBufferBase(GL_UNIFORM_BUFFER, 0, camera_buffer_.native_handle());
    ::glBindBufferBase(GL_UNIFORM_BUFFER, 1, light_buffer_.native_handle());

    for (const auto *entity: scene.entities) {
        const auto *material = entity->material();
        const auto *mesh = entity->mesh();
        const auto *texture = entity->texture();
        const auto *sampler = entity->sampler();

        ::glUseProgram(material->native_handle());

        const auto model_uniform = ::glGetUniformLocation(material->native_handle(), "model");
        ::glUniformMatrix4fv(model_uniform, 1, GL_FALSE, entity->model().data());

        ::glBindTextureUnit(0, texture->native_handle());
        ::glBindSampler(0, sampler->native_handle());

        const auto tex_uniform = ::glGetUniformLocation(material->native_handle(), "tex");
        ::glUniform1i(tex_uniform, 0);

        mesh->bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 36);
        ::glDrawElements(
            GL_TRIANGLES, mesh->index_count(), GL_UNSIGNED_INT, reinterpret_cast<void *>(mesh->index_offset())
        );
        mesh->unbind();
    }
}
}
