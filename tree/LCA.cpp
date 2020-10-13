#include "../datastructure/sparsetable.cpp"
 
struct F {
    using T = pair<int, int>;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return T{INF<int>, -1}; }
};
 
class LCA {
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