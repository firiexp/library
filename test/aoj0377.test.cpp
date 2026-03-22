#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0377"

#include <algorithm>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/bridge_tree.cpp"
#include "../datastructure/unionfind.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    BridgeTree g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        sc.read(a, b);
        g.add_edge(a, b);
    }
    int k = g.build();
    vector<int> v(k);
    UnionFind uf(k);
    for (int i = 0; i < k; ++i) v[i] = g.nodes[i].size();
    for (auto &&e : g.edges) {
        uf.unite(e.first, e.second);
    }
    int ans = 0;
    vector<int> dp1(v), dp2(k);
    auto dfs = [&](int x, int par, auto &&f) -> void{
        for (auto &&y : g.tree[x]) {
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
    pr.println(ans);
    return 0;
}
