#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../math/modular/discrete_logarithm_table.cpp"
#include "../math/modular/discrete_logarithm.cpp"

vector<ll> first_exponents(ll x, int mod) {
    vector<ll> first(mod, -1);
    x %= mod;
    if (x < 0) x += mod;
    ll value = 1 % mod;
    for (ll e = 0; first[value] < 0; ++e) {
        first[value] = e;
        value = value * x % mod;
    }
    return first;
}

int main() {
    for (int mod = 1; mod <= 120; ++mod) {
        for (int x = 0; x < mod; ++x) {
            if (gcd(x, mod) != 1) continue;
            const auto first = first_exponents(x, mod);
            const DiscreteLogarithmTable table(x, mod), negative(x - mod, mod);
            for (int y = mod - 1; y >= 0; --y) {
                for (ll value : {ll(y), ll(y - mod), ll(y + 3 * mod)}) {
                    assert(table.log(value) == first[y]);
                    assert(negative.log(value) == first[y]);
                }
            }
            for (ll y : {LLONG_MIN, LLONG_MAX}) {
                ll normalized = (y % mod + mod) % mod;
                assert(table.log(y) == first[normalized]);
            }
            const auto copy = table;
            assert(copy.log(1) == 0);
        }
    }
    for (ll x : {LLONG_MIN, LLONG_MAX}) {
        for (int mod : {1, 2, 17, 64, 81, 1000}) {
            ll normalized = (x % mod + mod) % mod;
            if (gcd(normalized, ll(mod)) != 1) continue;
            const auto first = first_exponents(x, mod);
            const DiscreteLogarithmTable table(x, mod);
            for (int y = 0; y < mod; ++y) assert(table.log(y) == first[y]);
        }
    }
    mt19937_64 rng(363);
    for (ll mod : {1000000007LL, 1000000000LL}) {
        const DiscreteLogarithmTable table(3, mod);
        for (int i = 0; i < 20; ++i) {
            ll y = rng() % mod;
            assert(table.log(y) == discrete_logarithm(3, y, mod));
        }
    }
    for (ll mod : {998244353LL, 1000000000039LL}) {
        const DiscreteLogarithmTable one(1, mod), minus_one(mod - 1, mod);
        assert(one.log(1) == 0);
        assert(one.log(2) == -1);
        assert(minus_one.log(-1) == 1);
        assert(minus_one.log(2) == -1);
        assert(minus_one.log(1) == 0);
    }
}
