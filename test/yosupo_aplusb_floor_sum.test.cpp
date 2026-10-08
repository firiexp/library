#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/floor_sum.cpp"

__int128 brute(ll n, ll m, ll a, ll b) {
    __int128 ans = 0;
    for (ll i = 0; i < n; ++i) {
        __int128 x = (__int128)a * i + b;
        ans += x / m - (x % m < 0);
    }
    return ans;
}

void self_check() {
    assert(floor_sum(4000000000LL, 1, 1, 0) == 7999999998000000000LL);
    assert(floor_sum(2, 3, -1, 0) == -1);
    assert(floor_sum(4294967295LL, 1, 1, -2147483647LL) == 0);
    assert(floor_sum(4294967295LL, 1, -1, 2147483647LL) == 0);
    for (ll m = 1; m <= 20; ++m) {
        for (ll a = -20; a <= 20; ++a) {
            for (ll b = -20; b <= 20; ++b) {
                for (ll n = 0; n <= 20; ++n) {
                    assert(floor_sum(n, m, a, b) == brute(n, m, a, b));
                }
            }
        }
    }
    vector<ll> edge{LLONG_MIN, LLONG_MIN + 1, -1, 0, 1, LLONG_MAX};
    for (ll a : edge) {
        for (ll b : edge) {
            for (ll m : {1LL, 3LL, 4294967295LL}) {
                for (ll n = 0; n <= 5; ++n) {
                    __int128 expected = brute(n, m, a, b);
                    if (expected >= LLONG_MIN && expected <= LLONG_MAX) {
                        assert(floor_sum(n, m, a, b) == expected);
                    }
                }
            }
        }
    }
    mt19937_64 rng(85);
    for (int tc = 0; tc < 10000; ++tc) {
        ll n = rng() % 50, m = 1 + rng() % 4294967295ULL;
        ll a = (ll)(rng() & LLONG_MAX), b = (ll)(rng() & LLONG_MAX);
        if (rng() & 1) a = -a;
        if (rng() & 1) b = -b;
        __int128 expected = brute(n, m, a, b);
        if (expected >= LLONG_MIN && expected <= LLONG_MAX) {
            assert(floor_sum(n, m, a, b) == expected);
        }
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
