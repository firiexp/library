#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/range_contour_sum.cpp"

void check(int n, int mode, mt19937 &rng) {
    vector<vector<int>> g(n), distance(n, vector<int>(n, -1));
    for (int i = 1; i < n; ++i) {
        int p = mode == 0 ? i - 1 : mode == 1 ? 0 : rng() % i;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    for (int v = 0; v < n; ++v) {
        vector<int> queue{v};
        distance[v][v] = 0;
        for (int i = 0; i < (int)queue.size(); ++i) {
            int x = queue[i];
            for (int u : g[x]) {
                if (distance[v][u] != -1) continue;
                distance[v][u] = distance[v][x] + 1;
                queue.push_back(u);
            }
        }
    }
    CentroidDecompositionQueryHelper helper(n);
    helper.G = g;
    helper.build();
    auto path = helper.path, dist = helper.dist;
    helper.build();
    assert(path == helper.path && dist == helper.dist);
    for (int v = 0; v < n; ++v) {
        assert(path[v].front() == v && path[v].back() == helper.root);
        for (int i = 0; i < (int)path[v].size(); ++i) {
            assert(dist[v][i] == distance[v][path[v][i]]);
            if (i > 0) assert(helper.parent[path[v][i - 1]] == path[v][i]);
        }
    }
    vector<long long> values(n);
    for (auto &x : values) x = (int)(rng() % 21) - 10;
    RangeContourSum solver(g, values);
    for (int step = 0; step < 200; ++step) {
        int v = rng() % n;
        if (step % 3 == 0) {
            long long x = (int)(rng() % 21) - 10;
            solver.add(v, x);
            values[v] += x;
        }
        int l = (int)(rng() % (n + 10)) - 5;
        int r = (int)(rng() % (n + 10)) - 5;
        if (step % 20 == 0) l = INT_MIN, r = INT_MAX;
        long long expected = 0;
        for (int u = 0; u < n; ++u)
            if (l <= distance[v][u] && distance[v][u] < r) expected += values[u];
        assert(solver.query(v, l, r) == expected);
        assert(solver.query(v, 0, 1) == values[v]);
    }
}

int main() {
    RangeContourSum empty({}, {});
    mt19937 rng(20261010);
    for (int n : {1, 2, 3, 63, 64, 65, 100})
        for (int mode = 0; mode < 3; ++mode) check(n, mode, rng);
    for (int tc = 0; tc < 500; ++tc) check(1 + rng() % 50, 2, rng);
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
