#pragma once

#include "camera.h"
#include "material.h"
#include "scene.h"

namespace game
{
class Renderer
{
public:
    void render(const Camera &camera, const Scene &scene) const;

private:
};
}
