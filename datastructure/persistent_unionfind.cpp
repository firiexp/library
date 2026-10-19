class PersistentUnionFind {
    struct Node {
        int val;
        int l;
        int r;
    };

    int n;
    vector<Node> node;
    vector<pair<int, int>> roots;

public:
    explicit PersistentUnionFind(int sz) : n(sz) {
        node.push_back({-1, 0, 0});
        roots.push_back({0, n});
    }

    int versions() const { return roots.size(); }
    int latest_version() const { return versions() - 1; }
    int count() const { return roots[latest_version()].second; }
    int count(int t) const { return roots[t].second; }

    int root(int t, int a) const {
        return root_with_size(t, a).first;
    }
    int root(int a) const { return root(latest_version(), a); }

    bool same(int t, int a, int b) const {
        return root(t, a) == root(t, b);
    }
    bool same(int a, int b) const { return same(latest_version(), a, b); }

    int size(int t, int a) const {
        return -root_with_size(t, a).second;
    }
    int size(int a) const { return size(latest_version(), a); }

    int copy_version(int t) {
        roots.push_back(roots[t]);
        return latest_version();
    }

    int unite(int t, int a, int b) {
        if (n == 0) {
            return copy_version(t);
        }
        int rt = roots[t].first;
        auto [ra, sa] = root_with_size(t, a);
        auto [rb, sb] = root_with_size(t, b);
        if (ra == rb) return copy_version(t);
        if (sa > sb) {
            swap(ra, rb);
            swap(sa, sb);
        }
        int nr = set_pair(rt, ra, sa + sb, rb, ra, 0, n);
        roots.push_back({nr, roots[t].second - 1});
        return latest_version();
    }
    int unite(int a, int b) { return unite(latest_version(), a, b); }

private:
    pair<int, int> root_with_size(int t, int a) const {
        while (true) {
            int p = get(roots[t].first, a, 0, n);
            if (p < 0) return {a, p};
            a = p;
        }
    }

    int make_node(int val, int l, int r) {
        node.push_back({val, l, r});
        return node.size() - 1;
    }

    int get(int id, int k, int l, int r) const {
        if (l + 1 == r) return node[id].val;
        int m = (l + r) >> 1;
        if (k < m) return get(node[id].l, k, l, m);
        return get(node[id].r, k, m, r);
    }

    int set(int id, int k, int val, int l, int r) {
        if (l + 1 == r) return make_node(val, -1, -1);
        int m = (l + r) >> 1;
        int nl = node[id].l;
        int nr = node[id].r;
        if (k < m) nl = set(nl, k, val, l, m);
        else nr = set(nr, k, val, m, r);
        return make_node(0, nl, nr);
    }

    int set_pair(int id, int a, int va, int b, int vb, int l, int r) {
        if (a > b) {
            swap(a, b);
            swap(va, vb);
        }
        int m = (l + r) >> 1;
        int nl = node[id].l;
        int nr = node[id].r;
        if (b < m) nl = set_pair(nl, a, va, b, vb, l, m);
        else if (a >= m) nr = set_pair(nr, a, va, b, vb, m, r);
        else {
            nl = set(nl, a, va, l, m);
            nr = set(nr, b, vb, m, r);
        }
        return make_node(0, nl, nr);
    }
};

/**
 * @brief 完全永続UnionFind(Fully Persistent Union Find)
 */
