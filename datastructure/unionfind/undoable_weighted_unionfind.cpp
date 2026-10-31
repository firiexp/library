template<class G>
class UndoableWeightedUnionFind {
    using T = typename G::T;
    struct Change {
        int a, b, size_a, size_b, bad_a, bad_b, total_bad;
        T weight_b;
    };

    vector<int> parent, bad;
    vector<T> weight;
    vector<Change> history;
    int total_bad = 0;

    pair<int, T> root_weight(int v) const {
        T result = G::e();
        while (parent[v] >= 0) {
            result = G::op(weight[v], result);
            v = parent[v];
        }
        return {v, result};
    }

public:
    explicit UndoableWeightedUnionFind(int n) : parent(n, -1), bad(n), weight(n, G::e()) {}

    int root(int v) const {
        while (parent[v] >= 0) v = parent[v];
        return v;
    }

    bool same(int a, int b) const { return root(a) == root(b); }
    int size(int v) const { return -parent[root(v)]; }
    bool consistent() const { return total_bad == 0; }
    bool consistent(int v) const { return bad[root(v)] == 0; }

    optional<T> diff(int a, int b) const {
        auto [ra, wa] = root_weight(a);
        auto [rb, wb] = root_weight(b);
        if (ra != rb || bad[ra]) return nullopt;
        return G::op(G::inv(wa), wb);
    }

    bool unite(int a, int b, const T &w) {
        auto [ra, wa] = root_weight(a);
        auto [rb, wb] = root_weight(b);
        T delta = G::op(wa, G::op(w, G::inv(wb)));
        if (parent[ra] > parent[rb]) {
            swap(ra, rb);
            delta = G::inv(delta);
        }
        history.push_back({ra, rb, parent[ra], parent[rb], bad[ra], bad[rb], total_bad, weight[rb]});
        if (ra == rb) {
            if (!(delta == G::e())) {
                ++bad[ra];
                ++total_bad;
            }
            return false;
        }
        parent[ra] += parent[rb];
        parent[rb] = ra;
        weight[rb] = delta;
        bad[ra] += bad[rb];
        return true;
    }

    int get_state() const { return (int)history.size(); }

    void undo() {
        assert(!history.empty());
        const auto &change = history.back();
        parent[change.a] = change.size_a;
        parent[change.b] = change.size_b;
        bad[change.a] = change.bad_a;
        bad[change.b] = change.bad_b;
        weight[change.b] = change.weight_b;
        total_bad = change.total_bad;
        history.pop_back();
    }

    void rollback(int state) {
        assert(0 <= state && state <= get_state());
        while (get_state() > state) undo();
    }
};

/**
 * @brief 差分・矛盾判定付きrollback UnionFind
 */
