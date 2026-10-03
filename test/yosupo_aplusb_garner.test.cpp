#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/garner.cpp"

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

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
