#pragma once
#define RAMQ ll,                                       \
             [](ll a, ll b) { return max(a, b); },     \
             []() { return 0; },                       \
             ll,                                       \
             [](ll lz, ll v) { return lz + v; },       \
             [](ll cur, ll old) { return cur + old; }, \
             []() { return 0ll; }
