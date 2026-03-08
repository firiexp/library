template <class M>
struct DynamicSegmentTree{
    using T = typename M::T;
    struct Node{
        T val;
        int l, r;
    };

    long long n{};
    vector<Node> node;
    int root;

    explicit DynamicSegmentTree(long long n): n(n), root(-1) {}

    void update(long long k, const T &x){
        if(n == 0) return;
        root = update_(root, k, x, 0, n);
    }

    void add(long long k, const T &x){
        if(n == 0) return;
        root = add_(root, k, x, 0, n);
    }

    T query(long long a, long long b) const {
        if(n == 0 || b <= a) return M::e();
        return query_(root, a, b, 0, n);
    }

    T get(long long k) const { return query(k, k+1); }
    T operator[](const long long &k) const { return get(k); }

private:
    int make_node(const T &v, int l, int r){
        node.push_back({v, l, r});
        return node.size()-1;
    }

    int update_(int id, long long k, const T &x, long long l, long long r){
        if(l+1 == r) return make_node(x, -1, -1);
        if(id == -1) id = make_node(M::e(), -1, -1);
        long long m = l + ((r-l)>>1);
        int ll = node[id].l, rr = node[id].r;
        if(k < m) ll = update_(ll, k, x, l, m);
        else rr = update_(rr, k, x, m, r);
        return make_node(M::f(value(ll), value(rr)), ll, rr);
    }

    int add_(int id, long long k, const T &x, long long l, long long r){
        if(l+1 == r) return make_node(M::f(value(id), x), -1, -1);
        if(id == -1) id = make_node(M::e(), -1, -1);
        long long m = l + ((r-l)>>1);
        int ll = node[id].l, rr = node[id].r;
        if(k < m) ll = add_(ll, k, x, l, m);
        else rr = add_(rr, k, x, m, r);
        return make_node(M::f(value(ll), value(rr)), ll, rr);
    }

    T query_(int id, long long a, long long b, long long l, long long r) const {
        if(id == -1 || r <= a || b <= l) return M::e();
        if(a <= l && r <= b) return node[id].val;
        long long m = l + ((r-l)>>1);
        return M::f(query_(node[id].l, a, b, l, m), query_(node[id].r, a, b, m, r));
    }

    T value(int id) const {
        return id == -1 ? M::e() : node[id].val;
    }
};

/*
struct Monoid{
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};
*/
