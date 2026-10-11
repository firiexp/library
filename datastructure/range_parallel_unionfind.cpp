class RangeParallelUnionFind {
    vector<vector<int>> parent;
    vector<int> lg;
    int components;

    int leader(int level, int v) {
        auto& p = parent[level];
        int r = v;
        while (p[r] >= 0) r = p[r];
        while (v != r) {
            int next = p[v];
            p[v] = r;
            v = next;
        }
        return r;
    }

    template<class F>
    int unite(int level, int a, int b, F& on_merge) {
        a = leader(level, a);
        b = leader(level, b);
        if (a == b) return 0;
        if (parent[level][a] > parent[level][b]) swap(a, b);
        if (level == 0) on_merge(a, b);
        parent[level][a] += parent[level][b];
        parent[level][b] = a;
        if (level == 0) {
            --components;
            return 1;
        }
        int half = 1 << (level - 1);
        int merged = unite(level - 1, a, b, on_merge);
        return merged + unite(level - 1, a + half, b + half, on_merge);
    }

public:
    explicit RangeParallelUnionFind(int n) : lg(n + 1), components(n) {
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        for (int level = 0; (1LL << level) <= n; ++level)
            parent.emplace_back(n - (1 << level) + 1, -1);
    }

    int root(int v) { return leader(0, v); }
    bool same(int a, int b) { return root(a) == root(b); }
    int size(int v) { return -parent[0][root(v)]; }
    int count() const { return components; }

    template<class F>
    int unite_range(int a, int b, int k, F on_merge) {
        if (k == 0 || a == b) return 0;
        int level = lg[k], length = 1 << level;
        int merged = unite(level, a, b, on_merge);
        return merged + unite(level, a + k - length, b + k - length, on_merge);
    }

    int unite_range(int a, int b, int k) {
        return unite_range(a, b, k, [](int, int) {});
    }
};

/**
 * @brief 区間の対応点を併合するUnionFind
 */
