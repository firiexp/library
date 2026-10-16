#define PROBLEM "https://judge.yosupo.jp/problem/k_shortest_walk"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../graph/k_shortest_walk.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m, s, t, k;
    in.read(n, m, s, t, k);
    vector<vector<edge<ll>>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        in.read(u, v, w);
        g[u].emplace_back(v, w);
    }
    auto costs = k_shortest_walk(s, t, k, g);
    for (int i = 0; i < k; ++i) out.println(i < (int)costs.size() ? costs[i] : -1);
}
