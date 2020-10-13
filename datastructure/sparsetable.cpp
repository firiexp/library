template <class F>
struct SparseTable {
    using T = typename F::T;
    vector<vector<T>> table;
    vector<int> u;
    SparseTable() = default;
    explicit SparseTable(const vector<T> &v){ build(v); }
 
    void build(const vector<T> &v){
        int n = v.size(), m = 1;
        while((1<<m) <= n) m++;
        table.assign(m, vector<T>(n));
        u.assign(n+1, 0);
        for (int i = 2; i <= n; ++i) {
            u[i] = u[i>>1] + 1;
        }
        for (int i = 0; i < n; ++i) {
            table[0][i] = v[i];
        }
        for (int i = 1; i < m; ++i) {
            int x = (1<<(i-1));
            for (int j = 0; j < n; ++j) {
                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x, n-1)]);
            }
        }
    }
 
    T query(int a, int b){
        int l = b-a;
        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);
    }
};