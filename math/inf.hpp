#pragma once

template <typename T = int>
struct INF {
    operator int() const {
        return 2147483647;
    }
    operator long() const {
        return 9223372036854775807L;
    }
    operator long long() const {
        return 9223372036854775807LL;
    }
};
