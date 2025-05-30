#pragma once

#include <span>

#include "vector3.h"
#include "matrix4.h"

namespace game
{
class Camera
{
public:
    Camera(
        const Vector3 &position,
        const Vector3 &look_at,
        const Vector3 &up,
        float fov,
        float width,
        float height,
        float near_plane,
        float far_plane
    );

    Vector3 position() const;
    Vector3 direction() const;
    Vector3 right() const;
    void adjust_yaw(float adjust);
    void adjust_pitch(float adjust);
    void translate(const Vector3 &translation); // relative position
    std::span<const float> view() const;
    std::span<const float> projection() const;

private:
    Matrix4 view_;
    Matrix4 projection_;
    Vector3 position_;
    Vector3 direction_;
    Vector3 up_;
    float pitch_;
    float yaw_;
};
}
