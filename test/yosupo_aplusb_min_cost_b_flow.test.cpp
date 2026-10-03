#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../graph/minimum_cost_b_flow.cpp"

struct InputEdge { int from, to, lower, upper, cost; };

void check_dual(const MinimumCostBFlow<ll, ll> &g) {
    auto potential = g.get_potential();
    assert((int)potential.size() == g.n);
    for (const auto &es : g.g) for (const auto &e : es)
        if (e.residual_cap() > 0) assert(e.cost + potential[e.from] - potential[e.to] >= 0);
}

void check(const vector<ll> &supply, const vector<InputEdge> &edges) {
    int n = supply.size();
    MinimumCostBFlow<ll, ll> g(n);
    for (int v = 0; v < n; ++v) g.add_supply(v, supply[v]);
    for (auto e : edges) g.add_edge(e.from, e.to, e.lower, e.upper, e.cost);
    ll best = LLONG_MAX;
    vector<ll> balance(n);
    auto enumerate = [&](auto &&self, int i, ll cost) -> void {
        if (i == (int)edges.size()) {
            if (balance == supply) best = min(best, cost);
            return;
        }
        auto e = edges[i];
        for (int f = e.lower; f <= e.upper; ++f) {
            balance[e.from] += f;
            balance[e.to] -= f;
            self(self, i + 1, cost + f * e.cost);
            balance[e.from] -= f;
            balance[e.to] += f;
        }
    };
    enumerate(enumerate, 0, 0);
    for (int repeat = 0; repeat < 2; ++repeat) {
        auto [ok, cost] = g.solve();
        assert(ok == (best != LLONG_MAX));
        if (!ok) break;
        assert(cost == best);
        auto flow = g.get_flows();
        assert(flow.size() == edges.size());
        fill(balance.begin(), balance.end(), 0);
        ll actual = 0;
        for (int i = 0; i < (int)edges.size(); ++i) {
            auto e = edges[i];
            assert(e.lower <= flow[i] && flow[i] <= e.upper);
            balance[e.from] += flow[i];
            balance[e.to] -= flow[i];
            actual += flow[i] * e.cost;
        }
        assert(balance == supply && actual == best);
        auto before = g.get_flows();
        check_dual(g);
        check_dual(g);
        assert(g.get_flows() == before);
    }
}

void self_check() {
    check({1, -1}, {{0, 1, 0, 1, 7}});
    check({0, 0}, {{0, 1, 0, 1, -1}, {1, 0, 0, 1, 0}});
    check({}, {});
    check({0}, {});
    check({1}, {});
    check({2, -2}, {{0, 1, 2, 2, 3}});
    check({0}, {{0, 0, -2, 1, -4}});
    check({-1, 1}, {{0, 1, -2, -1, 3}});
    check({2, -2}, {{0, 1, 0, 1, -1}});
    MinimumCostBFlow<ll, ll> g(3);
    g.add_edge(0, 1, 0, 1, 7);
    check_dual(g);
    g.add_supply(0, 1);
    g.add_demand(1, 1);
    assert(g.solve() == make_pair(true, (__int128_t)7));
    check_dual(g);
    g.add_edge(0, 2, 0, 1, -9);
    check_dual(g);
    assert(g.solve() == make_pair(true, (__int128_t)7));
    g.add_supply(0, 1);
    check_dual(g);
    assert(!g.solve().first);
    check_dual(g);
    g.add_demand(2, 1);
    check_dual(g);
    assert(g.solve() == make_pair(true, (__int128_t)-2));
    check_dual(g);
    g.add_edge(1, 0, 0, 1, -10);
    assert(g.solve() == make_pair(true, (__int128_t)-2));
    check_dual(g);

    mt19937 random(20261002);
    for (int tc = 0; tc < 100000; ++tc) {
        int n = 1 + random() % 5, m = random() % 8;
        vector<ll> supply(n);
        vector<InputEdge> edges;
        for (int i = 0; i < m; ++i) {
            int u = random() % n, v = random() % n;
            int lower = int(random() % 5) - 2, upper = lower + random() % 4;
            edges.push_back({u, v, lower, upper, int(random() % 9) - 4});
            int f = lower + random() % (upper - lower + 1);
            supply[u] += f;
            supply[v] -= f;
        }
        if (tc % 3 == 0) {
            ++supply[random() % n];
            --supply[random() % n];
        }
        if (tc % 7 == 0) ++supply[random() % n];
        check(supply, edges);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
