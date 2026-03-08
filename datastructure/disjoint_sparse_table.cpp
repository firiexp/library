template<class F>
struct DisjointSparseTable {
    using T = typename F::T;
    int n, lg;
    vector<vector<T>> table;

    DisjointSparseTable(): n(0), lg(0), table() {}
    explicit DisjointSparseTable(const vector<T> &v) { build(v); }

    void build(const vector<T> &v) {
        n = v.size();
        lg = 0;
        while ((1 << lg) < max(1, n)) ++lg;
        table.assign(lg + 1, vector<T>(n));
        if (n == 0) return;
        table[0] = v;
        for (int k = 1; k <= lg; ++k) table[k] = v;
        for (int k = 0; k < lg; ++k) {
            int len = 1 << k;
            for (int mid = len; mid < n; mid += len << 1) {
                int l = mid - len;
                int r = min(n, mid + len);
                table[k + 1][mid - 1] = v[mid - 1];
                for (int i = mid - 2; i >= l; --i) {
                    table[k + 1][i] = F::f(v[i], table[k + 1][i + 1]);
                }
                table[k + 1][mid] = v[mid];
                for (int i = mid + 1; i < r; ++i) {
                    table[k + 1][i] = F::f(table[k + 1][i - 1], v[i]);
                }
            }
        }
    }

    T query(int l, int r) const {
        if (l >= r) return F::e();
        --r;
        if (l == r) return table[0][l];
        int k = 31 - __builtin_clz(l ^ r);
        return F::f(table[k + 1][l], table[k + 1][r]);
    }
};

/**
 * @brief Disjoint Sparse Table
 */
