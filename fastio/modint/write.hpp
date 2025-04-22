#pragma once
#include <fastio/signed/write.hpp>
#include <math/modint.hpp>

template <int64_t M>
inline FASTIO& operator<<(FASTIO& io, Modint<M> x) {
    io << x.x;
    return io;
}
