class DominatorTree {
    int n;
    void unite(int x, int y){
        uf_par[y] = x;
    }

    int compress(int x){
        if(uf_par[x] == x) return x;
        int r = compress(uf_par[x]);
        if(semi[m[x]] > semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];
        return uf_par[x] = r;
    }

    int eval(int x){
        compress(x);
        return m[x];
    }


    void dfs(int x, int &cur){
        semi[x] = cur;
        ord[cur++] = x;
        for (auto &&i : G[x]) {
            if(!~semi[i]){
                par[i] = x;
                dfs(i, cur);
            }
        }
    }
public:
    DominatorTree(int n) : n(n), G(n), Grev(n), idom(n), semi(n), ord(n), par(n), uf_par(n), m(n), tmp(n), U(n) {}

    vector<vector<int>> G, Grev, tmp;
    vector<int> semi, ord, par, uf_par, m, U, idom;

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        Grev[b].emplace_back(a);
    }
    void build(int root){
        for (int i = 0; i < n; ++i) uf_par[i] = i, m[i] = i, semi[i] = -1, idom[i] = -1;
        int cur = 0;
        dfs(root, cur);
        for (int i = n-1; i >= 0; --i) {
            int a = ord[i];
            for (auto &&b : Grev[a]) {
                if(~semi[b]){
                    int c = eval(b);
                    semi[a] = min(semi[a], semi[c]);
                }
            }
            tmp[ord[semi[a]]].emplace_back(a);
            for (auto &&b : tmp[par[a]]) U[b] = eval(b);
            tmp[par[a]].clear();
            unite(par[a], a);
        }
        for (int i = 1; i < n; ++i) {
            int a = ord[i], b = U[a];
            if(semi[a] == semi[b]) idom[a] = semi[a];
            else idom[a] = idom[b];
        }
        for (int i = 1; i < n; ++i) {
            int a = ord[i];
            idom[a] = ord[idom[a]];
        }
        idom[root] = -1;
    }

};
