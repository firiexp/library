#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include "../graph/shortest_path/floyd_warshall.cpp"
#include "../graph/shortest_path/bellman_ford.cpp"

template <class T>
void check(int n, const vector<edge<T>> &edges) {
    auto result = floyd_warshall(n, edges);
    vector<edge<__int128>> wide;
    for (const auto &e : edges) wide.emplace_back(e.from, e.to, e.cost);
    vector<vector<__int128>> expected;
    bool negative = false;
    for (int s = 0; s < n; ++s) {
        expected.push_back(bellman_ford(s, n, wide));
        negative |= expected.back().empty();
    }
    assert(result.empty() == negative);
    if (negative) return;
    assert(int(result.size()) == n);
    for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
        if (expected[u][v] == numeric_limits<__int128>::max()) {
            assert(result[u][v] == INF<T>);
        } else {
            assert(result[u][v] == expected[u][v]);
        }
    }
}

int main() {
    using ll = long long;
    check<ll>(1, {});
    check<ll>(1, {{0, 0, -1}});
    check<ll>(1, {{0, 0, 1}, {0, 0, 0}});
    check<ll>(5, {});
    check<ll>(4, {{0, 1, 5}, {0, 1, -2}, {1, 2, 0}, {2, 0, 2}});
    check<ll>(4, {{0, 1, 5}, {2, 3, -2}, {3, 2, 1}});
    check<ll>(2, {{0, 1, INF<ll> - 1}, {1, 0, INF<ll> - 1}});
    check<ll>(3, {{0, 1, INF<ll> - 10}, {1, 2, 9}});
    check<ll>(3, {{0, 1, -INF<ll> + 10}, {1, 2, -9}});
    check<ll>(2, {{0, 1, -INF<ll> + 1}, {1, 0, INF<ll> - 1}});
    check<ll>(2, {{0, 1, -INF<ll> + 1}, {1, 0, INF<ll> - 2}});
    check<ll>(2, {{0, 1, -INF<ll> + 1}, {1, 0, -INF<ll> + 1}});
    check<ll>(2, {{0, 0, -INF<ll> + 1}, {0, 1, 0}});
    check<int>(2, {{0, 1, INF<int> - 1}, {1, 0, INF<int> - 1}});
    check<int>(3, {{0, 1, -INF<int> + 10}, {1, 2, -9}});
    check<int>(2, {{0, 1, -INF<int> + 1}, {1, 0, -INF<int> + 1}});
    check<short>(2, {{0, 1, INF<short> - 1}, {1, 0, INF<short> - 1}});
    check<short>(2, {{0, 1, -INF<short> + 1}, {1, 0, -INF<short> + 1}});
    mt19937 rng(425);
    for (int trial = 0; trial < 3000; ++trial) {
        int n = 1 + rng() % 8;
        vector<edge<ll>> edges;
        vector<int> potential(n);
        for (int &p : potential) p = int(rng() % 31) - 15;
        for (int m = rng() % (n * n + 1); m > 0; --m) {
            int u = rng() % n, v = rng() % n;
            ll w = int(rng() % 15) - 5;
            if (trial % 2) w = int(rng() % 16) + potential[v] - potential[u];
            edges.emplace_back(u, v, w);
        }
        check(n, edges);
        shuffle(edges.begin(), edges.end(), rng);
        check(n, edges);
        for (auto &e : edges) e.cost *= (INF<ll> - 1) / (64 * n);
        check(n, edges);
    }
    vector<edge<ll>> cycle;
    for (int i = 0; i < 100; ++i) cycle.emplace_back(i, (i + 1) % 100, -(INF<ll> - 1) / 99);
    check(100, cycle);
}
