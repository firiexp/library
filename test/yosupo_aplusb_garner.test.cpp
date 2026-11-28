#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/modular/garner.cpp"
#include "../math/modular/garner.cpp"
#include "../math/modular/pow.cpp"
#include "../math/modular/modinv.cpp"
#include "../math/extgcd.cpp"
#include "../math/modular/crt.cpp"
#include "../util/biginteger.cpp"

void self_check() {
    auto check = [](vector<pair<ll, ll>> equations, ll mod) {
        ll modulus = 1;
        for (auto [r, m] : equations) modulus *= m;
        ll expected = -1;
        for (ll x = 0; x < modulus; ++x) {
            bool valid = true;
            for (auto [r, m] : equations) valid &= (x - r % m) % m == 0;
            if (valid) {
                expected = x % mod;
                break;
            }
        }
        assert(expected >= 0);
        assert(Garner(equations, mod) == expected);
        reverse(equations.begin(), equations.end());
        assert(Garner(equations, mod) == expected);
    };
    check({}, 1);
    check({}, 7);
    check({{-4, 3}}, 5);
    check({{LLONG_MIN, 7}, {LLONG_MAX, 5}}, 35);
    check({{LLONG_MAX, 1}, {-4, 3}}, 3);
    mt19937 rng(61);
    for (int tc = 0; tc < 3000; ++tc) {
        vector<ll> mods{1, 4, 5, 7, 9};
        shuffle(mods.begin(), mods.end(), rng);
        vector<pair<ll, ll>> equations(rng() % 6);
        for (int i = 0; i < int(equations.size()); ++i)
            equations[i] = {int(rng() % 201) - 100, mods[i]};
        check(equations, 1 + rng() % 30);
    }
}

void check_large() {
    vector<ll> moduli{LLONG_MAX, LLONG_MAX - 1, LLONG_MAX - 2};
    BigInteger product = BigInteger(moduli[0]) * moduli[1] * moduli[2];
    for (const BigInteger &x : {product - 1, product / 3, (BigInteger(1) << 150) + 42}) {
        vector<pair<ll, ll>> equations;
        for (ll m : moduli) {
            ll r = (x % m).to_integral<ll>().value();
            equations.emplace_back(r - m, m);
        }
        vector<pair<ll, ll>> reversed(equations.rbegin(), equations.rend());
        for (ll mod : {1LL, 14LL, LLONG_MAX - 3, LLONG_MAX}) {
            assert(Garner(equations, mod) == x % mod);
            assert(Garner(reversed, mod) == x % mod);
        }
    }
}

int main() {
    self_check();
    check_large();
}
