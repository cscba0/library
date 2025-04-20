#pragma once
#include <data_structure/modint.hpp>
#include <fastio/signed/read.hpp>

template <long long M>
inline FASTIO& operator>>(FASTIO& io, modint<M>& x) {
    io >> x.x;
    return io;
}
