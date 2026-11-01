#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 4;
#include "../graph/shortest_path/dijkstra_restore.cpp"

void check(int n, const vector<edge<ll>> &edges) {
    vector<vector<ll>> d(n, vector<ll>(n, INF<ll>));
    for (int v = 0; v < n; ++v) d[v][v] = 0;
    for (auto e : edges) d[e.from][e.to] = min(d[e.from][e.to], e.cost);
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    for (int s = 0; s < n; ++s) {
        auto result = dijkstra_restore(s, n, edges);
        assert(result.dist == d[s]);
        for (int t = 0; t < n; ++t) {
            auto path = restore_edge_path(s, t, result);
            auto vertices = restore_path(s, t, result.parent);
            if (d[s][t] == INF<ll>) {
                assert(path.empty() && vertices.empty());
                assert(result.parent[t] == -1 && result.parent_edge[t] == -1);
                continue;
            }
            assert(path.size() < (size_t)n);
            assert(vertices.size() == path.size() + 1);
            int v = s;
            ll cost = 0;
            for (int i = 0; i < (int)path.size(); ++i) {
                int id = path[i];
                assert(0 <= id && id < (int)edges.size());
                auto e = edges[id];
                assert(e.from == v && vertices[i] == v);
                assert(result.parent[e.to] == v && result.parent_edge[e.to] == id);
                v = e.to;
                cost += e.cost;
            }
            assert(v == t && vertices.back() == t && cost == d[s][t]);
            if (s == t) assert(result.parent[t] == -1 && result.parent_edge[t] == -1);
        }
        assert(restore_edge_path(s, -1, result).empty());
        assert(restore_edge_path(s, n, result).empty());
    }
}

int main() {
    check(1, {});
    check(4, {{0, 0, 0}, {0, 1, 7}, {0, 1, 2}, {0, 1, 2},
              {1, 2, 0}, {2, 1, 0}, {2, 0, 0}});
    mt19937 rng(336);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + rng() % 9;
        vector<edge<ll>> edges;
        for (int m = rng() % 65; m--; )
            edges.emplace_back(rng() % n, rng() % n, rng() % 12);
        check(n, edges);
    }
}
