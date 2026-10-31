#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
static const int MOD = 998244353;
#include "../math/modular/modint.cpp"
#include "../math/linear_algebra/matrix.cpp"

struct MintRing : SemiRing {
    static T sample(mt19937 &rng) { return rng() % MOD; }
};

struct MinPlus {
    using T = ll;
    static T zero() { return 1LL << 60; }
    static T one() { return 0; }
    static T mul(T a, T b) { return a == zero() || b == zero() ? zero() : a + b; }
    static void add(T &a, T b) { a = min(a, b); }
    static T sample(mt19937 &rng) { return rng() % 3 ? ll(rng() % 21) - 10 : zero(); }
};

struct BooleanRing {
    using T = int;
    static T zero() { return 0; }
    static T one() { return 1; }
    static T mul(T a, T b) { return a && b; }
    static void add(T &a, T b) { a |= b; }
    static T sample(mt19937 &rng) { return rng() % 2; }
};

struct BlockRing {
    using T = array<mint, 4>;
    static T zero() { return {}; }
    static T one() { return {1, 0, 0, 1}; }
    static T mul(const T &a, const T &b) {
        return {a[0] * b[0] + a[1] * b[2], a[0] * b[1] + a[1] * b[3],
                a[2] * b[0] + a[3] * b[2], a[2] * b[1] + a[3] * b[3]};
    }
    static void add(T &a, const T &b) { for (int i = 0; i < 4; ++i) a[i] += b[i]; }
    static T sample(mt19937 &rng) { return {rng() % MOD, rng() % MOD, rng() % MOD, rng() % MOD}; }
};

template<class H>
vector<typename H::T> step(const matrix<H> &a, const vector<typename H::T> &v) {
    vector<typename H::T> result(v.size(), H::zero());
    for (size_t j = 0; j < v.size(); ++j) {
        for (size_t i = 0; i < v.size(); ++i) H::add(result[i], H::mul(a[i][j], v[j]));
    }
    return result;
}

template<class H>
void check() {
    mt19937 rng(272);
    for (int n = 0; n <= 5; ++n) for (int trial = 0; trial < 30; ++trial) {
        matrix<H> a(n);
        vector<typename H::T> v(n);
        for (auto &row : a.A) for (auto &x : row) x = H::sample(rng);
        if (trial == 0) a = matrix<H>(n);
        if (trial == 1) a = matrix<H>::I(n);
        for (auto &x : v) x = H::sample(rng);
        const auto original_a = a.A;
        const auto original_v = v;
        auto expected = v;
        for (int k = 0; k <= 33; ++k) {
            assert(a.pow_apply(k, v) == expected);
            expected = step(a, expected);
        }
        assert(a.A == original_a && v == original_v);
        for (ll k : {(1LL << 40) - 1, 1LL << 40, (1LL << 40) + 1, LLONG_MAX}) {
            assert(matrix<H>::I(n).pow_apply(k, v) == v);
            assert(matrix<H>(n).pow_apply(k, v) == vector<typename H::T>(n, H::zero()));
            if constexpr (!is_same_v<H, MinPlus>) assert(a.pow_apply(k, v) == step(a.pow(k), v));
        }
    }
}

int main() {
    check<MintRing>();
    check<MinPlus>();
    check<BooleanRing>();
    check<BlockRing>();
    matrix<MinPlus> a(2);
    a[0][1] = -3;
    assert((a.pow_apply(1, {7, 5}) == vector<ll>{2, MinPlus::zero()}));
    assert((a.pow_apply(2, {7, 5}) == vector<ll>(2, MinPlus::zero())));
}
