#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"

namespace plain {
#include "../graph/bellman_ford.cpp"
}
namespace propagated {
#include "../graph/bellman_ford_negative_loop.cpp"
}

void check(int n, const vector<tuple<int, int, ll>> &edges) {
    constexpr ll unreachable = 1000000000;
    vector<vector<ll>> d(n, vector<ll>(n, unreachable));
    for (int v = 0; v < n; ++v) d[v][v] = 0;
    vector<plain::edge<ll>> a;
    vector<propagated::edge<ll>> b;
    for (auto [u, v, w] : edges) {
        d[u][v] = min(d[u][v], w);
        a.emplace_back(u, v, w);
        b.emplace_back(u, v, w);
    }
    for (int k = 0; k < n; ++k) for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v)
        if (d[u][k] != unreachable && d[k][v] != unreachable)
            d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
    for (int s = 0; s < n; ++s) {
        auto result = plain::bellman_ford(s, n, a);
        auto marked = propagated::bellman_ford(s, n, b);
        bool any_negative = false;
        for (int v = 0; v < n; ++v) {
            bool negative = false;
            for (int k = 0; k < n; ++k)
                negative |= d[s][k] != unreachable && d[k][k] < 0 && d[k][v] != unreachable;
            any_negative |= negative;
            ll expected = negative ? -INF<ll> : d[s][v] == unreachable ? INF<ll> : d[s][v];
            assert(marked[v] == expected);
            if (!result.empty() && !negative)
                assert(result[v] == (d[s][v] == unreachable ? LLONG_MAX : d[s][v]));
        }
        assert(result.empty() == any_negative);
    }
}

void self_check() {
    check(1, {});
    check(1, {{0, 0, -1}});
    check(1, {{0, 0, 1}});
    check(4, {{0, 1, -2}, {0, 1, 3}, {2, 3, -1}, {3, 2, 0}});
    mt19937 rng(62);
    for (int tc = 0; tc < 1200; ++tc) {
        int n = 1 + rng() % 8;
        vector<tuple<int, int, ll>> edges;
        for (int i = rng() % (n * n + 1); i--; ) {
            int u = rng() % n, v = rng() % n;
            if (tc % 3 == 0 && u >= v) continue;
            edges.emplace_back(u, v, int(rng() % 15) - 5);
        }
        check(n, edges);
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
