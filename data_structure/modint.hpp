#pragma once
#include <cstdint>

template <int64_t Mod>
struct ModInt {
    int64_t x;
    constexpr ModInt(const int64_t x = 0) noexcept : x(x % Mod) {}
    constexpr ModInt operator+(const ModInt rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    constexpr ModInt operator-(const ModInt rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    constexpr ModInt &operator-() noexcept {
        x = -x + Mod;
        return *this;
    }
    constexpr ModInt operator*(const ModInt rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    constexpr ModInt operator/(const ModInt rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }
    constexpr ModInt &operator+=(const ModInt rhs) noexcept {
        x += rhs.x;
        if (x >= Mod) {
            x -= Mod;
        }
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt rhs) noexcept {
        if (x < rhs.x) {
            x += Mod;
        }
        x -= rhs.x;
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt rhs) noexcept {
        x = x * rhs.x % Mod;
        return *this;
    }
    constexpr ModInt &operator/=(ModInt rhs) noexcept {
        *this *= rhs.pow(Mod - 2);
        return *this;
    }
    constexpr ModInt pow(int64_t t) const noexcept {
        ModInt a = *this, res = 1;
        while (t) {
            if (t & 1) {
                res *= a;
            }
            a *= a;
            t >>= 1;
        }
        return res;
    }
};
