#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0422"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/makev.cpp"

#include "../util/modint_arbitrary.cpp"
int main() {
    int n, k, m;
    cin >> n >> k >> m;
    mint::set_mod(m);
    vector<int> a(2*k-1);
    for (int i = 0; i < 2*k-1; ++i) {
        a[i] = i-k+1;
    }
    auto dp = make_v(k, 1 << a.size(), mint(0));
    for (int i = 0; i < k; ++i) {
        dp[i][0] = 1;
    }
    mint ans = mint(k).pow(n);
    for (int S = 0; S < (1 << a.size()); ++S) {
        for (int i = 0; i < a.size(); ++i) {
            if(S & (1 << i)){
                for (int j = 0; j < k; ++j) {
                    if(0 <= j+a[i] && j+a[i] < k) dp[j+a[i]][S] += dp[j][S^(1<<i)];
                }
            }
        }
        if(__builtin_popcount(S) == n-1) {
            for (int i = 0; i < k; ++i) ans -= dp[i][S];
        }
    }
    cout << ans.val << "\n";
    return 0;
}