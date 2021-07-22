
class HeavyLightDecomposition {
    void dfs_sz(int v){
        for (auto &&u : G[v]) {
            if(u == par[v]) continue;
            par[u] = v; dep[u] = dep[v] + 1;
            dfs_sz(u);
            sub_size[v] += sub_size[u];
            if(sub_size[u] > sub_size[G[v][0]]) swap(u, G[v][0]);
        }
    }
    void dfs_hld(int v, int c, int &pos){
        id[v] = pos++;
        id_inv[id[v]]= v;
        tree_id[v] = c;
        for (auto &&u : G[v]) {
            if(u == par[v]) continue;
            head[u] = (u == G[v][0] ? head[v] : u);
            dfs_hld(u, c, pos);
        }
    }
public:
    int n;
    vector<vector<int>> G;
    vector<int> par, dep, sub_size, id, id_inv, tree_id, head;
    explicit HeavyLightDecomposition(int n) : n(n), G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n){}
    explicit HeavyLightDecomposition(vector<vector<int>> &G) :G(G), n(G.size()), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n) {}

    void add_edge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void build(vector<int> roots = {0}){
        int c = 0, pos = 0;
        for (auto &&i : roots) {
            dfs_sz(i);
            head[i] = i;
            dfs_hld(i, c++, pos);
        }
    }

    int lca(int u, int v){
        while(true){
            if(id[u] > id[v]) swap(u, v);
            if(head[u] == head[v]) return u;
            v = par[head[v]];
        }
    }

    int distance(int u, int v){ return dep[u] + dep[v] - 2*dep[lca(u, v)]; }

    template<typename F>
    void add(int u, int v, const F &f, bool edge){
        while (head[u] != head[v]){
            if(id[u] > id[v]) swap(u, v);
            f(id[head[v]], id[v]+1);
            v = par[head[v]];
        }
        if(id[u] > id[v]) swap(u, v);
        f(id[u]+edge, id[v]+1);
    }

    template<typename T, typename Q, typename F>
    T query(int u, int v, const T &e, const Q &q, const F &f, bool edge){
        T l = e, r = e;
        while(head[u] != head[v]){
            if(id[u] > id[v]) swap(u, v), swap(l, r);
            l = f(l, q(id[head[v]], id[v]+1));
            v = par[head[v]];
        }
        if(id[u] > id[v]) swap(u, v), swap(l, r);
        return f(q(id[u]+edge, id[v]+1), f(l, r));
    }

    template<typename T, typename QL, typename QR, typename F>
    T query_order(int u, int v, const T &e, const QL &ql, const QR &qr, const F &f, bool edge){
        T l = e, r = e;
        while(head[u] != head[v]){
            if(id[u] > id[v]) {
                l = f(l, qr(id[head[u]], id[u]+1));
                u = par[head[u]];
            }else {
                r = f(ql(id[head[v]], id[v]+1), r);
                v = par[head[v]];
            }
        }
        T mid = (id[u] > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));
        return f(f(l, mid), r);
    }
};