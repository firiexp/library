#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/CRT.cpp"

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
    mt19937 rng(61);
    for (int tc = 0; tc < 3000; ++tc) {
        vector<pair<ll, ll>> equations(rng() % 5);
        for (auto &[r, m] : equations) {
            r = int(rng() % 201) - 100;
            m = 1 + rng() % 10;
        }
        check(equations);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
