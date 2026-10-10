using namespace std;

struct CentroidDecompositionQueryHelper {
    int n, root;
    vector<vector<int>> G, tree, path, dist;
    vector<int> sz, parent, depth;
    vector<char> used;

    explicit CentroidDecompositionQueryHelper(int n)
        : n(n), root(-1), G(n), tree(n), path(n), dist(n), sz(n), parent(n, -1), depth(n), used(n, 0) {}

    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int build(int start = 0) {
        tree.assign(n, {});
        path.assign(n, {});
        dist.assign(n, {});
        fill(parent.begin(), parent.end(), -1);
        fill(depth.begin(), depth.end(), 0);
        fill(used.begin(), used.end(), 0);
        dfs_parent.resize(n);
        order.reserve(n);
        if (n == 0) return root = -1;
        return root = decompose(start, -1, 0);
    }

private:
    vector<int> dfs_parent, order;

    int dfs_size(int v, int p) {
        order.clear();
        order.push_back(v);
        dfs_parent[v] = p;
        for (int i = 0; i < (int)order.size(); ++i) {
            int x = order[i];
            sz[x] = 1;
            for (int u : G[x]) {
                if (u == dfs_parent[x] || used[u]) continue;
                dfs_parent[u] = x;
                order.push_back(u);
            }
        }
        for (int i = (int)order.size() - 1; i > 0; --i)
            sz[dfs_parent[order[i]]] += sz[order[i]];
        return sz[v];
    }

    int find_centroid(int v, int p, int half) {
        while (true) {
            int next = -1;
            for (int u : G[v]) {
                if (u != p && !used[u] && sz[u] > half) {
                    next = u;
                    break;
                }
            }
            if (next == -1) return v;
            p = v;
            v = next;
        }
    }

    void collect(int v, int p, int d, vector<pair<int, int>> &buf) {
        buf.emplace_back(v, d);
        dfs_parent[v] = p;
        for (int i = 0; i < (int)buf.size(); ++i) {
            auto [x, distance] = buf[i];
            for (int u : G[x]) {
                if (u == dfs_parent[x] || used[u]) continue;
                dfs_parent[u] = x;
                buf.emplace_back(u, distance + 1);
            }
        }
    }

    int decompose(int start, int p, int dep) {
        int centroid = find_centroid(start, -1, dfs_size(start, -1) / 2);
        used[centroid] = 1;
        parent[centroid] = p;
        depth[centroid] = dep;
        path[centroid].push_back(centroid);
        dist[centroid].push_back(0);
        for (auto &&u : G[centroid]) {
            if (used[u]) continue;
            vector<pair<int, int>> buf;
            collect(u, centroid, 1, buf);
            int child = decompose(u, centroid, dep + 1);
            tree[centroid].push_back(child);
            for (auto &&[v, d] : buf) {
                path[v].push_back(centroid);
                dist[v].push_back(d);
            }
        }
        return centroid;
    }
};

/**
 * @brief 重心分解クエリ補助(Centroid Query Helper)
 */
