#pragma once
#include <templates/macro/inf.hpp>

#define RmQ ll, [](ll a, ll b) { return min(a, b); }, []() { return INF; }
