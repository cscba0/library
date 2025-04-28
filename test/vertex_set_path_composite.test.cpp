#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <algorithm>                           // for reverse
#include <fastio/base.hpp>                     // for FASTIO, cin, cout
#include <fastio/char/write.hpp>               // for operator<<
#include <fastio/pair/read.hpp>                // for operator>>
#include <fastio/signed/read.hpp>              // for operator>>
#include <fastio/unsigned/read.hpp>            // for operator>>
#include <fastio/unsigned/write.hpp>           // for operator<<
#include <fastio/vector/read.hpp>              // for operator>>
#include <format>                              // for vector
#include <iterator>                            // for pair
#include <templates/macro/abbrev/eb.hpp>       // for eb
#include <templates/macro/abbrev/endl.hpp>     // for endl
#include <templates/macro/abbrev/mp.hpp>       // for MP
#include <templates/macro/abbrev/ull.hpp>      // for ull
#include <templates/macro/mod.hpp>             // for MOD1
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>                   // for rep
#include <tree/heavy_light_decomposition.hpp>  // for HeavyLightDecomposition
#include <type_traits>                         // for __decay_and_strip
#include <utility>                             // for pair, make_pair
#include <vector>                              // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<ull, ull>> a(n);
    cin >> a;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }
    HeavyLightDecomposition<pair<ull, ull>,
                            [](pair<ull, ull> a, pair<ull, ull> b) {
                                return MP(a.first * b.first % MOD1, (a.second * b.first + b.second) % MOD1);
                            },
                            []() { return MP(1, 0); }>
        hld(g, a);
    rep(_, q) {
        int T, u, v, x;
        cin >> T >> u >> v >> x;
        if (T == 0) {
            hld.set(u, {v, x});
        } else {
            auto it = hld(u, v);
            ull ans = (it.first * x) + it.second;
            ans %= MOD1;
            cout << ans << endl;
        }
    }
}
