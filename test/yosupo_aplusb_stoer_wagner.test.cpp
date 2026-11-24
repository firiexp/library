#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 2;
#include "../flow/gomory_hu_tree.cpp"
#include "../flow/stoer_wagner.cpp"

using Tree = GomoryHuTree<long long>;
using Edge = Tree::Edge;

void check(int n, const vector<Edge> &edges, long long expected) {
    vector<vector<long long>> graph(n, vector<long long>(n));
    for (auto [u, v, w] : edges) {
        graph[u][v] += w;
        if (u != v) graph[v][u] += w;
    }
    auto [value, side] = stoer_wagner(graph);
    assert(value == expected);
    if (n < 2) {
        assert(side.empty());
        return;
    }
    assert(!side.empty() && int(side.size()) < n);
    vector<bool> inside(n);
    for (int v : side) {
        assert(0 <= v && v < n && !inside[v]);
        inside[v] = true;
    }
    long long crossing = 0;
    for (auto [u, v, w] : edges) if (inside[u] != inside[v]) crossing += w;
    assert(crossing == value);
}

long long exhaustive_cut(int n, const vector<Edge> &edges) {
    long long best = LLONG_MAX;
    for (int mask = 1; mask < (1 << n) - 1; ++mask) {
        long long value = 0;
        for (auto [u, v, w] : edges) if (((mask >> u) ^ (mask >> v)) & 1) value += w;
        best = min(best, value);
    }
    return best;
}

int main() {
    check(0, {}, 0);
    check(1, {{0, 0, LLONG_MAX}}, 0);
    check(2, {{0, 1, LLONG_MAX}, {1, 1, LLONG_MAX}}, LLONG_MAX);
    check(3, {{0, 1, 8}, {1, 2, 0}}, 0);
    check(4, {{0, 1, 10}, {2, 3, 10}, {1, 2, 1}, {2, 1, 2}}, 3);
    check(4, {{0, 1, 3}, {2, 3, 4}}, 0);

    mt19937 rng(572);
    for (int trial = 0; trial < 600; ++trial) {
        int n = 2 + rng() % 8;
        vector<Edge> edges;
        for (int m = rng() % (n * n + 1); m > 0; --m)
            edges.push_back({int(rng() % n), int(rng() % n), int(rng() % 11)});
        check(n, edges, exhaustive_cut(n, edges));
    }
    for (int trial = 0; trial < 45; ++trial) {
        int n = 20 + rng() % 45;
        vector<Edge> edges;
        for (int u = 0; u < n; ++u) for (int v = 0; v < u; ++v) {
            if (trial % 3 == 0 && v < n / 2 && u >= n / 2) continue;
            if (trial % 3 == 1 && rng() % 5 != 0) continue;
            edges.push_back({u, v, int(rng() % 100)});
            if (rng() % 4 == 0) edges.push_back({v, u, int(rng() % 100)});
        }
        Tree tree(n, edges);
        long long expected = LLONG_MAX;
        for (auto e : tree.edges()) expected = min(expected, e.capacity);
        check(n, edges, expected);
    }
}
