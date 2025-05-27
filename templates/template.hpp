#pragma once
#ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#else
#include <ranges>
#endif
using namespace std;
using namespace std::views;
