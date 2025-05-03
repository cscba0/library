#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include <data_structure/randomized_binary_search_tree.hpp>  // for Randomiz...
#include <fastio/base.hpp>                                   // for FASTIO, cin
#include <fastio/char/write.hpp>                             // for operator<<
#include <fastio/signed/read.hpp>                            // for operator>>
#include <fastio/signed/write.hpp>                           // for operator<<
#include <fastio/vector/read.hpp>                            // for operator>>
#include <templates/macro/abbrev/endl.hpp>                   // for endl
#include <templates/macro/abbrev/ll.hpp>                     // for ll
#include <templates/macro/segtree/RSQ.hpp>                   // for RSQ
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>                                 // for rep
#include <vector>                                            // for vector
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;

    using rbst = RandomizedBinarySearchTree<RSQ(ll, 0)>;
    rbst tree;
    rbst::nptr root{nullptr};
    rep(i, n) {
        tree.insert(root, i, a[i]);
    }
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
