#pragma once
#include <data_structure/wavelet_matrix/base.hpp>

template <typename T>
T WaveletMatrix<T>::small(int l, int r, int p) {
    for (int i = 0; i < m; ++i) {
        int cnt = b[i].rank(false, r) - b[i].rank(false, l);
        if (cnt <= p) {
            p -= cnt;
            l = b[i].zero() + b[i].rank(true, l);
            r = b[i].zero() + b[i].rank(true, r);
        } else {
            l = b[i].rank(false, l);
            r = b[i].rank(false, r);
        }
    }
    return v[l];
}
