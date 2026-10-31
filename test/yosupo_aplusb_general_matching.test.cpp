#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/matching/general_matching.cpp"

void check(int n, const vector<pair<int, int>>& edges) {
    vector<int> adj(n);
    GeneralMatching gm(n);
    for (auto [u, v] : edges) {
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
        gm.add_edge(u, v);
    }
    vector<int> dp(1 << n);
    for (int mask = 1; mask < (1 << n); ++mask) {
        int v = __builtin_ctz((unsigned)mask);
        int remaining = mask ^ (1 << v);
        dp[mask] = dp[remaining];
        for (int neighbors = adj[v] & remaining; neighbors; neighbors &= neighbors - 1) {
            int to = __builtin_ctz((unsigned)neighbors);
            dp[mask] = max(dp[mask], 1 + dp[remaining ^ (1 << to)]);
        }
    }
    int count = gm.max_matching();
    assert(count == dp.back());
    const auto& match = gm.get_match();
    assert((int)match.size() == n);
    int matched = 0;
    for (int v = 0; v < n; ++v) if (match[v] != -1) {
        int to = match[v];
        assert(0 <= to && to < n && to != v);
        assert(match[to] == v && (adj[v] >> to & 1));
        ++matched;
    }
    assert(matched == 2 * count);
    auto pairs = gm.get_pairs();
    assert((int)pairs.size() == count);
    vector<char> used(n);
    for (auto [u, v] : pairs) {
        assert(u < v && !used[u] && !used[v] && match[u] == v);
        used[u] = used[v] = true;
    }
}

int main() {
    check(4, {{0, 1}, {0, 2}, {1, 3}});
    check(6, {{0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {2, 5}});
    check(10, {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 3},
               {2, 3}, {0, 6}, {4, 7}, {6, 8}, {7, 9}});
    for (int n = 0; n <= 6; ++n) {
        vector<pair<int, int>> all;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) all.emplace_back(u, v);
        for (int mask = 0; mask < (1 << all.size()); ++mask) {
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)all.size(); ++i) if (mask >> i & 1) edges.push_back(all[i]);
            check(n, edges);
        }
    }
    mt19937 rng(241);
    for (int tc = 0; tc < 3000; ++tc) {
        int n = rng() % 14, density = rng() % 101;
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v)
            if ((int)(rng() % 100) < density) edges.emplace_back(u, v);
        shuffle(edges.begin(), edges.end(), rng);
        check(n, edges);
    }
}
