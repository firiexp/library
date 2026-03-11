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
        if (n == 0) return root = -1;
        return root = decompose(start, -1, 0);
    }

private:
    int dfs_size(int v, int p) {
        sz[v] = 1;
        for (auto &&u : G[v]) {
            if (u == p || used[u]) continue;
            sz[v] += dfs_size(u, v);
        }
        return sz[v];
    }

    int find_centroid(int v, int p, int half) {
        for (auto &&u : G[v]) {
            if (u == p || used[u]) continue;
            if (sz[u] > half) return find_centroid(u, v, half);
        }
        return v;
    }

    void collect(int v, int p, int d, vector<pair<int, int>> &buf) {
        buf.emplace_back(v, d);
        for (auto &&u : G[v]) {
            if (u == p || used[u]) continue;
            collect(u, v, d + 1, buf);
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
