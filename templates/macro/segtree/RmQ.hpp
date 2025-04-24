#pragma once
#include <templates/macro/inf.hpp>

#define RmQ(T, E) T, [](T a, T b) { return min(a, b); }, []() -> T { return E; }
