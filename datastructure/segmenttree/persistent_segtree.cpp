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
        node.push_back({M::e(), 0, 0});
        root.push_back(0);
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

    T get(int t, int k) const {
        if(n == 0) return M::e();
        int id = root[t], l = 0, r = n;
        while(r-l > 1){
            int m = l + ((r-l)>>1);
            if(k < m){
                id = node[id].l;
                r = m;
            }else{
                id = node[id].r;
                l = m;
            }
        }
        return node[id].val;
    }
    T operator[](const int &k) const { return get(latest_version(), k); }

    template<class F>
    int search_right(int t, int l, F cond) const {
        T acc = M::e();
        return search_right_(root[t], l, 0, n, acc, cond);
    }
    template<class F>
    int search_right(int l, F cond) const {
        return search_right(latest_version(), l, move(cond));
    }

    template<class F>
    int search_left(int t, int r, F cond) const {
        T acc = M::e();
        return search_left_(root[t], r, 0, n, acc, cond);
    }
    template<class F>
    int search_left(int r, F cond) const {
        return search_left(latest_version(), r, move(cond));
    }

private:
    template<class F>
    int search_right_(int id, int a, int l, int r, T &acc, F &cond) const {
        if(r <= a) return n;
        if(a <= l){
            T next = M::f(acc, node[id].val);
            if(cond(next)){
                acc = move(next);
                return n;
            }
            if(r-l == 1) return l;
        }
        int m = l + ((r-l)>>1);
        int result = search_right_(node[id].l, a, l, m, acc, cond);
        if(result != n) return result;
        return search_right_(node[id].r, a, m, r, acc, cond);
    }

    template<class F>
    int search_left_(int id, int a, int l, int r, T &acc, F &cond) const {
        if(a <= l) return 0;
        if(r <= a){
            T next = M::f(node[id].val, acc);
            if(cond(next)){
                acc = move(next);
                return 0;
            }
            if(r-l == 1) return r;
        }
        int m = l + ((r-l)>>1);
        int result = search_left_(node[id].r, a, m, r, acc, cond);
        if(result != 0) return result;
        return search_left_(node[id].l, a, l, m, acc, cond);
    }

    int make_node(const T &v, int l, int r){
        node.push_back({v, l, r});
        return node.size()-1;
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
 */
