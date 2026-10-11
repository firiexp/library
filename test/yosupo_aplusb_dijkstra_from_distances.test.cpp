#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../graph/dijkstra.cpp"
#include "../graph/dijkstra_from_distances.cpp"
#include "../graph/dijkstra.cpp"
#include "../graph/dijkstra_from_distances.cpp"
#include "../graph/dijkstra_restore.cpp"
#include "../graph/dijkstra_radix_heap.cpp"

void check(const vector<ll>& initial, const vector<vector<edge<ll>>>& g) {
    int n = g.size();
    vector<vector<ll>> dist(n, vector<ll>(n, INF<ll>));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (auto e : g[i]) dist[i][e.to] = min(dist[i][e.to], e.cost);
    }
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (dist[i][k] != INF<ll> && dist[k][j] != INF<ll>) {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
    vector<ll> expected(n, INF<ll>);
    for (int v = 0; v < n; ++v) for (int s = 0; s < n; ++s) {
        if (initial[s] != INF<ll> && dist[s][v] != INF<ll>) {
            expected[v] = min(expected[v], initial[s] + dist[s][v]);
        }
    }
    auto original = initial;
    assert(dijkstra_from_distances(initial, g) == expected);
    assert(initial == original);
    auto moved = initial;
    auto storage = moved.data();
    auto result = dijkstra_from_distances(std::move(moved), g);
    assert(result == expected && result.data() == storage);
    if (n) {
        int s = n / 2;
        assert(dijkstra(s, g) == dist[s]);
        assert(dijkstra_restore(s, g).dist == dist[s]);
        assert(dijkstra_radix_heap(s, g) == dist[s]);
    }
}

void self_check() {
    check({}, {});
    check({INF<ll>, INF<ll>}, {{{1, 0}}, {{0, 0}}});
    check({50, -10, INF<ll>}, {{{2, 1}}, {{0, 2}, {0, 3}}, {}});
    check({LLONG_MIN, INF<ll>}, {{{1, 7}}, {}});
    check({INF<ll> - 10, INF<ll>}, {{{1, 7}}, {}});
    mt19937 rng(157);
    for (int tc = 0; tc < 2000; ++tc) {
        int n = 1 + rng() % 22;
        vector<vector<edge<ll>>> g(n);
        int m = rng() % 100;
        for (int i = 0; i < m; ++i) {
            int u = rng() % n, v = rng() % n;
            g[u].emplace_back(v, rng() % 31);
        }
        vector<ll> initial(n, INF<ll>);
        for (auto& x : initial) if (rng() % 3) x = int(rng() % 201) - 100;
        check(initial, g);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
