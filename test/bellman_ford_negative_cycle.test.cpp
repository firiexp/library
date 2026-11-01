#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../graph/shortest_path/bellman_ford.cpp"

void check(int n, const vector<edge<ll>> &edges) {
    vector<vector<int>> g(n);
    for (int id = 0; id < (int)edges.size(); ++id) g[edges[id].from].push_back(id);
    for (int s = 0; s < n; ++s) {
        vector<bool> reached(n, false);
        vector<int> queue = {s};
        reached[s] = true;
        for (int i = 0; i < (int)queue.size(); ++i) for (int id : g[queue[i]]) {
            int v = edges[id].to;
            if (!reached[v]) {
                reached[v] = true;
                queue.push_back(v);
            }
        }
        bool expected = false;
        vector<bool> used(n, false);
        auto dfs = [&](auto &&self, int start, int v, __int128 cost) -> void {
            used[v] = true;
            for (int id : g[v]) {
                auto e = edges[id];
                if (e.to == start) expected |= cost + e.cost < 0;
                else if (!used[e.to]) self(self, start, e.to, cost + e.cost);
            }
            used[v] = false;
        };
        for (int v = 0; v < n && !expected; ++v) if (reached[v]) dfs(dfs, v, v, 0);
        auto cycle = bellman_ford_negative_cycle(s, n, edges);
        assert(!cycle.empty() == expected);
        __int128 sum = 0;
        for (int i = 0; i < (int)cycle.size(); ++i) {
            int id = cycle[i], next = cycle[(i + 1) % cycle.size()];
            assert(0 <= id && id < (int)edges.size());
            auto e = edges[id];
            assert(reached[e.from] && e.to == edges[next].from && !used[e.from]);
            used[e.from] = true;
            sum += e.cost;
        }
        if (expected) assert(sum < 0);
    }
}

int main() {
    check(1, {});
    check(1, {{0, 0, -1}});
    check(3, {{0, 1, 4}, {0, 1, -1}, {1, 0, 1}, {2, 2, -2}});
    check(3, {{0, 1, 2}, {0, 1, 0}, {1, 2, -3}, {2, 0, 1}});
    check(3, {{0, 1, LLONG_MAX}, {1, 2, -1}, {2, 2, -1}});
    vector<edge<ll>> path;
    for (int v = 63; v > 0; --v) path.emplace_back(v - 1, v, 1);
    check(64, path);
    path.emplace_back(63, 61, -3);
    check(64, path);
    mt19937 rng(346);
    for (int tc = 0; tc < 1600; ++tc) {
        int n = 1 + rng() % 6;
        vector<edge<ll>> edges;
        for (int m = rng() % 17; m--; )
            edges.emplace_back(rng() % n, rng() % n, int(rng() % 9) - 4);
        check(n, edges);
    }
}
