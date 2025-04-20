#pragma once

#define RMQ(T, E) T, [](T a, T b) { return max(a, b); }, []() -> T { return E; }
