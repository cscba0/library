#pragma once
#include <templates/macro/inf.hpp>

#define RUMQ ll,                                                      \
             [](ll a, ll b) { return max(a, b); },                    \
             []() { return -INF; },                                   \
             ll,                                                      \
             [](ll lz, ll v) { return (lz == INF ? v : lz); },        \
             [](ll cur, ll old) { return (cur == INF ? old : cur); }, \
             []() { return INF; }
