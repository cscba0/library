#pragma once
#include <data_structure/wavelet_matrix/bit_vector.hpp>
#include <vector>

template <typename T = int>
struct WaveletMatrix {
    std::vector<T> v;
    int n, m;
    std::vector<BitVector> b;
    WaveletMatrix(const std::vector<T>& _v) : v(_v), n(v.size()), m(std::__lg(std::max(1, *std::max_element(v.begin(), v.end()))) + 1) {
        std::vector<bool> B(n);
        std::vector<T> nxt(n);
        b.reserve(m);
        for (int i = m - 1; 0 <= i; --i) {
            for (int j = 0; j < n; ++j) {
                B[j] = (v[j] >> i) & 1;
            }
            b.emplace_back(BitVector(B));
            int cnt[2] = {-1, b.back().zero() - 1};
            for (int j = 0; j < n; ++j) {
                nxt[++cnt[(v[j] >> i) & 1]] = v[j];
            }
            std::swap(v, nxt);
        }
    }

    T operator[](int p) {
        for (int i = 0; i < m; ++i) {
            if (b[i][p]) {
                p = b[i].zero() + b[i].rank(true, p);
            } else {
                p = b[i].rank(false, p);
            }
        }
        return v[p];
    }

    T small(int l, int r, int p);
};
