#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"

#include <data_structure/segment_tree.hpp>  // for SegmentTree
#include <fastio/base.hpp>                  // for FASTIO, cin, cout
#include <fastio/signed/write.hpp>          // for operator<<
#include <fastio/string/read.hpp>           // for operator>>
#include <fastio/string/write.hpp>          // for operator<<
#include <fastio/vector/write.hpp>          // for operator<<
#include <string/rolling_hash.hpp>          // for RollingHash
#include <string>                           // for basic_string, string
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/segtree/RSQ.hpp>  // for RSQ
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <templates/vector_output.hpp>  // for operator+
#include <vector>                       // for vector

using namespace std;

int main() {
    string t, s;
    cin >> t >> s;
    using rh = RollingHash;
    vector<rh> v;
    rep(i, (int)t.size()) {
        v.emplace_back(rh{t[i]});
    }
    SegmentTree<RSQ(rh, rh{})> seg(v);
    vector<int> ans;
    rh c = rh{s};
    rep(l, (int)t.size()) {
        int r = l + (int)s.size() - 1;
        if ((int)t.size() <= r) break;
        if (seg(l, r + 1) == c) {
            ans.emplace_back(l);
        }
    }
    cout << (ans + endl);
}
