#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/connectivity/offline_reachability.cpp"

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
    check(5, {{0, 1}, {1, 0}, {1, 2}, {2, 3}}, {});
    check(5, {{0, 1}, {1, 0}, {1, 2}, {2, 3}}, {{0, 1}, {1, 0}, {3, 0}, {4, 4}, {4, 0}});
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
    for (int k : {1, 63, 64, 65, 127, 128, 129, 130, 258}) {
        int n = 2 * k + 2;
        vector<pair<int, int>> edges, queries;
        for (int i = 0; i + 1 < n; ++i) edges.emplace_back(i, i + 1);
        for (int i = 0; i < k; ++i) {
            queries.emplace_back(i, k + i);
            queries.emplace_back(i, n - 1);
        }
        shuffle(queries.begin(), queries.end(), rng);
        check(n, edges, queries);
        for (auto &[u, v] : edges) swap(u, v);
        for (auto &[u, v] : queries) swap(u, v);
        check(n, edges, queries);
    }
    int n = 780;
    vector<pair<int, int>> edges, queries;
    for (int v = 0; v + 2 < n; ++v) edges.emplace_back(v, v + 2);
    for (int v = 0; v < 516; ++v) {
        queries.emplace_back(v, v + 2);
        queries.emplace_back(v, v + 3);
        if ((v / 64) % 2 == 0) queries.emplace_back(v, n - 2 + v % 2);
        queries.emplace_back(v, v);
        queries.emplace_back(v + 2, v);
    }
    shuffle(queries.begin(), queries.end(), rng);
    check(n, edges, queries);
    for (auto &[u, v] : edges) swap(u, v);
    for (auto &[u, v] : queries) swap(u, v);
    check(n, edges, queries);
    for (int tc = 0; tc < 40; ++tc) {
        int n = 200 + rng() % 100;
        vector<pair<int, int>> edges, queries;
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (rng() % 100 == 0) edges.emplace_back(u, v);
                queries.emplace_back(u, v);
            }
        }
        shuffle(queries.begin(), queries.end(), rng);
        check(n, edges, queries);
        queries.erase(remove_if(queries.begin(), queries.end(), [](auto query) {
            return query.second % 2 != 0;
        }), queries.end());
        check(n, edges, queries);
    }
}
