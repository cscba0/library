#pragma once
#define RSQ(T, E) T, [](T a, T b) { return a + b; }, []() -> T { return E; }
