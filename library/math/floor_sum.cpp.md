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


# :heavy_check_mark: math/floor_sum.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/floor_sum.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 21:30:52+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo_sum_of_floor_of_linear.test.cpp.html">test/yosupo_sum_of_floor_of_linear.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
ll floor_sum(ll n, ll m, ll a, ll b){
    ll ans = 0;
    if(a >= m) {
        ans += (n-1)*n/2*(a/m);
        a %= m;
    }
    if (b >= m){
        ans += n*(b/m);
        b %= m;
    }
    ll y = (a*n+b)/m, x = (y*m - b);
    if(!y) return ans;
    ans += (n-(x+a-1)/a)*y;
    ans += floor_sum(y, a, m, (a - x%a)%a);
    return ans;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/floor_sum.cpp"
ll floor_sum(ll n, ll m, ll a, ll b){
    ll ans = 0;
    if(a >= m) {
        ans += (n-1)*n/2*(a/m);
        a %= m;
    }
    if (b >= m){
        ans += n*(b/m);
        b %= m;
    }
    ll y = (a*n+b)/m, x = (y*m - b);
    if(!y) return ans;
    ans += (n-(x+a-1)/a)*y;
    ans += floor_sum(y, a, m, (a - x%a)%a);
    return ans;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

