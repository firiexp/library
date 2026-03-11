using namespace std;

#include "biconnected_components.cpp"

struct BlockCutTree {
    int n, block_count;
    BiconnectedComponents bcc;
    vector<vector<int>> tree, nodes;
    vector<int> id, rev;
    vector<char> is_articulation;

    explicit BlockCutTree(int n) : n(n), block_count(0), bcc(n), id(n, -1), is_articulation(n, 0) {}

    void add_edge(int u, int v) {
        bcc.add_edge(u, v);
    }

    int build() {
        block_count = bcc.build();
        vector<int> cnt(n);
        for (auto &&vs : bcc.bcc_vertices) {
            for (auto &&v : vs) ++cnt[v];
        }

        int m = block_count;
        id.assign(n, -1);
        is_articulation.assign(n, 0);
        for (int v = 0; v < n; ++v) {
            if (cnt[v] > 1) {
                is_articulation[v] = 1;
                id[v] = m++;
            }
        }

        tree.assign(m, {});
        nodes.assign(m, {});
        rev.assign(m, -1);
        for (int i = 0; i < block_count; ++i) {
            nodes[i] = bcc.bcc_vertices[i];
            for (auto &&v : bcc.bcc_vertices[i]) {
                if (cnt[v] > 1) {
                    tree[i].push_back(id[v]);
                    tree[id[v]].push_back(i);
                } else {
                    id[v] = i;
                }
            }
        }
        for (int v = 0; v < n; ++v) {
            if (is_articulation[v]) {
                nodes[id[v]].push_back(v);
                rev[id[v]] = v;
            }
        }
        return m;
    }
};

/**
 * @brief ブロックカット木(Block-Cut Tree)
 */
