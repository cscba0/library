#pragma once

#define OVERLOAD_REP(_1, _2, _3, name, ...) name
#define REP1(i, n) for (auto i = 0; (i) < (n); ++(i))
#define REP2(i, l, r) for (auto i = (l); (i) < (r); ++(i))
#define rep(...) OVERLOAD_REP(__VA_ARGS__, REP2, REP1)(__VA_ARGS__)
#define rrep(i, r, l) for (auto i = r; (i) > (l); --(i))
