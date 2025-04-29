#pragma once
#include <algorithm>
#include <data_structure/wavelet_matrix/bit_vector.hpp>
#include <vector>

template <typename T = int>
struct WaveletMatrix {
    std::vector<T> v;
    int n, m;
    std::vector<BitVector> b;
    WaveletMatrix(const std::vector<T>& _v) : v(_v), n(v.size()), m(std::__lg(std::max(1, *std::max_element(v.begin(), v.end()))) + 1), b(m, BitVector(n)) {
        std::vector<T> nxt(n);
        for (int i = m - 1; 0 <= i; --i) {
            for (int j = 0; j < n; ++j) {
                if ((v[j] >> i) & 1) {
                    b[m - i - 1].set(j);
                }
            }
            b[m - i - 1].build();
            int cnt[2] = {-1, b[m - i - 1].rank0(n) - 1};
            for (int j = 0; j < n; ++j) {
                nxt[++cnt[(v[j] >> i) & 1]] = v[j];
            }
            std::swap(v, nxt);
        }
    }

    T operator[](int p) {
        for (int i = 0; i < m; ++i) {
            if (b[i].get(p)) {
                p = b[i].zeros + b[i].rank1(p);
            } else {
                p = b[i].rank0(p);
            }
        }
        return v[p];
    }

    T small(int l, int r, int p);
};
