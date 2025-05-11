#pragma once
#include <cstdint>

template <int64_t Mod>
struct Modint {
    int64_t x;
    constexpr Modint(const int64_t x = 0) noexcept : x(x % Mod) {}
    constexpr Modint operator+(const Modint rhs) const noexcept {
        return Modint(*this) += rhs;
    }
    constexpr Modint operator-(const Modint rhs) const noexcept {
        return Modint(*this) -= rhs;
    }
    constexpr Modint &operator-() noexcept {
        if (x != 0) {
            x = -x + Mod;
        }
        return *this;
    }
    constexpr Modint operator*(const Modint rhs) const noexcept {
        return Modint(*this) *= rhs;
    }
    constexpr Modint operator/(const Modint rhs) const noexcept {
        return Modint(*this) /= rhs;
    }
    constexpr Modint &operator+=(const Modint rhs) noexcept {
        x += rhs.x;
        if (x >= Mod) {
            x -= Mod;
        }
        return *this;
    }
    constexpr Modint &operator-=(const Modint rhs) noexcept {
        if (x < rhs.x) {
            x += Mod;
        }
        x -= rhs.x;
        return *this;
    }
    constexpr Modint &operator*=(const Modint rhs) noexcept {
        x = (x * rhs.x) % Mod;
        return *this;
    }
    constexpr Modint &operator/=(Modint rhs) noexcept {
        *this *= rhs.pow(Mod - 2);
        return *this;
    }
    constexpr Modint pow(int64_t n) const noexcept {
        Modint a = *this, res = 1;
        while (n) {
            if (n & 1) {
                res *= a;
            }
            a *= a;
            n >>= 1;
        }
        return res;
    }
};
