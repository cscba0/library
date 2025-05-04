#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <sys/types.h>  // for uint

#include <data_structure/segment_tree.hpp>  // for Segtree
#include <fastio/base.hpp>                  // for FASTIO, cin, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/pair/read.hpp>             // for operator>>
#include <fastio/signed/read.hpp>           // for operator>>
#include <fastio/unsigned/read.hpp>         // for operator>>
#include <fastio/unsigned/write.hpp>        // for operator<<
#include <fastio/vector/read.hpp>           // for operator>>
#include <iterator>                         // for pair
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/abbrev/mp.hpp>    // for MP
#include <templates/macro/abbrev/ull.hpp>   // for ull
#include <templates/macro/mod.hpp>          // for MOD1
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <type_traits>  // for __decay_and_strip
#include <utility>      // for pair, make_pair
#include <vector>       // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<ull, ull>> a(n);
    cin >> a;
    SegmentTree<
        pair<ull, ull>,
        [](pair<ull, ull> a, pair<ull, ull> b) {
            return MP(a.first * b.first % MOD1, (a.second * b.first + b.second) % MOD1);
        },
        []() { return MP(1, 0); }>
        seg(a);
    rep(_, q) {
        uint T;
        ull l, r, x;
        cin >> T >> l >> r >> x;
        if (T == 0) {
            seg.set(l, {r, x});
        } else {
            auto res = seg(l, r);
            auto ans = (res.first * x + res.second) % MOD1;
            cout << ans << endl;
        }
    }
}
