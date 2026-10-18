#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_PERSISTENT_LAZY_SEGTREE_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_PERSISTENT_LAZY_SEGTREE_CPP

template<class M>
struct PersistentLazySegmentTree {
    using T = typename M::T;
    using L = typename M::L;

    struct Node {
        T val;
        L lazy;
        int left, right;
        bool has_lazy;
    };

    int n;
    vector<Node> node;
    vector<int> root;

    explicit PersistentLazySegmentTree(const vector<T> &values) : n(values.size()) {
        if (n) node.reserve(2 * (size_t)n - 1);
        root.push_back(n ? build(0, n, values) : -1);
    }

    int versions() const { return root.size(); }
    int latest_version() const { return versions() - 1; }

    int update(int t, int l, int r, const L &op) {
        assert(0 <= t && t < versions() && 0 <= l && l <= r && r <= n);
        int id = root[t];
        if (l < r) id = update_node(id, l, r, 0, n, op, M::l(), false);
        root.push_back(id);
        return latest_version();
    }

    int copy_range(int dst, int src, int l, int r) {
        assert(0 <= dst && dst < versions() && 0 <= src && src < versions());
        assert(0 <= l && l <= r && r <= n);
        int id = root[dst];
        if (l < r && root[dst] != root[src]) {
            id = copy_node(root[dst], root[src], l, r, 0, n, M::l(), false, M::l(), false);
        }
        root.push_back(id);
        return latest_version();
    }

    T query(int t, int l, int r) const {
        assert(0 <= t && t < versions() && 0 <= l && l <= r && r <= n);
        if (l == r) return M::e();
        return query_node(root[t], l, r, 0, n, M::l(), false);
    }

private:
    int make_parent(int left, int right) {
        node.push_back({M::f(node[left].val, node[right].val), M::l(), left, right, false});
        return node.size() - 1;
    }

    int build(int l, int r, const vector<T> &values) {
        if (r - l == 1) {
            node.push_back({values[l], M::l(), -1, -1, false});
            return node.size() - 1;
        }
        int mid = l + (r - l) / 2;
        int left = build(l, mid, values), right = build(mid, r, values);
        return make_parent(left, right);
    }

    int apply_copy(int id, const L &op) {
        Node copy = node[id];
        copy.val = M::g(copy.val, op);
        copy.lazy = copy.has_lazy ? M::h(copy.lazy, op) : op;
        copy.has_lazy = true;
        node.push_back(std::move(copy));
        return node.size() - 1;
    }

    pair<L, bool> descend(int id, const L &carry, bool has_carry) const {
        if (!has_carry) return {node[id].lazy, node[id].has_lazy};
        return {node[id].has_lazy ? M::h(node[id].lazy, carry) : carry, true};
    }

    int update_node(int id, int a, int b, int l, int r, const L &op, const L &carry, bool has_carry) {
        if (b <= l || r <= a) return has_carry ? apply_copy(id, carry) : id;
        if (a <= l && r <= b) return apply_copy(id, has_carry ? M::h(carry, op) : op);
        auto [next, has_next] = descend(id, carry, has_carry);
        int left = node[id].left, right = node[id].right, mid = l + (r - l) / 2;
        left = update_node(left, a, b, l, mid, op, next, has_next);
        right = update_node(right, a, b, mid, r, op, next, has_next);
        return make_parent(left, right);
    }

    int copy_node(int dst, int src, int a, int b, int l, int r,
                  const L &dst_carry, bool has_dst, const L &src_carry, bool has_src) {
        if (b <= l || r <= a) return has_dst ? apply_copy(dst, dst_carry) : dst;
        if (a <= l && r <= b) return has_src ? apply_copy(src, src_carry) : src;
        auto [dst_next, dst_has_next] = descend(dst, dst_carry, has_dst);
        auto [src_next, src_has_next] = descend(src, src_carry, has_src);
        int dl = node[dst].left, dr = node[dst].right;
        int sl = node[src].left, sr = node[src].right, mid = l + (r - l) / 2;
        int left = copy_node(dl, sl, a, b, l, mid, dst_next, dst_has_next, src_next, src_has_next);
        int right = copy_node(dr, sr, a, b, mid, r, dst_next, dst_has_next, src_next, src_has_next);
        return make_parent(left, right);
    }

    T query_node(int id, int a, int b, int l, int r, const L &carry, bool has_carry) const {
        if (b <= l || r <= a) return M::e();
        if (a <= l && r <= b) return has_carry ? M::g(node[id].val, carry) : node[id].val;
        auto [next, has_next] = descend(id, carry, has_carry);
        int mid = l + (r - l) / 2;
        return M::f(query_node(node[id].left, a, b, l, mid, next, has_next),
                    query_node(node[id].right, a, b, mid, r, next, has_next));
    }
};

#endif

/**
 * @brief 区間更新・区間コピー付き永続セグメント木
 */
