#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B"

#include <sys/types.h>  // for uint

#include <data_structure/unionfind_with_potential.hpp>  // for weighted_unionfind
#include <fastio/base.hpp>                              // for FASTIO, cin, cout
#include <fastio/char/write.hpp>                        // for operator<<
#include <fastio/signed/read.hpp>                       // for operator>>
#include <fastio/signed/write.hpp>                      // for operator<<
#include <fastio/unsigned/read.hpp>                     // for operator>>
#include <templates/macro/abbrev/endl.hpp>              // for endl
#include <templates/rep.hpp>                            // for rep
#include <templates/template.hpp>
#include <version>  // for std

int main() {
    int n, q;
    cin >> n >> q;
    UnionFindWithPotential uf(n);
    rep(_, q) {
        uint T;
        cin >> T;
        if (T) {
            int x, y;
            cin >> x >> y;
            if (!uf.same(x, y)) {
                cout << '?' << endl;
            } else {
                cout << uf.weight(x, y) << endl;
            }
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            uf.merge(x, y, z);
        }
    }
}
