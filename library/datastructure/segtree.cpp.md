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


# :warning: datastructure/segtree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/segtree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 21:46:13+09:00




## Required by

* :warning: <a href="../test/yosupo_point_set_range_composite.cpp.html">test/yosupo_point_set_range_composite.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class M>
struct SegmentTree{
    using T = typename M::T;
    int sz, n, height{};
    vector<T> seg;
    explicit SegmentTree(int n) {
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
        do {
            while(r&1) r >>= 1;
            if(!cond(M::f(val, seg[r]))){
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/segtree.cpp"
template <class M>
struct SegmentTree{
    using T = typename M::T;
    int sz, n, height{};
    vector<T> seg;
    explicit SegmentTree(int n) {
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
        do {
            while(r&1) r >>= 1;
            if(!cond(M::f(val, seg[r]))){
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

