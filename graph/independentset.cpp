class IndependentSet {
    int n;
    vector<ull> G;
    ull full_mask() const { return n == 64 ? ~0ull : (1ull << n) - 1; }
    pair<int, ull> dfs(ull R, ull P, ull X) {
        if (!P && !X) {
            return {__builtin_popcountll(R), R};
        }
        if (!P) return {-1, 0};
        pair<int, ull> res = {-1, 0};
        int pivot = -1, max_neighbors = -1;
        for (ull vertices = P | X; vertices; vertices &= vertices - 1) {
            int u = __builtin_ctzll(vertices);
            int neighbors = __builtin_popcountll(P & G[u]);
            if (neighbors > max_neighbors) {
                pivot = u;
                max_neighbors = neighbors;
            }
        }
        ull z = P & ~G[pivot];
        while (z) {
            int i = __builtin_ctzll(z);
            z &= z - 1;
            res = max(res, dfs(R | (1ull << i), P & G[i], X & G[i]));
            P ^= 1ull << i;
            X |= 1ull << i;
        }
        return res;
    }


public:
    explicit IndependentSet(int n): n(n), G(n) {
        for (int i = 0; i < n; ++i) {
            G[i] = full_mask() ^ (1ull << i);
        }
    }
    void add_edge(int u, int v){
        G[u] &= ~(1ull << v);
        G[v] &= ~(1ull << u);
    }
    pair<int, ull> maximum_independent_set() {
        return dfs(0, full_mask(), 0);
    }
};

/**
 * @brief 最大独立集合(Maximum Independent Set)
 */
