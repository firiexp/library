class DominatorTree {
    struct CSR {
        vector<int> start, elist;

        CSR() = default;

        CSR(int n, const vector<pair<int, int>> &edges, bool rev) : start(n + 1), elist(edges.size()) {
            for (auto &&[a, b] : edges) {
                ++start[(rev ? b : a) + 1];
            }
            for (int i = 0; i < n; ++i) start[i + 1] += start[i];
            auto counter = start;
            for (auto &&[a, b] : edges) {
                int from = rev ? b : a;
                int to = rev ? a : b;
                elist[counter[from]++] = to;
            }
        }
    };

    int n;
    vector<pair<int, int>> edges;
    vector<int> tin, tout;
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
public:
    DominatorTree(int n) : n(n), tin(n, -1), tout(n, -1), semi(n), ord(n), par(n), uf_par(n), m(n), U(n), idom(n), bucket_head(n), bucket_next(n) {}

    vector<int> semi, ord, par, uf_par, m, U, idom;
    vector<int> bucket_head, bucket_next;

    void add_edge(int a, int b){
        edges.emplace_back(a, b);
    }

    bool reachable(int v) const {
        return tin[v] != -1;
    }

    bool dominates(int u, int v) const {
        return reachable(u) && reachable(v) && tin[u] <= tin[v] && tin[v] < tout[u];
    }

    bool reachable_without_vertex(int target, int removed) const {
        return reachable(target) && !dominates(removed, target);
    }

    void build(int root){
        CSR G(n, edges, false), Grev(n, edges, true);
        for (int i = 0; i < n; ++i) {
            uf_par[i] = i;
            m[i] = i;
            semi[i] = -1;
            idom[i] = -1;
            par[i] = -1;
            bucket_head[i] = -1;
            bucket_next[i] = -1;
            tin[i] = tout[i] = -1;
        }
        int cur = 0;
        auto dfs = [&](auto &&self, int x) -> void {
            semi[x] = cur;
            ord[cur++] = x;
            for (int ei = G.start[x]; ei < G.start[x + 1]; ++ei) {
                int to = G.elist[ei];
                if(!~semi[to]){
                    par[to] = x;
                    self(self, to);
                }
            }
        };
        par[root] = root;
        dfs(dfs, root);
        for (int i = cur-1; i >= 0; --i) {
            int a = ord[i];
            for (int ei = Grev.start[a]; ei < Grev.start[a + 1]; ++ei) {
                int b = Grev.elist[ei];
                if(~semi[b]){
                    int c = eval(b);
                    semi[a] = min(semi[a], semi[c]);
                }
            }
            bucket_next[a] = bucket_head[ord[semi[a]]];
            bucket_head[ord[semi[a]]] = a;
            int p = par[a];
            for (int b = bucket_head[p]; b != -1; b = bucket_next[b]) {
                U[b] = eval(b);
            }
            bucket_head[p] = -1;
            unite(p, a);
        }
        for (int i = 1; i < cur; ++i) {
            int a = ord[i], b = U[a];
            if(semi[a] == semi[b]) idom[a] = semi[a];
            else idom[a] = idom[b];
        }
        for (int i = 1; i < cur; ++i) {
            int a = ord[i];
            idom[a] = ord[idom[a]];
        }
        idom[root] = -1;
        fill(bucket_head.begin(), bucket_head.end(), -1);
        for (int i = 1; i < cur; ++i) {
            int v = ord[i];
            bucket_next[v] = bucket_head[idom[v]];
            bucket_head[idom[v]] = v;
        }
        vector<int> stack;
        stack.reserve(cur);
        stack.push_back(root);
        int timer = 0;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            if (v < 0) {
                tout[~v] = timer;
                continue;
            }
            tin[v] = timer++;
            stack.push_back(~v);
            for (int to = bucket_head[v]; to != -1; to = bucket_next[to]) stack.push_back(to);
        }
    }

};


/**
 * @brief Dominator Tree
 */
