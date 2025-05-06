#include "camera.h"

#include <span>

#include "matrix4.h"
#include "vector3.h"

namespace
{
game::Vector3 create_direction(const float pitch, const float yaw)
{
    return game::Vector3::normalize(
        {
            std::cos(yaw) * std::cos(pitch),
            std::sin(pitch),
            std::sin(yaw) * std::cos(pitch)
        }
    );
}
}

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
    , pitch_{}
    , yaw_{}
{
}

Vector3 Camera::position() const
{
    return position_;
}

Vector3 Camera::direction() const
{
    return direction_;
}

Vector3 Camera::right() const
{
    return Vector3::normalize(Vector3::cross(direction_, up_));
}

void Camera::adjust_yaw(const float adjust)
{
    yaw_ += adjust;
    direction_ = create_direction(pitch_, yaw_);
    view_ = Matrix4::look_at(position_, position_ + direction_, up_);
}

void Camera::adjust_pitch(const float adjust)
{
    pitch_ += adjust;
    direction_ = create_direction(pitch_, yaw_);
    view_ = Matrix4::look_at(position_, position_ + direction_, up_);
}

void Camera::translate(const Vector3 &translation)
{
    position_ += translation;
    direction_ = create_direction(pitch_, yaw_);
    view_ = Matrix4::look_at(position_, position_ + direction_, up_);
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
