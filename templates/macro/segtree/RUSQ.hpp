#pragma once

#define RUSQ(T, E, S, I) pair<T, int>,                                                                                               \
                         [](pair<T, int> a, pair<T, int> b) -> pair<T, int> { return {a.first + b.first, a.second + b.second}; },    \
                         []() -> pair<T, int> { return {E, 0}; },                                                                    \
                         S,                                                                                                          \
                         [](S lz, pair<T, int> v) -> pair<T, int> { return (lz == I ? v : pair<T, int>(lz * v.second, v.second)); }, \
                         [](S cur, S old) -> S { return (cur == I ? old : cur); },                                                   \
                         []() -> S { return I; }
