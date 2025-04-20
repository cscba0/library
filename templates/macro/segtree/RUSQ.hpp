#pragma once
#include <templates/macro/inf.hpp>

#define RUSQ pair<ll, ll>,                                                                                            \
             [](pair<ll, ll> a, pair<ll, ll> b) -> pair<ll, ll> { return {a.first + b.first, a.second + b.second}; }, \
             []() -> pair<ll, ll> { return {0ll, 0ll}; },                                                             \
             ll,                                                                                                      \
             [](ll lz, pair<ll, ll> v) { return (lz == INF ? v : make_pair(lz * v.second, v.second)); },              \
             [](ll cur, ll old) { return (cur == INF ? old : cur); },                                                 \
             []() { return INF; }
