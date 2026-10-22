#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../math/prime/primitive_root.cpp"

ll pow_mod(ll x, ll e, ll mod) {
    ll result = 1;
    while (e) {
        if (e & 1) result = (__int128)result * x % mod;
        x = (__int128)x * x % mod;
        e >>= 1;
    }
    return result;
}

bool trial_prime(int n) {
    for (int d = 2; d * d <= n; ++d) {
        if (n % d == 0) return false;
    }
    return n >= 2;
}

void check_large(ll p) {
    assert(miller_rabin(1000000007LL));
    assert(prime_factor(1000000016000000063LL) == vector<ll>({1000000007LL, 1000000009LL}));
    ll g = primitive_root(p);
    assert(1 <= g && g < p);
    auto factors = prime_factor(p - 1);
    factors.erase(unique(factors.begin(), factors.end()), factors.end());
    assert(pow_mod(g, p - 1, p) == 1);
    for (ll factor : factors) assert(pow_mod(g, (p - 1) / factor, p) != 1);
    for (ll candidate = 2; candidate < g; ++candidate) {
        bool rejected = false;
        for (ll factor : factors) rejected |= pow_mod(candidate, (p - 1) / factor, p) == 1;
        assert(rejected);
    }
    assert(primitive_root(p) == g);
}

int main() {
    assert(primitive_root(2) == 1);
    assert(primitive_root(3) == 2);
    for (int p = 2; p < 3000; ++p) {
        if (!trial_prime(p)) continue;
        ll g = primitive_root(p), x = 1;
        vector<bool> seen(p);
        for (int i = 0; i < p - 1; ++i) {
            assert(x != 0 && !seen[x]);
            seen[x] = true;
            x = x * g % p;
        }
        assert(x == 1);
    }
    vector<ll> moduli = {3, 17, 257, 65537, 998244353, 1000000007,
                        1000000000039LL, 2305843009213693951LL, 9223372036854775783LL};
    for (int round = 0; round < 2; ++round) {
        for (ll p : moduli) check_large(p);
        reverse(moduli.begin(), moduli.end());
    }
}
