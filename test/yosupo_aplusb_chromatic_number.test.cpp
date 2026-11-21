#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/chromatic_number.cpp"

int brute_chromatic_number(int n, const vector<pair<int, int>> &edges) {
    vector<vector<int>> earlier(n);
    for (auto [u, v] : edges) earlier[max(u, v)].push_back(min(u, v));
    vector<int> color(n);
    int best = n;
    auto search = [&](auto &self, int v, int used) -> void {
        if (used >= best) return;
        if (v == n) {
            best = used;
            return;
        }
        for (int c = 0; c <= used; ++c) {
            if (any_of(earlier[v].begin(), earlier[v].end(), [&](int u) { return color[u] == c; })) continue;
            color[v] = c;
            self(self, v + 1, max(used, c + 1));
        }
    };
    search(search, 0, 0);
    return best;
}

vector<pair<int, int>> clique_edges(int n) {
    vector<pair<int, int>> pairs;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < u; ++v) pairs.emplace_back(u, v);
    }
    return pairs;
}

int main() {
    for (int n = 0; n <= 5; ++n) {
        auto pairs = clique_edges(n);
        for (int mask = 0; mask < (1 << pairs.size()); ++mask) {
            vector<pair<int, int>> edges;
            for (int e = 0; e < (int)pairs.size(); ++e) {
                if (mask >> e & 1) edges.push_back(pairs[e]);
            }
            assert(chromatic_number(n, edges) == brute_chromatic_number(n, edges));
        }
    }
    mt19937 rng(554);
    for (int trial = 0; trial < 300; ++trial) {
        int n = 6 + rng() % 5, density = rng() % 101;
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < u; ++v) {
                if (int(rng() % 100) < density) edges.emplace_back(u, v);
            }
        }
        assert(chromatic_number(n, edges) == brute_chromatic_number(n, edges));
    }
    vector<pair<int, int>> cycle;
    for (int u = 0; u < 19; ++u) cycle.emplace_back(u, (u + 1) % 19);
    assert(chromatic_number(20, {}) == 1);
    assert(chromatic_number(20, cycle) == 3);
    assert(chromatic_number(20, clique_edges(5)) == 5);
    assert(chromatic_number(20, clique_edges(20)) == 20);
}
