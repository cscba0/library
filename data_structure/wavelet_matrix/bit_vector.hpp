#pragma once
#include <immintrin.h>

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
