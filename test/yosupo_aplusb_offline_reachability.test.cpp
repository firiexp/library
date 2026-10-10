#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/offline_reachability.cpp"

void check(int n, const vector<pair<int, int>> &edges, const vector<pair<int, int>> &queries) {
    auto saved_edges = edges, saved_queries = queries;
    auto answer = offline_reachability(n, edges, queries);
    assert(edges == saved_edges && queries == saved_queries);
    vector<vector<int>> g(n);
    for (auto [u, v] : edges) g[u].push_back(v);
    vector<vector<char>> reach(n, vector<char>(n));
    for (int s = 0; s < n; ++s) {
        vector<int> queue{s};
        reach[s][s] = 1;
        for (int i = 0; i < (int)queue.size(); ++i) {
            for (int v : g[queue[i]]) {
                if (reach[s][v]) continue;
                reach[s][v] = 1;
                queue.push_back(v);
            }
        }
    }
    assert(answer.size() == queries.size());
    for (int i = 0; i < (int)queries.size(); ++i)
        assert(answer[i] == reach[queries[i].first][queries[i].second]);
}

int main() {
    check(0, {}, {});
    for (int n = 1; n <= 4; ++n) {
        vector<pair<int, int>> queries;
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < n; ++v) queries.emplace_back(u, v);
        for (int mask = 0; mask < (1 << (n * n)); ++mask) {
            vector<pair<int, int>> edges;
            for (auto [u, v] : queries)
                if (mask >> (u * n + v) & 1) edges.emplace_back(u, v);
            check(n, edges, queries);
        }
    }
    mt19937 rng(20261010);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + rng() % 20;
        vector<pair<int, int>> edges, queries;
        for (int i = rng() % (n * n + 1); i > 0; --i)
            edges.emplace_back(rng() % n, rng() % n);
        for (int i = rng() % 100; i > 0; --i)
            queries.emplace_back(rng() % n, rng() % n);
        check(n, edges, queries);
    }
    for (int k : {1, 63, 64, 65, 127, 128, 129, 130}) {
        int n = 2 * k + 2;
        vector<pair<int, int>> edges, queries;
        for (int i = 0; i + 1 < n; ++i) edges.emplace_back(i, i + 1);
        for (int i = 0; i < k; ++i) {
            queries.emplace_back(i, k + i);
            queries.emplace_back(i, n - 1);
        }
        check(n, edges, queries);
        for (auto &[u, v] : edges) swap(u, v);
        for (auto &[u, v] : queries) swap(u, v);
        check(n, edges, queries);
    }
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
