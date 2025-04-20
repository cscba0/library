#pragma once
#include <templates/macro/inf.hpp>

#define RAmQINF ll,                                       \
                [](ll a, ll b) { return min(a, b); },     \
                []() { return INF; },                     \
                ll,                                       \
                [](ll lz, ll v) { return lz + v; },       \
                [](ll cur, ll old) { return cur + old; }, \
                []() { return 0ll; }
