#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../graph/grid_bfs.cpp"
#include "../graph/generated_shortest_path.cpp"
#include "../graph/dijkstra_from_distances.cpp"
#include "../graph/bfs01.cpp"

template<class T>
void check_paths(const GeneratedShortestPathResult<T> &result, const vector<int> &sources,
                 const vector<vector<edge<T>>> &g) {
    assert(result.path_to(-1).empty() && result.path_to(g.size()).empty());
    for (int t = 0; t < (int)g.size(); ++t) {
        auto path = result.path_to(t);
        if (result.dist[t] == INF<T>) {
            assert(path.empty() && result.parent[t] == -1);
            continue;
        }
        assert(!path.empty() && path.back() == t && path.size() <= g.size());
        assert(find(sources.begin(), sources.end(), path.front()) != sources.end());
        assert(result.dist[path.front()] == T(0) && result.parent[path.front()] == -1);
        for (int i = 1; i < (int)path.size(); ++i) {
            int u = path[i - 1], v = path[i];
            bool found = false;
            for (auto e : g[u]) if (e.to == v && result.dist[u] + e.cost == result.dist[v]) found = true;
            assert(found);
        }
    }
}

int main() {
    mt19937 rng(235);
    for (int trial = 0; trial < 1200; ++trial) {
        int n = rng() % 25;
        vector<vector<edge<long long>>> g(n);
        vector<vector<long long>> floyd(n, vector<long long>(n, INF<long long>));
        for (int v = 0; v < n; ++v) floyd[v][v] = 0;
        int mode = trial % 3;
        if (n) for (int i = rng() % (n * n + 1); i > 0; --i) {
            int u = rng() % n, v = rng() % n;
            long long w = mode == 0 ? 1 : rng() % (mode == 1 ? 2 : 100);
            g[u].emplace_back(v, w);
            floyd[u][v] = min(floyd[u][v], w);
        }
        for (int k = 0; k < n; ++k) for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
            floyd[u][v] = min(floyd[u][v], floyd[u][k] + floyd[k][v]);
        }
        vector<int> sources;
        if (n) for (int i = rng() % (n + 3); i > 0; --i) sources.push_back(rng() % n);
        vector<long long> expected(n, INF<long long>), initial = expected;
        for (int s : sources) {
            initial[s] = 0;
            for (int v = 0; v < n; ++v) expected[v] = min(expected[v], floyd[s][v]);
        }
        assert(dijkstra_from_distances(initial, g) == expected);
        vector<int> calls(n);
        auto edges = [&](int v, auto emit) {
            assert(++calls[v] == 1);
            for (auto e : g[v]) emit(e.to, e.cost);
        };
        auto result = dijkstra_generated<long long>(n, sources, edges);
        assert(result.dist == expected);
        check_paths(result, sources, g);
        if (mode <= 1) {
            fill(calls.begin(), calls.end(), 0);
            auto binary = bfs01_generated<long long>(n, sources, edges);
            assert(binary.dist == expected);
            check_paths(binary, sources, g);
        }
        if (mode == 0) {
            fill(calls.begin(), calls.end(), 0);
            auto unweighted = bfs_generated(n, sources, [&](int v, auto emit) {
                assert(++calls[v] == 1);
                for (auto e : g[v]) emit(e.to);
            });
            vector<vector<edge<int>>> unit(n);
            for (int v = 0; v < n; ++v) {
                assert(unweighted.dist[v] == (expected[v] == INF<long long> ? INF<int> : expected[v]));
                for (auto e : g[v]) unit[v].emplace_back(e.to, 1);
            }
            check_paths(unweighted, sources, unit);
        }
        if (n) {
            auto emit_edges = [&](int v, auto emit) { for (auto e : g[v]) emit(e.to, e.cost); };
            assert(dijkstra_generated<long long>(n, 0, emit_edges).dist == floyd[0]);
            if (mode <= 1) assert(bfs01_generated<long long>(n, 0, emit_edges).dist == bfs01(0, g));
        }
    }
    for (int trial = 0; trial < 500; ++trial) {
        int h = 1 + rng() % 12, w = 1 + rng() % 12;
        vector<string> grid(h, string(w, '.'));
        for (auto &row : grid) for (auto &cell : row) if (rng() % 3 == 0) cell = '#';
        vector<pair<int, int>> sources;
        vector<int> ids;
        for (int i = rng() % 5; i > 0; --i) {
            int r = rng() % h, c = rng() % w;
            sources.emplace_back(r, c);
            if (grid[r][c] != '#') ids.push_back(r * w + c);
        }
        auto passable = [&](int r, int c) {
            assert(0 <= r && r < h && 0 <= c && c < w);
            return grid[r][c] != '#';
        };
        vector<vector<edge<int>>> g(h * w);
        for (int r = 0; r < h; ++r) for (int c = 0; c < w; ++c) {
            if (!passable(r, c)) continue;
            for (auto [dr, dc] : {pair<int, int>{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                int nr = r + dr, nc = c + dc;
                if (0 <= nr && nr < h && 0 <= nc && nc < w && passable(nr, nc)) g[r * w + c].emplace_back(nr * w + nc, 1);
            }
        }
        vector<int> initial(h * w, INF<int>);
        for (int id : ids) initial[id] = 0;
        auto expected = dijkstra_from_distances(initial, g);
        auto result = grid_bfs(h, w, sources, passable);
        check_paths(result.paths, ids, g);
        for (int r = 0; r < h; ++r) for (int c = 0; c < w; ++c) {
            assert(result.distance(r, c) == expected[r * w + c]);
            vector<pair<int, int>> path;
            for (int id : result.paths.path_to(r * w + c)) path.emplace_back(id / w, id % w);
            assert(result.path_to(r, c) == path);
        }
        assert(result.path_to(h, 0).empty());
        auto single = grid_bfs(h, w, pair<int, int>{0, 0}, passable);
        assert(single.distance(0, 0) == (passable(0, 0) ? 0 : INF<int>));
    }
    auto empty = grid_bfs(0, 5, vector<pair<int, int>>{}, [](int, int) { assert(false); return true; });
    assert(empty.paths.dist.empty() && empty.path_to(0, 0).empty());
    auto overflow = dijkstra_generated<long long>(3, 0, [](int v, auto emit) {
        if (v == 0) { emit(1, INF<long long> - 1); emit(2, LLONG_MAX); }
        if (v == 1) emit(2, LLONG_MAX);
    });
    assert(overflow.dist[1] == INF<long long> - 1 && overflow.dist[2] == INF<long long>);
    int width = 9;
    auto layers = bfs01_generated(2 * width, 0, [&](int v, auto emit) {
        int layer = v / width, column = v % width;
        if (column + 1 < width) emit(v + 1, layer);
        if (column == 3) emit((1 - layer) * width + column, 0);
        if (column > 0) emit(v - 1, 1);
    });
    assert(layers.dist[width + 8] == 5 && layers.dist[8] == 0);
    auto single = bfs_generated(1, 0, [](int, auto) {});
    assert(single.path_to(0) == vector<int>{0});
}
