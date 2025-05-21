#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <algorithm>  // for reverse
#include <data_structure/segment_tree.hpp>
#include <data_structure/tree/heavy_light_decomposition.hpp>  // for HeavyLightDecomposition
#include <fastio/base.hpp>                                    // for FASTIO, cin, cout
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
    cin >> a;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }
    HeavyLightDecomposition<SegmentTree<RSQ(ll, 0)>> hld(g, a);
    rep(_, q) {
        int T, u, v;
        cin >> T >> u >> v;
        if (T == 0) {
            hld.add(u, v);
        } else {
            cout << hld(u, v) << endl;
        }
    }
}
