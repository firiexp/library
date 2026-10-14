#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/mo.cpp"
#include "../tree/tree_mo.cpp"

int main() {
    tree_mo_solve({}, {}, [](int) { assert(false); }, [](int) { assert(false); },
                  [](int) { assert(false); });
    mt19937 rng(153);
    for (int tc = 0; tc < 2000; ++tc) {
        int n = 1 + rng() % 35, q = rng() % 61;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            int u = rng() % v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<pair<int, int>> paths(q);
        vector<vector<char>> expected(q, vector<char>(n));
        vector<int> colors(n), distinct(q);
        for (int &c : colors) c = rng() % 8;
        for (int id = 0; id < q; ++id) {
            auto &[s, t] = paths[id];
            s = rng() % n; t = rng() % n;
            vector<int> parent(n, -1), queue{s};
            parent[s] = s;
            for (int i = 0; i < (int)queue.size(); ++i) {
                int v = queue[i];
                for (int u : g[v]) {
                    if (parent[u] == -1) parent[u] = v, queue.push_back(u);
                }
            }
            set<int> used;
            for (int v = t;; v = parent[v]) {
                expected[id][v] = 1;
                used.insert(colors[v]);
                if (v == s) break;
            }
            distinct[id] = (int)used.size();
        }
        auto original_g = g;
        auto original_paths = paths;
        for (int run = 0; run < 2; ++run) {
            vector<char> active(n);
            vector<int> seen(q), frequency(8);
            int current = 0;
            tree_mo_solve(g, paths,
                [&](int v) {
                    assert(!active[v]);
                    active[v] = 1;
                    if (frequency[colors[v]]++ == 0) ++current;
                },
                [&](int v) {
                    assert(active[v]);
                    active[v] = 0;
                    if (--frequency[colors[v]] == 0) --current;
                },
                [&](int id) {
                    assert(0 <= id && id < q);
                    assert(active == expected[id] && current == distinct[id]);
                    ++seen[id];
                }, rng() % n);
            assert(current == 0 && count(active.begin(), active.end(), 0) == n);
            assert(count(seen.begin(), seen.end(), 1) == q);
            assert(g == original_g && paths == original_paths);
        }
    }
    for (bool star : {false, true}) {
        int n = 200000, q = 100000;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            int u = star ? 0 : v - 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<pair<int, int>> paths(q);
        for (auto &[u, v] : paths) u = rng() % n, v = rng() % n;
        vector<char> active(n);
        long long sum = 0;
        int count = 0, answers = 0;
        tree_mo_solve(g, paths,
            [&](int v) { assert(!active[v]); active[v] = 1; sum += v; ++count; },
            [&](int v) { assert(active[v]); active[v] = 0; sum -= v; --count; },
            [&](int id) {
                ++answers;
                auto [u, v] = paths[id];
                if (u > v) swap(u, v);
                if (star) {
                    assert(sum == (u == v ? u : u + v));
                    assert(count == (u == v ? 1 : u == 0 ? 2 : 3));
                } else {
                    assert(sum == (long long)(u + v) * (v - u + 1) / 2);
                    assert(count == v - u + 1);
                }
            }, n - 1);
        assert(sum == 0 && count == 0 && answers == q);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
