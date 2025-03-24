#include "matrix4.h"

namespace game
{
Matrix4 Matrix4::look_at(const Vector3 &eye, const Vector3 &look_at, const Vector3 &up)
{
    const auto f = Vector3::normalize(look_at - eye);
    const auto up_normalized = Vector3::normalize(up);

    const auto s = Vector3::normalize(Vector3::cross(f, up_normalized));
    const auto [ux, uy, uz] = Vector3::normalize(Vector3::cross(s, f));

    auto m = Matrix4{};
    m.elements_ = {
        {
            s.x, ux, -f.x, 0.0f,
            s.y, uy, -f.y, 0.0f,
            s.z, uz, -f.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }
    };

    return m * Matrix4(-eye);
}

Matrix4 Matrix4::perspective(float fov, float width, float height, float near_plane, float far_plane)
{
    Matrix4 m;

    const auto aspect_ratio = width / height;
    const auto tmp = std::tan(fov / 2.0f);
    const auto t = tmp * near_plane;
    const auto b = -t;
    const auto r = t * aspect_ratio;
    const auto l = b * aspect_ratio;

    m.elements_ = {
        {
            (2.0f * near_plane) / (r - l), 0.0f, 0.0f, 0.0f,
            0.0f, (2.0f * near_plane) / (t - b), 0.0f, 0.0f,
            (r + l) / (r - l), (t + b) / (t - b), -(far_plane + near_plane) / (far_plane - near_plane), -1.0f,
            0.0f, 0.0f, -(2.0f * far_plane * near_plane) / (far_plane - near_plane), 0.0f
        }
    };

    return m;
}


}
