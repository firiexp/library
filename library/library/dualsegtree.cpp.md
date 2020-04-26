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


# :warning: library/dualsegtree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/dualsegtree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

struct Monoid{
    using T = ll;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/dualsegtree.cpp"
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

struct Monoid{
    using T = ll;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

