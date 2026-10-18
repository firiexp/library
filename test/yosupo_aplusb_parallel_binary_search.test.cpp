#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/parallel_binary_search.cpp"
#include "../datastructure/unionfind.cpp"

int main() {
    mt19937 rng(154);
    for (int tc = 0; tc < 2000; ++tc) {
        int n = 1 + rng() % 12, m = rng() % 31, q = rng() % 41;
        vector<pair<int, int>> edges(m);
        for (auto &[u, v] : edges) u = rng() % n, v = rng() % n;
        vector<array<int, 3>> queries(q);
        for (auto &[u, v, z] : queries) u = rng() % n, v = rng() % n, z = rng() % (n + 2);
        vector<int> expected(q, m + 1);
        vector<vector<int>> g(n);
        for (int t = 0; t <= m; ++t) {
            if (t) {
                auto [u, v] = edges[t - 1];
                g[u].push_back(v);
                g[v].push_back(u);
            }
            for (int id = 0; id < q; ++id) {
                auto [u, v, z] = queries[id];
                vector<int> seen(n), queue{u};
                seen[u] = 1;
                if (!seen[v]) queue.push_back(v), seen[v] = 1;
                for (int i = 0; i < (int)queue.size(); ++i) {
                    for (int w : g[queue[i]]) {
                        if (!seen[w]) queue.push_back(w), seen[w] = 1;
                    }
                }
                if ((int)queue.size() >= z) expected[id] = min(expected[id], t);
            }
        }
        UnionFind uf(n);
        int applied = 0, resets = 0, checks = 0;
        auto answer = parallel_binary_search(m, q,
            [&] { uf = UnionFind(n); applied = 0; ++resets; },
            [&](int i) {
                assert(i == applied++);
                uf.unite(edges[i].first, edges[i].second);
            },
            [&](int id) {
                ++checks;
                auto [u, v, z] = queries[id];
                return uf.size(u) + (uf.same(u, v) ? 0 : uf.size(v)) >= z;
            });
        assert(answer == expected);
        if (q == 0) assert(resets == 0 && checks == 0 && applied == 0);
        else if (m == 0) assert(resets == 1 && checks == q && applied == 0);
    }
    int n = 100001;
    UnionFind uf(n);
    auto answer = parallel_binary_search(n - 1, n + 1,
        [&] { uf = UnionFind(n); },
        [&](int i) { uf.unite(i, i + 1); },
        [&](int i) { return uf.size(0) >= i + 1; });
    for (int i = 0; i <= n; ++i) assert(answer[i] == i);
}
