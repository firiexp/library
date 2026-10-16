#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../graph/minimum_steiner_tree.cpp"

struct InputEdge { int u, v; ll cost; };

void check(int n, const vector<InputEdge> &edges, const vector<vector<int>> &sets) {
    MinimumSteinerTree<ll> st(n);
    for (int i = 0; i < (int)edges.size(); ++i) {
        auto e = edges[i];
        assert(st.add_edge(e.u, e.v, e.cost) == i);
    }
    for (const auto &terminals : sets) {
        vector<ll> expected(n, INF<ll>);
        for (int mask = 0; mask < (1 << edges.size()); ++mask) {
            vector<int> component(n);
            iota(component.begin(), component.end(), 0);
            __int128 sum = 0;
            for (int i = 0; i < (int)edges.size(); ++i) {
                if (!((mask >> i) & 1)) continue;
                auto e = edges[i];
                sum += e.cost;
                int from = component[e.u], to = component[e.v];
                for (int &c : component) if (c == from) c = to;
            }
            bool connected = true;
            for (int t : terminals) connected &= component[t] == component[terminals[0]];
            if (!connected || sum >= INF<ll>) continue;
            for (int v = 0; v < n; ++v) {
                if (component[v] == component[terminals[0]]) expected[v] = min(expected[v], (ll)sum);
            }
        }
        auto input = terminals;
        st.build(input);
        assert(input == terminals);
        const auto &built = st;
        for (int v = 0; v < n; ++v) {
            assert(built.cost(v) == expected[v]);
            auto ids = built.restore(v);
            assert(built.restore(v) == ids);
            if (expected[v] == INF<ll>) {
                assert(ids.empty());
                continue;
            }
            vector<int> component(n);
            vector<char> used(edges.size());
            iota(component.begin(), component.end(), 0);
            __int128 sum = 0;
            for (int id : ids) {
                assert(0 <= id && id < (int)edges.size() && !used[id]);
                used[id] = true;
                auto e = edges[id];
                int from = component[e.u], to = component[e.v];
                assert(from != to);
                for (int &c : component) if (c == from) c = to;
                sum += e.cost;
            }
            assert(sum == expected[v]);
            for (int t : terminals) assert(component[t] == component[v]);
            for (int id : ids) assert(component[edges[id].u] == component[v]);
        }
    }
}

void self_check() {
    check(1, {}, {{0}, {0}});
    check(4, {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}}, {{1, 2, 3}, {0}, {3, 1}});
    check(4, {{0, 1, 0}, {1, 2, 0}, {2, 0, 0}, {1, 1, 0}, {0, 1, 0}},
          {{0, 1, 2}, {0, 3}, {3}, {1}});
    check(4, {}, {{0}, {1, 3}});
    check(4, {{0, 1, 3000000000LL}, {1, 2, 4000000000LL}, {2, 3, 5000000000LL}},
          {{0, 2, 3}, {3}});
    check(3, {{0, 1, INF<ll> - 10}, {1, 2, 3}, {0, 2, LLONG_MAX}, {1, 1, LLONG_MAX}},
          {{0, 1, 2}, {0}, {2}});
    mt19937 rng(83);
    for (int tc = 0; tc < 2000; ++tc) {
        int n = 1 + rng() % 7, m = rng() % 11;
        vector<InputEdge> edges;
        for (int i = 0; i < m; ++i) edges.push_back({int(rng() % n), int(rng() % n), ll(rng() % 8)});
        vector<int> terminals(n);
        iota(terminals.begin(), terminals.end(), 0);
        shuffle(terminals.begin(), terminals.end(), rng);
        terminals.resize(1 + rng() % min(n, 4));
        check(n, edges, {terminals, {int(rng() % n)}});
    }
    MinimumSteinerTree<int> path(20000);
    for (int i = 1; i < 20000; ++i) path.add_edge(i - 1, i, i & 1);
    path.build({0});
    assert(path.cost(19999) == 10000);
    assert(path.restore(19999).size() == 19999);
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
