#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/unionfind/unionfind.cpp"
#include "../graph/cycle_detection_undirected.cpp"

void check(int n, const vector<pair<int, int>> &edges) {
    UnionFind components(n);
    bool has_cycle = false;
    for (auto [u, v] : edges) {
        if (!components.unite(u, v)) {
            has_cycle = true;
            break;
        }
    }

    auto [vertices, edge_ids] = cycle_detection_undirected(edges, n);
    assert(!vertices.empty() == has_cycle);
    assert(vertices.size() == edge_ids.size());
    vector<bool> used_vertex(n), used_edge(edges.size());
    for (int i = 0, length = vertices.size(); i < length; ++i) {
        int v = vertices[i], next = vertices[(i + 1) % length], id = edge_ids[i];
        assert(0 <= v && v < n && !used_vertex[v]);
        assert(0 <= id && id < (int)edges.size() && !used_edge[id]);
        used_vertex[v] = used_edge[id] = true;
        auto [a, b] = edges[id];
        assert((v == a && next == b) || (v == b && next == a));
    }
}

int main() {
    check(0, {});
    check(8, {});
    check(6, {{0, 1}, {2, 3}, {2, 4}});
    check(6, {{0, 1}, {4, 4}});
    check(5, {{3, 2}, {2, 3}});
    check(6, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 2}});

    mt19937 rng(507);
    for (int mask = 0; mask < (1 << 10); ++mask) {
        vector<pair<int, int>> edges;
        int bit = 0;
        for (int u = 0; u < 4; ++u) {
            for (int v = u; v < 4; ++v, ++bit) {
                if (mask >> bit & 1) edges.emplace_back(u, v);
            }
        }
        shuffle(edges.begin(), edges.end(), rng);
        check(4, edges);
    }
    for (int tc = 0; tc < 2000; ++tc) {
        int n = 1 + rng() % 20, m = rng() % (2 * n);
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; ++i) edges.emplace_back(rng() % n, rng() % n);
        check(n, edges);
    }

    int n = 300000;
    vector<pair<int, int>> path;
    for (int i = 1; i < n; ++i) path.emplace_back(i - 1, i);
    check(n, path);
    path.emplace_back(n - 1, n / 2);
    check(n, path);
}
