#pragma once
#include <cstdint>
#include <cstring>
#include <fastio/base.hpp>

constexpr bool FastAllDigit(uint64_t x) {
    return !(~x & 0x1010101010101010);
}

constexpr bool FastAllDigit(uint32_t x) {
    return !(~x & 0x10101010);
}

template <std::unsigned_integral T>
inline FASTIO& operator>>(FASTIO& io, T& x) noexcept {
    io.seek();
    uint64_t x_{};
    union {
        char c[16];
        uint64_t d[2];
    };
    memcpy(c, io.ipos, 16);
    uint64_t a = d[0], b = d[1];
    if (FastAllDigit(a)) {
        a ^= 0x3030303030303030;
        a = (a * 10 + (a >> 8)) & 0x00ff00ff00ff00ff;
        a = (a * 100 + (a >> 16)) & 0x0000ffff0000ffff;
        a = (a * 10000 + (a >> 32)) & 0x00000000ffffffff;
        x_ = a, io.ipos += 8;
        if (FastAllDigit(b)) {
            b ^= 0x3030303030303030;
            b = (b * 10 + (b >> 8)) & 0x00ff00ff00ff00ff;
            b = (b * 100 + (b >> 16)) & 0x0000ffff0000ffff;
            b = (b * 10000 + (b >> 32)) & 0x00000000ffffffff;
            x_ = a * 100000000 + b, io.ipos += 8;
        }
    }
    for (; *io.ipos > 47; ++io.ipos) x_ = x_ * 10 + *io.ipos - 48;
    ++io.ipos;
    x = static_cast<T>(x_);
    return io;
}
