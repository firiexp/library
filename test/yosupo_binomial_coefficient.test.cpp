#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include <cstdint>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../math/CRT.cpp"
#include "../math/primefactor.cpp"
#include "../math/binom_mod_prime_power.cpp"

ll brute(ll n, ll k, ll mod) {
    if (k < 0 || k > n) return 0;
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1));
    dp[0][0] = 1 % mod;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j <= min(i, k); ++j) {
            dp[i + 1][j] += dp[i][j];
            dp[i + 1][j] %= mod;
            if (j != k) {
                dp[i + 1][j + 1] += dp[i][j];
                dp[i + 1][j + 1] %= mod;
            }
        }
    }
    return dp[n][k];
}

int main() {
    {
        map<ll, BinomModPrimePower> cache;
        for (int mod = 2; mod <= 120; ++mod) {
            auto pf = prime_factor<ll>(mod);
            vector<pair<ll, int>> fac;
            for (ll p : pf) {
                if (fac.empty() || fac.back().first != p) fac.emplace_back(p, 1);
                else fac.back().second++;
            }
            for (int n = 0; n <= 20; ++n) {
                for (int k = 0; k <= n; ++k) {
                    vector<pair<ll, ll>> rem;
                    for (auto [p, e] : fac) {
                        ll pe = 1;
                        for (int i = 0; i < e; ++i) pe *= p;
                        auto it = cache.find(pe);
                        if (it == cache.end()) it = cache.emplace(pe, BinomModPrimePower(p, e)).first;
                        rem.emplace_back(it->second.C(n, k), pe);
                    }
                    if (CRT(rem).first != brute(n, k, mod)) return 1;
                }
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    ll mod;
    sc.read(t, mod);
    auto pf = prime_factor<ll>(mod);
    vector<pair<ll, int>> fac;
    for (ll p : pf) {
        if (fac.empty() || fac.back().first != p) fac.emplace_back(p, 1);
        else fac.back().second++;
    }
    vector<BinomModPrimePower> binoms;
    vector<ll> mods;
    for (auto [p, e] : fac) {
        binoms.emplace_back(p, e);
        mods.emplace_back(binoms.back().modulus());
    }
    while (t--) {
        ll n, k;
        sc.read(n, k);
        vector<pair<ll, ll>> rem;
        for (int i = 0; i < (int)binoms.size(); ++i) {
            rem.emplace_back(binoms[i].C(n, k), mods[i]);
        }
        pr.writeln(CRT(rem).first);
    }
    return 0;
}
