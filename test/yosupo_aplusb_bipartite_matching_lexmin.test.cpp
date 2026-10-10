#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/bipartite_matching_lexmin.cpp"

void check(int l, int r, const vector<pair<int, int>> &edges) {
    Bipartite_Matching_LexMin solver(l, r);
    vector<vector<int>> g(l);
    for (auto [u, v] : edges) {
        solver.add_edge(u, v);
        g[u].push_back(v);
    }
    vector<int> current(l, -1), best;
    int size = -1;
    auto enumerate = [&](auto &&self, int u, int used, int count) -> void {
        if (u == l) {
            if (count > size || (count == size && current < best)) {
                size = count;
                best = current;
            }
            return;
        }
        current[u] = -1;
        self(self, u + 1, used, count);
        for (int v : g[u]) {
            if (used >> v & 1) continue;
            current[u] = v;
            self(self, u + 1, used | (1 << v), count + 1);
        }
    };
    enumerate(enumerate, 0, 0, 0);
    assert(solver.solve_LexMin() == size);
    for (int u = 0; u < l; ++u) {
        assert(solver.match[u] == (best[u] == -1 ? -1 : l + best[u]));
        if (best[u] != -1) assert(solver.match[l + best[u]] == u);
    }
    auto match = solver.match;
    assert(solver.solve_LexMin() == size && solver.match == match);
}

int main() {
    check(3, 2, {{0, 0}, {0, 1}, {1, 0}, {2, 1}});
    for (int mask = 0; mask < (1 << 16); ++mask) {
        vector<pair<int, int>> edges;
        for (int u = 0; u < 4; ++u)
            for (int v = 0; v < 4; ++v)
                if (mask >> (4 * u + v) & 1) edges.emplace_back(u, v);
        check(4, 4, edges);
    }
    mt19937 rng(20261010);
    for (int tc = 0; tc < 2000; ++tc) {
        int l = rng() % 7, r = rng() % 7;
        vector<pair<int, int>> edges;
        for (int u = 0; u < l; ++u)
            for (int v = 0; v < r; ++v)
                if (rng() % 3 == 0) edges.emplace_back(u, v);
        shuffle(edges.begin(), edges.end(), rng);
        check(l, r, edges);
    }
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
