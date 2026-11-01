#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/matching/dag_minimum_path_cover.cpp"

int brute(const vector<vector<int>> &g) {
    int n = g.size(), best = 0;
    vector<pair<int, int>> edges;
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) edges.emplace_back(v, to);
    }
    vector<bool> incoming(n), outgoing(n);
    auto enumerate = [&](auto &&self, size_t index, int count) -> void {
        if (index == edges.size()) {
            best = max(best, count);
            return;
        }
        self(self, index + 1, count);
        auto [v, to] = edges[index];
        if (!outgoing[v] && !incoming[to]) {
            outgoing[v] = incoming[to] = true;
            self(self, index + 1, count + 1);
            outgoing[v] = incoming[to] = false;
        }
    };
    enumerate(enumerate, 0, 0);
    return n - best;
}

void check(const vector<vector<int>> &g, int expected = -1) {
    auto paths = dag_minimum_path_cover(g);
    if (expected == -1) expected = brute(g);
    assert((int)paths.size() == expected);
    vector<bool> used(g.size());
    int count = 0;
    for (const auto &path : paths) {
        assert(!path.empty());
        for (int i = 0; i < (int)path.size(); ++i) {
            int v = path[i];
            assert(0 <= v && v < (int)g.size());
            assert(!used[v]);
            used[v] = true;
            ++count;
            if (i + 1 < (int)path.size()) {
                assert(find(g[v].begin(), g[v].end(), path[i + 1]) != g[v].end());
            }
        }
    }
    assert(count == (int)g.size());
}

int main() {
    mt19937 rng(337);
    for (int n = 0; n <= 5; ++n) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) edges.emplace_back(i, j);
        }
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        for (int mask = 0; mask < (1 << edges.size()); ++mask) {
            shuffle(order.begin(), order.end(), rng);
            vector<vector<int>> g(n);
            for (int i = 0; i < (int)edges.size(); ++i) {
                auto [u, v] = edges[i];
                if (mask >> i & 1) g[order[u]].push_back(order[v]);
            }
            check(g);
        }
    }
    check({{2}, {2}, {3, 4}, {}, {}}, 3);
    check({{1, 1}, {2, 2}, {}, {}, {5}, {}}, 3);
    for (int t = 0; t < 500; ++t) {
        int n = 2 + rng() % 8;
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);
        vector<vector<int>> g(n);
        int m = rng() % 19;
        for (int i = 0; i < m; ++i) {
            int u = rng() % n, v = rng() % n;
            if (u > v) swap(u, v);
            if (u != v) g[order[u]].push_back(order[v]);
        }
        check(g);
    }
    int n = 200000;
    vector<vector<int>> g(n);
    check(g, n);
    for (int i = 1; i < n; ++i) g[i].push_back(i - 1);
    check(g, 1);
}
