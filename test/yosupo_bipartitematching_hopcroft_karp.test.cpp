#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <queue>
#include <algorithm>
#include <cassert>
#include <random>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../graph/hopcroft_karp.cpp"

void repeated_matching_check() {
    mt19937 rng(55);
    for (int l = 0; l <= 6; ++l) {
        for (int r = 0; r <= 6; ++r) {
            HopcroftKarp hk(l, r);
            vector<vector<bool>> edges(l, vector<bool>(r));
            for (int step = 0; step < 25; ++step) {
                if (l && r && step > 0) {
                    int u = rng() % l, v = rng() % r;
                    hk.add_edge(u, v);
                    edges[u][v] = true;
                }
                vector<bool> possible(1 << r);
                possible[0] = true;
                for (int u = 0; u < l; ++u) {
                    auto next = possible;
                    for (int mask = 0; mask < (1 << r); ++mask) {
                        if (!possible[mask]) continue;
                        for (int v = 0; v < r; ++v)
                            if (edges[u][v] && !(mask >> v & 1)) next[mask | (1 << v)] = true;
                    }
                    possible = next;
                }
                int expected = 0;
                for (int mask = 0; mask < (1 << r); ++mask)
                    if (possible[mask]) expected = max(expected, __builtin_popcount((unsigned)mask));
                for (int repeat = 0; repeat < 2; ++repeat) {
                    assert(hk.max_matching() == expected);
                    auto pairs = hk.get_pairs();
                    assert(int(pairs.size()) == expected);
                    vector<bool> used_l(l), used_r(r);
                    for (auto [u, v] : pairs) {
                        assert(edges[u][v] && !used_l[u] && !used_r[v]);
                        used_l[u] = used_r[v] = true;
                        assert(hk.match_left[u] == v && hk.match_right[v] == u);
                    }
                }
            }
        }
    }
}

int main() {
    repeated_matching_check();
    Scanner in;
    Printer out;
    int l, r, m;
    in.read(l, r, m);
    HopcroftKarp hk(l, r);
    for (int i = 0; i < m; ++i) {
        int a, b;
        in.read(a, b);
        hk.add_edge(a, b);
    }
    int ans = hk.max_matching();
    out.println(ans);
    auto pairs = hk.get_pairs();
    for (auto&& [a, b] : pairs) {
        out.println(a, b);
    }
    return 0;
}
