#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0274"
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

#include "../util/makev.cpp"

#include "../flow/primaldual.cpp"

void solve(int d, int k, int l){
    vector<vector<int>> v(d, vector<int>(k, 0));
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> v[i][j];
        }
    }
    auto dp = make_v(d+1, l+1, 1 << (2*k), INF<int>);
    dp[0][0][0] = 0;
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j <= l; ++j) {
            for (int m = 0; m < 1 << (2*k); ++m) {
                chmin(dp[i+1][0][m], dp[i][j][m]);
                if(j == l || dp[i][j][m] == INF<int>) continue;
                for (int n = 0; n < k; ++n) {
                    if(((m >> 2*n)&3) == 2) continue;
                    chmin(dp[i][j+1][m+(1 << 2*n)], dp[i][j][m]+v[i][n]);
                }
            }
        }
    }
    int m, n, p;
    cin >> m >> n >> p;
    auto R = make_v(m, k, 0);
    auto T = make_v(p+1, k, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> R[i][j];
        }
    }
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> T[i][j];
        }
    }
    p++;
    PrimalDual<int, int> G(m+p+2);
    for (int i = 0; i < m; ++i) {
        G.add_edge(0, i+2, 1, 0);
    }
    for (int i = 0; i < p; ++i) {
        G.add_edge(m+2+i, 1, (i == p-1 ? n : 1), 0);
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            int S = 0;
            for (int o = 0; o < k; ++o) {
                if(R[i][o] < T[j][o]) {
                    S = -1;
                    break;
                }
                S |= (1 << 2*o)*(R[i][o]-T[j][o]);
            }
            if(S >= 0 && dp.back()[0][S] < INF<int>){
                G.add_edge(i+2, m+2+j, 1, dp.back()[0][S]);
            }
        }
    }
    int ok = 0;
    auto res = G.flow(0, 1, n, ok);
    if(!ok) puts("-1");
    else cout << res << "\n";
}

int main() {
    int d, k, l;
    while(cin >> d >> k >> l, d){
        solve(d, k, l);
    }
    return 0;
}