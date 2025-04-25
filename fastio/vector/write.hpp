#pragma once
#include <fastio/base.hpp>
#include <templates/vector_output.hpp>
#include <vector>

template <typename T>
inline FASTIO& operator<<(FASTIO& os, const std::vector<T>& v) {
    for (uint i = 0, siz = v.size(); i < siz; ++i) {
        os << v[i] << (i + 1 == siz ? "" : " ");
    }
    return os;
}

template <typename T>
inline FASTIO& operator<<(FASTIO& io, const vector_output<T>& v) noexcept {
    for (auto& x : v.v) {
        io << x << v.s;
    }
    return io;
}
