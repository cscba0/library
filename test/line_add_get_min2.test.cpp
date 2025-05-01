#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <data_structure/li_chao_tree.hpp>  // for DynamicLiChaoTree
#include <fastio/base.hpp>                  // for cin, FASTIO, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/signed/read.hpp>           // for operator>>
#include <fastio/signed/write.hpp>          // for operator<<
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/abbrev/ll.hpp>    // for ll
#include <templates/macro/inf.hpp>          // for INF
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>  // for rep
#include <vector>
#include <version>  // for std

using namespace std;

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
            t[i].b = INF;
            x.emplace_back(t[i].a);
        }
    }
    LiChaoTree<ll, []() { return INF; }> tree(x);
    rep(i, n) {
        tree.add(a[i].a, a[i].b);
    }
    rep(i, q) {
        if (t[i].b == INF) {
            cout << tree[t[i].a] << endl;
        } else {
            tree.add(t[i].a, t[i].b);
        }
    }
}
