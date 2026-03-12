template<class G>
struct DSUonTree {
    G &g;
    int n, root, ord;
    vector<int> par, sub_size, euler, down, up;

    explicit DSUonTree(G &g, int root = 0)
        : g(g), n(g.size()), root(root), ord(0),
          par(n, -1), sub_size(n), euler(n), down(n), up(n) {
        build();
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
        struct Frame {
            int v;
            bool keep;
            int stage;
            int child_idx;
        };
        vector<Frame> st = {{root, false, 0, 0}};
        while (!st.empty()) {
            Frame &cur = st.back();
            int v = cur.v;
            int heavy = (g[v].empty() || g[v][0] == par[v] ? -1 : g[v][0]);
            if (cur.stage == 0) {
                while (cur.child_idx < (int)g[v].size()) {
                    int u = g[v][cur.child_idx++];
                    if (u == par[v] || u == heavy) continue;
                    st.push_back({u, false, 0, 0});
                    goto next_iteration;
                }
                cur.stage = 1;
            }
            if (cur.stage == 1) {
                cur.stage = 2;
                if (heavy != -1) {
                    st.push_back({heavy, true, 0, 0});
                    goto next_iteration;
                }
            }
            if (cur.stage == 2) {
                for (auto &&u : g[v]) {
                    if (u == par[v] || u == heavy) continue;
                    for (int i = down[u]; i < up[u]; ++i) update(euler[i]);
                }
                update(v);
                query(v);
                if (!cur.keep) {
                    for (int i = down[v]; i < up[v]; ++i) clear(euler[i]);
                    reset();
                }
                st.pop_back();
            }
        next_iteration:;
        }
    }

private:
    void build() {
        vector<int> order;
        vector<int> st = {root};
        par[root] = -1;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            order.emplace_back(v);
            for (auto &&u : g[v]) {
                if (u == par[v]) continue;
                par[u] = v;
                st.emplace_back(u);
            }
        }
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int v = order[i];
            sub_size[v] = 1;
            int heavy_idx = -1;
            for (int j = 0; j < (int)g[v].size(); ++j) {
                int u = g[v][j];
                if (u == par[v]) continue;
                sub_size[v] += sub_size[u];
                if (heavy_idx == -1 || sub_size[u] > sub_size[g[v][heavy_idx]]) {
                    heavy_idx = j;
                }
            }
            if (heavy_idx > 0) swap(g[v][0], g[v][heavy_idx]);
        }

        struct EulerFrame {
            int v;
            int state;
        };
        vector<EulerFrame> euler_st = {{root, 0}};
        while (!euler_st.empty()) {
            auto [v, state] = euler_st.back();
            euler_st.pop_back();
            if (state == 0) {
                down[v] = ord;
                euler[ord++] = v;
                euler_st.push_back({v, 1});
                for (int i = (int)g[v].size() - 1; i >= 0; --i) {
                    int u = g[v][i];
                    if (u == par[v]) continue;
                    euler_st.push_back({u, 0});
                }
            } else {
                up[v] = ord;
            }
        }
    }

public:
};

/**
 * @brief DSU on Tree
 */
