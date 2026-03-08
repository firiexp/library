template<class G>
struct DSUonTree {
    G &g;
    int n, root, ord;
    vector<int> sub_size, euler, down, up;

    explicit DSUonTree(G &g, int root = 0)
        : g(g), n(g.size()), root(root), ord(0),
          sub_size(n), euler(n), down(n), up(n) {
        dfs_sz(root, -1);
        dfs_euler(root, -1);
    }

    int idx(int v) const {
        return down[v];
    }

    int begin(int v) const {
        return down[v];
    }

    int end(int v) const {
        return up[v];
    }

    template<class UPDATE, class QUERY, class CLEAR, class RESET>
    void run(UPDATE update, QUERY query, CLEAR clear, RESET reset) {
        auto dfs = [&](auto &&self, int v, int p, bool keep) -> void {
            int heavy = (g[v].empty() || g[v][0] == p ? -1 : g[v][0]);
            for (auto &&u : g[v]) {
                if (u == p || u == heavy) continue;
                self(self, u, v, false);
            }
            if (heavy != -1) self(self, heavy, v, true);
            for (auto &&u : g[v]) {
                if (u == p || u == heavy) continue;
                for (int i = down[u]; i < up[u]; ++i) update(euler[i]);
            }
            update(v);
            query(v);
            if (!keep) {
                for (int i = down[v]; i < up[v]; ++i) clear(euler[i]);
                reset();
            }
        };
        dfs(dfs, root, -1, false);
    }

private:
    void dfs_sz(int v, int p) {
        sub_size[v] = 1;
        int heavy_idx = -1;
        for (int i = 0; i < (int)g[v].size(); ++i) {
            int u = g[v][i];
            if (u == p) continue;
            dfs_sz(u, v);
            sub_size[v] += sub_size[u];
            if (heavy_idx == -1 || sub_size[u] > sub_size[g[v][heavy_idx]]) {
                heavy_idx = i;
            }
        }
        if (heavy_idx > 0) swap(g[v][0], g[v][heavy_idx]);
    }

    void dfs_euler(int v, int p) {
        down[v] = ord;
        euler[ord++] = v;
        for (auto &&u : g[v]) {
            if (u == p) continue;
            dfs_euler(u, v);
        }
        up[v] = ord;
    }
};

/**
 * @brief DSU on Tree
 */
