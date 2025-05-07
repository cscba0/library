#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include <data_structure/link_cut_tree.hpp>  // for LinkCutTree
#include <fastio/base.hpp>                   // for FASTIO, cin, cout
#include <fastio/char/write.hpp>             // for operator<<
#include <fastio/signed/read.hpp>            // for operator>>
#include <fastio/signed/write.hpp>           // for operator<<
#include <fastio/vector/read.hpp>            // for operator>>
#include <templates/macro/abbrev/endl.hpp>   // for endl
#include <templates/macro/abbrev/ll.hpp>     // for ll
#include <templates/macro/segtree/RSQ.hpp>   // for RSQ
#include <templates/rep.hpp>                 // for rep
#include <templates/template.hpp>
#include <vector>                            // for vector

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    LinkCutTree<RSQ(ll, 0)> t;
    rep(i, n) {
        t.add(a[i]);
    }
    rep(_, n - 1) {
        int u, v;
        cin >> u >> v;
        t.link(u, v);
    }
    rep(_, q) {
        ll T, u, v;
        cin >> T >> u >> v;
        if (T == 0) {
            ll w, x;
            cin >> w >> x;
            t.cut(u, v);
            t.link(w, x);
        } else if (T == 1) {
            t.set(u, t[u] + v);
        } else {
            ll ans = t(u, v);
            cout << ans << endl;
        }
    }
}
