#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/tree_center.cpp"
#include "../tree/tree_isomorphism.cpp"

using Graph = vector<vector<int>>;

void validate(const Graph &g, const Graph &h, const TreeIsomorphismResult &result,
        int root_g = -1, int root_h = -1) {
    if (!result.exists) {
        assert(result.mapping.empty());
        return;
    }
    int n = g.size();
    assert(h.size() == g.size() && result.mapping.size() == g.size());
    auto permutation = result.mapping;
    sort(permutation.begin(), permutation.end());
    for (int v = 0; v < n; ++v) assert(permutation[v] == v);
    if (root_g != -1 && n) assert(result.mapping[root_g] == root_h);
    vector<pair<int, int>> mapped, target;
    for (int u = 0; u < n; ++u) {
        for (int v : g[u]) mapped.emplace_back(result.mapping[u], result.mapping[v]);
        for (int v : h[u]) target.emplace_back(u, v);
    }
    sort(mapped.begin(), mapped.end());
    sort(target.begin(), target.end());
    assert(mapped == target);
}

void check_small(const Graph &g, const Graph &h) {
    int n = g.size();
    bool exists = false;
    vector<vector<bool>> rooted(n, vector<bool>(n));
    if (g.size() == h.size()) {
        vector<vector<bool>> adjacent(n, vector<bool>(n));
        for (int u = 0; u < n; ++u) for (int v : h[u]) adjacent[u][v] = true;
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        do {
            bool valid = true;
            for (int u = 0; u < n && valid; ++u) {
                if (g[u].size() != h[permutation[u]].size()) valid = false;
                for (int v : g[u]) if (!adjacent[permutation[u]][permutation[v]]) valid = false;
            }
            if (valid) {
                exists = true;
                for (int v = 0; v < n; ++v) rooted[v][permutation[v]] = true;
            }
        } while (next_permutation(permutation.begin(), permutation.end()));
    }
    auto saved_g = g, saved_h = h;
    auto result = tree_isomorphism(g, h);
    assert(result.exists == exists);
    validate(g, h, result);
    if (g.empty() || h.empty()) {
        result = rooted_tree_isomorphism(g, h, 0, 0);
        assert(result.exists == exists);
        validate(g, h, result);
    } else {
        for (int u = 0; u < n; ++u) for (int v = 0; v < (int)h.size(); ++v) {
            result = rooted_tree_isomorphism(g, h, u, v);
            assert(result.exists == (g.size() == h.size() && rooted[u][v]));
            validate(g, h, result, u, v);
        }
    }
    assert(g == saved_g && h == saved_h);
}

Graph make_tree(int n, int shape, mt19937 &random) {
    Graph g(n);
    for (int v = 1; v < n; ++v) {
        int parent = shape == 0 ? v - 1 : shape == 1 ? 0 : shape == 2 ? (v - 1) / 2 : random() % v;
        g[parent].push_back(v);
        g[v].push_back(parent);
    }
    return g;
}

Graph relabel(const Graph &g, const vector<int> &permutation, mt19937 &random) {
    Graph h(g.size());
    for (int u = 0; u < (int)g.size(); ++u) {
        for (int v : g[u]) h[permutation[u]].push_back(permutation[v]);
    }
    for (auto &adjacent : h) shuffle(adjacent.begin(), adjacent.end(), random);
    return h;
}

void self_check() {
    check_small({}, {});
    check_small({}, {{}});
    check_small({{}}, {});
    check_small({{}}, {{}});
    check_small({{1}, {0}}, {{1}, {0}});
    mt19937 random(196);
    check_small(make_tree(6, 0, random), make_tree(6, 1, random));
    Graph double_star{{1, 2, 3}, {0, 4, 5, 6}, {0}, {0}, {1}, {1}, {1}};
    check_small(double_star, relabel(double_star, {1, 0, 2, 3, 4, 5, 6}, random));
    for (int tc = 0; tc < 180; ++tc) {
        int n = 1 + random() % 7;
        Graph g = make_tree(n, tc % 4, random), h;
        if (tc % 2) h = make_tree(n, 3, random);
        else {
            vector<int> permutation(n);
            iota(permutation.begin(), permutation.end(), 0);
            shuffle(permutation.begin(), permutation.end(), random);
            h = relabel(g, permutation, random);
        }
        check_small(g, h);
    }
    check_small(make_tree(4, 0, random), make_tree(5, 0, random));
    for (int shape = 0; shape < 4; ++shape) {
        int n = 4096;
        Graph g = make_tree(n, shape, random);
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        shuffle(permutation.begin(), permutation.end(), random);
        Graph h = relabel(g, permutation, random);
        auto result = tree_isomorphism(g, h);
        assert(result.exists);
        validate(g, h, result);
        for (int root : {0, n / 2, n - 1}) {
            result = rooted_tree_isomorphism(g, h, root, permutation[root]);
            assert(result.exists);
            validate(g, h, result, root, permutation[root]);
        }
    }
}

int main() {
    self_check();
}
