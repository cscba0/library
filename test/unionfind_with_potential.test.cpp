#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include <data_structure/unionfind_with_potential.hpp>  // for WeightedUnionfind
#include <fastio/base.hpp>                              // for FASTIO, cout, cin
#include <fastio/char/write.hpp>                        // for operator<<
#include <fastio/modint/write.hpp>                      // for operator<<
#include <fastio/signed/read.hpp>                       // for operator>>
#include <fastio/signed/write.hpp>                      // for operator<<
#include <math/modint.hpp>                              // for ModInt
#include <templates/macro/abbrev/endl.hpp>              // for endl
#include <templates/macro/abbrev/ll.hpp>                // for ll
#include <templates/macro/mod.hpp>                      // for MOD1
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>  // for rep
#include <version>            // for std

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    UnionFindWithPotential<ll> uf(n);
    using mint = Modint<MOD1>;
    rep(_, q) {
        int t;
        cin >> t;
        if (t) {
            ll u, v;
            cin >> u >> v;
            if (uf.same(u, v)) {
                ll it = uf.weight(v, u);
                if (it < 0) {
                    it -= (it / MOD1 - 1) * MOD1;
                }
                cout << mint{it} << endl;
            } else {
                cout << -1 << endl;
            }
        } else {
            ll u, v, x;
            cin >> u >> v >> x;
            if (!uf.same(u, v)) {
                uf.merge(v, u, x);
                cout << 1 << endl;
            } else {
                ll it = uf.weight(v, u);
                if (it < 0) {
                    it -= (it / MOD1 - 1) * MOD1;
                }
                it %= MOD1;
                if (x < 0) {
                    x -= (x / MOD1 - 1) * MOD1;
                }
                if (it == x) {
                    cout << 1 << endl;
                } else {
                    cout << 0 << endl;
                }
            }
        }
    }
}
