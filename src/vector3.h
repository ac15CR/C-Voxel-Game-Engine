#pragma once

#include <cmath>
#include <format>

namespace game
{
struct Vector3
{
    constexpr Vector3()
        : Vector3(0.0f)
    {
    }

    constexpr Vector3(const float xyz)
        : Vector3(xyz, xyz, xyz)
    {
    }

    constexpr Vector3(const float x, const float y, const float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static Vector3 normalize(const Vector3 &v)
    {
        const auto length = std::hypot(v.x, v.y, v.z);
        if (length == 0.0f) {
            return {0.0f, 0.0f, 0.0f};
        }
        return {v.x / length, v.y / length, v.z / length};
    }

    static constexpr Vector3 cross(const Vector3 &v1, const Vector3 &v2)
    {
        const auto i = (v1.y * v2.z) - (v1.z * v2.y);
        const auto j = (v1.z * v2.x) - (v1.x * v2.z);
        const auto k = (v1.x * v2.y) - (v1.y * v2.x);

        return {i, j, k};
    }

    constexpr bool operator==(const Vector3 &) const = default;

    float x;
    float y;
    float z;
};

constexpr Vector3 &operator-=(Vector3 &v1, const Vector3 &v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;

    return v1;
}

constexpr Vector3 &operator+=(Vector3 &v1, const Vector3 &v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;

    return v1;
}

constexpr Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{
    auto tmp = v1;
    return tmp += v2;
}

constexpr Vector3 & operator*=(Vector3 &v1, const Vector3 &v2)
{
    v1.x *= v2.x;
    v1.y *= v2.y;
    v1.z *= v2.z;

    return v1;
}

constexpr Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
{
    auto tmp = v1;
    return tmp *= v2;
}

constexpr Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
    auto tmp = v1;
    return tmp -= v2;
}

constexpr Vector3 operator-(const Vector3 &v)
{
    return {-v.x, -v.y, -v.z};
}
}

template<>
struct std::formatter<game::Vector3>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::cbegin(ctx);
    }

    auto format(const game::Vector3 &obj, std::format_context &ctx) const
    {
        return std::format_to(
            ctx.out(), "x={}, y={}, z={}", obj.x, obj.y, obj.z
        );
    }
};
