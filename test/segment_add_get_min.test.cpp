#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <data_structure/dynamic_li_chao_tree.hpp>  // for DynamicLiChaoTree
#include <fastio/base.hpp>                          // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                    // for operator<<
#include <fastio/signed/read.hpp>                   // for operator>>
#include <fastio/signed/write.hpp>                  // for operator<<
#include <fastio/string/write.hpp>                  // for operator<<
#include <string>                                   // for basic_string
#include <templates/macro/abbrev/endl.hpp>          // for endl
#include <templates/macro/abbrev/ll.hpp>            // for ll
#include <templates/macro/inf.hpp>                  // for INF
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>                        // for rep

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    DynamicLiChaoTree<ll, -1000000001, 1000000001, []() { return INF; }> seg;
    rep(_, n) {
        ll l, r, a, b;
        cin >> l >> r >> a >> b;
        seg.add(a, b, l, r);
    }
    rep(_, q) {
        int T;
        cin >> T;
        if (T == 0) {
            ll l, r, a, b;
            cin >> l >> r >> a >> b;
            seg.add(a, b, l, r);
        } else {
            ll p;
            cin >> p;
            auto ans = seg(p);
            if (ans == INF) {
                cout << "INFINITY" << endl;
            } else {
                cout << ans << endl;
            }
        }
    }
}
