#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include <data_structure/dynamic_segment_tree.hpp>  // for DynamicSegmentTree
#include <fastio/base.hpp>                          // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                    // for operator<<
#include <fastio/signed/read.hpp>                   // for operator>>
#include <fastio/signed/write.hpp>                  // for operator<<
#include <templates/macro/abbrev/endl.hpp>          // for endl
#include <templates/macro/segtree/RSQ.hpp>          // for RSQ
#include <templates/rep.hpp>                        // for rep
#include <templates/template.hpp>
#include <version>  // for std

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    DynamicSegmentTree<RSQ(int, 0)> seg;
    rep(_, q) {
        int T, x, y;
        cin >> T >> x >> y;
        if (T) {
            cout << seg(x, y + 1) << endl;
        } else {
            seg.add(x, y);
        }
    }
}
