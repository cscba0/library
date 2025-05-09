#pragma once
#include <cstdint>

struct DynamicModint {
    static int64_t Mod;
    int64_t x;
    static void set_mod(int64_t M) {
        Mod = M;
    }
    DynamicModint(const int64_t x = 0) noexcept : x(x % Mod) {}
    DynamicModint operator+(const DynamicModint rhs) const noexcept {
        return DynamicModint(*this) += rhs;
    }
    DynamicModint operator-(const DynamicModint rhs) const noexcept {
        return DynamicModint(*this) -= rhs;
    }
    DynamicModint &operator-() noexcept {
        if (x != 0) {
            x = -x + Mod;
        }
        return *this;
    }
    DynamicModint operator*(const DynamicModint rhs) const noexcept {
        return DynamicModint(*this) *= rhs;
    }
    DynamicModint operator/(const DynamicModint rhs) const noexcept {
        return DynamicModint(*this) /= rhs;
    }
    DynamicModint &operator+=(const DynamicModint rhs) noexcept {
        x += rhs.x;
        if (x >= Mod) {
            x -= Mod;
        }
        return *this;
    }
    DynamicModint &operator-=(const DynamicModint rhs) noexcept {
        if (x < rhs.x) {
            x += Mod;
        }
        x -= rhs.x;
        return *this;
    }
    DynamicModint &operator*=(const DynamicModint rhs) noexcept {
        x = x * rhs.x % Mod;
        return *this;
    }
    DynamicModint &operator/=(DynamicModint rhs) noexcept {
        *this *= rhs.pow(Mod - 2);
        return *this;
    }
    DynamicModint pow(int64_t n) const noexcept {
        DynamicModint a = *this, res = 1;
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
int64_t DynamicModint::Mod{9982443543};
