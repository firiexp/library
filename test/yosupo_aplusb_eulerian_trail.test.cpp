#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/eulerian_trail.cpp"

template<bool directed>
bool brute_exists(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    vector<vector<int>> memo(n, vector<int>(1 << m, -1));
    auto dfs = [&](auto &&self, int v, int mask) -> bool {
        if (mask == (1 << m) - 1) return true;
        int &result = memo[v][mask];
        if (result != -1) return result;
        result = 0;
        for (int i = 0; i < m; ++i) {
            if ((mask >> i) & 1) continue;
            auto [a, b] = edges[i];
            if ((a == v && self(self, b, mask | (1 << i))) ||
                (!directed && b == v && self(self, a, mask | (1 << i)))) {
                result = 1;
                return true;
            }
        }
        return false;
    };
    for (int v = 0; v < n; ++v) if (dfs(dfs, v, 0)) return true;
    return false;
}

template<bool directed>
void check(int n, const vector<pair<int, int>> &edges) {
    EulerianTrail<directed> graph(n);
    int m = edges.size();
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edges[i];
        assert(graph.add_edge(u, v) == i);
    }
    const auto adjacency = graph.g;
    auto result = graph.solve();
    assert(result.exists == brute_exists<directed>(n, edges));
    auto repeated = graph.solve();
    assert(result.exists == repeated.exists);
    assert(result.vertices == repeated.vertices);
    assert(result.edge_ids == repeated.edge_ids);
    assert(graph.g == adjacency && (int)graph.edges.size() == m);
    for (int i = 0; i < m; ++i) {
        assert(graph.edges[i].from == edges[i].first);
        assert(graph.edges[i].to == edges[i].second);
    }
    if (!result.exists) {
        assert(result.vertices.empty() && result.edge_ids.empty());
        return;
    }
    assert((int)result.vertices.size() == m + 1);
    assert((int)result.edge_ids.size() == m);
    if (m == 0) assert(result.vertices == vector<int>{0});
    vector<bool> used(m);
    for (int v : result.vertices) assert(0 <= v && v < n);
    for (int i = 0; i < m; ++i) {
        int id = result.edge_ids[i];
        assert(0 <= id && id < m && !used[id]);
        used[id] = true;
        auto [a, b] = edges[id];
        int u = result.vertices[i], v = result.vertices[i + 1];
        assert((a == u && b == v) || (!directed && a == v && b == u));
    }
}

template<bool directed>
void self_check() {
    check<directed>(1, {});
    check<directed>(5, {});
    check<directed>(1, { {0, 0}, {0, 0}, {0, 0} });
    check<directed>(3, { {0, 1}, {1, 2} });
    check<directed>(3, { {0, 1}, {1, 2}, {2, 0} });
    check<directed>(2, { {0, 1}, {0, 1}, {1, 0}, {0, 0} });
    check<directed>(4, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    check<directed>(3, { {0, 1}, {0, 2} });
    check<directed>(4, { {1, 2}, {2, 1}, {1, 3}, {3, 1} });
    mt19937 rng(20261021);
    for (int tc = 0; tc < 2500; ++tc) {
        int n = rng() % 7 + 1, m = rng() % 11;
        vector<pair<int, int>> edges;
        int v = rng() % n;
        for (int i = 0; i < m; ++i) {
            int u = tc % 2 ? v : rng() % n;
            v = rng() % n;
            edges.emplace_back(u, v);
        }
        check<directed>(n, edges);
    }
    EulerianTrail<directed> path(3);
    path.add_edge(0, 1);
    path.add_edge(1, 2);
    assert(path.solve().exists);
    path.add_edge(2, 0);
    auto result = path.solve();
    assert(result.exists && result.edge_ids.size() == 3);
}

int main() {
    self_check<true>();
    self_check<false>();
}
