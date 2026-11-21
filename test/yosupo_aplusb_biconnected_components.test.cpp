#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/connectivity/biconnected_components.cpp"

bool connected(int mask, const vector<int> &adj) {
    if (mask == 0) return true;
    int reached = mask & -mask;
    int previous;
    do {
        previous = reached;
        for (int v = 0; v < int(adj.size()); ++v)
            if (reached >> v & 1) reached |= adj[v] & mask;
    } while (reached != previous);
    return reached == mask;
}

vector<int> reference_blocks(int n, const vector<pair<int, int>> &edges) {
    vector<int> adj(n);
    for (auto [u, v] : edges) {
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }
    vector<int> blocks;
    for (int mask = (1 << n) - 1; mask > 0; --mask) {
        if (any_of(blocks.begin(), blocks.end(), [&](int b) { return (mask & b) == mask; })) continue;
        if (!connected(mask, adj)) continue;
        bool block = true;
        for (int v = 0; v < n; ++v)
            if ((mask >> v & 1) && !connected(mask ^ (1 << v), adj)) block = false;
        if (block) blocks.push_back(mask);
    }
    sort(blocks.begin(), blocks.end());
    return blocks;
}

void check(BiconnectedComponents &g, int n, const vector<pair<int, int>> &edges) {
    int count = g.build(false);
    auto vertices = g.bcc_vertices;
    assert(g.bcc_edges.empty());
    auto ord = g.ord, low = g.low, par = g.par;
    int full_count = g.build();
    assert(full_count == count && int(g.bcc_edges.size()) == count);
    assert(g.bcc_vertices == vertices && g.ord == ord && g.low == low && g.par == par);
    vector<int> masks;
    for (int i = 0; i < count; ++i) {
        int mask = 0;
        for (int v : vertices[i]) {
            assert(0 <= v && v < n && !(mask >> v & 1));
            mask |= 1 << v;
        }
        masks.push_back(mask);
        vector<pair<int, int>> expected;
        for (auto [u, v] : edges)
            if (u != v && (mask >> u & 1) && (mask >> v & 1)) expected.push_back(minmax(u, v));
        auto actual = g.bcc_edges[i];
        sort(actual.begin(), actual.end());
        sort(expected.begin(), expected.end());
        assert(actual == expected);
    }
    sort(masks.begin(), masks.end());
    assert(masks == reference_blocks(n, edges));
}

int main() {
    BiconnectedComponents fixed(8);
    vector<pair<int, int>> edges{{3, 1}, {1, 4}, {4, 3}, {1, 0}, {0, 1}, {5, 6}, {7, 7}};
    for (auto [u, v] : edges) fixed.add_edge(u, v);
    fixed.build();
    vector<vector<pair<int, int>>> expected_edges{{{1, 4}, {3, 4}, {1, 3}}, {{0, 1}, {0, 1}}, {{5, 6}}, {}, {}};
    vector<vector<int>> expected_vertices{{1, 4, 3}, {0, 1}, {5, 6}, {2}, {7}};
    assert(fixed.bcc_edges == expected_edges && fixed.bcc_vertices == expected_vertices);
    check(fixed, 8, edges);
    assert(fixed.bcc_edges == expected_edges && fixed.bcc_vertices == expected_vertices);

    mt19937 rng(506);
    for (int n = 0; n <= 7; ++n) for (int tc = 0; tc < 100; ++tc) {
        BiconnectedComponents g(n);
        vector<pair<int, int>> input;
        check(g, n, input);
        for (int phase = 0; n > 0 && phase < 3; ++phase) {
            for (int m = rng() % 9; m > 0; --m) {
                int u = rng() % n, v = rng() % n;
                g.add_edge(u, v);
                input.emplace_back(u, v);
            }
            check(g, n, input);
        }
    }
}
