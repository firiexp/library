#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../graph/independentset.cpp"

pair<int, ull> brute(int n, const vector<pair<int, int>> &edges) {
    vector<ull> adjacent(n);
    for (auto [u, v] : edges) {
        adjacent[u] |= 1ull << v;
        adjacent[v] |= 1ull << u;
    }
    vector<char> independent(1 << n);
    independent[0] = true;
    pair<int, ull> best = {0, 0};
    for (ull mask = 1; mask < (1ull << n); ++mask) {
        int v = __builtin_ctzll(mask);
        ull rest = mask & (mask - 1);
        independent[mask] = independent[rest] && !(adjacent[v] & rest);
        if (independent[mask]) best = max(best, pair<int, ull>{__builtin_popcountll(mask), mask});
    }
    return best;
}

int main() {
    for (int n : {0, 1, 63, 64}) {
        IndependentSet empty(n), complete(n);
        ull all = n == 64 ? ~0ull : (1ull << n) - 1;
        assert((empty.maximum_independent_set() == pair<int, ull>{n, all}));
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) complete.add_edge(u, v);
        auto [size, mask] = complete.maximum_independent_set();
        assert(size == (n > 0));
        assert(__builtin_popcountll(mask) == size && (mask & ~all) == 0);
        assert(mask == (n ? 1ull << (n - 1) : 0));
    }
    for (int center : {0, 63}) {
        IndependentSet star(64);
        for (int v = 0; v < 64; ++v) if (v != center) star.add_edge(center, v);
        assert((star.maximum_independent_set() == pair<int, ull>{63, ~(1ull << center)}));
    }
    IndependentSet bipartite(64);
    for (int u = 0; u < 32; ++u) for (int v = 32; v < 64; ++v) bipartite.add_edge(u, v);
    assert((bipartite.maximum_independent_set() == pair<int, ull>{32, ~0ull << 32}));
    mt19937 rng(38);
    for (int n = 0; n <= 12; ++n) for (int tc = 0; tc < 60; ++tc) {
        IndependentSet solver(n);
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) if (int(rng() % 10) < tc % 10) {
            solver.add_edge(u, v);
            edges.emplace_back(u, v);
        }
        auto valid = [&](ull mask) {
            for (auto [u, v] : edges) if ((mask >> u & 1) && (mask >> v & 1)) return false;
            return true;
        };
        auto expected = brute(n, edges);
        auto [size, mask] = solver.maximum_independent_set();
        assert((pair<int, ull>{size, mask} == expected));
        assert(valid(mask));
        assert(solver.maximum_independent_set() == expected);
    }
    for (int n = 0; n <= 6; ++n) {
        vector<pair<int, int>> pairs;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) pairs.emplace_back(u, v);
        for (int mask = 0; mask < (1 << pairs.size()); ++mask) {
            IndependentSet solver(n);
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)pairs.size(); ++i) if (mask >> i & 1) {
                auto [u, v] = pairs[i];
                solver.add_edge(u, v);
                edges.emplace_back(u, v);
            }
            auto expected = brute(n, edges);
            assert(solver.maximum_independent_set() == expected);
            assert(solver.maximum_independent_set() == expected);
        }
    }
    for (int tc = 0; tc < 80; ++tc) {
        int n = 1 + rng() % 16;
        IndependentSet solver(n);
        vector<pair<int, int>> edges;
        for (int step = 0; step < 20; ++step) {
            int u = rng() % n, v = rng() % n;
            if (u != v) {
                solver.add_edge(u, v);
                edges.emplace_back(u, v);
            }
            assert(solver.maximum_independent_set() == brute(n, edges));
        }
    }
    IndependentSet triangles(63);
    ull expected_mask = 0;
    for (int i = 0; i < 63; i += 3) {
        triangles.add_edge(i, i + 1);
        triangles.add_edge(i, i + 2);
        triangles.add_edge(i + 1, i + 2);
        expected_mask |= 1ull << (i + 2);
    }
    assert((triangles.maximum_independent_set() == pair<int, ull>{21, expected_mask}));
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
