#ifndef FIRIEXP_LIBRARY_GRAPH_RANGE_EDGE_GRAPH_CPP
#define FIRIEXP_LIBRARY_GRAPH_RANGE_EDGE_GRAPH_CPP

#include "edge.cpp"

template<class T>
class RangeEdgeGraph {
    int n;
    vector<vector<edge<T>>> g;

    int down(int v) const { return v >= n ? v - n : n + v - 1; }
    int up(int v) const { return v >= n ? v - n : 2 * n + v - 2; }

    void connect(int l, int r, int v, const T &w, bool to_range) {
        auto add = [&](int node) {
            int from = to_range ? v : up(node), to = to_range ? down(node) : v;
            g[from].emplace_back(from, to, w);
        };
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) add(l++);
            if (r & 1) add(--r);
        }
    }

    void check_range(int l, int r) const { assert(0 <= l && l <= r && r <= n); }

public:
    explicit RangeEdgeGraph(int n) : n(n) {
        assert(0 <= n && n <= INT_MAX / 3);
        g.resize(n == 0 ? 0 : 3 * n - 2);
        for (int v = 1; v < n; ++v) {
            for (int child : {2 * v, 2 * v + 1}) {
                g[down(v)].emplace_back(down(v), down(child), T(0));
                g[up(child)].emplace_back(up(child), up(v), T(0));
            }
        }
    }

    void add_edge(int u, int v, const T &w) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        g[u].emplace_back(u, v, w);
    }

    void add_to_range(int u, int l, int r, const T &w) {
        assert(0 <= u && u < n);
        check_range(l, r);
        connect(l, r, u, w, true);
    }

    void add_from_range(int l, int r, int v, const T &w) {
        check_range(l, r);
        assert(0 <= v && v < n);
        connect(l, r, v, w, false);
    }

    void add_range_to_range(int l1, int r1, int l2, int r2, const T &w) {
        check_range(l1, r1);
        check_range(l2, r2);
        if (l1 == r1 || l2 == r2) return;
        assert(g.size() < (size_t)INT_MAX);
        int v = (int)g.size();
        g.emplace_back();
        connect(l1, r1, v, T(0), false);
        connect(l2, r2, v, w, true);
    }

    const vector<vector<edge<T>>> &graph() const { return g; }
};

#endif

/**
 * @brief 区間への辺を圧縮するグラフ
 */
