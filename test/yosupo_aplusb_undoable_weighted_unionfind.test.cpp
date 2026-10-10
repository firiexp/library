#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/undoable_weighted_unionfind.cpp"

struct AddGroup {
    using T = long long;
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T e() { return 0; }
    static T random(mt19937 &rng) { return int(rng() % 21) - 10; }
};

struct XorGroup {
    using T = int;
    static T op(T a, T b) { return a ^ b; }
    static T inv(T a) { return a; }
    static T e() { return 0; }
    static T random(mt19937 &rng) { return rng() & 1; }
};

struct PermutationGroup {
    using T = array<int, 3>;
    static T op(const T &a, const T &b) { return {a[b[0]], a[b[1]], a[b[2]]}; }
    static T inv(const T &a) {
        T result;
        for (int i = 0; i < 3; ++i) result[a[i]] = i;
        return result;
    }
    static T e() { return {0, 1, 2}; }
    static T random(mt19937 &rng) {
        T value = e();
        shuffle(value.begin(), value.end(), rng);
        return value;
    }
};

template<class G>
struct Constraint {
    int a, b;
    typename G::T w;
};

template<class G>
void check(const UndoableWeightedUnionFind<G> &uf, int n, const vector<Constraint<G>> &edges) {
    using T = typename G::T;
    vector<vector<pair<int, T>>> graph(n);
    for (const auto &edge : edges) {
        graph[edge.a].emplace_back(edge.b, edge.w);
        graph[edge.b].emplace_back(edge.a, G::inv(edge.w));
    }
    vector<int> component(n, -1), sizes(n);
    vector<T> potential(n, G::e());
    vector<bool> valid(n, true);
    for (int start = 0; start < n; ++start) {
        if (component[start] != -1) continue;
        vector<int> queue{start};
        component[start] = start;
        for (int i = 0; i < (int)queue.size(); ++i) {
            int v = queue[i];
            for (auto [u, w] : graph[v]) {
                auto expected = G::op(potential[v], w);
                if (component[u] == -1) {
                    component[u] = start;
                    potential[u] = expected;
                    queue.push_back(u);
                } else if (!(potential[u] == expected)) valid[start] = false;
            }
        }
        sizes[start] = (int)queue.size();
    }
    bool consistent = true;
    for (int v = 0; v < n; ++v) {
        consistent &= valid[component[v]];
        assert(uf.consistent(v) == valid[component[v]]);
        assert(uf.size(v) == sizes[component[v]]);
        for (int u = 0; u < n; ++u) {
            bool same = component[v] == component[u];
            assert(uf.same(v, u) == same);
            auto delta = uf.diff(v, u);
            assert(delta.has_value() == (same && valid[component[v]]));
            if (delta) assert(*delta == G::op(G::inv(potential[v]), potential[u]));
        }
    }
    assert(uf.consistent() == consistent);
}

template<class G>
void check_group(typename G::T x, typename G::T y) {
    UndoableWeightedUnionFind<G> uf(8), empty(0);
    check(empty, 0, vector<Constraint<G>>{});
    vector<Constraint<G>> edges;
    auto add = [&](int a, int b, typename G::T w) {
        bool merged = !uf.same(a, b);
        assert(uf.unite(a, b, w) == merged);
        edges.push_back({a, b, w});
        assert(uf.get_state() == (int)edges.size());
        check(uf, 8, edges);
    };
    add(0, 1, x);
    add(0, 1, x);
    add(0, 0, x);
    add(2, 3, y);
    add(2, 2, x);
    assert(!uf.diff(0, 0) && uf.diff(4, 4) == G::e());
    add(4, 5, y);
    add(6, 0, y);
    add(0, 2, x);
    add(0, 4, y);
    while (!edges.empty()) {
        uf.undo();
        edges.pop_back();
        check(uf, 8, edges);
    }
    mt19937 rng(138);
    for (int i = 0; i < 10000; ++i) {
        if (edges.empty() || rng() % 4) {
            add(rng() % 8, rng() % 8, G::random(rng));
        } else if (rng() & 1) {
            uf.undo();
            edges.pop_back();
            check(uf, 8, edges);
        } else {
            int state = rng() % (edges.size() + 1);
            uf.rollback(state);
            edges.resize(state);
            assert(uf.get_state() == state);
            check(uf, 8, edges);
        }
    }
    uf.rollback(0);
    check(uf, 8, vector<Constraint<G>>{});
}

template<class G>
void check_intervals() {
    mt19937 rng(138);
    const int q = 37, base = 64;
    for (int trial = 0; trial < 50; ++trial) {
        vector<Constraint<G>> edges;
        vector<pair<int, int>> intervals;
        vector<vector<int>> tree(2 * base);
        for (int i = 0; i < 30; ++i) {
            int l = rng() % q, r = l + 1 + rng() % (q - l);
            intervals.emplace_back(l, r);
            edges.push_back({int(rng() % 8), int(rng() % 8), G::random(rng)});
            for (l += base, r += base; l < r; l >>= 1, r >>= 1) {
                if (l & 1) tree[l++].push_back(i);
                if (r & 1) tree[--r].push_back(i);
            }
        }
        UndoableWeightedUnionFind<G> uf(8);
        auto dfs = [&](auto &&self, int node) -> void {
            int state = uf.get_state();
            for (int i : tree[node]) uf.unite(edges[i].a, edges[i].b, edges[i].w);
            if (node < base) {
                self(self, node * 2);
                self(self, node * 2 + 1);
            } else if (node - base < q) {
                int time = node - base;
                vector<Constraint<G>> active;
                for (int i = 0; i < (int)edges.size(); ++i)
                    if (intervals[i].first <= time && time < intervals[i].second) active.push_back(edges[i]);
                check(uf, 8, active);
            }
            uf.rollback(state);
        };
        dfs(dfs, 1);
        assert(uf.get_state() == 0 && uf.consistent());
    }
}

int main() {
    check_group<AddGroup>(3, -2);
    check_group<XorGroup>(1, 1);
    check_group<PermutationGroup>({1, 0, 2}, {0, 2, 1});
    check_intervals<AddGroup>();
    check_intervals<XorGroup>();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
