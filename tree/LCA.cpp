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
 
 
struct F {
    using T = pair<int, int>;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return T{INF<int>, -1}; }
};
 
class Graph {
    SparseTable<F> table;
    void dfs_euler(int v, int p, int d, int &k){
        id[v] = k;
        vs[k] = v;
        depth[k++] = d;
        for (auto &&u : G[v]) {
            if(u != p){
                dfs_euler(u, v, d+1, k);
                vs[k] = v;
                depth[k++] = d;
            }
        }
    }
public:
    int n;
    vector<vector<int>> G;
    vector<int> vs, depth, id;
    explicit Graph(int n) : n(n), G(n), vs(2*n-1), depth(2*n-1), id(n), table() {};
    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
 
    void eulertour(int root) {
        int k = 0;
        dfs_euler(root, -1, 0, k);
    }
 
    void buildLCA(){
        eulertour(0);
        vector<pair<int, int>> v(2*n-1);
        for (int i = 0; i < 2*n-1; ++i) {
            v[i] = make_pair(depth[i], i);
        }
        table.build(v);
    }
 
    int LCA(int u, int v){
        if(id[u] > id[v]) swap(u, v);
        return table.query(id[u], id[v]+1).second;
    }
};