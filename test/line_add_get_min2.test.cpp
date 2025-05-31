#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <sys/types.h>  // for uint

#include <algorithm>                        // for sort, unique
#include <data_structure/li_chao_tree.hpp>  // for LiChaoTree
#include <fastio/base.hpp>                  // for cin, FASTIO, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/signed/read.hpp>           // for operator>>
#include <fastio/signed/write.hpp>          // for operator<<
#include <fastio/unsigned/read.hpp>         // for operator>>
#include <math/inf.hpp>                     // for INF
#include <templates/macro/abbrev/eb.hpp>    // for eb
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/abbrev/ext.hpp>   // for ext
#include <templates/macro/abbrev/ll.hpp>    // for ll
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <vector>  // for vector

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> x;
    struct node {
        ll a, b;
    };
    vector<node> a(n);
    rep(i, n) {
        cin >> a[i].a >> a[i].b;
    }
    vector<node> t(q);
    rep(i, q) {
        uint T;
        cin >> T;
        if (T == 0) {
            cin >> t[i].a >> t[i].b;
        } else {
            cin >> t[i].a;
            t[i].b = Infinite{};
            x.eb(t[i].a);
        }
    }
    LiChaoTree<ll, []() -> ll { return Infinite{}; }> tree(x);
    if (x.empty()) {
        ext;
    }
    rep(i, n) {
        tree.add(a[i].a, a[i].b);
    }
    rep(i, q) {
        if (t[i].b == (ll)(Infinite{})) {
            cout << tree(t[i].a) << endl;
        } else {
            tree.add(t[i].a, t[i].b);
        }
    }
}
