#pragma once
#define RASQ(T, E, S, I) pair<T, int>,                                                                                                         \
                         [](pair<T, int> a, pair<T, int> b) -> pair<T, int> { return {a.first + b.first, a.second + b.second}; },              \
                         []() -> pair<T, int> { return {E, 0}; },                                                                              \
                         S,                                                                                                                    \
                         [](S lz, pair<T, int> v) -> pair<T, int> { return (lz == I ? v : pair<T, int>(v.first + lz * v.second, v.second)); }, \
                         [](S cur, S old) -> S { return cur + old; },                                                                          \
                         []() -> S { return I; }
