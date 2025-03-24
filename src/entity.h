#pragma once

#include <span>

#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "vector3.h"

namespace game
{
class Entity
{
public:
    Entity(const Mesh *mesh, const Material *material, const Vector3 &position);

    const Mesh* mesh() const;
    const Material* material() const;
    std::span<const float> model() const;
private:
    const Mesh *mesh_;
    const Material *material_;
    Matrix4 model_;
};
}
