#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../graph/maxflow_lower_bound.cpp"

using Edge = tuple<int, int, ll, ll>;

void check_result(int n, int s, int t, const vector<Edge> &edges, ll expected) {
    MaxFlowLowerBound<ll> g(n);
    for (auto [u, v, lower, upper] : edges) g.add_edge(u, v, lower, upper);
    auto result = g.max_flow_with_edges(s, t);
    assert(result.exists == (expected >= 0));
    assert(result.value == max(0LL, expected));
    if (result.exists) {
        assert(result.edge_flow.size() == edges.size());
        vector<ll> balance(n);
        for (size_t i = 0; i < edges.size(); ++i) {
            auto [u, v, lower, upper] = edges[i];
            ll f = result.edge_flow[i];
            assert(lower <= f && f <= upper);
            balance[u] += f;
            balance[v] -= f;
        }
        for (int v = 0; v < n; ++v)
            assert(balance[v] == (v == s ? expected : v == t ? -expected : 0));
    } else {
        assert(result.edge_flow.empty());
    }
    auto again = g.max_flow_with_edges(s, t);
    assert(again.exists == result.exists && again.value == result.value);
    assert(again.edge_flow == result.edge_flow);
    assert(g.max_flow(s, t) == make_pair(result.exists, result.value));
}

void check(int n, int s, int t, const vector<Edge> &edges) {
    vector<ll> balance(n);
    ll expected = -1;
    auto enumerate = [&](auto &&self, size_t i) -> void {
        if (i == edges.size()) {
            for (int v = 0; v < n; ++v)
                if (v != s && v != t && balance[v]) return;
            if (balance[s] >= 0 && balance[s] == -balance[t])
                expected = max(expected, balance[s]);
            return;
        }
        auto [u, v, lower, upper] = edges[i];
        for (ll f = lower; f <= upper; ++f) {
            balance[u] += f;
            balance[v] -= f;
            self(self, i + 1);
            balance[u] -= f;
            balance[v] += f;
        }
    };
    enumerate(enumerate, 0);
    check_result(n, s, t, edges, expected);
}

int main() {
    check(2, 0, 1, {});
    check(3, 0, 2, {{0, 1, 1, 1}});
    check(2, 0, 1, {{1, 0, 1, 2}});
    check(3, 0, 2, {{0, 0, 2, 3}, {0, 1, 1, 3}, {0, 1, 2, 2},
                    {1, 2, 3, 6}, {2, 2, 1, 1}, {0, 2, 0, 0}});
    check_result(3, 0, 2, {{0, 1, 1LL << 40, 2LL << 40},
                          {1, 2, 1LL << 40, 3LL << 40}}, 2LL << 40);
    mt19937 rng(106);
    for (int tc = 0; tc < 10000; ++tc) {
        int n = 2 + rng() % 5;
        int s = rng() % n, t = rng() % (n - 1);
        if (t >= s) ++t;
        vector<Edge> edges;
        int m = rng() % 8;
        for (int i = 0; i < m; ++i) {
            ll upper = rng() % 4, lower = rng() % (upper + 1);
            edges.emplace_back(rng() % n, rng() % n, lower, upper);
        }
        check(n, s, t, edges);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
