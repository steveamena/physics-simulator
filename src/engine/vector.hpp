#pragma once

template <typename T>
struct Vec2
{
    T x{};
    T y{};

    constexpr Vec2() = default;

    constexpr Vec2(T x, T y)
        : x(x), y(y)
    {
    }

    // Sum
    constexpr Vec2 operator+(const Vec2 &other) const
    {
        return {x + other.x, y + other.y};
    }

    // Subtraction
    constexpr Vec2 operator-(const Vec2 &other) const
    {
        return {x - other.x, y - other.y};
    }

    // Scalar product
    constexpr Vec2 operator*(T scalar) const
    {
        return {x * scalar, y * scalar};
    }

    // Dot product
    constexpr T dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    // +=
    constexpr Vec2 &operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    // -=
    constexpr Vec2 &operator-=(const Vec2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // *=
    constexpr Vec2 &operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
};