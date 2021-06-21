#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0377"
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

#include "../graph/twoedgeconnectedcomponents.cpp"

#include "../datastructure/unionfind.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    TwoEdgeConnectedComponents G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    int k = G.build();
    vector<vector<int>> g(k);
    vector<int> v(k);
    UnionFind uf(k);
    for (int i = 0; i < k; ++i) v[i] = G.out[i].size();
    for (int i = 0; i < n; ++i) {
        for (auto &&j : G.G[i]) {
            if(G.is_bridge(i, j)){
                g[G.bridge[i]].emplace_back(G.bridge[j]);
                uf.unite(G.bridge[i], G.bridge[j]);
            }
        }
    }
    int ans = 0;
    vector<int> dp1(v), dp2(k);
    auto dfs = [&](int x, int par, auto &&f) -> void{
        for (auto &&y : g[x]) {
            if(y == par) continue;
            f(y, x, f);
            dp2[x] += max(dp1[y], dp2[y]);
            dp1[x] += dp2[y];
        }
    };
    for (int i = 0; i < k; ++i) {
        if(uf.root(i) == i) {
            dfs(i, -1, dfs);
            ans += max(dp1[i], dp2[i]);
        }
    }
    cout << ans << "\n";
    return 0;
}