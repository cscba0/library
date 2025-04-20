#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <library/fastio/base.hpp>          // for FASTIO, cin, cout
#include <library/fastio/char/write.hpp>    // for operator<<
#include <library/fastio/signed/write.hpp>  // for operator<<
#include <library/fastio/string/read.hpp>   // for operator>>
#include <library/fastio/vector/write.hpp>  // for operator<<
#include <library/string/Zalgorithm.hpp>    // for Zalgorithm
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
