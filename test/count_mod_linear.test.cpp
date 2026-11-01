#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../math/count_mod_linear.cpp"

ll brute(ll n, ll m, ll a, ll b, ll l, ll r) {
    ll count = 0;
    for (ll i = 0; i < n; ++i) {
        ll x = ((__int128)a * i + b) % m;
        if (x < 0) x += m;
        count += l <= x && x < r;
    }
    return count;
}

void check(ll n, ll m, ll a, ll b, ll l, ll r) {
    assert(count_mod_linear(n, m, a, b, l, r) == brute(n, m, a, b, l, r));
}

int main() {
    for (ll n = 0; n <= 6; ++n) {
        for (ll m = 1; m <= 8; ++m) {
            for (ll a = -8; a <= 8; ++a) {
                for (ll b = -8; b <= 8; ++b) {
                    for (ll l = 0; l <= m; ++l) {
                        for (ll r = l; r <= m; ++r) check(n, m, a, b, l, r);
                    }
                }
            }
        }
    }
    const ll limit = (1LL << 32) - 1;
    const vector<ll> boundary{LLONG_MIN, LLONG_MIN + 1, -1, 0, 1, LLONG_MAX};
    for (ll a : boundary) {
        for (ll b : boundary) {
            for (ll m : {1LL, 7LL, limit - 1, limit}) {
                for (ll n : {0LL, 1LL, 50LL}) {
                    check(n, m, a, b, 0, m / 2);
                    check(n, m, a, b, m / 2, m);
                }
            }
            for (ll m = 1; m <= 17; ++m) {
                for (ll l = 0; l <= m; ++l) {
                    ll expected = limit / m * brute(m, m, a, b, l, m)
                                + brute(limit % m, m, a, b, l, m);
                    assert(count_mod_linear(limit, m, a, b, l, m) == expected);
                }
            }
        }
    }
    for (ll m : {limit - 1, limit}) {
        for (ll a : {1LL, m - 1}) {
            for (ll b : boundary) {
                for (auto [l, r] : vector<pair<ll, ll>>{{0, 0}, {0, 1}, {0, m}, {1, m}, {m / 2, m - 1}, {m, m}}) {
                    ll expected = r - l + brute(limit - m, m, a, b, l, r);
                    assert(count_mod_linear(limit, m, a, b, l, r) == expected);
                }
            }
        }
    }
    mt19937_64 rng(353);
    for (int t = 0; t < 20000; ++t) {
        ll n = rng() % 80, m = 1 + rng() % limit;
        ll a = rng() & LLONG_MAX, b = rng() & LLONG_MAX;
        if (rng() & 1) a = -a;
        if (rng() & 1) b = -b;
        ll l = rng() % (m + 1), r = rng() % (m + 1);
        if (l > r) swap(l, r);
        check(n, m, a, b, l, r);
    }
}
