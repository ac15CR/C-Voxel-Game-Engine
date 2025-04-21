#pragma once

#include "color.h"
#include "vector3.h"

namespace game
{

struct UV
{
    float x;
    float y;
};

struct VertexData
{
    Vector3 position;
    UV uv;
};

}