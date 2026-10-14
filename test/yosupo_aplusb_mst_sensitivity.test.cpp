#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/kruskal.cpp"
#include "../graph/mst_sensitivity.cpp"

void check(int n, vector<edge<long long>> edges) {
    int m = (int)edges.size();
    for (int i = 0; i < m; ++i) edges[i].idx = i % 3 == 0 ? -1 : 1000 - i % 3;
    auto original = edges;
    auto result = mst_sensitivity(n, edges);
    optional<long long> best;
    vector<optional<long long>> forced(m), forbidden(m);
    auto minimize = [](optional<long long> &a, long long b) {
        if (!a || b < *a) a = b;
    };
    for (int mask = 0; mask < (1 << m); ++mask) {
        if (__builtin_popcount((unsigned)mask) != n - 1) continue;
        vector<int> component(n);
        iota(component.begin(), component.end(), 0);
        bool valid = true;
        long long cost = 0;
        for (int i = 0; i < m; ++i) {
            if (!((mask >> i) & 1)) continue;
            const auto &e = edges[i];
            int a = component[e.from], b = component[e.to];
            if (a == b) { valid = false; break; }
            for (int &c : component) if (c == b) c = a;
            cost += e.cost;
        }
        if (!valid) continue;
        minimize(best, cost);
        for (int i = 0; i < m; ++i) minimize((mask >> i) & 1 ? forced[i] : forbidden[i], cost);
    }
    assert(result.exists == best.has_value());
    assert(result.cost == best.value_or(0));
    assert(result.forced == forced && result.forbidden == forbidden);
    for (int i = 0; i < m; ++i) {
        const auto &a = edges[i], &b = original[i];
        assert(tie(a.from, a.to, a.cost, a.idx) == tie(b.from, b.to, b.cost, b.idx));
    }
}

int main() {
    check(1, {});
    long long large = 1000000000000LL;
    check(1, {{0, 0, -large}, {0, 0, large}});
    check(2, {{0, 1, -large}, {0, 1, -large + 1}});
    check(2, {{0, 1, large - 1}, {0, 1, large}});
    check(3, {{0, 1, -large + 10}, {1, 2, large - 5}, {0, 2, 0}});
    for (int n = 1; n <= 4; ++n) {
        vector<pair<int, int>> pairs;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) pairs.emplace_back(u, v);
        int combinations = 1 << (2 * pairs.size());
        for (int state = 0; state < combinations; ++state) {
            int code = state;
            vector<edge<long long>> edges;
            for (auto [u, v] : pairs) {
                int choice = code % 4;
                code /= 4;
                if (choice) edges.emplace_back(u, v, choice - 2);
            }
            check(n, edges);
        }
    }
    mt19937 rng(139);
    for (int tc = 0; tc < 5000; ++tc) {
        int n = 1 + rng() % 8, m = rng() % 13;
        vector<edge<long long>> edges;
        for (int i = 0; i < m; ++i) edges.emplace_back(rng() % n, rng() % n, (int)(rng() % 21) - 10);
        check(n, edges);
    }
    int n = 100000;
    for (bool star : {false, true}) {
        vector<edge<long long>> edges;
        for (int v = 1; v < n; ++v) edges.emplace_back(star ? 0 : v - 1, v, 1);
        auto bridges = mst_sensitivity(n, edges);
        assert(bridges.exists && bridges.cost == n - 1);
        for (int i = 0; i < n - 1; ++i) {
            assert(bridges.forced[i] == n - 1 && !bridges.forbidden[i]);
        }
        if (star) {
            for (int v = 1; v < n; ++v) edges.emplace_back(v, v == n - 1 ? 1 : v + 1, 2);
        } else {
            for (int v = 2; v < n; ++v) edges.emplace_back(0, v, 2);
        }
        auto result = mst_sensitivity(n, edges);
        assert(result.exists && result.cost == n - 1);
        for (int i = 0; i < (int)edges.size(); ++i) {
            assert(result.forced[i] == (i < n - 1 ? n - 1 : n));
            assert(result.forbidden[i] == (i < n - 1 ? n : n - 1));
        }
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
