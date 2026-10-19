#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/link_cut_tree.cpp"

struct Monoid {
    using T = string;
    static T f(const T &a, const T &b) { return a + b; }
    static T e() { return ""; }
};

struct Forest {
    int n;
    vector<vector<bool>> edge;
    vector<int> roots;
    vector<string> values;
    Forest(int n) : n(n), edge(n, vector<bool>(n)), roots(n), values(n) {
        iota(roots.begin(), roots.end(), 0);
    }
    vector<int> path(int u, int v) const {
        vector<int> parent(n, -1), order{u};
        parent[u] = u;
        for (int i = 0; i < (int)order.size(); ++i) for (int w = 0; w < n; ++w) {
            if (edge[order[i]][w] && parent[w] == -1) {
                parent[w] = order[i];
                order.push_back(w);
            }
        }
        if (parent[v] == -1) return {};
        vector<int> result{v};
        while (v != u) result.push_back(v = parent[v]);
        reverse(result.begin(), result.end());
        return result;
    }
    void evert(int u) {
        int previous = roots[u];
        for (int &root : roots) if (root == previous) root = u;
    }
    bool link(int u, int v) {
        evert(u);
        if (roots[u] == roots[v]) return false;
        int target = roots[v];
        for (int &root : roots) if (root == u) root = target;
        edge[u][v] = edge[v][u] = true;
        return true;
    }
    bool cut(int u, int v) {
        evert(u);
        if (!edge[u][v]) return false;
        edge[u][v] = edge[v][u] = false;
        for (int w = 0; w < n; ++w) if (!path(v, w).empty()) roots[w] = v;
        return true;
    }
};

void check_get(const LinkCutTree<Monoid> &lct, const Forest &forest) {
    auto before = lct.nodes;
    auto stack = lct.push_stack;
    for (int x = 0; x < forest.n; ++x) assert(lct.get(x) == forest.values[x]);
    for (int x = 0; x < forest.n; ++x) {
        auto a = before[x], b = lct.nodes[x];
        assert(tie(a.l, a.r, a.p, a.sz, a.rev, a.val, a.sum, a.rsum) ==
               tie(b.l, b.r, b.p, b.sz, b.rev, b.val, b.sum, b.rsum));
    }
    assert(lct.push_stack == stack);
}

void pending_reverse_check() {
    LinkCutTree<Monoid> lct(9);
    Forest forest(9);
    for (int x = 0; x < 9; ++x) {
        forest.values[x] = string(1, 'a' + x);
        lct.set(x, forest.values[x]);
    }
    for (auto [u, v] : vector<pair<int, int>>{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {2, 5}, {5, 6}, {5, 7}, {7, 8}})
        assert(lct.link(u, v) == forest.link(u, v));
    for (int root : {0, 8, 4, 6}) {
        lct.evert(root);
        forest.evert(root);
        assert(lct.nodes[root].rev);
        check_get(lct, forest);
        for (int x : {root, 2, 8, 1, 5}) {
            forest.values[x] += 'x';
            lct.set(x, forest.values[x]);
        }
        check_get(lct, forest);
        for (int x = 0; x < 9; ++x) assert(lct.get_root(x) == root);
        for (int u = 0; u < 9; ++u) for (int v = 0; v < 9; ++v) {
            string expected;
            for (int x : forest.path(u, v)) expected += forest.values[x];
            forest.evert(u);
            assert(lct.fold(u, v) == expected);
        }
        assert(lct.cut(2, 5) == forest.cut(2, 5));
        for (int x : {2, 5, 6}) {
            forest.values[x] += 'y';
            lct.set(x, forest.values[x]);
        }
        for (int x = 0; x < 9; ++x) assert(lct.get_root(x) == forest.roots[x]);
        assert(lct.link(2, 5) == forest.link(2, 5));
        string expected;
        for (int x : forest.path(4, 8)) expected += forest.values[x];
        forest.evert(4);
        assert(lct.fold(4, 8) == expected);
    }
}

void self_check() {
    mt19937 rng(174);
    for (int tc = 0; tc < 180; ++tc) {
        int n = 1 + rng() % 24;
        LinkCutTree<Monoid> lct(n);
        Forest forest(n);
        for (int v = 0; v < n; ++v) {
            forest.values[v] = string(1, 'a' + v);
            lct.set(v, forest.values[v]);
            if (v && rng() % 2) {
                int u = rng() % v;
                assert(lct.link(u, v) == forest.link(u, v));
            }
        }
        for (int step = 0; step < 250; ++step) {
            int u = rng() % n, v = rng() % n;
            int op = rng() % 6;
            if (op == 0) {
                assert(lct.link(u, v) == forest.link(u, v));
            } else if (op == 1) {
                vector<pair<int, int>> edges;
                for (int a = 0; a < n; ++a) for (int b = a + 1; b < n; ++b)
                    if (forest.edge[a][b]) edges.emplace_back(a, b);
                if (!edges.empty() && rng() % 2) tie(u, v) = edges[rng() % edges.size()];
                if (rng() % 2) swap(u, v);
                assert(lct.cut(u, v) == forest.cut(u, v));
            } else if (op == 2) {
                forest.evert(u);
                lct.evert(u);
            } else if (op == 3) {
                for (int x : {u, v, int(rng() % n)}) {
                    forest.values[x] = string(1, 'a' + rng() % 26);
                    lct.set(x, forest.values[x]);
                }
            } else if (op == 4) {
                auto path = forest.path(u, v);
                if (!path.empty()) {
                    forest.evert(u);
                    assert(lct.dist(u, v) == (int)path.size() - 1);
                }
            }
            auto path = forest.path(u, v);
            int length = (int)path.size();
            int k = step % 5 == 0 ? -1 : step % 5 == 1 ? 0 : step % 5 == 2 ? length - 1 : step % 5 == 3 ? length : rng() % (n + 1);
            if (k < 0) {
                auto before = lct.nodes;
                assert(lct.jump(u, v, k) == -1);
                for (int x = 0; x < n; ++x) {
                    auto a = before[x], b = lct.nodes[x];
                    assert(tie(a.l, a.r, a.p, a.sz, a.rev, a.val, a.sum, a.rsum) ==
                           tie(b.l, b.r, b.p, b.sz, b.rev, b.val, b.sum, b.rsum));
                }
            } else {
                forest.evert(u);
                int expected = k < length ? path[k] : -1;
                assert(lct.jump(u, v, k) == expected);
            }
            for (int x = 0; x < n; ++x) assert(lct.get_root(x) == forest.roots[x]);
            assert(lct.connected(u, v) == !path.empty());
            check_get(lct, forest);
            auto root_u = forest.path(forest.roots[u], u);
            assert(lct.parent(u) == (root_u.size() == 1 ? -1 : root_u[root_u.size() - 2]));
            int ancestor = -1;
            if (!path.empty()) {
                auto root_v = forest.path(forest.roots[v], v);
                for (int i = 0; i < (int)min(root_u.size(), root_v.size()) && root_u[i] == root_v[i]; ++i)
                    ancestor = root_u[i];
            }
            assert(lct.lca(u, v) == ancestor);
            if (!path.empty()) {
                string expected;
                for (int x : path) expected += forest.values[x];
                forest.evert(u);
                assert(lct.fold(u, v) == expected);
                reverse(expected.begin(), expected.end());
                forest.evert(v);
                assert(lct.fold(v, u) == expected);
            }
        }
    }
}

int main() {
    pending_reverse_check();
    self_check();
}
