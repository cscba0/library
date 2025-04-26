#pragma once
#include <fastio/base.hpp>

template <std::floating_point T>
inline FASTIO& operator>>(FASTIO& io, T& x) noexcept {
    io.seek();
    x = 0;
    bool neg = false;
    if (*io.ipos == '-') {
        neg = true;
        ++io.ipos;
    }
    while ('.' < *io.ipos) {
        x = x * 10 + *io.ipos++ - '0';
    }
    if (*io.ipos == '.') {
        ++io.ipos;
        T y = 10;
        while (' ' < *io.ipos) {
            x += (*io.ipos++ - '0') / y;
            y *= 10;
        }
    }
    if (neg) {
        x = -x;
    }
    ++io.ipos;
    return io;
}
