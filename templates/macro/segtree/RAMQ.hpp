#pragma once
#define RAMQ(T, E, S, I) T,                                      \
                         [](T a, T b) { return max(a, b); },     \
                         []() { return E; },                     \
                         S,                                      \
                         [](S lz, T v) { return lz + v; },       \
                         [](S cur, S old) { return cur + old; }, \
                         []() { return I; }
