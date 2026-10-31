#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    for (int mod = 1; mod <= 90; ++mod) {
        for (int x = 0; x < mod; ++x) {
            const auto first = first_exponents(x, mod);
            for (int y = 0; y < mod; ++y) {
                assert(discrete_logarithm(x, y, mod) == first[y]);
                assert(discrete_logarithm(x - mod, y - mod, mod) == first[y]);
            }
        }
    }
    for (ll x : {LLONG_MIN, LLONG_MAX}) {
        for (int mod : {1, 2, 17, 64, 81, 1000}) {
            const auto first = first_exponents(x, mod);
            for (ll y : {LLONG_MIN, LLONG_MAX, 0LL, 1LL}) {
                ll normalized = (y % mod + mod) % mod;
                assert(discrete_logarithm(x, y, mod) == first[normalized]);
            }
        }
    }
    assert(discrete_logarithm(0, 0, 1000000007) == 1);
    assert(discrete_logarithm(0, 1, 1000000007) == 0);
    assert(discrete_logarithm(2, 0, 1LL << 60) == 60);
    assert(discrete_logarithm(2, 1LL << 40, 1LL << 60) == 40);
    assert(discrete_logarithm(2, 3LL << 40, 1LL << 60) == -1);
    for (ll mod : {998244353LL, 1000000000039LL}) {
        assert(discrete_logarithm(1, 2, mod) == -1);
        assert(discrete_logarithm(mod - 1, 2, mod) == -1);
        assert(discrete_logarithm(mod - 1, mod - 1, mod) == 1);
    }
}
