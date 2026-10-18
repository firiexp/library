#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/range_contour_sum.cpp"

void check(int n, int mode, mt19937 &rng) {
    vector<vector<int>> g(n), distance(n, vector<int>(n, -1));
    for (int i = 1; i < n; ++i) {
        int p = mode == 0 ? i - 1 : mode == 1 ? 0 : mode == 3 ? (i - 1) / 2 : rng() % i;
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
    for (int start : {0, n - 1, int(rng() % n), 0}) {
        int root = helper.build(start);
        auto path = helper.path, dist = helper.dist, tree = helper.tree;
        auto parent = helper.parent, depth = helper.depth;
        assert(helper.build(start) == root);
        assert(path == helper.path && dist == helper.dist && tree == helper.tree);
        assert(parent == helper.parent && depth == helper.depth);
        assert(helper.parent[root] == -1 && helper.depth[root] == 0);
        int edge_count = 0;
        for (int v = 0; v < n; ++v) {
            assert(path[v].front() == v && path[v].back() == root);
            assert(path[v].size() == dist[v].size());
            assert(int(path[v].size()) == helper.depth[v] + 1);
            for (int i = 0; i < (int)path[v].size(); ++i) {
                assert(dist[v][i] == distance[v][path[v][i]]);
                if (i > 0) assert(helper.parent[path[v][i - 1]] == path[v][i]);
            }
            for (int child : tree[v]) {
                assert(helper.parent[child] == v && helper.depth[child] == helper.depth[v] + 1);
                ++edge_count;
            }
        }
        assert(edge_count == n - 1);
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
    CentroidDecompositionQueryHelper empty_helper(0);
    assert(empty_helper.build() == -1 && empty_helper.build() == -1);
    mt19937 rng(20261010);
    for (int n : {1, 2, 3, 63, 64, 65, 100})
        for (int mode = 0; mode < 4; ++mode) check(n, mode, rng);
    for (int tc = 0; tc < 500; ++tc) check(1 + rng() % 50, 2, rng);
}
