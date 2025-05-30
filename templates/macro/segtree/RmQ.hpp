#pragma once

#define RmQ(T, E) T, [](T a, T b) -> T { return min(a, b); }, []() -> T { return E; }
