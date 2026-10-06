#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../math/matrix.cpp"
#include "../math/squarematrix.cpp"

template<bool Maximum>
struct Tropical {
    using T = ll;
    static T zero() { return Maximum ? -(1LL << 60) : 1LL << 60; }
    static T one() { return 0; }
    static T mul(T a, T b) { return a == zero() || b == zero() ? zero() : a + b; }
    static void add(T &a, T b) { a = Maximum ? max(a, b) : min(a, b); }
};

template<bool Maximum>
void tropical_check() {
    using H = Tropical<Maximum>;
    mt19937 rng(34);
    assert(matrix<H>(0).A.empty());
    for (int tc = 0; tc < 200; ++tc) {
        int n = 1 + rng() % 4, m = 1 + rng() % 4, k = 1 + rng() % 4;
        matrix<H> a(n, m), b(m, k);
        for (auto &row : a.A) for (ll &x : row) {
            assert(x == H::zero());
            if (rng() % 3) x = int(rng() % 15) - 7;
        }
        for (auto &row : b.A) for (ll &x : row) {
            assert(x == H::zero());
            if (rng() % 3) x = int(rng() % 15) - 7;
        }
        auto product = a * b;
        for (int i = 0; i < n; ++i) for (int j = 0; j < k; ++j) {
            ll expected = H::zero();
            for (int t = 0; t < m; ++t) {
                if (a[i][t] == H::zero() || b[t][j] == H::zero()) continue;
                ll candidate = a[i][t] + b[t][j];
                expected = Maximum ? max(expected, candidate) : min(expected, candidate);
            }
            assert(product[i][j] == expected);
        }
        matrix<H> square(n);
        for (auto &row : square.A) for (ll &x : row) {
            assert(x == H::zero());
            if (rng() % 3) x = int(rng() % 15) - 7;
        }
        // Enumerate walks directly, without matrix multiplication.
        for (int length = 0; length <= 4; ++length) {
            auto power = square.pow(length);
            for (int start = 0; start < n; ++start) {
                vector<ll> expected(n, H::zero());
                auto walk = [&](auto &&self, int v, int remaining, ll cost) -> void {
                    if (remaining == 0) {
                        expected[v] = Maximum ? max(expected[v], cost) : min(expected[v], cost);
                        return;
                    }
                    for (int to = 0; to < n; ++to)
                        if (square[v][to] != H::zero()) self(self, to, remaining - 1, cost + square[v][to]);
                };
                walk(walk, start, length, 0);
                assert(power[start] == expected);
            }
        }
        auto self = square;
        self *= self;
        assert(self.A == square.pow(2).A);
    }
}

template<class H>
void power_check() {
    mt19937 rng(110);
    assert((SquareMatrix<H, 0>().pow(0).A.empty()));
    assert((SquareMatrix<H, 0>().pow(8).A.empty()));
    for (int n = 0; n <= 6; ++n) for (int tc = 0; tc < 20; ++tc) {
        matrix<H> a(n), expected = matrix<H>::I(n);
        SquareMatrix<H, 6> fixed;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
            fixed[i][j] = a[i][j] = int(rng() % 15) - 7;
        for (int exponent = 0; exponent <= 33; ++exponent) {
            auto dynamic_power = a.pow(exponent);
            auto fixed_power = fixed.pow(exponent, n);
            assert(dynamic_power.A == expected.A);
            for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j)
                assert(fixed_power[i][j] == (i < n && j < n ? expected[i][j] : H::zero()));
            expected *= a;
        }
    }
}

struct CountedRing {
    using T = ll;
    inline static int products = 0;
    static T zero() { return 0; }
    static T one() { return 1; }
    static T mul(T a, T b) { ++products; return a * b; }
    static void add(T &a, T b) { a += b; }
};

void product_count_check() {
    matrix<CountedRing> a(1);
    SquareMatrix<CountedRing, 1> b;
    a[0][0] = b[0][0] = 1;
    for (auto [exponent, count] : vector<pair<ll, int>>{
             {0, 0}, {1, 1}, {2, 2}, {3, 3}, {7, 5}, {8, 4}, {9, 5}, {1000000000000000000LL, 83}}) {
        CountedRing::products = 0;
        assert(a.pow(exponent)[0][0] == 1);
        assert(CountedRing::products == count);
        CountedRing::products = 0;
        assert(b.pow(exponent)[0][0] == 1);
        assert(CountedRing::products == count);
    }
    a[0][0] = b[0][0] = LLONG_MAX;
    assert(a.pow(1)[0][0] == LLONG_MAX);
    assert(b.pow(1)[0][0] == LLONG_MAX);
}

mint permutation_determinant(const matrix<SemiRing> &a) {
    int n = a.height();
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    mint result = 0;
    do {
        mint term = 1;
        int inversions = 0;
        for (int i = 0; i < n; ++i) {
            term *= a[i][p[i]];
            for (int j = 0; j < i; ++j) inversions += p[j] > p[i];
        }
        result += inversions % 2 ? -term : term;
    } while (next_permutation(p.begin(), p.end()));
    return result;
}

void determinant_check() {
    mt19937 rng(35);
    for (int n = 0; n <= 5; ++n) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            matrix<SemiRing> a(n);
            for (int i = 0; i < n; ++i) a[i][p[i]] = 1;
            mint expected = permutation_determinant(a);
            assert(a.detarminant() == expected);
        } while (next_permutation(p.begin(), p.end()));
        for (int tc = 0; tc < 200; ++tc) {
            matrix<SemiRing> a(n);
            for (auto &row : a.A) for (auto &x : row) x = int(rng() % 7) - 3;
            if (n > 1 && tc % 3 == 0) a[0] = a[1];
            mint expected = permutation_determinant(a);
            assert(a.detarminant() == expected);
        }
    }
}

int main() {
    tropical_check<false>();
    tropical_check<true>();
    power_check<SemiRing>();
    power_check<Tropical<false>>();
    power_check<Tropical<true>>();
    product_count_check();
    determinant_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
