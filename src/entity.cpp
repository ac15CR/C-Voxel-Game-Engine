#include "entity.h"

#include <span>

#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "sampler.h"
#include "texture.h"
#include "vector3.h"

namespace game
{
Entity::Entity(
    const Mesh *mesh, const Material *material, const Vector3 &position, const Texture *texture, const Sampler *sampler
)
    : mesh_(mesh)
    , material_(material)
    , model_(position)
    , texture_(texture)
    , sampler_(sampler)
{
}

const Mesh *Entity::mesh() const
{
    return mesh_;
}

const Material *Entity::material() const
{
    return material_;
}

std::span<const float> Entity::model() const
{
    return model_.data();
}

const Texture *Entity::texture() const
{
    return texture_;
}

const Sampler *Entity::sampler() const
{
    return sampler_;
}
}
