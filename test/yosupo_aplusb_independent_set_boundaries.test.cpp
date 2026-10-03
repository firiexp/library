#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../graph/independentset.cpp"

int main() {
    for (int n : {0, 1, 63, 64}) {
        IndependentSet empty(n), complete(n);
        ull all = n == 64 ? ~0ull : (1ull << n) - 1;
        assert((empty.maximum_independent_set() == pair<int, ull>{n, all}));
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) complete.add_edge(u, v);
        auto [size, mask] = complete.maximum_independent_set();
        assert(size == (n > 0));
        assert(__builtin_popcountll(mask) == size && (mask & ~all) == 0);
    }
    mt19937 rng(38);
    for (int n = 0; n <= 12; ++n) for (int tc = 0; tc < 30; ++tc) {
        IndependentSet solver(n);
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v) if (rng() % 2) {
            solver.add_edge(u, v);
            edges.emplace_back(u, v);
        }
        auto valid = [&](ull mask) {
            for (auto [u, v] : edges) if ((mask >> u & 1) && (mask >> v & 1)) return false;
            return true;
        };
        int expected = 0;
        for (ull mask = 0; mask < (1ull << n); ++mask)
            if (valid(mask)) expected = max(expected, __builtin_popcountll(mask));
        auto [size, mask] = solver.maximum_independent_set();
        assert(size == expected && __builtin_popcountll(mask) == expected && valid(mask));
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
