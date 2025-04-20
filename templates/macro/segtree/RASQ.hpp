#pragma once
#include <templates/macro/inf.hpp>

#define RASQ pair<ll, ll>,                                                                                            \
             [](pair<ll, ll> a, pair<ll, ll> b) -> pair<ll, ll> { return {a.first + b.first, a.second + b.second}; }, \
             []() -> pair<ll, ll> { return {0ll, 0ll}; },                                                             \
             ll,                                                                                                      \
             [](ll lz, pair<ll, ll> v) { return (lz == INF ? v : make_pair(v.first + lz * v.second, v.second)); },    \
             [](ll cur, ll old) { return cur + old; },                                                                \
             []() { return 0ll; }
