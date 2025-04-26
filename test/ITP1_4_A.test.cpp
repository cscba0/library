#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/all/ITP1_4_A"

#include <data_structure/fraction.hpp>       // for Fraction
#include <fastio/base.hpp>                   // for FASTIO, cout, cin
#include <fastio/char/write.hpp>             // for operator<<
#include <fastio/fraction/write.hpp>         // for operator<<
#include <fastio/signed/read.hpp>            // for operator>>
#include <fastio/signed/write.hpp>           // for operator<<
#include <templates/macro/abbrev/endl.hpp>   // for endl
#include <templates/macro/abbrev/space.hpp>  // for space
#include <templates/qcfium.hpp>
#include <version>                           // for std

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << (a / b) << space;
    cout << (a % b) << space;
    cout << Fraction(a, b) << endl;
}
