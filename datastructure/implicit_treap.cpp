template <class M>
struct ImplicitTreap {
    using T = typename M::T;
    using L = typename M::L;

    struct Node {
        int l, r, sz;
        unsigned pri;
        bool rev, has_lazy;
        T val, sum, rsum;
        L lazy;

        Node(unsigned pri, const T &val)
            : l(-1), r(-1), sz(1), pri(pri), rev(false), has_lazy(false),
              val(val), sum(val), rsum(val), lazy(M::l()) {}
    };

    int root;
    vector<Node> nodes;
    vector<int> free_nodes;
    unsigned long long rng_state;

    ImplicitTreap() : root(-1), rng_state(0x123456789abcdef0ull) {}

    explicit ImplicitTreap(const vector<T> &v) : ImplicitTreap() {
        reserve((int)v.size());
        build_linear(v);
    }

    int size() const {
        return subtree_size(root);
    }

    bool empty() const {
        return root == -1;
    }

    void reserve(int capacity) {
        nodes.reserve(capacity);
        free_nodes.reserve(capacity);
    }

    T all_fold() const {
        return root == -1 ? M::e() : nodes[root].sum;
    }

    void insert(int k, const T &x) {
        auto [a, b] = split(root, k);
        root = merge(merge(a, new_node(x)), b);
    }

    void push_front(const T &x) {
        insert(0, x);
    }

    void push_back(const T &x) {
        insert(size(), x);
    }

    T erase(int k) {
        auto [a, bc] = split(root, k);
        auto [b, c] = split(bc, 1);
        T res = nodes[b].val;
        recycle_node(b);
        root = merge(a, c);
        return res;
    }

    T pop_front() {
        return erase(0);
    }

    T pop_back() {
        return erase(size() - 1);
    }

    T get(int k) {
        auto [a, bc] = split(root, k);
        auto [b, c] = split(bc, 1);
        T res = nodes[b].val;
        root = merge(merge(a, b), c);
        return res;
    }

    void set(int k, const T &x) {
        auto [a, bc] = split(root, k);
        auto [b, c] = split(bc, 1);
        nodes[b].val = x;
        nodes[b].sum = x;
        nodes[b].rsum = x;
        nodes[b].rev = false;
        nodes[b].has_lazy = false;
        nodes[b].lazy = M::l();
        pull(b);
        root = merge(merge(a, b), c);
    }

    void apply(int l, int r, const L &x) {
        auto [a, b, c] = split3(root, l, r);
        apply_node(b, x);
        root = merge(merge(a, b), c);
    }

    void reverse(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        toggle(b);
        root = merge(merge(a, b), c);
    }

    T fold(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        T res = b == -1 ? M::e() : nodes[b].sum;
        root = merge(merge(a, b), c);
        return res;
    }

private:
    int subtree_size(int x) const {
        return x == -1 ? 0 : nodes[x].sz;
    }

    unsigned next_rand() {
        rng_state ^= rng_state << 7;
        rng_state ^= rng_state >> 9;
        return static_cast<unsigned>(rng_state);
    }

    int new_node(const T &x) {
        unsigned pri = next_rand();
        if (!free_nodes.empty()) {
            int idx = free_nodes.back();
            free_nodes.pop_back();
            nodes[idx] = Node(pri, x);
            return idx;
        }
        nodes.emplace_back(pri, x);
        return (int)nodes.size() - 1;
    }

    void recycle_node(int x) {
        if (x != -1) free_nodes.push_back(x);
    }

    void build_linear(const vector<T> &v) {
        if (v.empty()) return;
        vector<int> ids(v.size());
        for (int i = 0; i < (int)v.size(); ++i) ids[i] = new_node(v[i]);

        vector<int> st;
        st.reserve(v.size());
        for (int cur : ids) {
            int last = -1;
            while (!st.empty() && nodes[st.back()].pri > nodes[cur].pri) {
                last = st.back();
                st.pop_back();
            }
            nodes[cur].l = last;
            if (!st.empty()) nodes[st.back()].r = cur;
            st.push_back(cur);
        }
        root = st.front();

        vector<int> ord;
        ord.reserve(v.size());
        st.assign(1, root);
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            ord.push_back(x);
            if (nodes[x].l != -1) st.push_back(nodes[x].l);
            if (nodes[x].r != -1) st.push_back(nodes[x].r);
        }
        for (int i = (int)ord.size() - 1; i >= 0; --i) pull(ord[i]);
    }

    void apply_node(int x, const L &lazy) {
        if (x == -1) return;
        nodes[x].val = M::g(nodes[x].val, lazy);
        nodes[x].sum = M::g(nodes[x].sum, lazy);
        nodes[x].rsum = M::g(nodes[x].rsum, lazy);
        if (nodes[x].has_lazy) nodes[x].lazy = M::h(nodes[x].lazy, lazy);
        else {
            nodes[x].lazy = lazy;
            nodes[x].has_lazy = true;
        }
    }

    void toggle(int x) {
        if (x == -1) return;
        swap(nodes[x].l, nodes[x].r);
        swap(nodes[x].sum, nodes[x].rsum);
        nodes[x].rev ^= 1;
    }

    void push(int x) {
        if (x == -1) return;
        if (nodes[x].rev) {
            toggle(nodes[x].l);
            toggle(nodes[x].r);
            nodes[x].rev = false;
        }
        if (nodes[x].has_lazy) {
            apply_node(nodes[x].l, nodes[x].lazy);
            apply_node(nodes[x].r, nodes[x].lazy);
            nodes[x].has_lazy = false;
            nodes[x].lazy = M::l();
        }
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

    int merge(int a, int b) {
        if (a == -1 || b == -1) return a == -1 ? b : a;
        if (nodes[a].pri < nodes[b].pri) {
            push(a);
            nodes[a].r = merge(nodes[a].r, b);
            pull(a);
            return a;
        }
        push(b);
        nodes[b].l = merge(a, nodes[b].l);
        pull(b);
        return b;
    }

    pair<int, int> split(int x, int k) {
        if (x == -1) return {-1, -1};
        push(x);
        if (k <= subtree_size(nodes[x].l)) {
            auto [a, b] = split(nodes[x].l, k);
            nodes[x].l = b;
            pull(x);
            return {a, x};
        }
        auto [a, b] = split(nodes[x].r, k - subtree_size(nodes[x].l) - 1);
        nodes[x].r = a;
        pull(x);
        return {x, b};
    }

    tuple<int, int, int> split3(int x, int l, int r) {
        auto [a, bc] = split(x, l);
        auto [b, c] = split(bc, r - l);
        return {a, b, c};
    }
};

/**
 * @brief Implicit Treap
 */
