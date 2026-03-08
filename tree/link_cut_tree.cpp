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

    explicit LinkCutTree(int n) : n(n), nodes(n) {}

    bool is_root(int x) const {
        int p = nodes[x].p;
        return p == -1 || (nodes[p].l != x && nodes[p].r != x);
    }

    void reverse(int x) {
        if (x == -1) return;
        swap(nodes[x].l, nodes[x].r);
        swap(nodes[x].sum, nodes[x].rsum);
        nodes[x].rev ^= 1;
    }

    void push(int x) {
        if (x == -1 || !nodes[x].rev) return;
        reverse(nodes[x].l);
        reverse(nodes[x].r);
        nodes[x].rev = false;
    }

    void pull(int x) {
        nodes[x].sz = 1;
        nodes[x].sum = nodes[x].val;
        nodes[x].rsum = nodes[x].val;
        if (nodes[x].l != -1) {
            int y = nodes[x].l;
            nodes[x].sz += nodes[y].sz;
            nodes[x].sum = M::f(nodes[y].sum, nodes[x].sum);
            nodes[x].rsum = M::f(nodes[x].rsum, nodes[y].rsum);
        }
        if (nodes[x].r != -1) {
            int y = nodes[x].r;
            nodes[x].sz += nodes[y].sz;
            nodes[x].sum = M::f(nodes[x].sum, nodes[y].sum);
            nodes[x].rsum = M::f(nodes[y].rsum, nodes[x].rsum);
        }
    }

    void rotate(int x) {
        int p = nodes[x].p;
        int g = nodes[p].p;
        if (nodes[p].l == x) {
            int b = nodes[x].r;
            nodes[x].r = p;
            nodes[p].l = b;
            if (b != -1) nodes[b].p = p;
        } else {
            int b = nodes[x].l;
            nodes[x].l = p;
            nodes[p].r = b;
            if (b != -1) nodes[b].p = p;
        }
        nodes[p].p = x;
        nodes[x].p = g;
        if (g != -1) {
            if (nodes[g].l == p) nodes[g].l = x;
            if (nodes[g].r == p) nodes[g].r = x;
        }
        pull(p);
        pull(x);
    }

    void splay(int x) {
        vector<int> st(1, x);
        for (int y = x; !is_root(y); y = nodes[y].p) st.emplace_back(nodes[y].p);
        while (!st.empty()) {
            push(st.back());
            st.pop_back();
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
        push(x);
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
