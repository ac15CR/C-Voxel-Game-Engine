#pragma once

#include "material.h"
#include "mesh.h"

namespace game
{

class Renderer
{
public:
    Renderer(Material material);
    void render() const;
private:
    Mesh mesh_;
    Material material_;
};

}