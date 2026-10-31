#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/connectivity/offlinedynamicconnectivity.cpp"

void check(int n, const vector<vector<int>> &count, UndoableUnionFind &uf) {
    vector<int> component(n, -1);
    for (int s = 0; s < n; ++s) {
        if (component[s] != -1) continue;
        vector<int> queue{s};
        component[s] = s;
        for (size_t i = 0; i < queue.size(); ++i) {
            int v = queue[i];
            for (int u = 0; u < n; ++u) {
                if (!(count[u][v] || count[v][u]) || component[u] != -1) continue;
                component[u] = s;
                queue.push_back(u);
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) assert(uf.same(u, v) == (component[u] == component[v]));
    }
}

int main() {
    mt19937 rng(192);
    for (int trial = 0; trial < 400; ++trial) {
        int n = 2 + rng() % 12, q = trial < 10 ? trial : rng() % 150;
        OfflineDynamicConnectivity dc(n, q);
        vector<vector<int>> count(n, vector<int>(n));
        vector<vector<vector<int>>> states;
        for (int t = 0; t < q; ++t) {
            for (int i = rng() % 5; i > 0; --i) {
                int u = rng() % n, v = rng() % n;
                if (u > v) swap(u, v);
                if (count[u][v] && rng() % 2) {
                    dc.erase(t, v, u);
                    --count[u][v];
                } else {
                    dc.insert(t, u, v);
                    ++count[u][v];
                }
            }
            states.push_back(count);
        }
        vector<vector<pair<int, int>>> expected(2 * dc.sz);
        auto add = [&](int l, int r, pair<int, int> e) {
            for (l += dc.sz, r += dc.sz; l < r; l >>= 1, r >>= 1) {
                if (l & 1) expected[l++].push_back(e);
                if (r & 1) expected[--r].push_back(e);
            }
        };
        for (auto [range, e] : dc.pend) add(range.first, range.second, e);
        for (auto [e, t] : dc.appear) add(t, q, e);
        for (int repeat = 0; repeat < 2; ++repeat) {
            dc.build();
            int time = 0;
            vector<int> stack;
            dc.dfs([&](int k, const auto &edges) {
                assert(edges.size() == expected[k].size());
                assert((vector<pair<int, int>>(edges.begin(), edges.end()) == expected[k]));
                stack.push_back(k);
            }, [&](int k, const auto &edges) {
                assert(stack.back() == k);
                stack.pop_back();
                assert((vector<pair<int, int>>(edges.begin(), edges.end()) == expected[k]));
            }, [&](int t) { assert(t == time++); });
            assert(stack.empty() && time == q);
            dc.uf.unite(0, n - 1);
            auto before = dc.uf.uni;
            int state = dc.uf.get_state();
            time = 0;
            dc.run([&](int t, UndoableUnionFind &uf) {
                assert(t == time++);
                auto active = states[t];
                ++active[0][n - 1];
                check(n, active, uf);
            });
            assert(time == q && dc.uf.uni == before && dc.uf.get_state() == state);
            dc.uf.undo();
            time = 0;
            dc.run([&](int t) {
                assert(t == time++);
                check(n, states[t], dc.uf);
            });
            assert(time == q && dc.uf.get_state() == 0);
        }
    }
}
