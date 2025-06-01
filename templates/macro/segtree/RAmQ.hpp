#pragma once
#define RAmQ(T, E, S, I) T,                                           \
                         [](T a, T b) -> T { return min(a, b); },     \
                         []() -> T { return E; },                     \
                         S,                                           \
                         [](S lz, T v) -> T { return lz + v; },       \
                         [](S cur, S old) -> S { return cur + old; }, \
                         []() -> S { return I; }
