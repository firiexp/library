#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

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
        const poly numerator(p), denominator(q);
        for (int n = 0; n < int(expected.size()); ++n) {
            mint value = n < int(p.size()) ? p[n] : mint(0);
            for (int j = 1; j <= n && j < int(q.size()); ++j)
                value -= q[j] * expected[n - j];
            expected[n] = value / q[0];
            assert(nth_term(numerator, denominator, n) == expected[n]);
        }
        assert(numerator.v == p && denominator.v == q);
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
    poly p(1 << 17), q(1 << 17);
    for (auto &v : p.v) v = rng() % ntt_mod;
    for (auto &v : q.v) v = rng() % ntt_mod;
    q[0] = 7;
    const auto original_p = p.v, original_q = q.v;
    for (int n : {0, 1, 2, 31, 63, 64, 127}) {
        poly prefix_p = p.pre(n + 1), prefix_q = q.pre(n + 1);
        vector<mint> coefficients(n + 1);
        for (int i = 0; i <= n; ++i) {
            coefficients[i] = prefix_p[i];
            for (int j = 1; j <= i; ++j) coefficients[i] -= prefix_q[j] * coefficients[i - j];
            coefficients[i] /= prefix_q[0];
        }
        mint expected = coefficients[n];
        assert(nth_term(p, q, n) == expected);
        assert(nth_term(prefix_p, prefix_q, n) == expected);
    }
    assert(p.v == original_p && q.v == original_q);
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
