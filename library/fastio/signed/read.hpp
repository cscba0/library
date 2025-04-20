#pragma once
#include <library/fastio/unsigned/read.hpp>

template <std::signed_integral T>
inline FASTIO& operator>>(FASTIO& io, T& x) noexcept {
    io.seek();
    x = 0;
    bool neg = false;
    if (*io.ipos == '-') {
        neg = true;
        ++io.ipos;
    }
    std::make_unsigned_t<T> u;
    io >> u;
    x = u;
    if (neg) {
        x = -x;
    }
    return io;
}
