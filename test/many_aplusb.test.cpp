#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <stdint.h>     // for uint64_t
#include <sys/types.h>  // for uint

#include <fastio/base.hpp>                  // for FASTIO, cin, FIO, cout
#include <fastio/unsigned/read.hpp>         // for operator>>
#include <fastio/unsigned/write.hpp>        // for operator<<
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>  // for rep
#include <version>            // for std

int main() {
    uint t;
    cin >> t;
    rep(_, 0U, t) {
        uint64_t a, b;
        cin >> a >> b;
        cout << a + b;
        *FIO.opos++ = endl;
    }
}
