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

    RootedTree(const vector<vector<int>> &g, int root, map<vector<int>, int> &ids, int other = -1)
        : children(g.size()), label(g.size()) {
        int n = g.size();
        vector<int> parent(n, -1);
        order.reserve(n);
        order.push_back(root);
        if (other != -1) {
            parent[root] = other;
            parent[other] = root;
            order.push_back(other);
        }
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

TreeIsomorphismResult restore(const RootedTree &a, const RootedTree &b, vector<int> mapping) {
    for (int v : a.order) {
        int w = mapping[v];
        for (int i = 0; i < (int)a.children[v].size(); ++i) {
            mapping[a.children[v][i]] = b.children[w][i];
        }
    }
    return {true, std::move(mapping)};
}
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
    return tree_isomorphism_detail::restore(a, b, std::move(mapping));
}

TreeIsomorphismResult tree_isomorphism(const vector<vector<int>> &g,
        const vector<vector<int>> &h) {
    if (g.size() != h.size()) return {false, {}};
    if (g.empty()) return {true, {}};
    auto centers_g = tree_center(g).second;
    auto centers_h = tree_center(h).second;
    if (centers_g.size() != centers_h.size()) return {false, {}};
    if (centers_g.size() == 1) return rooted_tree_isomorphism(g, h, centers_g[0], centers_h[0]);
    map<vector<int>, int> ids;
    tree_isomorphism_detail::RootedTree a(g, centers_g[0], ids, centers_g[1]);
    tree_isomorphism_detail::RootedTree b(h, centers_h[0], ids, centers_h[1]);
    if (a.label[centers_g[0]] != b.label[centers_h[0]]) swap(centers_h[0], centers_h[1]);
    if (a.label[centers_g[0]] != b.label[centers_h[0]]
        || a.label[centers_g[1]] != b.label[centers_h[1]]) return {false, {}};
    vector<int> mapping(g.size());
    for (int i = 0; i < 2; ++i) mapping[centers_g[i]] = centers_h[i];
    return tree_isomorphism_detail::restore(a, b, std::move(mapping));
}

#endif

/**
 * @brief 木の同型判定と頂点対応
 */
