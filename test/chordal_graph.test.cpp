#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/chordal_graph.cpp"
#include "../graph/chordal_graph.cpp"

bool oracle(const vector<vector<bool>> &adjacent) {
    int n = adjacent.size();
    vector<bool> alive(n, true);
    for (int step = 0; step < n; ++step) {
        int chosen = -1;
        for (int v = 0; v < n && chosen == -1; ++v) {
            if (!alive[v]) continue;
            bool simplicial = true;
            for (int u = 0; u < n; ++u) if (alive[u] && adjacent[v][u]) {
                for (int w = 0; w < u; ++w) {
                    if (alive[w] && adjacent[v][w] && !adjacent[u][w]) simplicial = false;
                }
            }
            if (simplicial) chosen = v;
        }
        if (chosen == -1) return false;
        alive[chosen] = false;
    }
    return true;
}

void check_small(int n, const vector<pair<int, int>> &edges) {
    auto copy = edges;
    auto result = recognize_chordal(n, edges);
    assert(copy == edges);
    vector<vector<bool>> adjacent(n, vector<bool>(n));
    for (auto [u, v] : edges) adjacent[u][v] = adjacent[v][u] = true;
    assert(result.chordal == oracle(adjacent));
    if (result.chordal) {
        assert(result.induced_cycle.empty() && (int)result.peo.size() == n);
        vector<int> index(n, -1);
        for (int i = 0; i < n; ++i) {
            int v = result.peo[i];
            assert(0 <= v && v < n && index[v] == -1);
            index[v] = i;
        }
        for (int v = 0; v < n; ++v) for (int u = 0; u < n; ++u) {
            if (!adjacent[v][u] || index[u] <= index[v]) continue;
            for (int w = 0; w < u; ++w) {
                if (adjacent[v][w] && index[w] > index[v]) assert(adjacent[u][w]);
            }
        }
    } else {
        assert(result.peo.empty());
        auto &cycle = result.induced_cycle;
        int k = cycle.size();
        assert(k >= 4);
        vector<bool> seen(n);
        for (int v : cycle) {
            assert(0 <= v && v < n && !seen[v]);
            seen[v] = true;
        }
        for (int i = 0; i < k; ++i) for (int j = i + 1; j < k; ++j) {
            assert(adjacent[cycle[i]][cycle[j]] == (j == i + 1 || (i == 0 && j == k - 1)));
        }
    }
}

void check_large(int n, const vector<pair<int, int>> &edges, int expected) {
    auto result = recognize_chordal(n, edges);
    if (expected != -1) assert(result.chordal == bool(expected));
    vector<int> position(n, -1);
    if (result.chordal) {
        assert(result.induced_cycle.empty() && (int)result.peo.size() == n);
        for (int i = 0; i < n; ++i) {
            int v = result.peo[i];
            assert(0 <= v && v < n && position[v] == -1);
            position[v] = i;
        }
        vector<vector<int>> graph(n);
        for (auto [u, v] : edges) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        for (auto &neighbors : graph) sort(neighbors.begin(), neighbors.end());
        for (int v = 0; v < n; ++v) {
            int p = -1;
            for (int u : graph[v]) if (position[u] > position[v] && (p == -1 || position[u] < position[p])) p = u;
            if (p == -1) continue;
            for (int u : graph[v]) if (position[u] > position[p]) {
                assert(binary_search(graph[p].begin(), graph[p].end(), u));
            }
        }
    } else {
        assert(result.peo.empty());
        int k = result.induced_cycle.size(), count = 0;
        assert(k >= 4);
        for (int i = 0; i < k; ++i) {
            int v = result.induced_cycle[i];
            assert(0 <= v && v < n && position[v] == -1);
            position[v] = i;
        }
        for (auto [u, v] : edges) if (position[u] != -1 && position[v] != -1) {
            int delta = abs(position[u] - position[v]);
            assert(delta == 1 || delta == k - 1);
            ++count;
        }
        assert(count == k);
    }
}

int main() {
    for (int n = 0; n <= 6; ++n) {
        vector<pair<int, int>> all;
        for (int u = 0; u < n; ++u) for (int v = 0; v < u; ++v) all.emplace_back(u, v);
        for (int mask = 0; mask < (1 << all.size()); ++mask) {
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)all.size(); ++i) if (mask >> i & 1) edges.push_back(all[i]);
            check_small(n, edges);
        }
    }
    mt19937 rng(142);
    for (int trial = 0; trial < 10000; ++trial) {
        int n = rng() % 21, density = rng() % 101;
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) for (int v = 0; v < u; ++v) {
            if (int(rng() % 100) < density) edges.emplace_back(u, v);
        }
        shuffle(edges.begin(), edges.end(), rng);
        for (auto &[u, v] : edges) if (rng() & 1) swap(u, v);
        check_small(n, edges);
    }
    int n = 200000;
    vector<pair<int, int>> edges;
    check_large(n, edges, 1);
    for (int v = 1; v < n; ++v) edges.emplace_back(v - 1, v);
    check_large(n, edges, 1);
    edges.emplace_back(n - 1, 0);
    check_large(n, edges, 0);
    edges.clear();
    for (int v = 1; v < n; ++v) edges.emplace_back(0, v);
    check_large(n, edges, 1);
    edges.clear();
    for (int v = 0; v < 632; ++v) for (int u = 0; u < v; ++u) edges.emplace_back(u, v);
    check_large(632, edges, 1);
    edges.erase(find(edges.begin(), edges.end(), pair<int, int>{0, 1}));
    edges.erase(find(edges.begin(), edges.end(), pair<int, int>{2, 3}));
    check_large(632, edges, 0);
    edges.clear();
    for (int v = 2; v < 100002; ++v) {
        edges.emplace_back(0, v);
        edges.emplace_back(1, v);
    }
    check_large(100002, edges, 0);
    edges.clear();
    for (int v = 1; v < 100000; ++v) {
        edges.emplace_back(0, v);
        edges.emplace_back(v, v == 99999 ? 1 : v + 1);
    }
    check_large(100000, edges, 0);
    edges = {{0, 1}};
    for (int v = 2; v < 100001; ++v) {
        auto [a, b] = edges[rng() % edges.size()];
        edges.emplace_back(a, v);
        edges.emplace_back(b, v);
    }
    check_large(100001, edges, 1);
    set<pair<int, int>> unique;
    while ((int)unique.size() < 200000) {
        int u = rng() % n, v = rng() % n;
        if (u != v) unique.emplace(min(u, v), max(u, v));
    }
    edges.assign(unique.begin(), unique.end());
    check_large(n, edges, -1);
}
