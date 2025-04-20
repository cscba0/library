#pragma once
#include <library/fastio/base.hpp>
#include <templates/vector_output.hpp>
#include <vector>

template <typename T>
inline FASTIO& operator<<(FASTIO& io, std::vector<T>& v) noexcept {
    for (size_t i = 0, size = v.size(); i < size; ++i) {
        io << v[i] << " \n"[i + 1 == size];
    }
    return io;
}

template <typename T>
inline FASTIO& operator<<(FASTIO& io, const vector_output<T>& v) noexcept {
    for (auto& x : v.v) {
        io << x << v.s;
    }
    return io;
}
