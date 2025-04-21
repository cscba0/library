#pragma once
#include <data_structure/modint.hpp>
#include <fastio/signed/write.hpp>

template <int64_t M>
inline FASTIO& operator<<(FASTIO& io, ModInt<M> x) {
    io << x.x;
    return io;
}
