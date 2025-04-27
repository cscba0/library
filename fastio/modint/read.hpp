#pragma once
#include <fastio/signed/read.hpp>
#include <math/modint.hpp>

template <int64_t M>
inline FASTIO& operator>>(FASTIO& io, Modint<M>& x) {
    io >> x.x;
    x.x %= M;
    return io;
}
