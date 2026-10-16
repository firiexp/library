#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../graph/k_shortest_walk.cpp"

vector<ll> naive(int s, int t, int k, const vector<vector<edge<ll>>> &g) {
    vector<int> count(g.size());
    vector<ll> result;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> queue;
    queue.emplace(0, s);
    while (!queue.empty() && (int)result.size() < k) {
        auto [cost, v] = queue.top();
        queue.pop();
        if (count[v] == k) continue;
        ++count[v];
        if (v == t) result.push_back(cost);
        for (const auto &e : g[v]) {
            if (count[e.to] < k) queue.emplace(cost + e.cost, e.to);
        }
    }
    return result;
}

void check(const vector<vector<edge<ll>>> &g, int s, int t, int k) {
    auto copy = g;
    assert(k_shortest_walk(s, t, k, g) == naive(s, t, k, g));
    for (int v = 0; v < (int)g.size(); ++v) {
        assert(copy[v].size() == g[v].size());
        for (int i = 0; i < (int)g[v].size(); ++i) {
            assert(copy[v][i].from == g[v][i].from);
            assert(copy[v][i].to == g[v][i].to);
            assert(copy[v][i].cost == g[v][i].cost);
        }
    }
}

void self_check() {
    for (int mask = 0; mask < 81; ++mask) {
        vector<vector<edge<ll>>> g(2);
        int state = mask;
        for (int u = 0; u < 2; ++u) for (int v = 0; v < 2; ++v) {
            int kind = state % 3;
            state /= 3;
            if (kind) g[u].emplace_back(u, v, kind == 1 ? 0 : 3);
        }
        for (int s = 0; s < 2; ++s) for (int t = 0; t < 2; ++t) check(g, s, t, 8);
    }
    vector<vector<edge<ll>>> g(4);
    g[0].emplace_back(1, 0);
    g[0].emplace_back(1, 0);
    g[1].emplace_back(0, 0);
    g[1].emplace_back(2, 5);
    g[2].emplace_back(1, 0);
    g[3].emplace_back(3, 0);
    for (int s = 0; s < 4; ++s) for (int t = 0; t < 4; ++t) {
        check(g, s, t, 0);
        check(g, s, t, 1);
        check(g, s, t, 30);
    }
    vector<vector<edge<ll>>> large_cost(3);
    large_cost[0].emplace_back(1, 3000000000LL);
    large_cost[0].emplace_back(1, 3000000000LL);
    large_cost[1].emplace_back(2, 4000000000LL);
    check(large_cost, 0, 2, 10);
    large_cost[0].clear();
    large_cost[1].clear();
    large_cost[0].emplace_back(2, LLONG_MAX);
    large_cost[0].emplace_back(2, LLONG_MAX - 1);
    check(large_cost, 0, 2, 5);
    mt19937 rng(84);
    for (int tc = 0; tc < 10000; ++tc) {
        int n = 1 + rng() % 8, m = rng() % 25;
        vector<vector<edge<ll>>> graph(n);
        for (int i = 0; i < m; ++i) graph[rng() % n].emplace_back(rng() % n, rng() % 10);
        check(graph, rng() % n, rng() % n, rng() % 25);
    }
    vector<vector<edge<int>>> path(20000);
    for (int i = 0; i < 19999; ++i) path[i].emplace_back(i + 1, 1);
    assert(k_shortest_walk(0, 19999, 20, path) == vector<int>{19999});
    path.back().emplace_back(19999, 7);
    auto costs = k_shortest_walk(0, 19999, 20, path);
    assert(costs.size() == 20);
    for (int i = 0; i < 20; ++i) assert(costs[i] == 19999 + 7 * i);
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
