#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../flow/primaldual.cpp"

void check(int n, const vector<array<int, 4>>& edges) {
    int total = 0;
    for (auto e : edges) total += e[2];
    vector<long long> best(total + 1, INF<long long>);
    vector<int> balance(n);
    auto enumerate = [&](auto&& self, int i, long long cost) -> void {
        if (i == (int)edges.size()) {
            for (int v = 1; v < n - 1; ++v) if (balance[v]) return;
            if (balance[0] < 0 || balance[0] != -balance[n - 1]) return;
            best[balance[0]] = min(best[balance[0]], cost);
            return;
        }
        auto [u, v, cap, c] = edges[i];
        for (int f = 0; f <= cap; ++f) {
            balance[u] += f;
            balance[v] -= f;
            self(self, i + 1, cost + (long long)f * c);
            balance[u] -= f;
            balance[v] += f;
        }
    };
    enumerate(enumerate, 0, 0);
    int maximum = total;
    while (best[maximum] == INF<long long>) --maximum;
    for (int limit = 0; limit <= maximum + 2; ++limit) {
        PrimalDual<int, long long> mf(n);
        for (auto [u, v, cap, cost] : edges) mf.add_edge(u, v, cap, cost);
        auto legacy = mf;
        auto initial = mf.G;
        auto curve = mf.slope(0, n - 1, limit);
        int amount = min(limit, maximum);
        assert((curve.front() == pair<int, long long>{0, 0}));
        assert((curve.back() == pair<int, long long>{amount, best[amount]}));
        long long previous = -1;
        for (int i = 1; i < (int)curve.size(); ++i) {
            auto [l, c1] = curve[i - 1];
            auto [r, c2] = curve[i];
            assert(l < r && c1 <= c2);
            assert((c2 - c1) % (r - l) == 0);
            long long marginal = (c2 - c1) / (r - l);
            assert(previous < marginal);
            previous = marginal;
            for (int f = l; f <= r; ++f) assert(c1 + marginal * (f - l) == best[f]);
        }
        int ok = -1;
        assert(legacy.flow(0, n - 1, limit, ok) == best[amount]);
        assert(ok == (limit <= maximum));
        for (int v = 0; v < n; ++v) for (int i = 0; i < (int)mf.G[v].size(); ++i) {
            auto e = mf.G[v][i];
            auto rev = mf.G[e.to][e.rev];
            assert(rev.to == v && rev.rev == i && e.cap >= 0);
            assert(e.cap + rev.cap == initial[v][i].cap + initial[e.to][e.rev].cap);
            if (e.cap) assert(e.cost + mf.potential[v] - mf.potential[e.to] >= 0);
        }
    }
}

int main() {
    check(2, {});
    check(2, {{0, 0, 2, 0}, {0, 1, 2, 0}, {0, 1, 2, 0}, {0, 1, 1, 3}});
    check(5, {{0, 4, 1, 1}, {0, 1, 1, 1}, {1, 2, 1, 0}, {2, 4, 1, 0},
              {0, 2, 1, 100}, {3, 2, 1, 0}});
    check(6, {{0, 1, 1, 0}, {0, 2, 1, 0}, {1, 3, 1, 1}, {1, 4, 1, 2},
              {2, 3, 1, 2}, {2, 4, 1, 100}, {3, 5, 1, 0}, {4, 5, 1, 0}});
    mt19937 rng(94);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = 2 + rng() % 4;
        vector<array<int, 4>> edges;
        for (int i = 0; i < 7; ++i)
            edges.push_back({(int)(rng() % n), (int)(rng() % n), (int)(rng() % 3), (int)(rng() % 7)});
        check(n, edges);
    }
    for (long long limit : {0LL, 1LL, 1000000000001LL, INF<long long>}) {
        PrimalDual<long long, long long> mf(2);
        mf.add_edge(0, 1, 1000000000000LL, 7);
        mf.add_edge(0, 1, 1000000000000LL, 7);
        auto curve = mf.slope(0, 1, limit);
        long long amount = min(limit, 2000000000000LL);
        vector<pair<long long, long long>> expected{{0, 0}};
        if (amount) expected.emplace_back(amount, amount * 7);
        assert(curve == expected);
    }
    PrimalDual<int, long long> unlimited(2);
    unlimited.add_edge(0, 1, 3, 5);
    assert((unlimited.slope(0, 1) == vector<pair<int, long long>>{{0, 0}, {3, 15}}));
    PrimalDual<int, long long> distances(5);
    distances.add_edge(0, 1, 1, 1);
    distances.add_edge(0, 2, 1, 100);
    distances.add_edge(1, 2, 1, 2);
    distances.add_edge(2, 3, 1, 4);
    distances.dijkstra(0);
    assert((distances.min_cost == vector<long long>{0, 1, 3, 7, INF<long long>}));
    PrimalDual<int, long long> wide(4);
    long long cost = INF<long long> / 8;
    wide.add_edge(0, 3, 1, cost);
    wide.add_edge(0, 1, 1, 2 * cost);
    wide.add_edge(1, 3, 1, cost);
    wide.add_edge(2, 1, 1, 0);
    assert((wide.slope(0, 3) == vector<pair<int, long long>>{{0, 0}, {1, cost}, {2, 4 * cost}}));
    for (int v = 0; v < 4; ++v) for (auto e : wide.G[v])
        if (e.cap) assert(e.cost + wide.potential[v] - wide.potential[e.to] >= 0);
}
