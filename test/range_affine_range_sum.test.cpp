#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <data_structure/lazy_segment_tree.hpp>  // for LazySegmentTree
#include <fastio/base.hpp>                       // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                 // for operator<<
#include <fastio/signed/read.hpp>                // for operator>>
#include <fastio/signed/write.hpp>               // for operator<<
#include <fastio/vector/read.hpp>                // for operator>>
#include <iterator>                              // for pair
#include <templates/macro/abbrev/endl.hpp>       // for endl
#include <templates/macro/abbrev/ll.hpp>         // for ll
#include <templates/macro/mod.hpp>               // for MOD1
#include <templates/rep.hpp>                     // for rep
#include <templates/template.hpp>
#include <utility>  // for pair
#include <vector>   // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;
    vector<pair<ll, ll>> v(n);
    rep(i, n) {
        v[i] = {a[i], 1};
    }
    LazySegmentTree<pair<ll, ll>,
                    [](pair<ll, ll> a, pair<ll, ll> b) -> pair<ll, ll> { return {(a.first + b.first) % MOD1, a.second + b.second}; },
                    []() -> pair<ll, ll> { return {0, 1}; },
                    pair<ll, ll>,
                    [](pair<ll, ll> lz, pair<ll, ll> d) -> pair<ll, ll> { return {(d.first * lz.first + d.second * lz.second) % MOD1, d.second}; },
                    [](pair<ll, ll> a, pair<ll, ll> b) -> pair<ll, ll> { return {a.first * b.first % MOD1, (a.second + a.first * b.second) % MOD1}; },
                    []() -> pair<ll, ll> { return {1, 0}; }>
        seg(v);
    rep(_, q) {
        int T, l, r;
        cin >> T >> l >> r;
        if (T) {
            cout << seg(l, r).first << endl;
        } else {
            ll b, c;
            cin >> b >> c;
            seg.apply(l, r, {b, c});
        }
    }
}
