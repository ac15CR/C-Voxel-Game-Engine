#pragma once

#include <span>

#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "sampler.h"
#include "texture.h"
#include "vector3.h"

namespace game
{
class Entity
{
public:
    Entity(const Mesh *mesh, const Material *material, const Vector3 &position, const Texture *texture, const Sampler *sampler);

    const Mesh* mesh() const;
    const Material* material() const;
    std::span<const float> model() const;
    const Texture* texture() const;
    const Sampler* sampler() const;
private:
    const Mesh *mesh_;
    const Material *material_;
    Matrix4 model_;
    const Texture *texture_;
    const Sampler *sampler_;
};
}
