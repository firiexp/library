template <class M>
struct DualSegmentTree{
    using T = typename M::T;
    int sz, height{};
    vector<T> lazy;
    explicit DualSegmentTree(int n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        lazy.assign(2*sz, M::e());
    }

    void eval(int k){
        if(lazy[k] == M::e()) return;
        lazy[(k<<1)|0] = M::f(lazy[(k<<1)|0], lazy[k]);
        lazy[(k<<1)|1] = M::f(lazy[(k<<1)|1], lazy[k]);
        lazy[k] = M::e();
    }
    void thrust(int k){ for (int i = height; i; --i) eval(k>>i); }
    void update(int a, int b, const T &x){
        thrust(a += sz); thrust(b += sz-1);
        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {
            if(l&1) lazy[l] = M::f(lazy[l], x), l++;
            if(r&1) --r, lazy[r] = M::f(lazy[r], x);
        }
    }

    T operator[](int k){
        thrust(k += sz);
        return lazy[k];
    }
};
/*
struct Monoid{
    using T = ll;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};
*/