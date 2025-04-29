#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

// 0-indexed, closed-interval bitvector supporting access, rank, and select
// rank(flag, r): number of bits equal to flag in [0..r]
// select(flag, k): position of the (k+1)-th occurrence of flag (0-indexed k). Returns -1 if not found.
struct BitVector {
    int n;                     // number of bits
    std::vector<bool> bits;    // underlying bit storage
    std::vector<int> prefix1;  // prefix sum of 1-bits
    std::vector<int> prefix0;  // prefix sum of 0-bits

    // Construct from a vector<bool>
    BitVector(const std::vector<bool>& v)
        : n(static_cast<int>(v.size())),
          bits(v),
          prefix1(n),
          prefix0(n) {
        int c1 = 0;
        for (int i = 0; i < n; ++i) {
            if (bits[i]) {
                ++c1;
            }
            prefix1[i] = c1;
            prefix0[i] = (i + 1) - c1;
        }
    }

    int zero() const {
        return prefix0[n - 1];
    }

    // Access bit at position p (0-indexed)
    // Throws if p is out of range
    int operator[](int p) const {
        if (p < 0 || p >= n) {
            throw std::out_of_range("BitVector::access: index out of range");
        }
        return bits[p] ? 1 : 0;
    }

    // Count of bits equal to flg in [0..r] (closed interval)
    // If r < 0 returns 0; if r >= n returns count over entire vector
    int rank(bool flg, int r) const {
        --r;
        if (r < 0) return 0;
        if (r >= n) r = n - 1;
        return flg ? prefix1[r] : prefix0[r];
    }

    // Position of the (k+1)-th occurrence of flg (0-indexed k)
    // Returns -1 if fewer than k+1 occurrences
    // Uses binary search on prefix sums: O(log n)
    int select(bool flg, int k) const {
        int target = k + 1;
        if (target <= 0) {
            throw std::invalid_argument("BitVector::select: k must be >= 0");
        }
        const auto& pref = flg ? prefix1 : prefix0;
        auto it = std::lower_bound(pref.begin(), pref.end(), target);
        if (it == pref.end()) {
            return -1;  // not found
        }
        return static_cast<int>(std::distance(pref.begin(), it));
    }
};
