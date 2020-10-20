#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0438"
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
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../string/rolling_hash_u64.cpp"
#include "../util/makev.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    vector<char> c(n);
    for (auto &&i : c) cin >> i;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        G[a].emplace_back(b);
    }
    rolling_hash_u64 ro(n);
    int B = 19;
    auto dp = make_v(B, n, u64(0));
    auto to = make_v(B, n, -1);
    for (int i = 0; i+1 < n; ++i) {
        G[i].emplace_back(i+1);
    }
    auto ok = [&](int x, int y){
        for (int i = B-1; i >= 0; --i) {
            if(~to[i][x] && ~to[i][y] && dp[i][x] == dp[i][y]){
                x = to[i][x], y = to[i][y];
            }
        }
        while(true){
            if(c[x] != c[y]) return c[x] < c[y];
            x = to[0][x], y = to[0][y];
            if(y == -1) return false;
            if(x == -1) return true;
        }
    };
    for (int i = n-1; i >= 0; --i) {
        for (auto &&j : G[i]) {
            if(to[0][i] == -1 || ok(j, to[0][i])) to[0][i] = j;
        }
        if(to[0][i] != -1){
            dp[0][i] = c[i];
            for (int j = 1; j < B; ++j) {
                to[j][i] = to[j-1][to[j-1][i]];
                if(~to[j][i]) {
                    dp[j][i] = ro.mul(dp[j-1][i], ro.p()[1 << (j-1)])+dp[j-1][to[j-1][i]];
                    if(dp[j][i] >= M) dp[j][i] -= M;
                }else break;
            }
        }
    }
    int x = 0;
    while(true){
        cout << c[x];
        if(x == n-1) break;
        x = to[0][x];
    }
    puts("");
    return 0;
}
