#include "entity.h"

#include <span>

#include "matrix4.h"
#include "material.h"
#include "mesh.h"
#include "vector3.h"

namespace game
{
Entity::Entity(const Mesh *mesh, const Material *material, const Vector3 &position)
    : mesh_(mesh)
    , material_(material)
    , model_(position)
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
}
