#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <fastio/base.hpp>                  // for FASTIO, cin, cout
#include <fastio/char/write.hpp>            // for operator<<
#include <fastio/signed/write.hpp>          // for operator<<
#include <fastio/string/read.hpp>           // for operator>>
#include <fastio/vector/write.hpp>          // for operator<<
#include <string/z_algorithm.hpp>           // for Zalgorithm
#include <string>                           // for basic_string, string
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/qcfium.hpp>

using namespace std;

int main() {
    string s;
    cin >> s;
    auto z = Zalgorithm(s);
    cout << z << endl;
}
