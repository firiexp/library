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
    - Last commit date: 2020-09-09 19:12:23+09:00




## Depends on

* :warning: <a href="extgcd.cpp.html">math/extgcd.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "extgcd.cpp"

pair<ll, ll> CRT(const vector<pair<ll, ll>> &a){
    ll R = 0, M = 1;
    for (auto &&i : a) {
        ll r = (i.first+i.second)%i.second, m = i.second;
        if(m < M) swap(r, R), swap(m, M);
        if(M%m == 0){
            if(R % m != r) return {};
            continue;
        }
        ll p, q;
        ll g = extgcd(M, m, p, q); // p = inv(M') mod m'
        ll mm = m/g;
        ll x = (r-R)/g % mm * p % mm;
        R += x*M;
        M *= mm;
        if(R < 0) R += M;
    }
    return {R, M};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/extgcd.cpp"
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
 
#line 2 "math/CRT.cpp"

pair<ll, ll> CRT(const vector<pair<ll, ll>> &a){
    ll R = 0, M = 1;
    for (auto &&i : a) {
        ll r = (i.first+i.second)%i.second, m = i.second;
        if(m < M) swap(r, R), swap(m, M);
        if(M%m == 0){
            if(R % m != r) return {};
            continue;
        }
        ll p, q;
        ll g = extgcd(M, m, p, q); // p = inv(M') mod m'
        ll mm = m/g;
        ll x = (r-R)/g % mm * p % mm;
        R += x*M;
        M *= mm;
        if(R < 0) R += M;
    }
    return {R, M};
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

