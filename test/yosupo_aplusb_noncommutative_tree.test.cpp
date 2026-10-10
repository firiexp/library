#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/weightedunionfind.cpp"
#include "../tree/rerooting.cpp"

struct Permutations {
    using T = array<int, 4>;
    static T e() { return {0, 1, 2, 3}; }
    static T op(T a, T b) {
        T c;
        for (int i = 0; i < 4; ++i) c[i] = a[b[i]];
        return c;
    }
    static T inv(T a) {
        T b;
        for (int i = 0; i < 4; ++i) b[a[i]] = i;
        return b;
    }
};

void unionfind_check() {
    using G = Permutations;
    WeightedUnionFind<G> minimal(4);
    G::T b{1, 0, 2, 3}, c{0, 2, 1, 3};
    minimal.unite(0, 1, G::e());
    minimal.unite(2, 3, b);
    minimal.unite(0, 2, c);
    assert(minimal.diff(0, 3) == G::op(c, b));
    assert(minimal.diff(2, 3) == b);
    mt19937 rng(28);
    for (int n = 1; n <= 40; ++n) {
        vector<G::T> potential(n, G::e());
        for (auto &p : potential) shuffle(p.begin(), p.end(), rng);
        vector<int> component(n);
        iota(component.begin(), component.end(), 0);
        WeightedUnionFind<G> uf(n);
        auto difference = [&](int u, int v) {
            return G::op(G::inv(potential[u]), potential[v]);
        };
        for (int step = 0; step < 100; ++step) {
            // Force the single-vertex component to join a larger one.
            int u = rng() % n, v = rng() % n;
            if (n >= 3 && step == 0) u = 1, v = 2;
            if (n >= 3 && step == 1) u = 0, v = 1;
            bool distinct = component[u] != component[v];
            assert(uf.unite(u, v, difference(u, v)) == distinct);
            int from = component[v], to = component[u];
            for (int &id : component) if (id == from) id = to;
            for (int a = 0; a < n; ++a) {
                assert(uf.size(a) == count(component.begin(), component.end(), component[a]));
                uf.root(a);
                uf.root(a);
                for (int b = 0; b < n; ++b) {
                    assert(uf.same(a, b) == (component[a] == component[b]));
                    if (uf.same(a, b)) assert(uf.diff(a, b) == difference(a, b));
                }
            }
        }
    }
}

struct OrderedTree {
    using T = string;
    using U = string;
    static T e() { return ""; }
    static T f(const T &a, const T &b) { return a + b; }
    static T g(const T &a, const U &edge) { return edge + "(" + a + ")"; }
};

void rerooting_check() {
    ReRooting<OrderedTree> star(4);
    star.add_edge(0, 1, "a");
    star.add_edge(0, 2, "b");
    star.add_edge(0, 3, "c");
    assert(star.solve()[0] == "a()b()c()");
    assert(star.solve()[2] == "b(a()c())");
    mt19937 rng(44);
    for (int n = 0; n < 40; ++n) {
        for (int tc = 0; tc < 100; ++tc) {
            vector<pair<int, int>> edges;
            for (int v = 1; v < n; ++v) edges.emplace_back(rng() % v, v);
            shuffle(edges.begin(), edges.end(), rng);
            ReRooting<OrderedTree> tree(n);
            vector<vector<pair<int, string>>> adj(n);
            for (auto [u, v] : edges) {
                string x = to_string(u) + ":" + to_string(v);
                string y = to_string(v) + ":" + to_string(u);
                tree.add_edge(u, v, x, y);
                adj[u].emplace_back(v, x);
                adj[v].emplace_back(u, y);
            }
            auto dfs = [&](auto &&self, int v, int parent) -> string {
                string result;
                for (auto [to, label] : adj[v])
                    if (to != parent) result += label + "(" + self(self, to, v) + ")";
                return result;
            };
            vector<string> expected;
            for (int root = 0; root < n; ++root) expected.push_back(dfs(dfs, root, -1));
            assert(tree.solve() == expected);
            assert(tree.solve() == expected);
        }
    }
}

int main() {
    unionfind_check();
    rerooting_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
