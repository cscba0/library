#pragma once
#include <cstdint>
#include <fastio/base.hpp>

inline FASTIO& operator>>(FASTIO& io, __int128& x) noexcept {
    io.seek();
    bool neg = false;
    if (*io.ipos == '-') {
        neg = true;
        ++io.ipos;
    }
    __int128 y = 0;
    while (true) {
        uint64_t v;
        memcpy(&v, io.ipos, 8);
        if (v ^= 0x3030303030303030, !(v & 0xf0f0f0f0f0f0f0f0)) {
            v = (v * 10 + (v >> 8)) & 0xff00ff00ff00ff;
            v = (v * 100 + (v >> 16)) & 0xffff0000ffff;
            v = (v * 10000 + (v >> 32)) & 0xffffffff;
            y = 100000000 * y + v;
            io.ipos += 8;
        } else {
            break;
        }
    }
    {
        uint32_t v;
        memcpy(&v, io.ipos, 4);
        if (v ^= 0x30303030, !(v & 0xf0f0f0f0)) {
            v = (v * 10 + (v >> 8)) & 0xff00ff;
            v = (v * 100 + (v >> 16)) & 0xffff;
            y = 10000 * y + v;
            io.ipos += 4;
        }
    }
    {
        uint16_t v;
        memcpy(&v, io.ipos, 2);
        if (v ^= 0x3030, !(v & 0xf0f0)) {
            v = (v * 10 + (v >> 8)) & 0xff;
            y = 100 * y + v;
            io.ipos += 2;
        }
    }
    if (' ' < *io.ipos) {
        y = y * 10 + *io.ipos++ - '0';
    }
    ++io.ipos;
    x = static_cast<__int128>(y);
    if (neg) {
        x = -x;
    }
    return io;
}
