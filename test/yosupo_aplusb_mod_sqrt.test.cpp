#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../math/modular/mod_sqrt.cpp"
#include "../math/modular/pow.cpp"
#include "../fps/ntt.cpp"

ll mod_pow(ll a, ll exponent, ll p) {
    return pow_(a, exponent, p);
}

ll square_mod(ll x, ll p) {
    return (__int128)x * x % p;
}

void check(ll a, ll p, bool exists) {
    ll result = mod_sqrt(a, p);
    assert((result != -1) == exists);
    if (exists) {
        assert(0 <= result && result < p);
        assert(square_mod(result, p) == ((__int128)a % p + p) % p);
    }
}

int main() {
    for (int p : {2, 3, 5, 7, 17, 41, 97, 257}) {
        vector<bool> square(p);
        for (ll x = 0; x < p; ++x) square[x * x % p] = true;
        for (ll a = -2 * p; a <= 2 * p; ++a) check(a, p, square[(a % p + p) % p]);
    }
    mt19937_64 rng(264);
    vector<ll> primes{2, 3, 5, 17, 257, 65537, 998244353, 1000000007, 2013265921, 4294967291LL,
                      1000000000039LL, (1LL << 61) - 1, 4179340454199820289LL,
                      9223372036854775549LL, 9223372036854775783LL};
    for (ll p : primes) {
        check(4, p, true);
        for (ll a : {LLONG_MIN, -p, -1LL, p - 1, p, LLONG_MAX}) {
            check(a, p, a % p == 0 || p == 2 || mod_pow(a, (p - 1) / 2, p) == 1);
        }
    }
    for (int mode = 0; mode < 3; ++mode) {
        for (int i = 0; i < 10000; ++i) {
            ll p = mode == 0 ? 998244353 : primes[mode == 1 ? i % primes.size() : rng() % primes.size()];
            ll x = rng() % p;
            ll a = square_mod(x, p);
            check(a, p, true);
            check(a - p, p, true);
            check(0, p, true);
            if (p != 2) {
                ll z = 2;
                while (mod_pow(z, (p - 1) / 2, p) == 1) ++z;
                check(z, p, false);
            }
        }
    }
    for (int i = 0; i < 10000; ++i) {
        mint a = rng() % ntt_mod, root = 123;
        ll expected = mod_sqrt(a.val, ntt_mod);
        bool ok = mod_sqrt(a, root);
        assert(ok == (expected != -1));
        if (ok) assert(root * root == a);
        else assert(root == mint(123));
        a *= a;
        assert(mod_sqrt(a, root) && root * root == a);
        assert(mod_sqrt(mint(0), root) && root == mint(0));
    }
}
