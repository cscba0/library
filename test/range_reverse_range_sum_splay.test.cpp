#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include <data_structure/splay_tree.hpp>    // for SplayTree
#include <fastio/base.hpp>                  // for FASTIO, cin, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/signed/read.hpp>           // for operator>>
#include <fastio/signed/write.hpp>          // for operator<<
#include <fastio/vector/read.hpp>           // for operator>>
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/abbrev/ll.hpp>    // for ll
#include <templates/macro/segtree/RSQ.hpp>  // for RSQ
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <vector>  // for vector

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;

    using splay = SplayTree<RSQ(ll, 0)>;
    splay::nptr root{nullptr};
    splay tree(a, root);
    rep(_, q) {
        ll T, l, r;
        cin >> T >> l >> r;
        if (T == 0) {
            tree.reverse(root, l, r);
        } else {
            auto ans = tree(root, l, r);
            cout << ans << endl;
        }
    }
}
