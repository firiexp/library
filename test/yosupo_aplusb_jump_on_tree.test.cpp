#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/jump_on_tree.cpp"

void check(JumpOnTree &jt, int root) {
    jt.build(root);
    int n = jt.n;
    vector<int> parent(n, -1), depth(n), order{root};
    for (int i = 0; i < n; ++i) {
        int v = order[i];
        for (int u : jt.G[v]) {
            if (u == parent[v]) continue;
            parent[u] = v;
            depth[u] = depth[v] + 1;
            order.push_back(u);
        }
    }
    assert(jt.depth == depth);
    for (int v = 0; v < n; ++v) {
        int u = v;
        for (int k = 0; k <= depth[v]; ++k) {
            assert(jt.ancestor(v, k) == u);
            u = parent[u];
        }
        assert(jt.ancestor(v, depth[v] + 1) == -1);
        assert(jt.ancestor(v, INT_MAX) == -1);
    }
    for (int s = 0; s < n; ++s) {
        for (int t = 0; t < n; ++t) {
            int u = s, v = t;
            vector<int> left, right;
            while (u != v) {
                if (depth[u] >= depth[v]) {
                    left.push_back(u);
                    u = parent[u];
                } else {
                    right.push_back(v);
                    v = parent[v];
                }
            }
            assert(jt.lca(s, t) == u);
            left.push_back(u);
            left.insert(left.end(), right.rbegin(), right.rend());
            assert(jt.dist(s, t) == int(left.size()) - 1);
            for (int k = 0; k < int(left.size()); ++k) assert(jt.jump(s, t, k) == left[k]);
            assert(jt.jump(s, t, left.size()) == -1);
            assert(jt.jump(s, t, INT_MAX) == -1);
        }
    }
}

void self_check() {
    for (int n : {1, 2, 3, 4, 7, 8, 9, 16, 17, 32, 33}) {
        for (int shape = 0; shape < 3; ++shape) {
            JumpOnTree jt(n);
            for (int v = 1; v < n; ++v) {
                int p = shape == 0 ? 0 : shape == 1 ? v - 1 : (v - 1) / 2;
                jt.add_edge(p, v);
            }
            for (int root : {0, n - 1, n / 2, 0}) check(jt, root);
        }
    }
    mt19937 rng(188);
    for (int tc = 0; tc < 200; ++tc) {
        int n = 1 + rng() % 25;
        JumpOnTree jt(n);
        for (int v = 1; v < n; ++v) jt.add_edge(rng() % v, v);
        check(jt, rng() % n);
        check(jt, rng() % n);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
