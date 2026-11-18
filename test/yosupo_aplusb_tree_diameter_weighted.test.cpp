#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../tree/diameter_weighted.cpp"

using Tree = vector<vector<pair<int, long long>>>;

void add_edge(Tree &g, int u, int v, long long w) {
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
}

void check(const Tree &g) {
    auto [length, path] = tree_diameter_weighted_path(g);
    auto [diameter, ends] = tree_diameter_weighted(g);
    if (g.empty()) {
        assert(length == 0 && path.empty());
        assert(diameter == 0 && ends == make_pair(-1, -1));
        return;
    }
    int n = g.size();
    vector<vector<long long>> dist(n, vector<long long>(n));
    long long longest = 0;
    for (int s = 0; s < n; ++s) {
        auto dfs = [&](auto &&self, int v, int parent) -> void {
            for (auto [u, w] : g[v]) if (u != parent) {
                dist[s][u] = dist[s][v] + w;
                longest = max(longest, dist[s][u]);
                self(self, u, v);
            }
        };
        dfs(dfs, s, -1);
    }
    assert(length == longest && diameter == longest);
    assert(0 <= ends.first && ends.first < n && 0 <= ends.second && ends.second < n);
    assert(dist[ends.first][ends.second] == longest);
    assert(!path.empty());
    vector<bool> seen(n);
    long long sum = 0;
    int prev = -1;
    for (int v : path) {
        assert(0 <= v && v < n && !seen[v]);
        seen[v] = true;
        if (prev != -1) {
            auto edge = find_if(g[v].begin(), g[v].end(), [&](auto e) { return e.first == prev; });
            assert(edge != g[v].end());
            sum += edge->second;
        }
        prev = v;
    }
    assert(sum == length);
}

int main() {
    check({});
    check(Tree(1));
    Tree star(4);
    for (int v = 1; v < 4; ++v) add_edge(star, 0, v, 0);
    check(star);
    star[0][1].second = star[2][0].second = 5000000000LL;
    check(star);

    mt19937 rng(441);
    for (int trial = 0; trial < 1000; ++trial) {
        int n = 1 + rng() % 16;
        Tree g(n);
        for (int v = 1; v < n; ++v) add_edge(g, v, rng() % v, rng() % 5);
        check(g);
    }
}
