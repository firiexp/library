#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../graph/shortest_path/bfs01.cpp"
#include "../graph/shortest_path/dijkstra.cpp"

template<class T>
void check(int n, const vector<tuple<int, int, int>> &edges) {
    vector<vector<edge<T>>> g(n);
    for (auto [u, v, w] : edges) g[u].emplace_back(v, T(w));
    auto original = g;
    for (int s = 0; s < n; ++s) assert(bfs01(s, g) == dijkstra(s, g));
    for (int v = 0; v < n; ++v) {
        assert(g[v].size() == original[v].size());
        for (int i = 0; i < int(g[v].size()); ++i) {
            assert(g[v][i].to == original[v][i].to);
            assert(g[v][i].cost == original[v][i].cost);
        }
    }
}

struct CountedDistance {
    int value;
    static inline int additions = 0;
    constexpr CountedDistance(int value = 0) : value(value) {}
    friend CountedDistance operator+(CountedDistance a, CountedDistance b) {
        ++additions;
        return a.value + b.value;
    }
    friend bool operator<=(CountedDistance a, CountedDistance b) {
        return a.value <= b.value;
    }
    friend bool operator==(CountedDistance a, CountedDistance b) {
        return a.value == b.value;
    }
};

template<> constexpr CountedDistance INF<CountedDistance> = CountedDistance(1000000000);

void check_edge_scans() {
    int n = 103;
    vector<vector<edge<CountedDistance>>> g(n);
    g[0].emplace_back(1, 1);
    g[0].emplace_back(2, 0);
    g[2].emplace_back(1, 0);
    for (int v = 1; v < n - 1; ++v) g[1].emplace_back(v, 1);
    CountedDistance::additions = 0;
    auto d = bfs01(0, g);
    assert(CountedDistance::additions == n + 1);
    assert(d[0] == 0 && d[1] == 0 && d[2] == 0);
    for (int v = 3; v < n - 1; ++v) assert(d[v] == 1);
    assert(d.back() == INF<CountedDistance>);
}

void self_check() {
    check<int>(1, {});
    check<int>(1, {{0, 0, 0}, {0, 0, 1}});
    check<int>(6, {{0, 1, 1}, {0, 2, 0}, {2, 1, 0}, {1, 3, 1},
                   {1, 3, 1}, {3, 4, 0}, {4, 3, 0}, {4, 4, 1}});
    check_edge_scans();
    mt19937 rng(185);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 1 + rng() % 15;
        vector<tuple<int, int, int>> edges;
        for (int i = rng() % (n * n + 1); i--; ) {
            int u = rng() % n, v = rng() % n;
            int w = tc % 3 == 0 ? 1 : tc % 3 == 1 ? 0 : rng() % 2;
            edges.emplace_back(u, v, w);
            if (i % 5 == 0) edges.emplace_back(u, v, w);
        }
        check<int>(n, edges);
        check<long long>(n, edges);
    }
}

int main() {
    self_check();
}
