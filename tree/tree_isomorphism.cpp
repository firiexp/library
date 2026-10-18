#ifndef FIRIEXP_LIBRARY_TREE_TREE_ISOMORPHISM_CPP
#define FIRIEXP_LIBRARY_TREE_TREE_ISOMORPHISM_CPP

#include "tree_center.cpp"

struct TreeIsomorphismResult {
    bool exists;
    vector<int> mapping;
};

namespace tree_isomorphism_detail {
struct RootedTree {
    vector<vector<int>> children;
    vector<int> order, label;

    RootedTree(const vector<vector<int>> &g, int root, map<vector<int>, int> &ids)
        : children(g.size()), label(g.size()) {
        int n = g.size();
        vector<int> parent(n, -1);
        order.reserve(n);
        order.push_back(root);
        for (int i = 0; i < n; ++i) {
            int v = order[i];
            for (int to : g[v]) if (to != parent[v]) {
                parent[to] = v;
                children[v].push_back(to);
                order.push_back(to);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            auto &ch = children[v];
            sort(ch.begin(), ch.end(), [&](int a, int b) { return label[a] < label[b]; });
            vector<int> key;
            key.reserve(ch.size());
            for (int to : ch) key.push_back(label[to]);
            label[v] = ids.try_emplace(std::move(key), (int)ids.size()).first->second;
        }
    }
};
}

TreeIsomorphismResult rooted_tree_isomorphism(const vector<vector<int>> &g,
        const vector<vector<int>> &h, int root_g, int root_h) {
    if (g.size() != h.size()) return {false, {}};
    if (g.empty()) return {true, {}};
    map<vector<int>, int> ids;
    tree_isomorphism_detail::RootedTree a(g, root_g, ids), b(h, root_h, ids);
    if (a.label[root_g] != b.label[root_h]) return {false, {}};
    vector<int> mapping(g.size());
    mapping[root_g] = root_h;
    for (int v : a.order) {
        int w = mapping[v];
        for (int i = 0; i < (int)a.children[v].size(); ++i) {
            mapping[a.children[v][i]] = b.children[w][i];
        }
    }
    return {true, std::move(mapping)};
}

TreeIsomorphismResult tree_isomorphism(const vector<vector<int>> &g,
        const vector<vector<int>> &h) {
    if (g.size() != h.size()) return {false, {}};
    if (g.empty()) return {true, {}};
    auto centers_g = tree_center(g).second;
    auto centers_h = tree_center(h).second;
    if (centers_g.size() != centers_h.size()) return {false, {}};
    for (int root_h : centers_h) {
        auto result = rooted_tree_isomorphism(g, h, centers_g[0], root_h);
        if (result.exists) return result;
    }
    return {false, {}};
}

#endif

/**
 * @brief 木の同型判定と頂点対応
 */
