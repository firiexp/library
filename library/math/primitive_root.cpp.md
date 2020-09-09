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


# :warning: math/primitive_root.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/primitive_root.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 00:00:31+09:00




## Depends on

* :warning: <a href="pow.cpp.html">math/pow.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "pow.cpp"
int primitive_root(int m) {
    if (m == 2) return 1;
    int divs[20] = {2};
    int cnt = 1;
    int x = (m-1)/2;
    while (x%2 == 0) x /= 2;
    for (ll i = 3; i*i <= x; i += 2) {
        if (x%i == 0) {
            divs[cnt++] = i;
            while (x%i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt && ok; i++) {
            ok |= pow_(g, (m-1)/divs[i], m) != 1;
        }
        if (ok) return g;
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/pow.cpp"
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
#line 2 "math/primitive_root.cpp"
int primitive_root(int m) {
    if (m == 2) return 1;
    int divs[20] = {2};
    int cnt = 1;
    int x = (m-1)/2;
    while (x%2 == 0) x /= 2;
    for (ll i = 3; i*i <= x; i += 2) {
        if (x%i == 0) {
            divs[cnt++] = i;
            while (x%i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt && ok; i++) {
            ok |= pow_(g, (m-1)/divs[i], m) != 1;
        }
        if (ok) return g;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

