#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <limits>
#include <queue>
#include <random>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../tree/centroid_decomposition_query_helper.cpp"

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 1; n <= 60; ++n) {
            for (int trial = 0; trial < 120; ++trial) {
                vector<vector<int>> g(n);
                CentroidDecompositionQueryHelper cd(n);
                for (int v = 1; v < n; ++v) {
                    int p = uniform_int_distribution<int>(0, v - 1)(rng);
                    g[v].push_back(p);
                    g[p].push_back(v);
                    cd.add_edge(v, p);
                }
                int root = cd.build();
                if (root < 0 || cd.parent[root] != -1) return 1;

                vector<vector<int>> all_dist(n, vector<int>(n, -1));
                for (int s = 0; s < n; ++s) {
                    queue<int> q;
                    q.push(s);
                    all_dist[s][s] = 0;
                    while (!q.empty()) {
                        int v = q.front();
                        q.pop();
                        for (auto &&u : g[v]) {
                            if (all_dist[s][u] != -1) continue;
                            all_dist[s][u] = all_dist[s][v] + 1;
                            q.push(u);
                        }
                    }
                }

                for (int c = 0; c < n; ++c) {
                    for (auto &&u : cd.tree[c]) {
                        if (cd.parent[u] != c) return 1;
                    }
                }
                for (int v = 0; v < n; ++v) {
                    if (cd.path[v].empty() || cd.path[v].size() != cd.dist[v].size()) return 1;
                    if (cd.path[v].back() != root) return 1;
                    for (int i = 0; i < (int)cd.path[v].size(); ++i) {
                        if (all_dist[v][cd.path[v][i]] != cd.dist[v][i]) return 1;
                        if (i + 1 < (int)cd.path[v].size()) {
                            if (cd.parent[cd.path[v][i]] != cd.path[v][i + 1]) return 1;
                            if (cd.depth[cd.path[v][i]] <= cd.depth[cd.path[v][i + 1]]) return 1;
                        }
                    }
                }

                vector<int> best(n, INF<int>);
                vector<char> active(n, 0);
                for (int iter = 0; iter < 200; ++iter) {
                    int type = uniform_int_distribution<int>(0, 1)(rng);
                    int v = uniform_int_distribution<int>(0, n - 1)(rng);
                    if (type == 0) {
                        active[v] = 1;
                        for (int i = 0; i < (int)cd.path[v].size(); ++i) {
                            best[cd.path[v][i]] = min(best[cd.path[v][i]], cd.dist[v][i]);
                        }
                    } else {
                        int got = INF<int>;
                        for (int i = 0; i < (int)cd.path[v].size(); ++i) {
                            got = min(got, best[cd.path[v][i]] + cd.dist[v][i]);
                        }
                        int expect = INF<int>;
                        for (int u = 0; u < n; ++u) {
                            if (active[u]) expect = min(expect, all_dist[v][u]);
                        }
                        if (got != expect) return 1;
                    }
                }
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
