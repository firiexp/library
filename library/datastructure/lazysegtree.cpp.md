---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: datastructure/lazysegtree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/lazysegtree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class M>
struct LazySegmentTree{
    using T = typename M::T;
    using L = typename M::L;
    int sz, height{};
    vector<T> seg; vector<L> lazy;
    explicit LazySegmentTree(int n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        seg.assign(2*sz, M::e());
        lazy.assign(2*sz, M::l());
    }

    void set(int k, const T &x){ 
        seg[k + sz] = x; 
    }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);
    }

    T reflect(int k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k], lazy[k]); }

    void eval(int k){
        if(lazy[k] == M::l()) return;
        lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);
        lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);
        seg[k] = reflect(k);
        lazy[k] = M::l();
    }
    void thrust(int k){ for (int i = height; i; --i) eval(k>>i); }
    void recalc(int k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}
    void update(int a, int b, const L &x){
        thrust(a += sz); thrust(b += sz-1);
        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {
            if(l&1) lazy[l] = M::h(lazy[l], x), l++;
            if(r&1) --r, lazy[r] = M::h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }

    T query(int a, int b){ // [l, r)
        thrust(a += sz);
        thrust(b += sz-1);
        T ll = M::e(), rr = M::e();
        for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {
            if (l & 1) ll = M::f(ll, reflect(l++));
            if (r & 1) rr = M::f(reflect(--r), rr);
        }
        return M::f(ll, rr);
    }
};

struct Monoid{
    using T = ll;
    using L = ll;
    static T f(T a, T b) { return min(a, b); }
    static T g(T a, L b) {
        if(b == e()) return a; else return b;
    }
    static L h(L a, L b) {
        if(b == e()) return a; else return b;
    }
    static T e() { return 0; }
    static L l() { return 0; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/lazysegtree.cpp"
template <class M>
struct LazySegmentTree{
    using T = typename M::T;
    using L = typename M::L;
    int sz, height{};
    vector<T> seg; vector<L> lazy;
    explicit LazySegmentTree(int n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        seg.assign(2*sz, M::e());
        lazy.assign(2*sz, M::l());
    }

    void set(int k, const T &x){ 
        seg[k + sz] = x; 
    }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);
    }

    T reflect(int k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k], lazy[k]); }

    void eval(int k){
        if(lazy[k] == M::l()) return;
        lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);
        lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);
        seg[k] = reflect(k);
        lazy[k] = M::l();
    }
    void thrust(int k){ for (int i = height; i; --i) eval(k>>i); }
    void recalc(int k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}
    void update(int a, int b, const L &x){
        thrust(a += sz); thrust(b += sz-1);
        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {
            if(l&1) lazy[l] = M::h(lazy[l], x), l++;
            if(r&1) --r, lazy[r] = M::h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }

    T query(int a, int b){ // [l, r)
        thrust(a += sz);
        thrust(b += sz-1);
        T ll = M::e(), rr = M::e();
        for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {
            if (l & 1) ll = M::f(ll, reflect(l++));
            if (r & 1) rr = M::f(reflect(--r), rr);
        }
        return M::f(ll, rr);
    }
};

struct Monoid{
    using T = ll;
    using L = ll;
    static T f(T a, T b) { return min(a, b); }
    static T g(T a, L b) {
        if(b == e()) return a; else return b;
    }
    static L h(L a, L b) {
        if(b == e()) return a; else return b;
    }
    static T e() { return 0; }
    static L l() { return 0; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

