#pragma once
#include <cstdint>

template <int64_t Modulus>
struct modint {
    int64_t x;
    constexpr modint(const int64_t x = 0) noexcept : x(x % Modulus) {}
    constexpr modint operator+(const modint rhs) const noexcept {
        return modint(*this) += rhs;
    }
    constexpr modint operator-(const modint rhs) const noexcept {
        return modint(*this) -= rhs;
    }
    constexpr modint operator*(const modint rhs) const noexcept {
        return modint(*this) *= rhs;
    }
    constexpr modint operator/(const modint rhs) const noexcept {
        return modint(*this) /= rhs;
    }
    constexpr modint &operator+=(const modint rhs) noexcept {
        x += rhs.x;
        if (x >= Modulus) {
            x -= Modulus;
        }
        return *this;
    }
    constexpr modint &operator-=(const modint rhs) noexcept {
        if (x < rhs.x) {
            x += Modulus;
        }
        x -= rhs.x;
        return *this;
    }
    constexpr modint &operator*=(const modint rhs) noexcept {
        x = x * rhs.x % Modulus;
        return *this;
    }
    constexpr modint &operator/=(modint rhs) noexcept {
        *this *= rhs.pow(Modulus - 2);
        return *this;
    }
    constexpr modint pow(int64_t t) const noexcept {
        modint a = *this, res = 1;
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
