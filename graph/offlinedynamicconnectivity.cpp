using namespace std;

#include "../datastructure/undoableunionfind.cpp"

struct OfflineDynamicConnectivity {
    int n, q, sz;
    UndoableUnionFind uf;
    vector<vector<pair<int, int>>> seg;
    vector<pair<pair<int, int>, pair<int, int>>> pend;
    map<pair<int, int>, int> cnt, appear;

    explicit OfflineDynamicConnectivity(int n, int q) : n(n), q(q), uf(n) {
        sz = 1;
        while (sz < q) sz <<= 1;
        seg.resize(2 * sz);
    }

    void add_segment(int l, int r, const pair<int, int> &e) {
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) seg[l++].push_back(e);
            if (r & 1) seg[--r].push_back(e);
        }
    }

    void insert(int t, int a, int b) {
        auto e = minmax(a, b);
        if (cnt[e]++ == 0) appear[e] = t;
    }

    void erase(int t, int a, int b) {
        auto e = minmax(a, b);
        if (--cnt[e] == 0) {
            pend.emplace_back(make_pair(appear[e], t), e);
            appear.erase(e);
        }
    }

    void build() {
        for (auto &&[e, c] : cnt) {
            if (!c) continue;
            pend.emplace_back(make_pair(appear[e], q), e);
        }
        for (auto &&[range, e] : pend) add_segment(range.first, range.second, e);
    }

    template <class Enter, class Leave, class Leaf>
    void dfs(const Enter &enter, const Leave &leave, const Leaf &leaf, int k = 1) {
        enter(k, seg[k]);
        if (k < sz) {
            dfs(enter, leave, leaf, k << 1);
            dfs(enter, leave, leaf, k << 1 | 1);
        } else if (k - sz < q) {
            leaf(k - sz);
        }
        leave(k, seg[k]);
    }

    template <class F>
    void run(const F &f) {
        dfs(
            [&](int, const vector<pair<int, int>> &edges) {
                for (auto &&[u, v] : edges) uf.unite(u, v);
            },
            [&](int, const vector<pair<int, int>> &edges) {
                for (int i = 0; i < (int)edges.size(); ++i) uf.undo();
            },
            [&](int t) {
                if constexpr (is_invocable_v<F, int, UndoableUnionFind &>) {
                    f(t, uf);
                } else {
                    f(t);
                }
            }
        );
    }
};

/**
 * @brief Offline Dynamic Connectivity
 */
