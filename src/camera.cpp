#include "camera.h"

#include <span>

#include "matrix4.h"
#include "vector3.h"

namespace game
{
Camera::Camera(
    const Vector3 &position, const Vector3 &look_at, const Vector3 &up, float fov, float width, float height,
    float near_plane, float far_plane
)
    : view_(Matrix4::look_at(position, look_at, up))
    , projection_(Matrix4::perspective(fov, width, height, near_plane, far_plane))
    , position_(position)
    , direction_(look_at) // - position)
    , up_(up)
{
}

void Camera::translate(const Vector3 &translation)
{
    position_ += translation;
    direction_ += translation;
    view_ = Matrix4::look_at(position_, direction_, up_);
}


std::span<const float> Camera::view() const
{
    return view_.data();
}

std::span<const float> Camera::projection() const
{
    return projection_.data();
}
}
