#pragma once
#include <cmath>
#include <compare>
#include <iostream>

struct Vec2 {
    int x = 0;
    int y = 0;

    // --- Constructors ---
    constexpr Vec2() : x(0), y(0) {};
    constexpr Vec2(int x, int y) : x(x), y(y) {}

    // --- Arithmetic operators ---
    constexpr Vec2 operator+(const Vec2& other) const noexcept {
        return {x + other.x, y + other.y};
    }

    constexpr Vec2 operator-(const Vec2& other) const noexcept {
        return {x - other.x, y - other.y};
    }

    constexpr Vec2& operator+=(const Vec2& other) noexcept {
        x += other.x; y += other.y; return *this;
    }

    constexpr Vec2& operator-=(const Vec2& other) noexcept {
        x -= other.x; y -= other.y; return *this;
    }

    constexpr Vec2 operator*(int scalar) const noexcept {
        return {x * scalar, y * scalar};
    }

    constexpr Vec2 operator/(int scalar) const noexcept {
        return {x / scalar, y / scalar};
    }

    constexpr Vec2& operator*=(int scalar) noexcept {
        x *= scalar; y *= scalar; return *this;
    }

    constexpr Vec2& operator/=(int scalar) noexcept {
        x /= scalar; y /= scalar; return *this;
    }

    // --- Comparison ---
    constexpr bool operator==(const Vec2& other) {
        return x == other.x && y == other.y;
    }

    // --- Utilities ---
    [[nodiscard]] constexpr int manhattan() const noexcept {
        return std::abs(x) + std::abs(y);
    }
    
    [[nodiscard]] constexpr int smallestSquare() const noexcept {
        return std::max(std::abs(x), std::abs(y));
    }

    [[nodiscard]] constexpr int lengthSq() const noexcept {
        return x * x + y * y;
    }

    [[nodiscard]] double length() const noexcept {
        return std::sqrt(static_cast<double>(lengthSq()));
    }

    [[nodiscard]] constexpr bool isZero() const noexcept {
        return x == 0 && y == 0;
    }

    static constexpr Vec2 zero() noexcept { return {0, 0}; }
    static constexpr Vec2 up() noexcept { return {0, -1}; }
    static constexpr Vec2 down() noexcept { return {0, 1}; }
    static constexpr Vec2 left() noexcept { return {-1, 0}; }
    static constexpr Vec2 right() noexcept { return {1, 0}; }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};
