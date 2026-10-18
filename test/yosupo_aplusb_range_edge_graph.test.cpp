#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 4;
#include "../util/fastio.cpp"
#include "../graph/range_edge_graph.cpp"
#include "../graph/dijkstra.cpp"

int main() {
    RangeEdgeGraph<int> empty(0);
    empty.add_range_to_range(0, 0, 0, 0, 0);
    assert(empty.graph().empty());
    mt19937 rng(152);
    for (int tc = 0; tc < 4000; ++tc) {
        int n = 1 + rng() % 9;
        RangeEdgeGraph<long long> rg(n);
        vector<vector<long long>> expected(n, vector<long long>(n, INF<long long>));
        for (int i = 0; i < n; ++i) expected[i][i] = 0;
        for (int i = 0; i < 30; ++i) {
            int l1 = rng() % (n + 1), r1 = rng() % (n + 1);
            int l2 = rng() % (n + 1), r2 = rng() % (n + 1);
            if (l1 > r1) swap(l1, r1);
            if (l2 > r2) swap(l2, r2);
            int type = rng() % 4, u = rng() % n, v = rng() % n;
            long long w = rng() % 8;
            if (tc % 11 == 0) w *= 1000000000000LL;
            if (type == 0) {
                rg.add_edge(u, v, w);
                l1 = u; r1 = u + 1; l2 = v; r2 = v + 1;
            } else if (type == 1) {
                rg.add_to_range(u, l2, r2, w);
                l1 = u; r1 = u + 1;
            } else if (type == 2) {
                rg.add_from_range(l1, r1, v, w);
                l2 = v; r2 = v + 1;
            } else {
                size_t before = rg.graph().size();
                rg.add_range_to_range(l1, r1, l2, r2, w);
                assert(rg.graph().size() == before + (l1 < r1 && l2 < r2));
            }
            for (int a = l1; a < r1; ++a) {
                for (int b = l2; b < r2; ++b) expected[a][b] = min(expected[a][b], w);
            }
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    expected[i][j] = min(expected[i][j], expected[i][k] + expected[k][j]);
                }
            }
        }
        for (int i = 0; i < (int)rg.graph().size(); ++i) {
            for (const auto &e : rg.graph()[i]) assert(e.from == i);
        }
        for (int s = 0; s < n; ++s) {
            auto dist = dijkstra(s, rg.graph());
            for (int v = 0; v < n; ++v) assert(dist[v] == expected[s][v]);
        }
    }
    int n = 100000, q = 100000;
    RangeEdgeGraph<int> rg(n);
    rg.add_to_range(0, 0, n, 1);
    for (int i = 0; i < q; ++i) {
        int l = rng() % n, r = l + 1 + rng() % (n - l);
        int w = 1 + i % 11;
        if (i % 4 == 0) rg.add_range_to_range(0, n, l, r, w);
        if (i % 4 == 1) rg.add_range_to_range(l, r, n / 3, 2 * n / 3, w);
        if (i % 4 == 2) rg.add_to_range(i % n, l, l + 1, w);
        if (i % 4 == 3) rg.add_from_range(l, r, i % n, w);
    }
    auto dist = dijkstra(0, rg.graph());
    assert(dist[0] == 0);
    for (int v = 1; v < n; ++v) assert(dist[v] == 1);
    assert((int)rg.graph().size() == 3 * n - 2 + q / 2);
}
