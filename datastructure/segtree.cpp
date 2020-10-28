template <class M>
struct SegmentTree{
    using T = typename M::T;
    int sz, n, height{};
    vector<T> seg;
    explicit SegmentTree(int n) : n(n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        seg.assign(2*sz, M::e());
    }

    void set(int k, const T &x){ seg[k + sz] = x; }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);
    }

    void update(int k, const T &x){
        k += sz;
        seg[k] = x;
        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);
    }

    T query(int a, int b){
        T l = M::e(), r = M::e();
        for(a += sz, b += sz; a < b; a >>=1, b>>=1){
            if(a & 1) l = M::f(l, seg[a++]);
            if(b & 1) r = M::f(seg[--b], r);
        }
        return M::f(l, r);
    }

    template<class F>
    int search_right(int l, F cond){
        if(l == n) return n;
        T val = M::e();
        l += sz;
        do {
            while(!(l&1)) l >>= 1;
            if(!cond(M::f(val, seg[l]))){
                while(l < sz) {
                    l <<= 1;
                    if (cond(M::f(val, seg[l]))){
                        val = M::f(val, seg[l]);
                        l++;
                    }
                }
                return l - sz;
            }
            val = M::f(val, seg[l]);
            l++;
        } while((l & -l) != l);
        return n;
    }

    template<class F>
    int search_left(int r, F cond){
        if(r == 0) return 0;
        T val = M::e();
        r += sz;
        do {
            r--;
            while(r&1) r >>= 1;
            if(!cond(M::f(seg[r], val))){
                while(r < sz) {
                    r = ((r << 1)|1);
                    if (cond(M::f(seg[r], val))){
                        val = M::f(seg[r], val);
                        r--;
                    }
                }
                return r + 1 - sz;
            }
            val = M::f(seg[r], val);
        } while((r & -r) != r);
        return 0;
    }
    T operator[](const int &k) const { return seg[k + sz]; }
};


/*
struct Monoid{
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }
    static T e() { return {1, 0}; }
};
*/