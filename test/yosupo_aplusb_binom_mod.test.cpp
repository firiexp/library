#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/combinatorics/binom_mod.cpp"
#include "../math/combinatorics/binom_mod.cpp"
#include "../util/biginteger.cpp"

void check_prime_powers() {
    mt19937_64 random(266);
    for (auto [p, q] : vector<pair<ll, int>>{{2, 1}, {3, 1}, {5, 1}, {17, 1},
                                           {997, 1}, {999983, 1}, {2, 4}, {3, 3}, {17, 2}}) {
        const BinomModPrimePower binom(p, q);
        assert(binom.C(-1, 0) == 0);
        for (int tc = 0; tc < 300; ++tc) {
            ll n = random() & LLONG_MAX;
            if (tc < 6) n = vector<ll>{0, p - 1, p, p + 1, p * p, LLONG_MAX}[tc];
            int limit = min(n, 40LL);
            BigInteger value = 1;
            for (int k = 0; k <= limit; ++k) {
                if (k) value = value * (n - k + 1) / k;
                ll expected = stoll((value % binom.modulus()).to_string());
                assert(binom.C(n, k) == expected);
                assert(binom.C(n, n - k) == expected);
            }
        }
    }
    const BinomModPrimePower binary(2, 1);
    for (int tc = 0; tc < 1000; ++tc) {
        ll k = random() & LLONG_MAX;
        assert(binary.C(LLONG_MAX, k) == 1);
        if (k > 0 && k < (1LL << 62)) assert(binary.C(1LL << 62, k) == 0);
    }
}

int main() {
    check_prime_powers();
    vector<int> moduli;
    for (int m = 1; m <= 500; ++m) moduli.push_back(m);
    for (int m : {1024, 6561, 65536, 510510, 531441, 999983, 1000000}) moduli.push_back(m);
    for (int m : moduli) {
        const BinomMod binom(m);
        assert(binom.modulus() == m);
        vector<ll> row(102);
        row[0] = 1 % m;
        for (int n = 0; n <= 100; ++n) {
            assert(binom.C(n, -1) == 0);
            assert(binom.C(n, n + 1) == 0);
            for (int k = 0; k <= n; ++k) assert(binom.C(n, k) == row[k]);
            for (int k = n + 1; k > 0; --k) row[k] = (row[k] + row[k - 1]) % m;
        }
        for (ll n : {1000000000000000000LL, 999999999999999999LL}) {
            assert(binom.C(n, 0) == 1 % m);
            assert(binom.C(n, n) == 1 % m);
            assert(binom.C(n, 1) == n % m);
            assert(binom.C(n, n - 1) == n % m);
            ll pairs = (__int128)n * (n - 1) / 2 % m;
            assert(binom.C(n, 2) == pairs);
            assert(binom.C(n, n - 2) == pairs);
            for (ll k : {37, 100, 10000}) {
                assert(binom.C(n, k) == binom.C(n, n - k));
                assert(binom.C(n, k) == (binom.C(n - 1, k - 1) + binom.C(n - 1, k)) % m);
            }
        }
    }
}
