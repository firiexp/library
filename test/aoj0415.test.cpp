#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415"
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

#include "../graph/twoedgeconnectedcomponents.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> V(n);
    for (auto &&i : V) scanf("%d", &i);
    TwoEdgeConnectedComponents G_(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        G_.add_edge(u, v);
    }
    int k = G_.build();
    vector<vector<int>> G(k);
    vector<ll> v(k);
    for (int i = 0; i < k; ++i) {
        for (auto &&j : G_.out[i]) {
            v[i] += V[j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto &&j : G_.G[i]) {
            if(G_.is_bridge(i, j)){
                G[G_.bridge[i]].emplace_back(G_.bridge[j]);
            }
        }
    }
    ll ans = 0;
    auto dfs = [&](int x, int par, auto &&f) -> void {
        ll val1 = 0, val2 = 0;
        for (auto &&i : G[x]) {
            if(i == par) continue;
            f(i, x, f);
            if(val1 <= v[i]){
                val2 = val1; val1 = v[i];
            }else if(val2 <= v[i]){
                val2 = v[i];
            }
        }
        ans = max(ans, val1+val2+v[x]);
        v[x] += val1;
    };
    dfs(0, -1, dfs);
    cout << ans << "\n";
    return 0;
}