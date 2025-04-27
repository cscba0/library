#pragma once
#include <cstdint>
#include <string>
#include <vector>

constexpr int64_t RollingHashSize = 30;
constexpr int64_t RollingHashMod1 = 998244353;
constexpr int64_t RollingHashMod2 = 888528229;

static std::vector<int64_t> RollingHashPowTable1, RollingHashPowTable2;

struct RollingHash {
    int64_t x, y;
    int64_t l;

    RollingHash() : x(0), y(0), l(0) {}
    RollingHash(int64_t _v) : x(_v % RollingHashMod1), y(_v % RollingHashMod2), l(1) {}
    RollingHash(int64_t _v, int64_t _l) : x(_v % RollingHashMod1), y(_v % RollingHashMod2), l(_l) {}
    RollingHash(char C) : RollingHash(std::string(1, C)) {}
    RollingHash(const std::string &S) : x(f(S)), y(g(S)), l(S.size()) {}

    static int64_t f(const std::string &S) {
        int64_t res = 0;
        for (char c : S) {
            res = (res * RollingHashSize + (c - 'a' + 1)) % RollingHashMod1;
        }
        return res;
    }

    static int64_t g(const std::string &S) {
        int64_t res = 0;
        for (char c : S) {
            res = (res * RollingHashSize + (c - 'a' + 1)) % RollingHashMod2;
        }
        return res;
    }

    static int64_t pow1(size_t x) {
        while (RollingHashPowTable1.size() <= x) {
            if (RollingHashPowTable1.empty()) {
                RollingHashPowTable1.emplace_back(1);
            }
            RollingHashPowTable1.emplace_back((RollingHashPowTable1.back() * RollingHashSize) % RollingHashMod1);
        }
        return RollingHashPowTable1[x];
    }

    static int64_t pow2(size_t x) {
        while (RollingHashPowTable2.size() <= x) {
            if (RollingHashPowTable2.empty()) {
                RollingHashPowTable2.emplace_back(1);
            }
            RollingHashPowTable2.emplace_back((RollingHashPowTable2.back() * RollingHashSize) % RollingHashMod2);
        }
        return RollingHashPowTable2[x];
    }

    RollingHash &operator+=(const RollingHash &rhs) {
        x = (x * pow1(rhs.l) + rhs.x) % RollingHashMod1;
        y = (y * pow2(rhs.l) + rhs.y) % RollingHashMod2;
        l += rhs.l;
        return *this;
    }

    RollingHash operator+(const RollingHash &rhs) const {
        RollingHash res = *this;
        res += rhs;
        return res;
    }

    bool operator==(const RollingHash &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};
