#pragma once
#include <bit>
#include <fastio/signed/read.hpp>

inline FASTIO& operator>>(FASTIO& io, long double& x) noexcept {
    io.seek();
    x = 0;
    while ('0' <= *io.ipos and *io.ipos <= '9') {
        x = x * 10 + *io.ipos++ - '0';
    }
    if (*io.ipos != '.') {
        return io;
    }
    ++io.ipos;
    long double p = 1;
    while (true) {
        uint64_t cur = *reinterpret_cast<uint64_t*>(io.ipos);
        uint8_t cnt = std::countr_zero((~cur >> 4) & 0x0101010101010101);
        cur <<= 64 - cnt;
        cur &= 0x0f0f0f0f0f0f0f0f;
        cur = (cur * 10 + (cur >> 8)) & 0x00ff00ff00ff00ff;
        cur = (cur * 100 + (cur >> 16)) & 0x0000ffff0000ffff;
        cur = (cur * 10000 + (cur >> 32)) & 0x00000000ffffffff;
        if (cnt == 64) {
            p *= 1000000000;
            x += static_cast<long double>(cur) / p;
            io.ipos += 8;
        } else {
            break;
        }
    }
    for (; '0' <= *io.ipos && *io.ipos <= '9'; ++io.ipos) {
        p *= 10;
        x += (*io.ipos - '0') / p;
    }
    return io;
}
FASTIO& operator>>(FASTIO& io, double& x) {
    long double l;
    io >> l;
    x = l;
    return io;
}
FASTIO& operator>>(FASTIO& io, float& x) {
    long double l;
    io >> l;
    x = l;
    return io;
}
