#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <iostream>
#include <string/Zalgorithm.hpp>            // for Zalgorithm
#include <string>                           // for basic_string, string
#include <templates/macro/abbrev/endl.hpp>  // for endl
#include <templates/qcfium.hpp>

int main() {
    std::string s;
    std::cin >> s;
    auto z = Zalgorithm(s);
    for (uint i = 0, siz = z.size(); i < siz; ++i) {
        std::cout << z[i] << " \n"[i + 1 == siz];
    }
}
