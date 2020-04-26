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


# :warning: library/garner.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/garner.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T>
T pow_ (T x, T n, T M){
    uint64_t u = 1, xx = x;
    while (n > 0){
        if (n&1) u = u * xx % M;
        xx = xx * xx % M;
        n >>= 1;
    }
    return static_cast<T>(u);
};


template<typename T>
T extgcd(T a, T b, T &x ,T &y){
    for (T u = y = 1, v = x = 0; a; ) {
        ll q = b/a;
        swap(x -= q*u, u);
        swap(y -= q*v, v);
        swap(b -= q*a, a);
    }
    return b;
}

template<typename T>
T mod_inv(T x, T m){
    T s, t;
    extgcd(x, m, s, t);
    return (m+s)% m;
}

ll Garner(vector<pair<ll, ll>> a, ll mod){
    a.emplace_back(0, mod);
    vector<ll> A(a.size(), 1), B(a.size(), 0);
    for (int i = 0; i < a.size(); ++i) {
        ll t = (a[i].first+a[i].second-B[i])* mod_inv(A[i], a[i].second) % a[i].second;
        for (int j = i+1; j < a.size() ; ++j) {
            (B[j] += t * A[j]) %= a[j].second;
            (A[j] *= a[i].second) %= a[j].second;
        }
    }
    return B.back();
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/garner.cpp"
template <class T>
T pow_ (T x, T n, T M){
    uint64_t u = 1, xx = x;
    while (n > 0){
        if (n&1) u = u * xx % M;
        xx = xx * xx % M;
        n >>= 1;
    }
    return static_cast<T>(u);
};


template<typename T>
T extgcd(T a, T b, T &x ,T &y){
    for (T u = y = 1, v = x = 0; a; ) {
        ll q = b/a;
        swap(x -= q*u, u);
        swap(y -= q*v, v);
        swap(b -= q*a, a);
    }
    return b;
}

template<typename T>
T mod_inv(T x, T m){
    T s, t;
    extgcd(x, m, s, t);
    return (m+s)% m;
}

ll Garner(vector<pair<ll, ll>> a, ll mod){
    a.emplace_back(0, mod);
    vector<ll> A(a.size(), 1), B(a.size(), 0);
    for (int i = 0; i < a.size(); ++i) {
        ll t = (a[i].first+a[i].second-B[i])* mod_inv(A[i], a[i].second) % a[i].second;
        for (int j = i+1; j < a.size() ; ++j) {
            (B[j] += t * A[j]) %= a[j].second;
            (A[j] *= a[i].second) %= a[j].second;
        }
    }
    return B.back();
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

