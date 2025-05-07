#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <data_structure/link_cut_tree.hpp>  // for LinkCutTree
#include <fastio/base.hpp>                   // for FASTIO, cin, cout
#include <fastio/char/write.hpp>             // for operator<<
#include <fastio/pair/read.hpp>              // for operator>>
#include <fastio/signed/read.hpp>            // for operator>>
#include <fastio/unsigned/read.hpp>          // for operator>>
#include <fastio/unsigned/write.hpp>         // for operator<<
#include <fastio/vector/read.hpp>            // for operator>>
#include <iterator>                          // for pair
#include <templates/macro/abbrev/endl.hpp>   // for endl
#include <templates/macro/abbrev/ll.hpp>     // for ll
#include <templates/macro/abbrev/mp.hpp>     // for MP
#include <templates/macro/abbrev/ull.hpp>    // for ull
#include <templates/macro/mod.hpp>           // for MOD1
#include <templates/rep.hpp>                 // for rep
#include <templates/template.hpp>
#include <utility>                           // for pair, make_pair
#include <vector>                            // for vector

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<ull, ull>> a(n);
    cin >> a;
    LinkCutTree<pair<ull, ull>,
                [](pair<ull, ull> a, pair<ull, ull> b) {
                    return MP(a.first * b.first % MOD1, (a.second * b.first + b.second) % MOD1);
                },
                []() -> pair<ull, ull> { return {1, 0}; }>
        t;
    rep(i, n) {
        t.add(a[i]);
    }
    rep(_, n - 1) {
        int u, v;
        cin >> u >> v;
        t.link(u, v);
    }
    rep(_, q) {
        int T;
        cin >> T;
        if (T == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            t.cut(u, v);
            t.link(w, x);
        } else if (T == 1) {
            int p;
            ll c, d;
            cin >> p >> c >> d;
            t.set(p, {c, d});
        } else {
            int u, v;
            ll x;
            cin >> u >> v >> x;
            pair<ull, ull> ans = t(u, v);
            cout << ((ans.first * x) + ans.second) % MOD1 << endl;
        }
    }
}
