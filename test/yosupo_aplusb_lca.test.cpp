#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../tree/LCA.cpp"

void check_roots(LCA &tree) {
    for (int root = 0; root < tree.n; ++root) {
        vector<int> parent(tree.n, -1), depth(tree.n);
        queue<int> que;
        parent[root] = root;
        que.push(root);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int u : tree.G[v]) {
                if (parent[u] != -1) continue;
                parent[u] = v;
                depth[u] = depth[v] + 1;
                que.push(u);
            }
        }

        if (root % 2 == 0) tree.build(root);
        else tree.buildLCA(root);
        for (int u = 0; u < tree.n; ++u) {
            for (int v = 0; v < tree.n; ++v) {
                int a = u, b = v;
                while (depth[a] > depth[b]) a = parent[a];
                while (depth[b] > depth[a]) b = parent[b];
                while (a != b) {
                    a = parent[a];
                    b = parent[b];
                }
                assert(tree.lca(u, v) == a);
            }
        }
    }
}

int main() {
    LCA tree(5);
    tree.add_edge(3, 4);
    tree.add_edge(0, 1);
    tree.add_edge(0, 3);
    tree.add_edge(3, 2);
    tree.eulertour(3);
    assert((tree.vs == vector<int>{3, 4, 3, 0, 1, 0, 3, 2, 3}));
    assert((tree.depth == vector<int>{0, 1, 0, 1, 2, 1, 0, 1, 0}));
    assert((tree.id == vector<int>{3, 4, 7, 0, 1}));
    check_roots(tree);

    mt19937 rng(494);
    for (int n = 1; n <= 32; ++n) {
        for (int rep = 0; rep < 4; ++rep) {
            LCA random_tree(n);
            vector<pair<int, int>> edges;
            for (int v = 1; v < n; ++v) edges.emplace_back(rng() % v, v);
            shuffle(edges.begin(), edges.end(), rng);
            for (auto [u, v] : edges) random_tree.add_edge(u, v);
            check_roots(random_tree);
        }
    }
}
