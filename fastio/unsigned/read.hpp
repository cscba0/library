#pragma once
#include <cstdint>
#include <cstring>
#include <fastio/base.hpp>

template <std::unsigned_integral T>
inline FASTIO& operator>>(FASTIO& io, T& x) noexcept {
    io.seek();
    std::common_type_t<T, uint64_t> y = 0;
    if (io.ipos + 8 <= io.iend) {
        uint64_t v;
        memcpy(&v, io.ipos, 8);
        if (!((v -= 0x3030303030303030) & 0x8080808080808080)) {
            v = (v * 10 + (v >> 8)) & 0xff00ff00ff00ff;
            v = (v * 100 + (v >> 16)) & 0xffff0000ffff;
            v = (v * 10000 + (v >> 32)) & 0xffffffff;
            y = 100000000 * y + v;
            io.ipos += 8;
        }
    }
    if (io.ipos + 8 <= io.iend) {
        uint64_t v;
        memcpy(&v, io.ipos, 8);
        if (!((v -= 0x3030303030303030) & 0x8080808080808080)) {
            v = (v * 10 + (v >> 8)) & 0xff00ff00ff00ff;
            v = (v * 100 + (v >> 16)) & 0xffff0000ffff;
            v = (v * 10000 + (v >> 32)) & 0xffffffff;
            y = 100000000 * y + v;
            io.ipos += 8;
        }
    }
    if (io.ipos + 4 <= io.iend) {
        uint32_t v;
        memcpy(&v, io.ipos, 4);
        if (!((v -= 0x30303030) & 0x80808080)) {
            v = (v * 10 + (v >> 8)) & 0xff00ff;
            v = (v * 100 + (v >> 16)) & 0xffff;
            y = 10000 * y + v;
            io.ipos += 4;
        }
    }
    if (io.ipos + 2 <= io.iend) {
        uint16_t v;
        memcpy(&v, io.ipos, 2);
        if (!((v -= 0x3030) & 0x8080)) {
            v = (v * 10 + (v >> 8)) & 0xff;
            y = 100 * y + v;
            io.ipos += 2;
        }
    }
    while (io.ipos != io.iend && ' ' < *io.ipos) {
        y = y * 10 + *io.ipos++ - '0';
    }
    ++io.ipos;
    x = static_cast<T>(y);
    return io;
}
