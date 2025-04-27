#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <data_structure/persistent_unionfind.hpp>  // for PersistentUnionfind
#include <fastio/base.hpp>                          // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                    // for operator<<
#include <fastio/signed/read.hpp>                   // for operator>>
#include <fastio/signed/write.hpp>                  // for operator<<
#include <templates/macro/abbrev/endl.hpp>          // for endl
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>  // for rep
#include <vector>             // for vector

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    PersistentUnionFind uf(n);
    vector<int> a(q);
    rep(i, q) {
        int t, x, u, v;
        cin >> t >> x >> u >> v;
        ++x;
        if (t == 0) {
            a[i] = uf.merge(u, v, x == 0 ? 0 : a[x - 1]);
        } else {
            cout << static_cast<int>(uf.same(u, v, x == 0 ? 0 : a[x - 1])) << endl;
        }
    }
}
