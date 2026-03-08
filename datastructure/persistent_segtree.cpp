template <class M>
struct PersistentSegmentTree{
    using T = typename M::T;
    struct Node{
        T val;
        int l, r;
    };

    int n{};
    vector<Node> node;
    vector<int> root;

    explicit PersistentSegmentTree(int n): n(n){
        if(n == 0){
            node.push_back({M::e(), -1, -1});
            root.push_back(0);
        }else{
            root.push_back(build(0, n));
        }
    }
    explicit PersistentSegmentTree(const vector<T> &v): n(v.size()){
        if(n == 0){
            node.push_back({M::e(), -1, -1});
            root.push_back(0);
        }else{
            root.push_back(build(0, n, v));
        }
    }

    int latest_version() const { return root.size()-1; }
    int versions() const { return root.size(); }

    int update(int t, int k, const T &x){
        if(n == 0){
            root.push_back(root[t]);
            return latest_version();
        }
        root.push_back(update_(root[t], k, x, 0, n));
        return latest_version();
    }
    int update(int k, const T &x){ return update(latest_version(), k, x); }

    int add(int t, int k, const T &x){
        if(n == 0){
            root.push_back(root[t]);
            return latest_version();
        }
        root.push_back(add_(root[t], k, x, 0, n));
        return latest_version();
    }
    int add(int k, const T &x){ return add(latest_version(), k, x); }

    T query(int t, int a, int b) const {
        if(n == 0 || b <= a) return M::e();
        return query_(root[t], a, b, 0, n);
    }
    T query(int a, int b) const { return query(latest_version(), a, b); }

    T get(int t, int k) const { return query(t, k, k+1); }
    T operator[](const int &k) const { return get(latest_version(), k); }

private:
    int make_node(const T &v, int l, int r){
        node.push_back({v, l, r});
        return node.size()-1;
    }

    int build(int l, int r){
        if(l+1 == r) return make_node(M::e(), -1, -1);
        int m = (l+r)>>1;
        int ll = build(l, m), rr = build(m, r);
        return make_node(M::f(node[ll].val, node[rr].val), ll, rr);
    }
    int build(int l, int r, const vector<T> &v){
        if(l+1 == r) return make_node(v[l], -1, -1);
        int m = (l+r)>>1;
        int ll = build(l, m, v), rr = build(m, r, v);
        return make_node(M::f(node[ll].val, node[rr].val), ll, rr);
    }

    int update_(int id, int k, const T &x, int l, int r){
        if(l+1 == r) return make_node(x, -1, -1);
        int m = (l+r)>>1;
        int ll = node[id].l, rr = node[id].r;
        if(k < m) ll = update_(ll, k, x, l, m);
        else rr = update_(rr, k, x, m, r);
        return make_node(M::f(node[ll].val, node[rr].val), ll, rr);
    }

    int add_(int id, int k, const T &x, int l, int r){
        if(l+1 == r) return make_node(M::f(node[id].val, x), -1, -1);
        int m = (l+r)>>1;
        int ll = node[id].l, rr = node[id].r;
        if(k < m) ll = add_(ll, k, x, l, m);
        else rr = add_(rr, k, x, m, r);
        return make_node(M::f(node[ll].val, node[rr].val), ll, rr);
    }

    T query_(int id, int a, int b, int l, int r) const {
        if(r <= a || b <= l) return M::e();
        if(a <= l && r <= b) return node[id].val;
        int m = (l+r)>>1;
        return M::f(query_(node[id].l, a, b, l, m), query_(node[id].r, a, b, m, r));
    }
};

/*
struct Monoid{
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};
*/

/**
 * @brief 永続セグメント木(Persistent Segment Tree)
 * @docs _md/persistent_segtree.md
 */
