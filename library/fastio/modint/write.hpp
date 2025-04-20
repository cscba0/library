#pragma once
#include <library/data_structure/modint.hpp>
#include <library/fastio/signed/write.hpp>

template <long long M>
inline FASTIO& operator<<(FASTIO& io, modint<M> x) {
    io << x.x;
    return io;
}
