#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/lowlink.cpp"

int components(int n, const vector<pair<int, int>> &edges, int vertex, int edge) {
    vector<vector<int>> g(n);
    for (int i = 0; i < (int)edges.size(); ++i) {
        auto [u, v] = edges[i];
        if (i == edge || u == vertex || v == vertex) continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<bool> seen(n);
    int count = 0;
    for (int v = 0; v < n; ++v) {
        if (v == vertex || seen[v]) continue;
        ++count;
        vector<int> q{v};
        seen[v] = true;
        for (int p = 0; p < (int)q.size(); ++p) {
            for (int u : g[q[p]]) {
                if (seen[u]) continue;
                seen[u] = true;
                q.push_back(u);
            }
        }
    }
    return count;
}

void check(int n, const vector<pair<int, int>> &edges) {
    LowLink g(n);
    for (auto [u, v] : edges) g.add_edge(u, v);
    auto input = g.edges;
    int base = components(n, edges, -1, -1);
    vector<pair<int, int>> bridges;
    for (int i = 0; i < (int)edges.size(); ++i) {
        auto [u, v] = edges[i];
        if (components(n, edges, -1, i) > base) bridges.emplace_back(min(u, v), max(u, v));
    }
    sort(bridges.begin(), bridges.end());
    vector<int> articulation;
    for (int v = 0; v < n; ++v)
        if (components(n, edges, v, -1) > base) articulation.push_back(v);
    g.build();
    auto ord = g.ord, low = g.low, par = g.par;
    for (int repeat = 0; repeat < 2; ++repeat) {
        assert(g.edges == input && g.bridge == bridges && g.articulation == articulation);
        assert(g.ord == ord && g.low == low && g.par == par);
        for (int v = 0; v < n; ++v)
            assert(bool(g.cut[v]) == binary_search(articulation.begin(), articulation.end(), v));
        for (auto [u, v] : input)
            assert(g.is_bridge(u, v) == binary_search(bridges.begin(), bridges.end(), make_pair(min(u, v), max(u, v))));
        g.build();
    }
}

void self_check() {
    for (int n = 0; n <= 5; ++n) {
        vector<pair<int, int>> all;
        for (int u = 0; u < n; ++u)
            for (int v = u + 1; v < n; ++v) all.emplace_back(u, v);
        for (int mask = 0; mask < (1 << all.size()); ++mask) {
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)all.size(); ++i)
                if (mask >> i & 1) edges.push_back(all[i]);
            check(n, edges);
        }
    }
    mt19937 rng(143);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + rng() % 15, m = rng() % 35;
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; ++i) edges.emplace_back(rng() % n, rng() % n);
        check(n, edges);
    }
    for (int n : {2, 31, 32, 33, 1000, 65536}) {
        int threshold = 1;
        while (threshold < n - 1 && 1LL * (threshold + 1) * (32 - __builtin_clz((unsigned)threshold)) <= n) ++threshold;
        for (int b : {0, 1, threshold - 1, threshold, min(n - 1, threshold + 1), n - 1}) {
            vector<pair<int, int>> edges;
            for (int v = 1; v <= b; ++v) edges.emplace_back(0, v);
            auto expected = edges;
            for (int order = 0; order < 3; ++order) {
                if (order == 1) reverse(edges.begin(), edges.end());
                if (order == 2) shuffle(edges.begin(), edges.end(), rng);
                LowLink g(n);
                for (auto [u, v] : edges) g.add_edge(v, u);
                g.build();
                assert(g.bridge == expected);
                g.build();
                assert(g.bridge == expected);
            }
        }
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
