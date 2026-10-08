#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/pell_equation.cpp"

pair<__int128, __int128> oracle(ll n) {
    ll a0 = 0;
    while ((a0 + 1) * (a0 + 1) <= n) ++a0;
    if (a0 * a0 == n) return {0, 0};
    ll m = 0, d = 1, a = a0;
    __int128 x0 = 0, x1 = 1, y0 = 1, y1 = 0;
    while (true) {
        __int128 x = a * x1 + x0, y = a * y1 + y0;
        if (x > LLONG_MAX) return {-1, -1};
        if (x * x - n * y * y == 1) return {x, y};
        x0 = x1;
        x1 = x;
        y0 = y1;
        y1 = y;
        m = d * a - m;
        d = (n - m * m) / d;
        a = (a0 + m) / d;
    }
}

void self_check() {
    assert(sqrt_fraction(0) == vector<ll>{0});
    assert(sqrt_fraction(2) == (vector<ll>{1, 2}));
    assert(sqrt_fraction(3) == (vector<ll>{1, 1, 2}));
    assert(sqrt_fraction(13) == (vector<ll>{3, 1, 1, 1, 1, 6}));
    auto check = [](ll d, ll x, ll y) {
        assert(pell_equation(d) == make_pair(x, y));
        if (x) assert((__int128)x * x - (__int128)d * y * y == 1);
    };
    check(199, 16266196520LL, 1153080099LL);
    check(10000000000000001LL, 20000000000000001LL, 200000000LL);
    check(61, 1766319049, 226153980);
    for (ll d = 1; d <= 2000; ++d) {
        auto [x, y] = oracle(d);
        if (x >= 0) {
            check(d, (ll)x, (ll)y);
        }
    }
    vector<ll> ks{2, 3, 100000000, 2147483647};
    mt19937_64 rng(119);
    for (int tc = 0; tc < 500; ++tc) ks.push_back(2 + rng() % 2147483646);
    for (ll k : ks) {
        check(k * k - 1, k, 1);
        check(k * k, 0, 0);
        assert(sqrt_fraction(k * k) == vector<ll>{k});
        check(k * k + 1, 2 * k * k + 1, 2 * k);
        assert(sqrt_fraction(k * k + 1) == (vector<ll>{k, 2 * k}));
    }
    check(3037000499LL * 3037000499LL - 1, 3037000499LL, 1);
    check(3037000499LL * 3037000499LL, 0, 0);
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
