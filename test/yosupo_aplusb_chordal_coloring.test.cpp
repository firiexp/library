#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/chordal_graph.cpp"

void check(int n, const vector<pair<int, int>> &edges, int expected = -1) {
    auto copy = edges;
    auto result = chordal_coloring(n, edges);
    assert(edges == copy);
    auto recognition = recognize_chordal(n, edges);
    assert(result.chordal == recognition.chordal);
    if (!result.chordal) {
        assert(result.color_count == 0 && result.color.empty() && result.max_clique.empty());
        assert(result.induced_cycle == recognition.induced_cycle);
        return;
    }
    assert(result.induced_cycle.empty());
    assert((int)result.color.size() == n);
    assert((int)result.max_clique.size() == result.color_count);
    if (expected != -1) assert(result.color_count == expected);
    for (int c : result.color) assert(0 <= c && c < result.color_count);
    vector<bool> in_clique(n);
    for (int v : result.max_clique) {
        assert(0 <= v && v < n && !in_clique[v]);
        in_clique[v] = true;
    }
    long long clique_edges = 0;
    for (auto [u, v] : edges) {
        assert(result.color[u] != result.color[v]);
        clique_edges += in_clique[u] && in_clique[v];
    }
    assert(clique_edges == 1LL * result.color_count * (result.color_count - 1) / 2);
    if (n <= 12) {
        vector<int> adjacent(n);
        for (auto [u, v] : edges) adjacent[u] |= 1 << v, adjacent[v] |= 1 << u;
        int maximum = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            bool clique = true;
            for (int v = 0; v < n; ++v) if (mask >> v & 1) {
                if ((mask & adjacent[v]) != (mask ^ (1 << v))) clique = false;
            }
            if (clique) maximum = max(maximum, __builtin_popcount((unsigned)mask));
        }
        assert(maximum == result.color_count);
    }
}

int main() {
    check(0, {}, 0);
    check(1, {}, 1);
    check(6, {}, 1);
    check(7, {{0, 1}, {1, 2}, {2, 0}, {1, 3}, {2, 3}, {4, 5}}, 3);
    check(5, {{0, 1}, {1, 2}, {2, 3}, {3, 0}});
    mt19937 rng(292);
    for (int trial = 0; trial < 5000; ++trial) {
        int n = rng() % 13, density = rng() % 101;
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) for (int v = 0; v < u; ++v) {
            if (int(rng() % 100) < density) edges.emplace_back(u, v);
        }
        shuffle(edges.begin(), edges.end(), rng);
        check(n, edges);
    }
    int n = 200000;
    check(n, {}, 1);
    vector<pair<int, int>> edges;
    for (int v = 1; v < n; ++v) edges.emplace_back(v - 1, v);
    check(n, edges, 2);
    edges.clear();
    for (int v = 1; v < n; ++v) edges.emplace_back(0, v);
    check(n, edges, 2);
    edges.clear();
    for (int v = 0; v < 1000; ++v) for (int u = 0; u < v; ++u) edges.emplace_back(u, v);
    check(1000, edges, 1000);
}
