#pragma once
#include <templates/macro/inf.hpp>

#define RAMQINF ll,                                       \
                [](ll a, ll b) { return max(a, b); },     \
                []() { return -INF; },                    \
                ll,                                       \
                [](ll lz, ll v) { return lz + v; },       \
                [](ll cur, ll old) { return cur + old; }, \
                []() { return 0ll; }
