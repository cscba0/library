#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <data_structure/dynamic_li_chao_tree.hpp>  // for DynamicLiChaoTree
#include <fastio/base.hpp>                          // for cin, FASTIO, cout
#include <fastio/char/write.hpp>                    // for operator<<
#include <fastio/signed/read.hpp>                   // for operator>>
#include <fastio/signed/write.hpp>                  // for operator<<
#include <math/inf.hpp>                             // for INF
#include <templates/macro/abbrev/endl.hpp>          // for endl
#include <templates/macro/abbrev/ll.hpp>            // for ll
#include <templates/rep.hpp>                        // for rep
#include <templates/template.hpp>
#include <version>  // for std

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    DynamicLiChaoTree<ll, -1000000001, 1000000001, []() -> ll { return Infinite{}; }> tree;
    rep(_, n) {
        ll a, b;
        cin >> a >> b;
        tree.add(a, b);
    }
    rep(_, q) {
        int T;
        cin >> T;
        if (T == 0) {
            ll a, b;
            cin >> a >> b;
            tree.add(a, b);
        } else {
            ll p;
            cin >> p;
            cout << tree(p) << endl;
        }
    }
}
