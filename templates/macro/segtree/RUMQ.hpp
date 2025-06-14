#pragma once

#define RUMQ(T, E, S, I) T,                                       \
                         [](T a, T b) -> T { return max(a, b); }, \
                         []() { return E; },                      \
                         S,                                       \
                         [](S lz, T v) -> T {                     \
                             if (lz == I) {                       \
                                 return v;                        \
                             }                                    \
                             return lz;                           \
                         },                                       \
                         [](S cur, S old) -> S {                  \
                             if (cur == I) {                      \
                                 return old;                      \
                             }                                    \
                             return cur;                          \
                         },                                       \
                         []() { return I; }
