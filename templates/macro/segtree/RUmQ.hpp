#pragma once
#include <templates/macro/inf.hpp>

#define RUmQ(T, E, S, I) T,                                       \
                         [](T a, T b) -> T { return min(a, b); }, \
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
