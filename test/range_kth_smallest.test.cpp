#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <algorithm>                                // for max_element
#include <data_structure/wavelet_matrix/base.hpp>   // for WaveletMatrix
#include <data_structure/wavelet_matrix/small.hpp>  // for WaveletMatrix::small
#include <fastio/base.hpp>                          // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                    // for operator<<
#include <fastio/signed/read.hpp>                   // for operator>>
#include <fastio/signed/write.hpp>                  // for operator<<
#include <fastio/vector/read.hpp>                   // for operator>>
#include <templates/macro/abbrev/endl.hpp>          // for endl
#include <templates/rep.hpp>                        // for rep
#include <templates/template.hpp>
#include <vector>  // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    WaveletMatrix<int> wm(a);
    rep(_, q) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << wm.small(l, r, k) << endl;
    }
}
