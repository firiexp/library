#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../util/modint_base.cpp"
#include "../math/matrix_determinant_mod.cpp"

namespace dynamic_modint_test {
#include "../util/modint_arbitrary.cpp"
}

ll permutation_determinant(const vector<vector<ll>>& a, int mod) {
    int n = a.size();
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    ll ans = 0;
    do {
        ll term = 1 % mod;
        int inversions = 0;
        for (int i = 0; i < n; ++i) {
            ll x = (a[i][p[i]] % mod + mod) % mod;
            term = term * x % mod;
            for (int j = 0; j < i; ++j) inversions += p[j] > p[i];
        }
        ans = (ans + (inversions & 1 ? -term : term)) % mod;
    } while (next_permutation(p.begin(), p.end()));
    return ans < 0 ? ans + mod : ans;
}

void check(const vector<vector<ll>>& a, int mod) {
    auto original = a;
    ll result = matrix_determinant_mod(a, mod);
    assert(a == original);
    assert(0 <= result && result < mod);
    assert(result == permutation_determinant(a, mod));
}

template<class Mint>
void check_modint(const vector<vector<ll>>& a) {
    int n = a.size();
    vector<vector<Mint>> values(n, vector<Mint>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) values[i][j] = a[i][j];
    }
    auto original = values;
    auto result = matrix_determinant_mod(values);
    static_assert(is_same_v<decltype(result), Mint>);
    ll expected = permutation_determinant(a, Mint::get_mod());
    assert(result.value() == expected);
    assert(result * 2 + 3 == Mint(expected * 2 + 3));
    assert(values == original);
}

template<class Mint>
void check_modint_cases() {
    check_modint<Mint>({});
    check_modint<Mint>({{0}});
    check_modint<Mint>({{2, 1}, {3, 2}});
    check_modint<Mint>({{0, 1}, {1, 0}});
    check_modint<Mint>({{1, 2}, {2, 4}});
    check_modint<Mint>({{LLONG_MIN, LLONG_MAX}, {LLONG_MAX, LLONG_MIN}});
    mt19937_64 rng(7901);
    for (int tc = 0; tc < 200; ++tc) {
        int n = rng() % 7;
        vector<vector<ll>> a(n, vector<ll>(n));
        for (auto& row : a) for (auto& x : row) {
            x = rng() & LLONG_MAX;
            if (rng() & 1) x = -x;
        }
        check_modint<Mint>(a);
    }
}

void self_check() {
    check_modint_cases<modint<1>>();
    check_modint_cases<modint<6>>();
    check_modint_cases<modint<998244353>>();
    check_modint_cases<modint<INT_MAX>>();
    for (int mod : {1, 6, 12, 998244353, INT_MAX}) {
        dynamic_modint_test::mint::set_mod(mod);
        check_modint_cases<dynamic_modint_test::mint>();
    }
    assert(matrix_determinant_mod({{2, 1}, {3, 2}}, 6) == 1);
    for (int mod : {1, 2, 6, 12, 1000000000, INT_MAX}) {
        check({}, mod);
        check({{0}}, mod);
        check({{0, 1}, {1, 0}}, mod);
        check({{1, 2, 3}, {0, 0, 0}, {4, 5, 6}}, mod);
        check({{1, 2}, {2, 4}}, mod);
        check({{LLONG_MIN, LLONG_MAX}, {LLONG_MAX, LLONG_MIN}}, mod);
    }
    for (int mod = 1; mod <= 16; ++mod) {
        for (int code = 0; code < mod * mod * mod * mod; ++code) {
            int rest = code;
            vector<vector<ll>> a(2, vector<ll>(2));
            for (auto& row : a) for (auto& x : row) {
                x = rest % mod;
                rest /= mod;
            }
            check(a, mod);
        }
    }
    mt19937_64 rng(79);
    for (int tc = 0; tc < 3000; ++tc) {
        int n = rng() % 7, mod = 1 + rng() % INT_MAX;
        vector<vector<ll>> a(n, vector<ll>(n));
        for (auto& row : a) for (auto& x : row) {
            x = rng() & LLONG_MAX;
            if (rng() & 1) x = -x;
        }
        if (n && tc % 7 == 0) a[rng() % n] = a[rng() % n];
        check(a, mod);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
