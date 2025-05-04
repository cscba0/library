#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <data_structure/unionfind.hpp>     // for unionfind
#include <fastio/base.hpp>                  // for FASTIO, cin, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/signed/read.hpp>           // for operator>>
#include <fastio/signed/write.hpp>          // for operator<<
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <version>  // for std

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    rep(_, q) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t) {
            cout << static_cast<int>(uf.same(u, v)) << endl;
        } else {
            uf.merge(u, v);
        }
    }
}
