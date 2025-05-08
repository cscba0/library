#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <data_structure/strong_link_cut_tree.hpp>  // for StrongLinkCutTree
#include <fastio/base.hpp>                          // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                    // for operator<<
#include <fastio/signed/read.hpp>                   // for operator>>
#include <fastio/signed/write.hpp>                  // for operator<<
#include <format>                                   // for vector
#include <templates/macro/abbrev/eb.hpp>            // for eb
#include <templates/macro/abbrev/endl.hpp>          // for endl
#include <templates/macro/segtree/RSQ.hpp>          // for RSQ
#include <templates/rep.hpp>                        // for rep
#include <templates/template.hpp>
#include <vector>                                   // for vector

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    rep(i, 1, n) {
        int u;
        cin >> u;
        g[u].eb(i);
    }
    StrongLinkCutTree<RSQ(int, 0)> lct(g);
    rep(_, q) {
        int u, v;
        cin >> u >> v;
        cout << lct.lca(u, v) << endl;
    }
}
