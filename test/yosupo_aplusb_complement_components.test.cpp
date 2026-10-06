#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../graph/complement_components.cpp"

void check(const vector<vector<int>> &g) {
    int n = g.size();
    auto before = g;
    auto components = complement_components(g);
    assert(g == before);
    vector<vector<bool>> adjacent(n, vector<bool>(n));
    for (int v = 0; v < n; ++v) for (int u : g[v]) adjacent[v][u] = true;
    vector<int> expected(n, -1), actual(n, -1);
    int count = 0;
    for (int start = 0; start < n; ++start) if (expected[start] < 0) {
        queue<int> q;
        q.push(start);
        expected[start] = count++;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u = 0; u < n; ++u) {
                if (u == v || adjacent[v][u] || expected[u] >= 0) continue;
                expected[u] = expected[v];
                q.push(u);
            }
        }
    }
    assert(int(components.size()) == count);
    for (int i = 0; i < int(components.size()); ++i) {
        assert(!components[i].empty());
        for (int v : components[i]) {
            assert(0 <= v && v < n);
            assert(actual[v] == -1);
            actual[v] = i;
        }
    }
    for (int v = 0; v < n; ++v) {
        assert(actual[v] >= 0);
        for (int u = 0; u < n; ++u)
            assert((actual[v] == actual[u]) == (expected[v] == expected[u]));
    }
}

int main() {
    for (int n = 0; n <= 6; ++n) {
        int m = n * (n - 1) / 2;
        for (int mask = 0; mask < (1 << m); ++mask) {
            vector<vector<int>> g(n);
            int bit = 0;
            for (int v = 0; v < n; ++v) for (int u = 0; u < v; ++u, ++bit) {
                if (!(mask >> bit & 1)) continue;
                g[v].push_back(u);
                g[u].push_back(v);
            }
            check(g);
        }
    }
    mt19937 rng(41);
    for (int tc = 0; tc < 500; ++tc) {
        int n = rng() % 101, density = rng() % 101;
        vector<vector<int>> g(n);
        for (int v = 0; v < n; ++v) for (int u = 0; u < v; ++u) {
            if (int(rng() % 100) >= density) continue;
            g[v].push_back(u);
            g[u].push_back(v);
        }
        for (auto &adj : g) shuffle(adj.begin(), adj.end(), rng);
        check(g);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
