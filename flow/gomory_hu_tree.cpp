#include "dinic.cpp"

template<class T>
class GomoryHuTree {
    static_assert(numeric_limits<T>::is_integer && numeric_limits<T>::is_signed,
                  "GomoryHuTree requires a signed integer capacity type");

public:
    struct Edge {
        int u, v;
        T capacity;
    };

private:
    int n, levels;
    vector<Edge> tree_edges;
    vector<int> depth, order;
    vector<vector<int>> up;
    vector<vector<T>> minimum;

public:
    GomoryHuTree(int n, const vector<Edge> &edges) : n(n), levels(1), depth(n) {
        assert(n >= 1);
        Dinic<T, false> flow(n);
        for (auto [u, v, capacity] : edges) {
            assert(0 <= u && u < n && 0 <= v && v < n && capacity >= 0);
            if (u == v) continue;
            assert(capacity <= numeric_limits<T>::max() / 2);
            flow.add_edge(u, v, capacity);
        }
        vector<int> parent(n);
        vector<T> cut(n);
        for (int s = 1; s < n; ++s) {
            int t = parent[s];
            flow.reset_flow();
            T value = flow.flow(s, t, numeric_limits<T>::max());
            auto side = flow.min_cut(s);
            for (int v = 1; v < n; ++v)
                if (v != s && parent[v] == t && side[v]) parent[v] = s;
            if (t != 0 && side[parent[t]]) {
                parent[s] = parent[t];
                parent[t] = s;
                cut[s] = cut[t];
                cut[t] = value;
            } else {
                cut[s] = value;
            }
        }
        tree_edges.reserve(n - 1);
        vector<vector<pair<int, T>>> graph(n);
        for (int v = 1; v < n; ++v) {
            tree_edges.push_back({v, parent[v], cut[v]});
            graph[v].emplace_back(parent[v], cut[v]);
            graph[parent[v]].emplace_back(v, cut[v]);
        }
        while ((1LL << levels) <= n) ++levels;
        up.assign(levels, vector<int>(n));
        minimum.assign(levels, vector<T>(n, numeric_limits<T>::max()));
        order.push_back(0);
        order.reserve(n);
        for (int i = 0; i < int(order.size()); ++i) {
            int v = order[i];
            for (auto [u, capacity] : graph[v]) if (u != up[0][v]) {
                up[0][u] = v;
                minimum[0][u] = capacity;
                depth[u] = depth[v] + 1;
                order.push_back(u);
            }
        }
        for (int k = 1; k < levels; ++k) for (int v = 0; v < n; ++v) {
            int p = up[k - 1][v];
            up[k][v] = up[k - 1][p];
            minimum[k][v] = min(minimum[k - 1][v], minimum[k - 1][p]);
        }
    }

    const vector<Edge> &edges() const { return tree_edges; }

    T min_cut(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        T result = numeric_limits<T>::max();
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < levels; ++k) if (diff >> k & 1) {
            result = min(result, minimum[k][u]);
            u = up[k][u];
        }
        if (u == v) return result;
        for (int k = levels - 1; k >= 0; --k) if (up[k][u] != up[k][v]) {
            result = min(result, min(minimum[k][u], minimum[k][v]));
            u = up[k][u];
            v = up[k][v];
        }
        return min(result, min(minimum[0][u], minimum[0][v]));
    }

    vector<bool> min_cut_side(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        int source = u, removed = -1;
        while (u != v) {
            if (depth[u] < depth[v]) swap(u, v);
            if (removed == -1 || minimum[0][u] < minimum[0][removed]) removed = u;
            u = up[0][u];
        }
        vector<bool> side(n);
        for (int x : order) side[x] = x == removed || side[up[0][x]];
        if (!side[source]) side.flip();
        return side;
    }
};

/**
 * @brief 全頂点対最小カット(Gomory–Hu木)
 */
