#ifndef FIRIEXP_LIBRARY_TREE_TREE_MO_CPP
#define FIRIEXP_LIBRARY_TREE_TREE_MO_CPP

#include "hld.cpp"
#include "../util/mo.cpp"

template<class Add, class Erase, class Output>
void tree_mo_solve(const vector<vector<int>> &g, const vector<pair<int, int>> &paths,
                   Add add, Erase erase, Output output, int root = 0) {
    if (paths.empty()) return;
    int n = (int)g.size();
    assert(0 <= root && root < n);
    HeavyLightDecomposition hld(n);
    hld.G = g;
    hld.build({root});
    vector<int> tin(n), tout(n), tour, stack{root};
    tour.reserve(2 * n);
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (v < 0) {
            v = ~v;
            tout[v] = (int)tour.size();
            tour.push_back(v);
        } else {
            tin[v] = (int)tour.size();
            tour.push_back(v);
            stack.push_back(~v);
            for (int i = (int)g[v].size() - 1; i >= 0; --i) {
                int u = g[v][i];
                if (u != hld.parent(v)) stack.push_back(u);
            }
        }
    }
    vector<Query> queries;
    queries.reserve(paths.size());
    vector<int> extra(paths.size(), -1);
    for (int i = 0; i < (int)paths.size(); ++i) {
        auto [u, v] = paths[i];
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (tin[u] > tin[v]) swap(u, v);
        int w = hld.lca(u, v);
        if (w == u) queries.emplace_back(tin[u], tin[v] + 1, i);
        else {
            queries.emplace_back(tout[u], tin[v] + 1, i);
            extra[i] = w;
        }
    }
    vector<char> active(n);
    auto toggle = [&](int i) {
        int v = tour[i];
        if (active[v]) erase(v);
        else add(v);
        active[v] ^= 1;
    };
    mo_solve(2 * n, queries, toggle, toggle, toggle, toggle, [&](int id) {
        int w = extra[id];
        if (w != -1) add(w);
        output(id);
        if (w != -1) erase(w);
    });
    for (int v = 0; v < n; ++v) {
        if (active[v]) erase(v);
    }
}

#endif

/**
 * @brief 木上パスのMo
 */
