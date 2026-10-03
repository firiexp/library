#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <algorithm>
#include <cassert>
#include <climits>
#include <random>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../fps/nth_term.cpp"

void self_check() {
    auto check = [](const vector<mint> &p, const vector<mint> &q) {
        vector<mint> expected(40);
        for (int n = 0; n < int(expected.size()); ++n) {
            mint value = n < int(p.size()) ? p[n] : mint(0);
            for (int j = 1; j <= n && j < int(q.size()); ++j)
                value -= q[j] * expected[n - j];
            expected[n] = value / q[0];
            assert(nth_term(poly(p), poly(q), n) == expected[n]);
        }
    };
    check({}, {1});
    check({}, {2, -1});
    check({1}, {1});
    check({1}, {2, -1});
    check({2, 4, 6}, {2});
    check({1, 0, 3, 4, 5}, {3, -1});
    assert(nth_term(poly(vector<mint>{1}), poly(vector<mint>{2}), LLONG_MAX) == mint(0));
    assert(nth_term(poly(vector<mint>{1}), poly(vector<mint>{2, -2}), LLONG_MAX) == mint(2).inv());
    mt19937 rng(8);
    for (int tc = 0; tc < 150; ++tc) {
        vector<mint> p(rng() % 10), q(1 + rng() % 10);
        for (auto &v : p) v = int(rng() % 21) - 10;
        for (auto &v : q) v = int(rng() % 21) - 10;
        q[0] = tc % 3 == 0 ? 1 : 1 + rng() % 100;
        check(p, q);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;

    int d;
    ll n;
    sc.read(d, n);
    vector<mint> a(d), c(d);
    for (int i = 0; i < d; ++i) {
        int x;
        sc.read(x);
        a[i] = x;
    }
    for (int i = 0; i < d; ++i) {
        int x;
        sc.read(x);
        c[i] = x;
    }

    poly q(d + 1);
    q[0] = 1;
    for (int i = 0; i < d; ++i) q[i + 1] = -c[i];
    poly p = (poly(a) * q).cut(d);
    pr.println(nth_term(p, q, n).val);
    return 0;
}
