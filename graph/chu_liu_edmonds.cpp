template<class T>
struct ChuLiuEdmonds {
    struct Edge {
        int from, to;
        T cost;
    };

    struct Result {
        bool exists;
        T cost;
        vector<int> parent;
        vector<int> edge_id;
    };

    struct UnionFind {
        vector<int> p;

        explicit UnionFind(int n) : p(n, -1) {}

        int root(int x) {
            if (p[x] < 0) return x;
            return p[x] = root(p[x]);
        }

        bool unite(int a, int b) {
            a = root(a);
            b = root(b);
            if (a == b) return false;
            if (p[a] > p[b]) swap(a, b);
            p[a] += p[b];
            p[b] = a;
            return true;
        }
    };

    struct SkewHeapNode {
        T key, lazy;
        int idx;
        SkewHeapNode *l, *r;

        SkewHeapNode(T key, int idx) : key(key), lazy(0), idx(idx), l(nullptr), r(nullptr) {}
    };

    int n, root;
    vector<Edge> edges;

    explicit ChuLiuEdmonds(int n, int root) : n(n), root(root) {}

    int add_edge(int from, int to, T cost) {
        edges.push_back({from, to, cost});
        return (int)edges.size() - 1;
    }

    static void push(SkewHeapNode *node) {
        if (node == nullptr || node->lazy == T(0)) return;
        if (node->l != nullptr) {
            node->l->key += node->lazy;
            node->l->lazy += node->lazy;
        }
        if (node->r != nullptr) {
            node->r->key += node->lazy;
            node->r->lazy += node->lazy;
        }
        node->lazy = T(0);
    }

    static SkewHeapNode* meld(SkewHeapNode *a, SkewHeapNode *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (b->key < a->key) swap(a, b);
        push(a);
        a->r = meld(a->r, b);
        swap(a->l, a->r);
        return a;
    }

    static SkewHeapNode* pop(SkewHeapNode *a) {
        push(a);
        return meld(a->l, a->r);
    }

    Result solve() const {
        vector<SkewHeapNode> nodes;
        nodes.reserve(edges.size());
        vector<SkewHeapNode*> come(n, nullptr);
        for (int i = 0; i < (int)edges.size(); ++i) {
            nodes.emplace_back(edges[i].cost, i);
            come[edges[i].to] = meld(come[edges[i].to], &nodes.back());
        }

        UnionFind uf(n);
        vector<int> used(n, -1), from(n, -1), stem(n, -1);
        vector<T> from_cost(n, T(0));
        vector<int> parent_edge(edges.size(), -1), order;
        used[root] = root;
        T total = T(0);

        for (int start = 0; start < n; ++start) {
            if (used[start] != -1) continue;
            int cur = start;
            vector<int> child_edges;
            int cycle = 0;
            while (used[cur] == -1 || used[cur] == start) {
                used[cur] = start;
                while (come[cur] != nullptr && uf.root(edges[come[cur]->idx].from) == cur) {
                    come[cur] = pop(come[cur]);
                }
                if (come[cur] == nullptr) return {false, T(0), {}, {}};
                int idx = come[cur]->idx;
                int src = uf.root(edges[idx].from);
                T cost = come[cur]->key;
                come[cur] = pop(come[cur]);

                from[cur] = src;
                from_cost[cur] = cost;
                if (stem[cur] == -1) stem[cur] = idx;
                total += cost;
                order.push_back(idx);
                while (cycle) {
                    parent_edge[child_edges.back()] = idx;
                    child_edges.pop_back();
                    --cycle;
                }
                child_edges.push_back(idx);

                if (used[src] == start) {
                    int p = cur;
                    do {
                        if (come[p] != nullptr) {
                            come[p]->key -= from_cost[p];
                            come[p]->lazy -= from_cost[p];
                        }
                        if (p != cur) {
                            int pv = p;
                            int cv = cur;
                            uf.unite(pv, cv);
                            cur = uf.root(cv);
                            come[cur] = meld(come[pv], come[cv]);
                        }
                        p = uf.root(from[p]);
                        ++cycle;
                    } while (p != cur);
                } else {
                    cur = src;
                }
            }
        }

        vector<int> used_edge(edges.size(), 0), edge_id(n, -1), parent(n, -1);
        parent[root] = root;
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int idx = order[i];
            if (used_edge[idx]) continue;
            int v = edges[idx].to;
            edge_id[v] = idx;
            parent[v] = edges[idx].from;
            int x = stem[v];
            while (x != idx) {
                used_edge[x] = 1;
                x = parent_edge[x];
            }
        }
        return {true, total, parent, edge_id};
    }
};

/**
 * @brief 最小全域有向木(Chu-Liu/Edmonds)
 * @docs _md/chu_liu_edmonds.md
 */
