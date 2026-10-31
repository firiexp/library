#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 998244353;

#include "../math/modular/modint.cpp"
#include "../math/linear_algebra/matrix.cpp"
#include "../math/linear_algebra/squarematrix.cpp"
#include "../math/linear_algebra/squarematrix_mint.cpp"

struct MinPlus {
    using T = ll;
    static T zero() { return 1LL << 60; }
    static T one() { return 0; }
    static T mul(T a, T b) { return a == zero() || b == zero() ? zero() : a + b; }
    static void add(T &a, T b) { a = min(a, b); }
};

struct Boolean {
    using T = int;
    static T zero() { return 0; }
    static T one() { return 1; }
    static T mul(T a, T b) { return a && b; }
    static void add(T &a, T b) { a |= b; }
};

struct BlockRing {
    using T = array<mint, 4>;
    static T zero() { return {}; }
    static T one() { return {1, 0, 0, 1}; }
    static T mul(const T &a, const T &b) {
        return {a[0] * b[0] + a[1] * b[2], a[0] * b[1] + a[1] * b[3],
                a[2] * b[0] + a[3] * b[2], a[2] * b[1] + a[3] * b[3]};
    }
    static void add(T &a, const T &b) {
        for (int i = 0; i < 4; ++i) a[i] += b[i];
    }
};

template <class H>
typename H::T random_value(mt19937 &rng) {
    if constexpr (is_same<H, BlockRing>::value) return {rng() % 7, rng() % 7, rng() % 7, rng() % 7};
    else if constexpr (is_same<H, Boolean>::value) return rng() & 1;
    else return int(rng() % 15) - 7;
}

template <class H>
void check_semiring() {
    mt19937 rng(222);
    for (int n = 0; n <= 5; ++n) for (int tc = 0; tc < 30; ++tc) {
        matrix<H> a(n);
        SquareMatrix<H, 6> fixed;
        for (auto &row : fixed.A) for (auto &x : row) x = random_value<H>(rng);
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            auto x = random_value<H>(rng);
            if (tc == 0) x = H::zero();
            if (tc == 1) x = i == j ? H::one() : H::zero();
            if (tc == 2) x = i + 1 == j ? H::one() : H::zero();
            if (tc == 3) x = H::one();
            a[i][j] = fixed[i][j] = x;
        }
        auto original = a.A;
        auto original_fixed = fixed.A;
        matrix<H> expected_power = matrix<H>::I(n), expected_sum(n);
        for (int k = 0; k <= 25; ++k) {
            auto [p, s] = a.pow_sum(k);
            auto [fp, fs] = fixed.pow_sum(k, n);
            assert(p.A == expected_power.A && s.A == expected_sum.A);
            for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
                assert(fp[i][j] == (i < n && j < n ? expected_power[i][j] : H::zero()));
                assert(fs[i][j] == (i < n && j < n ? expected_sum[i][j] : H::zero()));
            }
            if constexpr (is_same<H, SemiRing>::value) {
                SquareMatrixMint<6> optimized;
                optimized.A = fixed.A;
                auto [mp, ms] = optimized.pow_sum(k, n);
                assert(mp.A == fp.A && ms.A == fs.A);
                assert(optimized.A == original_fixed);
            }
            assert(a.A == original && fixed.A == original_fixed);
            expected_sum += expected_power;
            expected_power *= a;
        }
    }
    auto [p, s] = SquareMatrix<H, 0>().pow_sum(LLONG_MAX);
    assert(p.A.empty() && s.A.empty());
    assert(matrix<H>(0).pow_sum(LLONG_MAX).first.A.empty());
}

void check_large() {
    matrix<SemiRing> a = matrix<SemiRing>::I(2);
    SquareMatrix<SemiRing, 2> b = SquareMatrix<SemiRing, 2>::I();
    SquareMatrixMint<2> c = SquareMatrixMint<2>::I();
    a[0][1] = b[0][1] = c[0][1] = 1;
    for (ll k : {0LL, 1LL, 2LL, 1000000000000000000LL, LLONG_MAX}) {
        auto [p, s] = a.pow_sum(k);
        auto [fp, fs] = b.pow_sum(k);
        auto [mp, ms] = c.pow_sum(k);
        assert(p[0][0] == mint(1) && p[1][1] == mint(1));
        assert(p[0][1] == mint(k) && p[1][0] == mint(0));
        assert(s[0][0] == mint(k) && s[1][1] == mint(k));
        assert(s[0][1] == mint(k) * mint(k - 1) / mint(2) && s[1][0] == mint(0));
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
            assert(p[i][j] == fp[i][j] && p[i][j] == mp[i][j]);
            assert(s[i][j] == fs[i][j] && s[i][j] == ms[i][j]);
        }
    }
    auto [p, s] = SquareMatrixMint<0>().pow_sum(LLONG_MAX);
    assert(p.A.empty() && s.A.empty());
    matrix<MinPlus> scalar(1);
    scalar[0][0] = 1;
    auto [mp, ms] = scalar.pow_sum(1000000000000000000LL);
    assert(mp[0][0] == 1000000000000000000LL && ms[0][0] == 0);
}

int main() {
    check_semiring<SemiRing>();
    check_semiring<MinPlus>();
    check_semiring<Boolean>();
    check_semiring<BlockRing>();
    check_large();
}
