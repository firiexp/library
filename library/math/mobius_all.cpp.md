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


# :warning: math/mobius_all.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/mobius_all.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<int> mobius_all(int M){
    vector<int> mobius(M), isprime(M);
    for (int i = 0; i < M; ++i) {
        mobius[i] = isprime[i] = 1;
    }
    for (int i = 2; i < M; ++i) {
        if(isprime[i]){
            for (int j = i; j < M; j += i) {
                mobius[j] = -mobius[j];
                isprime[j] = 0;
            }
            isprime[i] = 1;
            ll x = (ll)i*i;
            if(x <= M){
                for (int j = x; j < M; j += x) {
                    mobius[j] = 0;
                }
            }
        }
    }
    return mobius;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/mobius_all.cpp"
vector<int> mobius_all(int M){
    vector<int> mobius(M), isprime(M);
    for (int i = 0; i < M; ++i) {
        mobius[i] = isprime[i] = 1;
    }
    for (int i = 2; i < M; ++i) {
        if(isprime[i]){
            for (int j = i; j < M; j += i) {
                mobius[j] = -mobius[j];
                isprime[j] = 0;
            }
            isprime[i] = 1;
            ll x = (ll)i*i;
            if(x <= M){
                for (int j = x; j < M; j += x) {
                    mobius[j] = 0;
                }
            }
        }
    }
    return mobius;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
