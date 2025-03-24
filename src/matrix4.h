#pragma once

#include <array>
#include <span>
#include <format>

#include "vector3.h"

namespace game
{
class Matrix4
{
public:
    constexpr Matrix4()
        : elements_(
            {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            }
        )
    {
    }

    constexpr Matrix4(const std::array<float, 16u> &elements)
        : elements_(elements)
    {
    }

    constexpr Matrix4(const Vector3 &translation)
        : elements_(
            {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                translation.x, translation.y, translation.z, 1.0f
            }
        )
    {
    }

    static Matrix4 look_at(const Vector3 &eye, const Vector3 &look_at, const Vector3 &up);
    static Matrix4 perspective(float fov, float width, float height, float near_plane, float far_plane);

    constexpr std::span<const float> data() const
    {
        return elements_;
    }

    friend constexpr Matrix4 &operator*=(Matrix4 &m1, const Matrix4 &m2);

private:
    std::array<float, 16u> elements_;
};

constexpr Matrix4 &operator*=(Matrix4 &m1, const Matrix4 &m2)
{
    const auto &a = m1.elements_;
    const auto &b = m2.elements_;

    m1.elements_ = {
        a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3],
        a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3],
        a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3],
        a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3],

        a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7],
        a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7],
        a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7],
        a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7],

        a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11],
        a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11],
        a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11],
        a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11],

        a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15],
        a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15],
        a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15],
        a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15],
    };

    return m1;
}


constexpr Matrix4 operator*(const Matrix4 &m1, const Matrix4 &m2)
{
    auto tmp{m1};
    return tmp *= m2;
}

}


template<>
struct std::formatter<game::Matrix4>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::Matrix4 &obj, std::format_context &ctx) const
    {
        return std::format_to(
            ctx.out(), "{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}",
            obj.data()[0], obj.data()[4], obj.data()[8], obj.data()[12],
            obj.data()[1], obj.data()[5], obj.data()[9], obj.data()[13],
            obj.data()[2], obj.data()[6], obj.data()[10], obj.data()[14],
            obj.data()[3], obj.data()[7], obj.data()[11], obj.data()[15]
        );
    }
};
