#pragma once
#include <numeric>

template <typename T = long long>
struct Fraction {
    T x, y;
    constexpr Fraction(const T _x = 0, const T _y = 1) noexcept : x(_x), y(_y) {}
    constexpr Fraction operator+(const Fraction rhs) const noexcept {
        return Fraction(*this) += rhs;
    }
    constexpr Fraction operator-(const Fraction rhs) const noexcept {
        return Fraction(*this) -= rhs;
    }
    constexpr Fraction operator*(const Fraction rhs) const noexcept {
        return Fraction(*this) *= rhs;
    }
    constexpr Fraction operator/(const Fraction rhs) const noexcept {
        return Fraction(*this) /= rhs;
    }
    constexpr Fraction &operator+=(const Fraction rhs) noexcept {
        const T l = std::lcm(y, rhs.y);
        x *= l / y;
        x += rhs.x * (l / rhs.y);
        y = l;
        const T g = std::gcd(x, y);
        x /= g;
        y /= g;
        return *this;
    }
    constexpr Fraction &operator-=(const Fraction rhs) noexcept {
        const T l = std::lcm(y, rhs.y);
        x *= l / y;
        x -= rhs.x * (l / rhs.y);
        y = l;
        return *this;
    }
    constexpr Fraction &operator*=(const Fraction rhs) noexcept {
        x *= rhs.x;
        y *= rhs.y;
        const T g = std::gcd(x, y);
        x /= g;
        y /= g;
        return *this;
    }
    constexpr Fraction &operator/=(Fraction rhs) noexcept {
        x *= rhs.y;
        y *= rhs.x;
        const T g = std::gcd(x, y);
        x /= g;
        y /= g;
        return *this;
    }
    bool operator==(const Fraction rhs) const noexcept {
        return x * rhs.y == y * rhs.x;
    }
    auto operator<=>(const Fraction rhs) const noexcept {
        return x * rhs.y <=> y * rhs.x;
    }
};
