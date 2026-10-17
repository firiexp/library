#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../tree/virtual_tree_helper.cpp"

void self_check() {
    VirtualTreeHelper fixed(7);
    for (int v = 1; v < 7; ++v) fixed.add_edge((v - 1) / 2, v);
    fixed.build();
    auto check_fixed = [&](const vector<int> &input, int root, const vector<int> &vertices, const vector<int> &parent) {
        auto tr = fixed.make(input);
        assert(tr.root == root && tr.vertices == vertices && tr.parent == parent);
    };
    for (int repeat = 0; repeat < 3; ++repeat) {
        check_fixed({6, 3, 5, 4, 3}, 0, {0, 2, 6, 5, 1, 4, 3}, {-1, 0, 2, 2, 0, 1, 1});
        check_fixed({}, -1, {}, {});
        check_fixed(vector<int>(10000, 4), 4, {4}, {-1});
        check_fixed({4, 3}, 1, {1, 4, 3}, {-1, 1, 1});
        check_fixed({0, 4, 6}, 0, {0, 6, 4}, {-1, 0, 0});
    }
    mt19937 rng(5);
    for (int tc = 0; tc < 200; ++tc) {
        int n = 1 + rng() % 30, root = rng() % n;
        VirtualTreeHelper vt(n);
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            int p = tc % 3 == 0 ? 0 : tc % 3 == 1 ? v - 1 : rng() % v;
            vt.add_edge(p, v);
            g[p].push_back(v);
            g[v].push_back(p);
        }
        vt.build(root);
        vector<int> parent(n, -1), depth(n), order{root};
        for (int i = 0; i < n; ++i) for (int u : g[order[i]]) if (u != parent[order[i]]) {
            parent[u] = order[i];
            depth[u] = depth[order[i]] + 1;
            order.push_back(u);
        }
        auto lca = [&](int u, int v) {
            while (u != v) {
                if (depth[u] < depth[v]) swap(u, v);
                u = parent[u];
            }
            return u;
        };
        for (int query = 0; query < 30; ++query) {
            vector<int> input(query % 10);
            for (int &v : input) v = rng() % n;
            if (query % 3 == 0) fill(input.begin(), input.end(), root);
            set<int> expected(input.begin(), input.end());
            for (int u : input) for (int v : input) expected.insert(lca(u, v));
            auto tr = vt.make(input);
            assert(tr.vertices.size() == expected.size());
            assert(tr.parent.size() == expected.size());
            assert(set<int>(tr.vertices.begin(), tr.vertices.end()) == expected);
            if (expected.empty()) {
                assert(tr.root == -1);
                continue;
            }
            assert(tr.root == tr.vertices.front());
            set<int> visited;
            for (int i = 0; i < (int)tr.vertices.size(); ++i) {
                int v = tr.vertices[i], p = parent[v];
                while (p != -1 && !expected.count(p)) p = parent[p];
                assert(tr.parent[i] == p);
                assert(p == -1 ? v == tr.root : visited.count(p));
                visited.insert(v);
            }
            auto repeated = vt.make(input);
            assert(tr.root == repeated.root && tr.vertices == repeated.vertices && tr.parent == repeated.parent);
        }
    }
    AuxTree aux(1);
    aux.buildLCA();
    vector<int> empty;
    aux.make(empty);
    aux.clear(empty);
    assert(empty.empty() && aux.out[0].empty());
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
