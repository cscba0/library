#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <algorithm>                                          // for reverse
#include <data_structure/tree/heavy_light_decomposition.hpp>  // for HeavyLi...
#include <fastio/base.hpp>                                    // for FASTIO
#include <fastio/char/write.hpp>                              // for operator<<
#include <fastio/signed/read.hpp>                             // for operator>>
#include <fastio/signed/write.hpp>                            // for operator<<
#include <fastio/vector/read.hpp>                             // for operator>>
#include <format>                                             // for vector
#include <templates/macro/abbrev/eb.hpp>                      // for eb
#include <templates/macro/abbrev/endl.hpp>                    // for endl
#include <templates/macro/abbrev/ll.hpp>                      // for ll
#include <templates/macro/segtree/RSQ.hpp>                    // for RSQ
#include <templates/rep.hpp>                                  // for rep
#include <templates/template.hpp>
#include <vector>  // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    vector<int> p(n - 1);
    cin >> a >> p;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        g[p[i]].eb(i + 1);
    }
    HeavyLightDecomposition<RSQ(ll, 0)> hld(g, a);
    rep(_, q) {
        int T, u;
        cin >> T >> u;
        if (T == 0) {
            int x;
            cin >> x;
            hld.add(u, x);
        } else {
            cout << hld.part(u) << endl;
        }
    }
}
