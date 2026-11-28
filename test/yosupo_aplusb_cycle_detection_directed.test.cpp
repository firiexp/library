#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/cycle_detection_directed.cpp"

void check(int n, const vector<pair<int, int>> &edges, bool has_cycle) {
    vector<vector<int>> g(n);
    vector<vector<pair<int, int>>> labelled(n);
    int id = 7;
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        labelled[u].push_back({v, id});
        id -= 3;
    }

    auto check_vertices = [&](const vector<int> &vertices) {
        assert(!vertices.empty() == has_cycle);
        vector<bool> used(n);
        for (int i = 0, k = vertices.size(); i < k; ++i) {
            int v = vertices[i], to = vertices[(i + 1) % k];
            assert(0 <= v && v < n && !used[v]);
            used[v] = true;
            assert(find(g[v].begin(), g[v].end(), to) != g[v].end());
        }
    };
    check_vertices(cycle_detection_directed_vertices(g));
    auto [vertices, edge_ids] = cycle_detection_directed_with_edges(labelled);
    check_vertices(vertices);
    assert(vertices.size() == edge_ids.size());
    for (int i = 0, k = vertices.size(); i < k; ++i) {
        const auto &out = labelled[vertices[i]];
        auto edge = make_pair(vertices[(i + 1) % k], edge_ids[i]);
        assert(find(out.begin(), out.end(), edge) != out.end());
    }
}

int main() {
    check(0, {}, false);
    check(5, {{0, 1}, {0, 2}, {2, 1}, {2, 1}}, false);
    check(4, {{0, 1}, {3, 3}}, true);
    check(3, {{0, 1}, {0, 1}, {1, 0}}, true);
    check(8, {{0, 1}, {2, 3}, {3, 4}, {3, 5}, {5, 6}, {6, 4}, {6, 3}}, true);
    assert(cycle_detection_directed({{{0, -19}}}) == vector<int>{-19});

    int n = 300000;
    vector<pair<int, int>> edges;
    for (int v = 1; v < n; ++v) edges.emplace_back(v - 1, v);
    check(n, edges, false);
    edges.emplace_back(n - 1, n / 2);
    check(n, edges, true);
}
