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
        return root == -1 ? 0 : nodes[root].sz;
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
        int v = new_node(x);
        root = insert_node(root, k, v);
    }

    void push_front(const T &x) {
        insert(0, x);
    }

    void push_back(const T &x) {
        insert(size(), x);
    }

    T erase(int k) {
        return erase_node(root, k);
    }

    T pop_front() {
        return erase(0);
    }

    T pop_back() {
        return erase(size() - 1);
    }

    T get(int k) {
        int v = root;
        while (true) {
            push(v);
            int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
            if (k == left_size) return nodes[v].val;
            if (k < left_size) v = nodes[v].l;
            else {
                k -= left_size + 1;
                v = nodes[v].r;
            }
        }
    }

    vector<T> to_vector() {
        vector<T> result;
        result.reserve(size());
        vector<int> stack;
        int v = root;
        while (v != -1 || !stack.empty()) {
            while (v != -1) {
                push(v);
                stack.push_back(v);
                v = nodes[v].l;
            }
            v = stack.back();
            stack.pop_back();
            result.push_back(nodes[v].val);
            v = nodes[v].r;
        }
        return result;
    }

    void set(int k, const T &x) {
        set_node(root, k, x);
    }

    void apply(int l, int r, const L &x) {
        apply_range(root, l, r, x);
    }

    void reverse(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        toggle(b);
        root = merge(merge(a, b), c);
    }

    T fold(int l, int r) {
        return fold_node(root, l, r);
    }

    template<class F>
    int search_right(int l, F cond) {
        if (l == size()) return l;
        T val = M::e();
        return search_right_node(root, l, val, cond);
    }

    template<class F>
    int search_left(int r, F cond) {
        if (r == 0) return 0;
        T val = M::e();
        return search_left_node(root, r, val, cond);
    }

private:
    int insert_node(int v, int k, int x) {
        if (v == -1) return x;
        if (nodes[x].pri < nodes[v].pri) {
            auto [a, b] = split(v, k);
            nodes[x].l = a;
            nodes[x].r = b;
            pull(x);
            return x;
        }
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (k <= left_size) nodes[v].l = insert_node(nodes[v].l, k, x);
        else nodes[v].r = insert_node(nodes[v].r, k - left_size - 1, x);
        pull(v);
        return v;
    }

    T erase_node(int &v, int k) {
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (k == left_size) {
            int x = v;
            T res = nodes[x].val;
            v = merge(nodes[x].l, nodes[x].r);
            recycle_node(x);
            return res;
        }
        T res = k < left_size ? erase_node(nodes[v].l, k) : erase_node(nodes[v].r, k - left_size - 1);
        pull(v);
        return res;
    }

    template<class F>
    int search_right_node(int v, int l, T &val, F &cond) {
        if (v == -1) return 0;
        if (l == 0) {
            T next = M::f(val, nodes[v].sum);
            if (cond(next)) {
                val = move(next);
                return nodes[v].sz;
            }
        }
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (l < left_size) {
            int r = search_right_node(nodes[v].l, l, val, cond);
            if (r < left_size) return r;
        }
        if (l <= left_size) {
            T next = M::f(val, nodes[v].val);
            if (!cond(next)) return left_size;
            val = move(next);
        }
        return left_size + 1 + search_right_node(nodes[v].r, max(0, l - left_size - 1), val, cond);
    }

    template<class F>
    int search_left_node(int v, int r, T &val, F &cond) {
        if (v == -1) return 0;
        if (r == nodes[v].sz) {
            T next = M::f(nodes[v].sum, val);
            if (cond(next)) {
                val = move(next);
                return 0;
            }
        }
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (left_size + 1 < r) {
            int l = search_left_node(nodes[v].r, r - left_size - 1, val, cond);
            if (l > 0) return left_size + 1 + l;
        }
        if (left_size < r) {
            T next = M::f(nodes[v].val, val);
            if (!cond(next)) return left_size + 1;
            val = move(next);
        }
        return search_left_node(nodes[v].l, min(r, left_size), val, cond);
    }

    void apply_range(int v, int l, int r, const L &x) {
        if (l == r) return;
        if (l == 0 && r == nodes[v].sz) {
            apply_node(v, x);
            return;
        }
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (l < left_size) apply_range(nodes[v].l, l, min(r, left_size), x);
        if (l <= left_size && left_size < r) nodes[v].val = M::g(nodes[v].val, x);
        if (left_size + 1 < r) {
            apply_range(nodes[v].r, max(0, l - left_size - 1), r - left_size - 1, x);
        }
        pull(v);
    }

    void set_node(int v, int k, const T &x) {
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (k < left_size) set_node(nodes[v].l, k, x);
        else if (k == left_size) nodes[v].val = x;
        else set_node(nodes[v].r, k - left_size - 1, x);
        pull(v);
    }

    T fold_node(int v, int l, int r) {
        if (l == r) return M::e();
        if (l == 0 && r == nodes[v].sz) return nodes[v].sum;
        push(v);
        int left_size = nodes[v].l == -1 ? 0 : nodes[nodes[v].l].sz;
        if (r <= left_size) return fold_node(nodes[v].l, l, r);
        if (left_size < l) return fold_node(nodes[v].r, l - left_size - 1, r - left_size - 1);
        T res = nodes[v].val;
        if (l < left_size) res = M::f(fold_node(nodes[v].l, l, left_size), res);
        if (left_size + 1 < r) res = M::f(res, fold_node(nodes[v].r, 0, r - left_size - 1));
        return res;
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
        Node &node = nodes[x];
        node.val = M::g(node.val, lazy);
        node.sum = M::g(node.sum, lazy);
        node.rsum = M::g(node.rsum, lazy);
        if (node.has_lazy) node.lazy = M::h(node.lazy, lazy);
        else {
            node.lazy = lazy;
            node.has_lazy = true;
        }
    }

    void toggle(int x) {
        if (x == -1) return;
        Node &node = nodes[x];
        swap(node.l, node.r);
        swap(node.sum, node.rsum);
        node.rev ^= 1;
    }

    void push(int x) {
        if (x == -1) return;
        Node &node = nodes[x];
        if (node.rev) {
            toggle(node.l);
            toggle(node.r);
            node.rev = false;
        }
        if (node.has_lazy) {
            apply_node(node.l, node.lazy);
            apply_node(node.r, node.lazy);
            node.has_lazy = false;
        }
    }

    void pull(int x) {
        Node &node = nodes[x];
        node.sz = 1;
        node.sum = node.val;
        node.rsum = node.val;
        if (node.l != -1) {
            const Node &left = nodes[node.l];
            node.sz += left.sz;
            node.sum = M::f(left.sum, node.sum);
            node.rsum = M::f(node.rsum, left.rsum);
        }
        if (node.r != -1) {
            const Node &right = nodes[node.r];
            node.sz += right.sz;
            node.sum = M::f(node.sum, right.sum);
            node.rsum = M::f(right.rsum, node.rsum);
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
        int left_size = nodes[x].l == -1 ? 0 : nodes[nodes[x].l].sz;
        if (k <= left_size) {
            auto [a, b] = split(nodes[x].l, k);
            nodes[x].l = b;
            pull(x);
            return {a, x};
        }
        auto [a, b] = split(nodes[x].r, k - left_size - 1);
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
