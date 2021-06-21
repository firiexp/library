#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/modint.cpp"

int main() {
    ll n;
    cin >> n;
    const ll k = 20000000; // 20000000
    vector<int> dp(k+1);
    iota(dp.begin(),dp.end(), 0);
    for (int i = 2; i <= k; ++i) {
        if(dp[i] != i) continue;
        for (int j = i; j <= k; j += i) {
            dp[j] = dp[j]/i*(i-1);
        }
    }
    vector<mint> a(k+1);
    for (int i = 0; i < k; ++i) {
        a[i+1] = a[i] + dp[i+1];
    }
    vector<mint> memo(n/k+1);
    vector<bool> calced(n/k+1);
    mint pp = mint(2).inv();
    auto rec = [&](ll x, auto &&f) -> mint {
        if(x <= k) return a[x];
        if(calced[n/x]) return memo[n/x];
        auto res = mint(x)*mint(x+1)*pp;
        for (ll i = 2; i <= x; ++i) {
            ll j = x/i, newi = (i > j ? x/j : i);
            res -= mint(newi-i+1)*f(x/i, f);
            i = newi;
        }
        return calced[n/x] = 1, memo[n/x] = res;
    };
    cout << rec(n, rec).val << "\n";
    return 0;
}