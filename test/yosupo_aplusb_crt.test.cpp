#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/modular/crt.cpp"

void self_check() {
    auto check = [](vector<pair<ll, ll>> equations) {
        ll modulus = 1;
        for (auto [r, m] : equations) modulus = lcm(modulus, m);
        pair<ll, ll> expected{0, 0};
        for (ll x = 0; x < modulus; ++x) {
            bool valid = true;
            for (auto [r, m] : equations) valid &= (x - r % m) % m == 0;
            if (valid) {
                expected = {x, modulus};
                break;
            }
        }
        assert(CRT(equations) == expected);
        reverse(equations.begin(), equations.end());
        assert(CRT(equations) == expected);
    };
    check({});
    check({{2, 3}, {-4, 3}});
    check({{1, 2}, {0, 4}});
    check({{LLONG_MIN, 7}, {LLONG_MAX, 5}});
    check({{LLONG_MAX, 1}});
    auto check_large = [](ll r, ll m, ll s, ll n) {
        ll count = m / gcd(m, n);
        __int128 modulus = __int128(count) * n;
        assert(modulus <= LLONG_MAX);
        s %= n;
        if (s < 0) s += n;
        pair<ll, ll> expected{0, 0};
        for (ll k = 0; k < count; ++k) {
            __int128 x = __int128(k) * n + s;
            if ((x - r) % m == 0) {
                expected = {(ll)x, (ll)modulus};
                break;
            }
        }
        assert(CRT({{r, m}, {s, n}}) == expected);
        assert(CRT({{s, n}, {r, m}}) == expected);
    };
    check_large(0, 2, 4000000000000000000LL, 4000000000000000001LL);
    check_large(LLONG_MIN, 1, LLONG_MIN, LLONG_MAX);
    check_large(0, 2, 1, LLONG_MAX - 1);
    check_large(LLONG_MIN, 7, LLONG_MAX, LLONG_MAX);
    mt19937 rng(61);
    for (int tc = 0; tc < 3000; ++tc) {
        vector<pair<ll, ll>> equations(rng() % 5);
        for (auto &[r, m] : equations) {
            r = int(rng() % 201) - 100;
            m = 1 + rng() % 10;
        }
        check(equations);
    }
    mt19937_64 rng64(398);
    for (int tc = 0; tc < 3000; ++tc) {
        ll m = 1 + rng64() % 32;
        ll n = LLONG_MAX / m - rng64() % 1000;
        ll r = tc % 2 ? LLONG_MIN + tc : LLONG_MAX - tc;
        ll s = tc % 3 ? LLONG_MIN + tc : LLONG_MAX - tc;
        check_large(r, m, s, n);
    }
}

int main() {
    self_check();
}
