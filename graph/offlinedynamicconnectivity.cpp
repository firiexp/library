using namespace std;

#include "../datastructure/undoableunionfind.cpp"

struct OfflineDynamicConnectivity {
    struct EdgeRange {
        vector<pair<int, int>>::const_iterator first, last;
        auto begin() const { return first; }
        auto end() const { return last; }
        size_t size() const { return last - first; }
    };

    int n, q, sz;
    UndoableUnionFind uf;
    vector<size_t> offset;
    vector<pair<int, int>> events;
    vector<pair<pair<int, int>, pair<int, int>>> pend;
    map<pair<int, int>, int> cnt, appear;

    explicit OfflineDynamicConnectivity(int n, int q) : n(n), q(q), uf(n) {
        sz = 1;
        while (sz < q) sz <<= 1;
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
        auto enumerate = [&](auto visit) {
            auto add = [&](int l, int r, const pair<int, int> &e) {
                for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
                    if (l & 1) visit(l++, e);
                    if (r & 1) visit(--r, e);
                }
            };
            for (auto &&[range, e] : pend) add(range.first, range.second, e);
            for (auto &&[e, t] : appear) add(t, q, e);
        };
        offset.assign(2 * sz + 1, 0);
        enumerate([&](int k, const auto &) { ++offset[k + 1]; });
        for (size_t i = 1; i < offset.size(); ++i) offset[i] += offset[i - 1];
        events.resize(offset.back());
        auto cursor = offset;
        enumerate([&](int k, const auto &e) { events[cursor[k]++] = e; });
    }

    template <class Enter, class Leave, class Leaf>
    void dfs(const Enter &enter, const Leave &leave, const Leaf &leaf, int k = 1) {
        EdgeRange edges{events.cbegin() + offset[k], events.cbegin() + offset[k + 1]};
        enter(k, edges);
        if (k < sz) {
            dfs(enter, leave, leaf, k << 1);
            dfs(enter, leave, leaf, k << 1 | 1);
        } else if (k - sz < q) {
            leaf(k - sz);
        }
        leave(k, edges);
    }

    template <class F>
    void run(const F &f) {
        dfs(
            [&](int, const EdgeRange &edges) {
                for (auto &&[u, v] : edges) uf.unite(u, v);
            },
            [&](int, const EdgeRange &edges) {
                for (size_t i = 0; i < edges.size(); ++i) uf.undo();
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
