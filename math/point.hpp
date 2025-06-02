#pragma once
#include <cmath>

template <typename T = int>
struct Point {
    T x, y;
    inline constexpr Point() noexcept : x(0), y(0) {}
    inline constexpr Point(T _x, T _y) noexcept : x(_x), y(_y) {}

    long double distance(const Point<T>& rhs) noexcept {
        return sqrtl(distancePow(*this, rhs));
    }
    T distancePow(const Point<T>& rhs) noexcept {
        return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
    }

    bool operator==(const Point& rhs) {
        return y == rhs.y && x == rhs.x;
    }

    Point& operator++() {
        ++x;
        ++y;
        return *this;
    }
    Point& operator--() {
        --x;
        --y;
        return *this;
    }

    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }

    auto operator<=>(const Point<T>& other) const {
        if (auto cmp = x <=> other.x; cmp != 0) return cmp;
        return y <=> other.y;
    }
};
