#ifndef FIRIEXP_LIBRARY_TREE_TREE_MO_CPP
#define FIRIEXP_LIBRARY_TREE_TREE_MO_CPP

#include "../util/mo.cpp"

template<class Add, class Erase, class Output>
void tree_mo_solve(const vector<vector<int>> &g, const vector<pair<int, int>> &paths,
                   Add add, Erase erase, Output output, int root = 0) {
    if (paths.empty()) return;
    int n = (int)g.size();
    assert(0 <= root && root < n);
    vector<int> tin(n), parent(n, -1), tour, stack{root};
    tour.reserve(2 * n - 1);
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (v < 0) {
            if (parent[~v] != -1) tour.push_back(parent[~v]);
        } else {
            tin[v] = (int)tour.size();
            tour.push_back(v);
            stack.push_back(~v);
            for (int i = (int)g[v].size() - 1; i >= 0; --i) {
                int u = g[v][i];
                if (u != parent[v]) {
                    parent[u] = v;
                    stack.push_back(u);
                }
            }
        }
    }
    vector<Query> queries;
    queries.reserve(paths.size());
    for (int i = 0; i < (int)paths.size(); ++i) {
        auto [u, v] = paths[i];
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (tin[u] > tin[v]) swap(u, v);
        queries.emplace_back(tin[u], tin[v], i);
    }
    vector<char> active(n);
    auto move = [&](int from, int to) {
        if (active[to]) {
            erase(from);
            active[from] = 0;
        } else {
            add(to);
            active[to] = 1;
        }
    };
    auto forward = [&](int i) { move(tour[i], tour[i + 1]); };
    auto backward = [&](int i) { move(tour[i + 1], tour[i]); };
    add(root);
    active[root] = 1;
    mo_solve((int)tour.size(), queries, backward, forward, forward, backward, output);
    for (int v = 0; v < n; ++v) {
        if (active[v]) erase(v);
    }
}

#endif

/**
 * @brief 木上パスのMo
 */
