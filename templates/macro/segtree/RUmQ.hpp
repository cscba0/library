#pragma once
#include <templates/macro/inf.hpp>

#define RUmQ ll,                                                      \
             [](ll a, ll b) { return min(a, b); },                    \
             []() { return INF; },                                    \
             ll,                                                      \
             [](ll lz, ll v) { return (lz == INF ? v : lz); },        \
             [](ll cur, ll old) { return (cur == INF ? old : cur); }, \
             []() { return INF; }
