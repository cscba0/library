#pragma once
#define RAMQ(T, E, S, I) T,                                           \
                         [](T a, T b) -> T { return max(a, b); },     \
                         []() -> T { return E; },                     \
                         S,                                           \
                         [](S lz, T v) -> T { return lz + v; },       \
                         [](S cur, S old) -> S { return cur + old; }, \
                         []() -> S { return I; }
