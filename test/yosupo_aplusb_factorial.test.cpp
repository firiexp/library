#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
const int MOD = 998244353;

#include "../math/combinatorics/factorial.cpp"

template <class Mint>
void check_prime_tables(const Factorial<Mint> &f) {
    Mint fact = 1;
    for (int i = 0; i <= f.max_n(); ++i) {
        if (i) fact *= Mint(i);
        assert(f.fact(i) == fact);
        assert(f.fact(i) * f.inv_fact(i) == Mint(1));
        if (i) assert(f.inv(i) * Mint(i) == Mint(1));
    }
}

template <class Mint>
void check_combinations(const Factorial<Mint> &f) {
    mt19937 rng(223);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = rng() % (f.max_n() + 1);
        int k = min(n, int(rng() % 20));
        Mint p = 1, denom = 1;
        for (int i = 0; i < k; ++i) {
            p *= Mint(n - i);
            denom *= Mint(i + 1);
        }
        assert(f.P(n, k) == p);
        assert(f.C(n, k) == p / denom);
        assert(f.H(n - k + 1, k) == p / denom);
    }
    assert(f.C(-1, 0) == Mint(0) && f.C(2, 3) == Mint(0));
    assert(f.P(2, -1) == Mint(0) && f.H(0, 1) == Mint(0));
    assert(f.H(0, 0) == Mint(1));
    assert(f.inv(0) == Mint(0) && f.inv(-1) == Mint(0));
    assert(f.inv_fact(-1) == Mint(0));
    for (int i = 0; i < 20; ++i) {
        assert(f[i] == f.fact(i));
        assert(f[-i] == f.inv_fact(i));
        assert(f.fact(-i) == f.inv_fact(i));
    }
}

void check_large_extensions() {
    constexpr int block = 5000000;
    Factorial<> f(block - 1);
    check_prime_tables(f);
    f.ensure(2 * block - 1);
    check_prime_tables(f);
    int before = f.max_n();
    Factorial<> shared;
    shared.ensure(-1);
    shared.ensure(10);
    assert(shared.max_n() == before);
    for (int i = before + 1; i <= before + 64; ++i) f.ensure(i);
    check_combinations(f);
    assert(shared.max_n() == before + 64);
}

void check_small_extensions() {
    using Mint = modint<1000000007>;
    Factorial<Mint> f;
    for (int i = 0; i <= 1000; ++i) {
        f.ensure(i);
        assert(f.max_n() == i);
    }
    for (int i = 1064; i <= 2024; i += 64) f.ensure(i);
    check_prime_tables(f);
    check_combinations(f);
}

template <uint P>
void check_fallback(int initial, int n) {
    using Mint = modint<P>;
    Factorial<Mint> f(initial);
    vector<Mint> old(initial + 1);
    for (int i = 0; i <= initial; ++i) old[i] = f.inv_fact(i);
    f.ensure(n);
    vector<Mint> inverses(n + 1);
    inverses[1] = 1;
    Mint fact = 1, inv_fact = 1;
    for (int i = 0; i <= n; ++i) {
        if (i >= 2) inverses[i] = -Mint(P / i) * inverses[P % i];
        if (i) { fact *= Mint(i); inv_fact *= inverses[i]; }
        assert(f.fact(i) == fact);
        assert(f.inv(i) == inverses[i]);
        assert(f.inv_fact(i) == inv_fact);
        if (i <= initial) assert(f.inv_fact(i) == old[i]);
    }
}

int main() {
    check_large_extensions();
    check_small_extensions();
    Factorial<modint<5000011>> near_mod(5000010);
    check_prime_tables(near_mod);
    check_combinations(near_mod);
    check_fallback<17>(8, 5000008);
    check_fallback<1000000008>(0, 5000000);
    check_fallback<25326001>(0, 5000000);
}
