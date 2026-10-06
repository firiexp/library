#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/SCC.cpp"

void check(SCC &g, int n, const vector<pair<int, int>> &edges) {
    int k = g.build();
    assert(int(g.cmp.size()) == n && int(g.sz.size()) == k);
    assert(int(g.G_out.size()) == k);
    vector<vector<bool>> reachable(n, vector<bool>(n));
    for (int v = 0; v < n; ++v) reachable[v][v] = true;
    for (auto [u, v] : edges) reachable[u][v] = true;
    for (int w = 0; w < n; ++w)
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < n; ++v)
                reachable[u][v] = reachable[u][v] || (reachable[u][w] && reachable[w][v]);
    vector<int> sizes(k);
    for (int u = 0; u < n; ++u) {
        assert(0 <= g[u] && g[u] < k);
        ++sizes[g[u]];
        for (int v = 0; v < n; ++v)
            assert((g[u] == g[v]) == (reachable[u][v] && reachable[v][u]));
    }
    assert(g.sz == sizes);
    for (int size : sizes) assert(size > 0);
    vector<set<int>> dag(k);
    for (auto [u, v] : edges) {
        if (g[u] == g[v]) continue;
        assert(g[u] < g[v]);
        dag[g[u]].insert(g[v]);
    }
    for (int c = 0; c < k; ++c)
        assert(g.G_out[c] == vector<int>(dag[c].begin(), dag[c].end()));
    auto cmp = g.cmp;
    auto out = g.G_out;
    assert(g.build() == k);
    assert(g.cmp == cmp && g.sz == sizes && g.G_out == out);
}

void check_scc() {
    SCC empty;
    check(empty, 0, {});
    mt19937 rng(20261006);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = rng() % 13;
        SCC g(n);
        vector<pair<int, int>> edges;
        check(g, n, edges);
        if (n == 0) continue;
        for (int phase = 0; phase < 3; ++phase) {
            int m = rng() % (n * n + 1);
            for (int i = 0; i < m; ++i) {
                int u = rng() % n, v = rng() % n;
                g.add_edge(u, v);
                edges.emplace_back(u, v);
                if (i % 3 == 0) {
                    g.add_edge(u, v);
                    edges.emplace_back(u, v);
                }
            }
            check(g, n, edges);
        }
    }
    int n = 20000;
    SCC fanout(n), single(n);
    for (int v = 0; v < n; ++v) {
        single.add_edge(0, v);
        single.add_edge(v, 0);
        for (int repeat = 0; repeat < 10; ++repeat) fanout.add_edge(0, v);
    }
    assert(fanout.build() == n);
    vector<int> expected(n - 1);
    iota(expected.begin(), expected.end(), 1);
    assert(fanout[0] == 0 && fanout.G_out[0] == expected);
    for (int c = 1; c < n; ++c) assert(fanout.G_out[c].empty());
    assert(single.build() == 1 && single.sz == vector<int>{n});
    assert(single.G_out == vector<vector<int>>(1));
}

int main() {
    check_scc();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
