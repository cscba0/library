#pragma once

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define UNIQ(x) sort(x.begin(), x.end()), x.erase(unique(x.begin(), x.end()), x.end())
