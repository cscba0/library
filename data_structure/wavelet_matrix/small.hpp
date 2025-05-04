#pragma once
#include <data_structure/wavelet_matrix.hpp>

template <typename T>
T WaveletMatrix<T>::small(int l, int r, int p) {
    for (int i = 0; i < m; ++i) {
        int cnt = b[i].rank0(r) - b[i].rank0(l);
        if (cnt <= p) {
            p -= cnt;
            l = b[i].zeros + b[i].rank1(l);
            r = b[i].zeros + b[i].rank1(r);
        } else {
            l = b[i].rank0(l);
            r = b[i].rank0(r);
        }
    }
    return v[l];
}
