#pragma once

#include "camera.h"
#include "material.h"
#include "scene.h"
#include "buffer.h"

namespace game
{
class Renderer
{
public:
    Renderer();
    void render(const Camera &camera, const Scene &scene) const;

private:
    Buffer camera_buffer_;
};
}
