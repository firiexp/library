#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/min_of_mod_of_linear.cpp"

__int128 sum_floor(__int128 n, __int128 m, __int128 a, __int128 b) {
    __int128 ans = 0;
    while (true) {
        ans += n * (n - 1) / 2 * (a / m) + n * (b / m);
        a %= m;
        b %= m;
        __int128 y = a * n + b;
        if (y < m) return ans;
        n = y / m;
        b = y % m;
        swap(a, m);
    }
}

ll binary_search_min(ll n, ll m, ll a, ll b) {
    __int128 base = sum_floor(n, m, a, b);
    ll lo = -1, hi = m - 1;
    while (hi - lo > 1) {
        ll mid = lo + (hi - lo) / 2;
        __int128 greater = sum_floor(n, m, a, (__int128)b + m - 1 - mid) - base;
        if (greater < n) hi = mid;
        else lo = mid;
    }
    return hi;
}

void self_check() {
    for (ll m = 1; m <= 50; ++m) {
        for (ll a = 0; a < m; ++a) {
            for (ll b = 0; b < m; ++b) {
                ll expected = m;
                for (ll n = 1; n <= 60; ++n) {
                    expected = min(expected, (a * (n - 1) + b) % m);
                    assert(min_of_mod_of_linear(n, m, a, b) == expected);
                }
            }
        }
    }
    mt19937_64 rng(125);
    for (int tc = 0; tc < 10000; ++tc) {
        ll m = 1 + rng() % LLONG_MAX, a = rng() % m, b = rng() % m;
        ll n = 1 + rng() % 100, expected = m;
        for (ll x = 0; x < n; ++x) {
            expected = min(expected, (ll)(((__int128)a * x + b) % m));
        }
        assert(min_of_mod_of_linear(n, m, a, b) == expected);
        assert(min_of_mod_of_linear(LLONG_MAX, m, a, b) == b % gcd(a, m));
    }
    for (ll m : {1LL, 2LL, 4294967295LL, LLONG_MAX - 1, LLONG_MAX}) {
        for (ll a : {0LL, m / 2, m - 1}) {
            for (ll b : {0LL, m / 2, m - 1}) {
                for (ll n : {1LL, 2LL, LLONG_MAX / 2, LLONG_MAX}) {
                    assert(min_of_mod_of_linear(n, m, a, b) == binary_search_min(n, m, a, b));
                }
            }
        }
    }
    for (int tc = 0; tc < 1000; ++tc) {
        ll n = 1 + rng() % LLONG_MAX, m = 1 + rng() % LLONG_MAX;
        ll a = rng() % m, b = rng() % m;
        assert(min_of_mod_of_linear(n, m, a, b) == binary_search_min(n, m, a, b));
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
