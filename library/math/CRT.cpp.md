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


# :warning: math/CRT.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/CRT.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




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

pair<ll, ll> CRT(const vector<pair<ll, ll>> &a){
    ll r = 0, M = 1;
    for (int i = 0; i < a.size(); ++i) {
        ll p, q;
        ll d = extgcd(M, a[i].second, p, q);
        if((a[i].first - r )%d != 0) return make_pair(0, -1);
        ll tmp = (a[i].first - r) / d * p % (a[i].second / d);
        r += M * tmp;
        M *= a[i].second/d;
    }
    return make_pair((r+M) % M, M);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/CRT.cpp"
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

pair<ll, ll> CRT(const vector<pair<ll, ll>> &a){
    ll r = 0, M = 1;
    for (int i = 0; i < a.size(); ++i) {
        ll p, q;
        ll d = extgcd(M, a[i].second, p, q);
        if((a[i].first - r )%d != 0) return make_pair(0, -1);
        ll tmp = (a[i].first - r) / d * p % (a[i].second / d);
        r += M * tmp;
        M *= a[i].second/d;
    }
    return make_pair((r+M) % M, M);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

