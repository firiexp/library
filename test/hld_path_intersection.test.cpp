#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../tree/hld.cpp"

int main() {
    mt19937 rng(339);
    for (int trial = 0; trial < 150; ++trial) {
        int n = 1 + trial % 10;
        HeavyLightDecomposition hld(n);
        vector<vector<int>> graph(n);
        for (int v = 1; v < n; ++v) {
            if (trial % 3 == 0 && rng() % 3 == 0) continue;
            int p = trial % 3 == 1 ? v - 1 : trial % 3 == 2 ? 0 : rng() % v;
            graph[v].push_back(p);
            graph[p].push_back(v);
            hld.add_edge(v, p);
        }
        vector<vector<vector<int>>> paths(n, vector<vector<int>>(n));
        for (int source = 0; source < n; ++source) {
            vector<int> parent(n, -1), queue{source};
            parent[source] = source;
            for (int i = 0; i < int(queue.size()); ++i) {
                for (int v : graph[queue[i]]) if (parent[v] == -1) {
                    parent[v] = queue[i];
                    queue.push_back(v);
                }
            }
            for (int target : queue) {
                auto &path = paths[source][target];
                for (int v = target; v != source; v = parent[v]) path.push_back(v);
                path.push_back(source);
                reverse(path.begin(), path.end());
            }
        }
        vector<int> roots, order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);
        vector<bool> seen(n);
        for (int v : order) if (!seen[v]) {
            roots.push_back(v);
            for (int u = 0; u < n; ++u) if (!paths[v][u].empty()) seen[u] = true;
        }
        hld.build(roots);
        const auto &index = hld;
        auto ids = hld.id, parents = hld.par, depths = hld.dep;
        for (int a = 0; a < n; ++a) for (int b = 0; b < n; ++b)
            for (int c = 0; c < n; ++c) for (int d = 0; d < n; ++d) {
                vector<int> expected;
                for (int v : paths[a][b])
                    if (find(paths[c][d].begin(), paths[c][d].end(), v) != paths[c][d].end())
                        expected.push_back(v);
                auto [x, y] = index.path_intersection(a, b, c, d);
                if (expected.empty()) {
                    assert(x == -1 && y == -1);
                } else {
                    assert(x == expected.front() && y == expected.back());
                    assert(paths[x][y] == expected);
                    vector<int> actual;
                    index.path_ordered(x, y, [&](int l, int r, bool reversed) {
                        if (reversed) for (int i = r - 1; i >= l; --i) actual.push_back(index.id_inv[i]);
                        else for (int i = l; i < r; ++i) actual.push_back(index.id_inv[i]);
                    });
                    assert(actual == expected);
                }
            }
        assert(ids == hld.id && parents == hld.par && depths == hld.dep);
    }
    int n = 200000;
    HeavyLightDecomposition path(n);
    for (int i = 1; i < n; ++i) path.add_edge(i - 1, i);
    path.build({n / 2});
    for (int i = 0; i < n; i += 97) {
        assert(path.path_intersection(0, n - 1, i, i) == make_pair(i, i));
        assert(path.path_intersection(n - 1, 0, i, n - 1) == make_pair(n - 1, i));
        if (i > 0) assert(path.path_intersection(0, i - 1, i, n - 1) == make_pair(-1, -1));
    }
}
