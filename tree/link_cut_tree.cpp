template <class M>
struct LinkCutTree {
    using T = typename M::T;

    struct Node {
        int l, r, p, sz;
        bool rev;
        T val, sum, rsum;
        Node() : l(-1), r(-1), p(-1), sz(1), rev(false), val(M::e()), sum(M::e()), rsum(M::e()) {}
    };

    int n;
    vector<Node> nodes;
    vector<int> push_stack;

    explicit LinkCutTree(int n) : n(n), nodes(n), push_stack() {
        push_stack.reserve(64);
    }

    bool is_root(int x) const {
        int p = nodes[x].p;
        return p == -1 || (nodes[p].l != x && nodes[p].r != x);
    }

    void reverse(int x) {
        if (x == -1) return;
        Node &nx = nodes[x];
        swap(nx.l, nx.r);
        swap(nx.sum, nx.rsum);
        nx.rev ^= 1;
    }

    void push(int x) {
        if (x == -1 || !nodes[x].rev) return;
        reverse(nodes[x].l);
        reverse(nodes[x].r);
        nodes[x].rev = false;
    }

    void pull(int x) {
        Node &nx = nodes[x];
        nx.sz = 1;
        nx.sum = nx.val;
        nx.rsum = nx.val;
        if (nx.l != -1) {
            int y = nx.l;
            nx.sz += nodes[y].sz;
            nx.sum = M::f(nodes[y].sum, nx.sum);
            nx.rsum = M::f(nx.rsum, nodes[y].rsum);
        }
        if (nx.r != -1) {
            int y = nx.r;
            nx.sz += nodes[y].sz;
            nx.sum = M::f(nx.sum, nodes[y].sum);
            nx.rsum = M::f(nodes[y].rsum, nx.rsum);
        }
    }

    void rotate(int x) {
        Node &nx = nodes[x];
        int p = nx.p;
        Node &np = nodes[p];
        int g = np.p;
        if (np.l == x) {
            int b = nx.r;
            nx.r = p;
            np.l = b;
            if (b != -1) nodes[b].p = p;
        } else {
            int b = nx.l;
            nx.l = p;
            np.r = b;
            if (b != -1) nodes[b].p = p;
        }
        np.p = x;
        nx.p = g;
        if (g != -1) {
            Node &ng = nodes[g];
            if (ng.l == p) {
                ng.l = x;
            } else if (ng.r == p) {
                ng.r = x;
            }
        }
        pull(p);
        pull(x);
    }

    void splay(int x) {
        push_stack.clear();
        push_stack.emplace_back(x);
        for (int y = x; !is_root(y); y = nodes[y].p) push_stack.emplace_back(nodes[y].p);
        for (int i = (int)push_stack.size() - 1; i >= 0; --i) {
            push(push_stack[i]);
        }
        while (!is_root(x)) {
            int p = nodes[x].p;
            int g = nodes[p].p;
            if (!is_root(p)) {
                bool zigzig = (nodes[p].l == x) == (nodes[g].l == p);
                rotate(zigzig ? p : x);
            }
            rotate(x);
        }
    }

    int expose(int x) {
        int rp = -1;
        for (int cur = x; cur != -1; cur = nodes[cur].p) {
            splay(cur);
            nodes[cur].r = rp;
            pull(cur);
            rp = cur;
        }
        splay(x);
        return rp;
    }

    void evert(int x) {
        expose(x);
        reverse(x);
    }

    int get_root(int x) {
        expose(x);
        while (nodes[x].l != -1) {
            push(x);
            x = nodes[x].l;
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) {
        return get_root(u) == get_root(v);
    }

    bool link(int u, int v) {
        evert(u);
        if (get_root(v) == u) return false;
        expose(v);
        nodes[u].p = v;
        nodes[v].r = u;
        pull(v);
        return true;
    }

    bool cut(int u, int v) {
        evert(u);
        expose(v);
        if (nodes[v].l != u || nodes[u].r != -1) return false;
        nodes[v].l = -1;
        nodes[u].p = -1;
        pull(v);
        return true;
    }

    int lca(int u, int v) {
        if (!connected(u, v)) return -1;
        expose(u);
        return expose(v);
    }

    int parent(int x) {
        expose(x);
        if (nodes[x].l == -1) return -1;
        x = nodes[x].l;
        push(x);
        while (nodes[x].r != -1) {
            x = nodes[x].r;
            push(x);
        }
        splay(x);
        return x;
    }

    void set(int x, const T &val) {
        expose(x);
        nodes[x].val = val;
        pull(x);
    }

    T get(int x) {
        expose(x);
        return nodes[x].val;
    }

    T fold(int u, int v) {
        evert(u);
        expose(v);
        return nodes[v].sum;
    }

    int dist(int u, int v) {
        evert(u);
        expose(v);
        return nodes[v].sz - 1;
    }
};

/**
 * @brief Link-Cut Tree
 */
