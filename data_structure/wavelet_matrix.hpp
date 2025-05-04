#pragma once
#include <immintrin.h>

#include <algorithm>
#include <cstdint>
#include <vector>

struct BitVector {
    static constexpr uint32_t w = 64;
    std::vector<uint64_t> block;
    std::vector<uint32_t> count;
    uint64_t n, zeros;

    inline uint64_t get(uint64_t i) const { return uint64_t(block[i / w] >> (i % w)) & 1u; }
    inline void set(uint64_t i) { block[i / w] |= 1LL << (i % w); }

    BitVector() {}
    BitVector(int _n) { init(_n); }
    void init(int _n) {
        n = zeros = _n;
        block.resize(n / w + 1, 0);
        count.resize(block.size(), 0);
    }

    __attribute__((target("popcnt"))) void build() {
        for (uint32_t i = 1; i < block.size(); ++i) {
            count[i] = count[i - 1] + _mm_popcnt_u64(block[i - 1]);
        }
        zeros = rank0(n);
    }

    inline uint32_t rank0(uint32_t i) const { return i - rank1(i); }
    __attribute__((target("bmi2,popcnt"))) inline uint32_t rank1(uint32_t i) const {
        return count[i / w] + _mm_popcnt_u64(_bzhi_u64(block[i / w], i % w));
    }
};

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
