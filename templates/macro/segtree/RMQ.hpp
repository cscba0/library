#pragma once

#define RMQ(T, E) T, [](T a, T b) -> T { return max(a, b); }, []() -> T { return E; }
