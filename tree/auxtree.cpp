#include "../datastructure/sparsetable.cpp"

struct F {
    using T = pair<int, int>;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return T{INF<int>, -1}; }
};

class AuxTree {
    SparseTable<F> table;
    void dfs_euler(int v, int p, int d, int &k, int &l){
        id[v] = k;
        vs[k] = v;
        depth[k++] = d;
        dep[v] = d;
        fi[v] = l++;
        for (auto &&u : G[v]) {
            if(u != p){
                dfs_euler(u, v, d+1, k, l);
                vs[k] = v;
                depth[k++] = d;
            }
        }
    }
public:
    int n;
    vector<vector<int>> G, out;
    vector<int> vs, depth, dep, id, fi;
    explicit AuxTree(int n) : n(n), G(n), out(n), vs(2*n-1), depth(2*n-1), dep(n), id(n), fi(n), table() {};
    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    void eulertour(int root) {
        int k = 0, l = 0;
        dfs_euler(root, -1, 0, k, l);
    }

    void buildLCA(){
        eulertour(0);
        vector<pair<int, int>> v(2*n-1);
        for (int i = 0; i < 2*n-1; ++i) {
            v[i] = make_pair(depth[i], vs[i]);
        }
        table.build(v);
    }

    void make(vector<int> &v){
        sort(v.begin(),v.end(), [&](int a, int b){ return fi[a] < fi[b]; });
        v.erase(unique(v.begin(), v.end()), v.end());
        int k = v.size();
        stack<int> s;
        s.emplace(v.front());
        for (int i = 0; i+1 < k; ++i) {
            int w = LCA(v[i], v[i+1]);
            if(w != v[i]){
                int u = s.top(); s.pop();
                while(!s.empty() && dep[w] < dep[s.top()]){
                    out[s.top()].emplace_back(u);
                    out[u].emplace_back(s.top());
                    u = s.top(); s.pop();
                }
                if(s.empty() || s.top() != w){
                    s.emplace(w);
                    v.emplace_back(w);
                }
                out[w].emplace_back(u);
                out[u].emplace_back(w);
            }
            s.emplace(v[i+1]);
        }
        while(s.size() > 1){
            int u = s.top(); s.pop();
            out[s.top()].emplace_back(u);
            out[u].emplace_back(s.top());
        }
    }

    void clear(vector<int> &v){
        for (auto &&i : v) {
            out[i].clear();
            out[i].shrink_to_fit();
        }
    }

    int LCA(int u, int v){
        if(id[u] > id[v]) swap(u, v);
        return table.query(id[u], id[v]+1).second;
    }

    int distance(int u, int v){
        return dep[u]+dep[v]-2*dep[LCA(u, v)];
    }
};
