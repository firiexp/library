class IndependentSet {
    int n;
    vector<ull> G;
    ull full_mask() const { return n == 64 ? ~0ull : (1ull << n) - 1; }
    int color_bound(ull vertices) const {
        int colors = 0;
        while (vertices) {
            ++colors;
            ull available = vertices;
            while (available) {
                int v = 63 - __builtin_clzll(available);
                ull bit = 1ull << v;
                vertices &= ~bit;
                available &= ~bit & ~G[v];
            }
        }
        return colors;
    }
    void dfs(ull R, ull P, ull X, pair<int, ull> &best) {
        if (!P && !X) {
            best = max(best, pair<int, ull>{__builtin_popcountll(R), R});
            return;
        }
        if (!P) return;
        int bound = __builtin_popcountll(R) + color_bound(P);
        if (bound < best.first || (bound == best.first && (R | P) <= best.second)) return;
        int pivot = -1, max_neighbors = -1;
        for (ull vertices = P | X; vertices; vertices &= vertices - 1) {
            int u = __builtin_ctzll(vertices);
            int neighbors = __builtin_popcountll(P & G[u]);
            if (neighbors >= max_neighbors) {
                pivot = u;
                max_neighbors = neighbors;
            }
        }
        ull z = P & ~G[pivot];
        while (z) {
            int i = 63 - __builtin_clzll(z);
            z &= ~(1ull << i);
            dfs(R | (1ull << i), P & G[i], X & G[i], best);
            P ^= 1ull << i;
            X |= 1ull << i;
        }
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
        pair<int, ull> best = {-1, 0};
        dfs(0, full_mask(), 0, best);
        return best;
    }
};

/**
 * @brief 最大独立集合(Maximum Independent Set)
 */
