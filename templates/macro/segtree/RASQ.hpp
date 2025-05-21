#pragma once
#define RASQ(T, E, S, I, _INF) pair<T, int>,                                                                                            \
                               [](pair<T, int> a, pair<T, int> b) -> pair<T, int> { return {a.first + b.first, a.second + b.second}; }, \
                               []() -> pair<T, int> { return {E, 0}; },                                                                 \
                               S,                                                                                                       \
                               [](S lz, pair<T, int> v) { return (lz == _INF ? v : make_pair(v.first + lz * v.second, v.second)); },    \
                               [](S cur, S old) { return cur + old; },                                                                  \
                               []() { return I; }
