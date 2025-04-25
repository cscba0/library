#pragma once
#include <cmath>

template <typename T = int>
struct Point {
    T y, x;
    inline constexpr Point() noexcept : y(0), x(0) {}
    inline constexpr Point(T _y, T _x) noexcept : y(_y), x(_x) {}

    long double distance(const Point<T>& rhs) noexcept {
        return sqrtl(distancePow(*this, rhs));
    }
    T distancePow(const Point<T>& rhs) noexcept {
        return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
    }

    bool operator==(const Point& rhs) {
        return y == rhs.y && x == rhs.x;
    }
};
