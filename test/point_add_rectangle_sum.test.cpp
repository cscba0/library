#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include <data_structure/segment_tree_2d.hpp>  // for SegmentTree2D
#include <fastio/base.hpp>                     // for FASTIO, cin, cout
#include <fastio/char/write.hpp>               // for operator<<
#include <fastio/point/read.hpp>               // for operator>>
#include <fastio/signed/read.hpp>              // for operator>>
#include <fastio/signed/write.hpp>             // for operator<<
#include <format>                              // for vector
#include <math/point.hpp>                      // for Point
#include <templates/macro/abbrev/eb.hpp>       // for eb
#include <templates/macro/abbrev/endl.hpp>     // for endl
#include <templates/macro/abbrev/ll.hpp>       // for ll
#include <templates/macro/segtree/RSQ.hpp>     // for RSQ
#include <templates/rep.hpp>                   // for rep
#include <templates/template.hpp>
#include <vector>  // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<Point<ll>> p;
    vector<ll> w(n);
    rep(i, n) {
        Point<ll> P;
        cin >> P;
        p.eb(P);
        cin >> w[i];
    }
    vector<vector<ll>> t(q, vector<ll>(4));
    rep(i, q) {
        int T;
        cin >> T;
        if (T == 0) {
            cin >> t[i][0] >> t[i][1] >> t[i][2];
            t[i][3] = -1;
            p.eb(Point{t[i][0], t[i][1]});
        } else {
            cin >> t[i][0] >> t[i][1] >> t[i][2] >> t[i][3];
        }
    }
    SegmentTree2D<RSQ(ll, 0), ll> seg(p);
    rep(i, n) {
        seg.add(p[i], w[i]);
    }
    rep(i, q) {
        if (t[i][3] == -1) {
            ll x, y, w;
            x = t[i][0];
            y = t[i][1];
            w = t[i][2];
            seg.add(x, y, w);
        } else {
            ll l, r, T, d;
            l = t[i][0];
            T = t[i][1];
            r = t[i][2];
            d = t[i][3];
            cout << seg(l, r, T, d) << endl;
        }
    }
}
