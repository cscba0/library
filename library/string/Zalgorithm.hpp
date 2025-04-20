#pragma once
#include <cstdint>
#include <string>
#include <vector>

inline std::vector<int> Zalgorithm(const std::string& s) noexcept {
    std::vector<int> Z(s.size());
    Z[0] = s.size();
    for (uint32_t i = 1, j = 0, siz = s.size(); i < siz;) {
        while (i + j < s.size() && s[j] == s[i + j]) {
            ++j;
        }
        Z[i] = j;
        if (j == 0) {
            ++i;
        } else {
            uint k = 1;
            for (; k < j && k + Z[k] < j; ++k) {
                Z[i + k] = Z[k];
            }
            i += k;
            j -= k;
        }
    }
    return Z;
}
