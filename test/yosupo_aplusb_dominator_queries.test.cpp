#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/dominatortree.cpp"

vector<bool> bfs(const vector<vector<int>> &g, int root, int removed) {
    vector<bool> seen(g.size());
    if (root == removed) return seen;
    vector<int> q{root};
    seen[root] = true;
    for (int i = 0; i < (int)q.size(); ++i) {
        for (int to : g[q[i]]) if (to != removed && !seen[to]) {
            seen[to] = true;
            q.push_back(to);
        }
    }
    return seen;
}

void check(const vector<vector<int>> &g) {
    int n = g.size();
    DominatorTree dt(n);
    for (int u = 0; u < n; ++u) for (int v : g[u]) dt.add_edge(u, v);
    const auto &queries = dt;
    for (int root = n - 1; root >= 0; --root) {
        dt.build(root);
        auto original = bfs(g, root, -1);
        vector<vector<bool>> without;
        for (int removed = 0; removed < n; ++removed) without.push_back(bfs(g, root, removed));
        for (int v = 0; v < n; ++v) {
            assert(queries.reachable(v) == original[v]);
            for (int u = 0; u < n; ++u) {
                assert(queries.dominates(u, v) == (original[v] && !without[u][v]));
                assert(queries.reachable_without_vertex(v, u) == without[u][v]);
            }
            int immediate = -1;
            if (v != root && original[v]) {
                for (int d = 0; d < n; ++d) if (d != v && !without[d][v]) {
                    bool deepest = true;
                    for (int u = 0; u < n; ++u) {
                        if (u != v && u != d && !without[u][v] && without[u][d]) deepest = false;
                    }
                    if (deepest) {
                        assert(immediate == -1);
                        immediate = d;
                    }
                }
            }
            assert(dt.idom[v] == immediate);
        }
        auto idom = dt.idom;
        dt.build(root);
        assert(dt.idom == idom);
    }
}

void self_check() {
    check({{}});
    check({{0, 0}});
    check({{1, 3}, {2}, {}, {2}, {4}});
    check({{1, 1}, {2, 1}, {0}, {4}, {}, {}});
    for (int mask = 0; mask < (1 << 9); ++mask) {
        vector<vector<int>> g(3);
        for (int u = 0; u < 3; ++u) for (int v = 0; v < 3; ++v) {
            if (mask >> (3 * u + v) & 1) g[u].push_back(v);
        }
        check(g);
    }
    mt19937 random(195);
    for (int tc = 0; tc < 400; ++tc) {
        int n = 1 + random() % 9;
        vector<vector<int>> g(n);
        for (int i = random() % (n * n + 1); i; --i) g[random() % n].push_back(random() % n);
        check(g);
    }
    DominatorTree dt(3);
    dt.add_edge(0, 1);
    dt.add_edge(1, 2);
    dt.build(0);
    assert(!dt.reachable_without_vertex(2, 1));
    dt.add_edge(0, 2);
    dt.build(0);
    assert(dt.reachable_without_vertex(2, 1));
    dt.build(2);
    assert(!dt.reachable(0) && !dt.reachable(1) && dt.reachable(2));
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
