#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0439"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../tree/virtual_tree_helper.cpp"

template <typename T>
using GPQ = priority_queue<T, vector<T>, greater<T>>;

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    vector<vector<int>> color(n);
    VirtualTreeHelper vt(n);
    for (int i = 0; i < n; ++i) {
        int x;
        sc.read(x);
        color[x - 1].emplace_back(i);
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        sc.read(u, v);
        --u;
        --v;
        vt.add_edge(u, v);
    }
    vt.build();

    vector<int> ans(n, INF<int>);
    vector<int> cmp(n), dist(n);
    vector<vector<int>> g(n);
    vector<int> is_target(n, 0);
    for (auto &&vs : color) {
        if (vs.empty()) continue;
        for (int v : vs) is_target[v] = 1;
        auto tree = vt.make(vs);
        for (int v : tree.vertices) g[v].clear();
        for (int i = 1; i < (int)tree.vertices.size(); ++i) {
            int v = tree.vertices[i];
            int p = tree.parent[i];
            g[v].emplace_back(p);
            g[p].emplace_back(v);
        }

        GPQ<pair<int, int>> q;
        for (int i = 0; i < (int)tree.vertices.size(); ++i) {
            int v = tree.vertices[i];
            if (is_target[v]) {
                dist[v] = 0;
                cmp[v] = v;
                q.emplace(0, v);
            } else {
                dist[v] = INF<int>;
            }
        }
        while (!q.empty()) {
            auto [d, v] = q.top();
            q.pop();
            if (d != dist[v]) continue;
            for (auto &&u : g[v]) {
                if (dist[u] > dist[v] + vt.distance(v, u)) {
                    dist[u] = dist[v] + vt.distance(v, u);
                    cmp[u] = cmp[v];
                    q.emplace(dist[u], u);
                }
            }
        }
        for (int v : tree.vertices) {
            for (auto &&u : g[v]) {
                int a = cmp[v], b = cmp[u];
                if (a != b) ans[a] = min(ans[a], vt.distance(a, b));
            }
        }
        for (int v : vs) is_target[v] = 0;
    }

    for (auto &&x : ans) pr.writeln(x);
    return 0;
}
