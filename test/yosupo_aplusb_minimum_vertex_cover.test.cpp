#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/hopcroft_karp.cpp"

void check(HopcroftKarp &hk, const vector<unsigned> &edges, int r) {
    int l = edges.size(), best = l + r;
    for (unsigned mask = 0; mask < (1U << l); ++mask) {
        unsigned right = 0;
        for (int u = 0; u < l; ++u) if (!(mask >> u & 1)) right |= edges[u];
        best = min(best, __builtin_popcount(mask) + __builtin_popcount(right));
    }
    for (int repeat = 0; repeat < 2; ++repeat) {
        auto [left, right] = hk.minimum_vertex_cover();
        assert((int)(left.size() + right.size()) == best);
        assert(is_sorted(left.begin(), left.end()) && is_sorted(right.begin(), right.end()));
        vector<bool> seen_l(l), seen_r(r);
        for (int u : left) { assert(0 <= u && u < l && !seen_l[u]); seen_l[u] = true; }
        for (int v : right) { assert(0 <= v && v < r && !seen_r[v]); seen_r[v] = true; }
        for (int u = 0; u < l; ++u) for (int v = 0; v < r; ++v)
            if (edges[u] >> v & 1) assert(seen_l[u] || seen_r[v]);
        auto pairs = hk.get_pairs();
        assert((int)pairs.size() == best);
        fill(seen_l.begin(), seen_l.end(), false);
        fill(seen_r.begin(), seen_r.end(), false);
        for (auto [u, v] : pairs) {
            assert((edges[u] >> v & 1) && !seen_l[u] && !seen_r[v]);
            seen_l[u] = seen_r[v] = true;
            assert(hk.match_left[u] == v && hk.match_right[v] == u);
        }
        assert(hk.max_matching() == best);
    }
}

void self_check() {
    for (unsigned mask = 0; mask < (1U << 16); ++mask) {
        HopcroftKarp hk(4, 4);
        vector<unsigned> edges(4);
        for (int u = 0; u < 4; ++u) for (int v = 0; v < 4; ++v) if (mask >> (4 * u + v) & 1) {
            hk.add_edge(u, v);
            edges[u] |= 1U << v;
        }
        if (mask & 1) hk.max_matching();
        check(hk, edges, 4);
    }
    mt19937 random(56);
    for (int l = 0; l <= 6; ++l) for (int r = 0; r <= 6; ++r) {
        HopcroftKarp hk(l, r);
        vector<unsigned> edges(l);
        check(hk, edges, r);
        if (!l || !r) continue;
        for (int step = 0; step < 30; ++step) {
            int u = random() % l, v = random() % r;
            hk.add_edge(u, v);
            if (step % 3 == 0) hk.add_edge(u, v);
            edges[u] |= 1U << v;
            if (step % 2) hk.max_matching();
            check(hk, edges, r);
        }
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
