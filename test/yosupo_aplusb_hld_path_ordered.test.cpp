#define STANDALONE

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

void check_tree(const vector<vector<int>> &g, vector<int> roots) {
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
            auto check_jump = [&](int k, int expected) {
                assert(ordered.jump(u, v, k) == expected);
                assert(ordered_edges.jump(u, v, k) == expected);
            };
            check_jump(INT_MIN, -1);
            check_jump(-1, -1);
            check_jump(INT_MAX, -1);
            if (p[v] == -1) {
                check_jump(0, -1);
                continue;
            }
            vector<int> path{v};
            while (path.back() != u) path.push_back(p[path.back()]);
            reverse(path.begin(), path.end());
            int length = (int)path.size() - 1;
            for (int k = 0; k <= length; ++k) check_jump(k, path[k]);
            check_jump(length + 1, -1);
            int up = 0;
            while (up < length && parent[path[up]] == path[up + 1]) ++up;
            assert(ordered_edges.lca(u, v) == path[up]);
            assert(ordered_edges.ancestor(u, up) == path[up]);
            assert(ordered_edges.distance(u, v) == length);
            auto check_length = [&](const auto &index, int expected) {
                int size = 0;
                index.path(u, v, [&](int l, int r) { size += r - l; });
                assert(size == expected);
                auto count = [](int l, int r) { return r - l; };
                assert(index.path_query(u, v, 0, count, plus<int>()) == expected);
            };
            check_length(ordered, length + 1);
            check_length(ordered_edges, length);
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
                assert(ordered.path_query_ordered(u, v, string(), ql, qr,
                    [](const string &a, const string &b) { return a + b; }, edge) == text);
                if (edge) {
                    assert(ordered_edges.path_query_ordered(u, v, string(), ql, qr, plus<string>()) == text);
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
}
