#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/hld_edge.cpp"

vector<int> parents(const vector<vector<int>> &g, int root) {
    vector<int> p(g.size(), -1), q{root};
    p[root] = root;
    for (int i = 0; i < (int)q.size(); ++i) {
        for (int to : g[q[i]]) if (p[to] == -1) {
            p[to] = q[i];
            q.push_back(to);
        }
    }
    return p;
}

void check_tree(vector<vector<int>> g, vector<int> roots) {
    int n = g.size();
    HeavyLightDecomposition hld(g);
    HeavyLightDecompositionEdge edges(g);
    hld.build(roots);
    edges.build(roots);
    const auto &ordered = hld;
    const auto &ordered_edges = edges;
    vector<int> parent(n);
    for (int root : roots) {
        auto p = parents(g, root);
        for (int i = 0; i < n; ++i) if (p[i] != -1) parent[i] = p[i];
    }
    vector<long long> values[2] = {vector<long long>(n), vector<long long>(n)};
    vector<long long> expected_values[2] = {vector<long long>(n), vector<long long>(n)};
    for (int u = 0; u < n; ++u) {
        auto p = parents(g, u);
        for (int v = 0; v < n; ++v) {
            if (p[v] == -1) continue;
            vector<int> path{v};
            while (path.back() != u) path.push_back(p[path.back()]);
            reverse(path.begin(), path.end());
            for (bool edge : {false, true}) {
                vector<int> expected;
                if (!edge) expected = path;
                else for (int i = 1; i < (int)path.size(); ++i) {
                    int a = path[i - 1], b = path[i];
                    expected.push_back(parent[a] == b ? a : b);
                }
                vector<int> actual;
                string text, expected_text;
                int offset = 0;
                long long first = u - v, step = v % 5 - 2;
                ordered.path_ordered(u, v, [&](int l, int r, bool reversed) {
                    assert(0 <= l && l < r && r <= n);
                    for (int i = 0; i < r - l; ++i) {
                        int vertex = hld.id_inv[reversed ? r - 1 - i : l + i];
                        actual.push_back(vertex);
                        text += to_string(vertex) + ",";
                    }
                    for (int i = l; i < r; ++i) {
                        int k = offset + (reversed ? r - 1 - i : i - l);
                        values[edge][i] += first + step * k;
                    }
                    offset += r - l;
                }, edge);
                for (int i = 0; i < (int)expected.size(); ++i) {
                    expected_text += to_string(expected[i]) + ",";
                    expected_values[edge][hld.id[expected[i]]] += first + step * i;
                }
                assert(actual == expected && text == expected_text);
                assert(offset == (int)expected.size());
                assert(values[edge] == expected_values[edge]);
                auto ql = [&](int l, int r) {
                    string result;
                    for (int i = l; i < r; ++i) result += to_string(hld.id_inv[i]) + ",";
                    return result;
                };
                auto qr = [&](int l, int r) {
                    string result;
                    for (int i = r; i-- > l;) result += to_string(hld.id_inv[i]) + ",";
                    return result;
                };
                assert(hld.path_query_ordered(u, v, string(), ql, qr,
                    [](const string &a, const string &b) { return a + b; }, edge) == text);
                if (edge) {
                    vector<int> wrapped;
                    ordered_edges.path_ordered(u, v, [&](int l, int r, bool reversed) {
                        for (int i = 0; i < r - l; ++i) {
                            wrapped.push_back(edges.hld.id_inv[reversed ? r - 1 - i : l + i]);
                        }
                    });
                    assert(wrapped == expected);
                }
            }
        }
    }
}

void self_check() {
    check_tree({{}}, {0});
    check_tree({{1}, {0}, {3, 4}, {2}, {2}, {}}, {1, 3, 5});
    mt19937 random(194);
    for (int tc = 0; tc < 60; ++tc) {
        int n = 2 + random() % 25;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int p = tc % 4 == 0 ? i - 1 : tc % 4 == 1 ? 0 : tc % 4 == 2 ? (i - 1) / 2 : random() % i;
            g[p].push_back(i);
            g[i].push_back(p);
        }
        for (auto &adj : g) shuffle(adj.begin(), adj.end(), random);
        check_tree(g, {0});
        check_tree(g, {int(random() % n)});
    }
    int n = 200000;
    HeavyLightDecomposition path(n);
    for (int i = 1; i < n; ++i) path.add_edge(i - 1, i);
    path.build();
    int size = 0;
    path.path_ordered(n - 1, 0, [&](int l, int r, bool reversed) {
        assert(reversed && l == 0 && r == n);
        size += r - l;
    });
    assert(size == n);
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
