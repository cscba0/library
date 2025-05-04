#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include <sys/types.h>  // for uint

#include <fastio/base.hpp>                  // for FASTIO, cin, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/int128/read.hpp>           // for operator>>
#include <fastio/int128/write.hpp>          // for operator<<
#include <fastio/unsigned/read.hpp>         // for operator>>
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/macro/abbrev/lint.hpp>  // for lint
#include <templates/rep.hpp>                // for rep
#include <templates/template.hpp>
#include <version>  // for std

using namespace std;

int main() {
    uint t;
    cin >> t;
    rep(_, t) {
        lint a, b;
        cin >> a >> b;
        cout << a + b << endl;
    }
}
