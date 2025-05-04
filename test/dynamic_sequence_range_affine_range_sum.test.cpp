#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <data_structure/lazy_reversible_randomized_binary_search_tree.hpp>
#include <fastio/base.hpp>
#include <fastio/char/write.hpp>
#include <fastio/signed/read.hpp>
#include <fastio/signed/write.hpp>
#include <iterator>
#include <memory>
#include <templates/macro/abbrev/endl.hpp>
#include <templates/macro/abbrev/ll.hpp>
#include <templates/macro/mod.hpp>
#include <templates/qcfium.hpp>
#include <templates/rep.hpp>
#include <utility>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    using rbst = LazyReversibleRandomizedBinarySearchTree<
        pair<ll, ll>,
        [](pair<ll, ll> a, pair<ll, ll> b) -> pair<ll, ll> {
            return {(a.first + b.first) % MOD1, (a.second + b.second) % MOD1};
        },
        []() -> pair<ll, ll> {
            return {0, 0};
        },
        pair<ll, ll>,
        [](pair<ll, ll> f, pair<ll, ll> x) -> pair<ll, ll> {
            return {((x.first * f.first) % MOD1 + x.second * f.second % MOD1) % MOD1, x.second};
        },
        [](pair<ll, ll> a, pair<ll, ll> b) -> pair<ll, ll> {
            return {a.first * b.first % MOD1, (b.second * a.first + a.second) % MOD1};
        },
        []() -> pair<ll, ll> {
            return {1, 0};
        }>;
    rbst t;
    rbst::nptr root{nullptr};
    rep(i, n) {
        ll a;
        cin >> a;
        t.insert(root, i, {a, 1});
    }
    rep(_, q) {
        int T;
        cin >> T;
        switch (T) {
            case 0: {
                ll i, x;
                cin >> i >> x;
                t.insert(root, i, {x, 1});
                break;
            }
            case 1: {
                ll i;
                cin >> i;
                t.erase(root, i);
                break;
            }
            case 2: {
                ll l, r;
                cin >> l >> r;
                t.reverse(root, l, r);
                break;
            }
            case 3: {
                ll l, r, b, c;
                cin >> l >> r >> b >> c;
                t.apply(root, l, r, {b, c});
                break;
            }
            case 4: {
                ll l, r;
                cin >> l >> r;
                ll ans = t(root, l, r).first;
                cout << ans << endl;
                break;
            }
        }
    }
}
