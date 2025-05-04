#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include <data_structure/hash_map.hpp>      // for HashMap
#include <fastio/base.hpp>                  // for cin, FASTIO, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/signed/read.hpp>           // for operator>>
#include <fastio/unsigned/read.hpp>         // for operator>>
#include <fastio/unsigned/write.hpp>        // for operator<<
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/abbrev/ull.hpp>   // for ull
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <version>  // for std
using namespace std;

int main() {
    int q;
    cin >> q;
    HashMap t;
    rep(_, q) {
        ull T, k;
        cin >> T >> k;
        if (T == 0) {
            ull v;
            cin >> v;
            t[k] = v;
        } else {
            cout << t[k] << endl;
        }
    }
}
