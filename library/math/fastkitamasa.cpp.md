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


# :warning: math/fastkitamasa.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/fastkitamasa.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class Fast_Kitamasa {
    poly c, b, ic;
    int k;
    int mod;
public:
    explicit Fast_Kitamasa(vector<int> &c, int mod) : c(c), mod(mod){
        k = static_cast<int>(c.size() - 1);
        calc_ic();
    }
    void multiply_mod(poly &a, poly x){
        auto beta = a*x;
        auto q = beta*ic;
        q.cut(k-1);
        auto result = c*q;
        for (int i = k-1; i <= 2*k-2; ++i) {
            (result[i] += beta[i]) %= mod;
        }
        a = poly(vector<int>(result.v.begin()+k-1, result.v.begin()+2*k-1));
    }

    void calc_ic() {
        ic = poly(vector<int>(1, 1));
        int t = 1;
        while(t <= k){
            t = min(2*t, k+1);
            auto cc = poly(vector<int>(c.v.begin(), c.v.begin()+t));
            auto current = cc*ic;
            (current[0] += 2) %= mod;
            ic = ic*current;
        }
        ic.cut(t);
    }

    poly kitamasa(int n){
        b = poly(vector<int>(k, 0));
        auto x = poly(vector<int>(k, 0));
        b[k-1] = 1;
        x[k-2] = 1;
        while (n != 0){
            if ((n & 1) == 1){
                multiply_mod(b, x);
            }
            n /= 2;
            multiply_mod(x, x);
        }
        return b;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/fastkitamasa.cpp"
class Fast_Kitamasa {
    poly c, b, ic;
    int k;
    int mod;
public:
    explicit Fast_Kitamasa(vector<int> &c, int mod) : c(c), mod(mod){
        k = static_cast<int>(c.size() - 1);
        calc_ic();
    }
    void multiply_mod(poly &a, poly x){
        auto beta = a*x;
        auto q = beta*ic;
        q.cut(k-1);
        auto result = c*q;
        for (int i = k-1; i <= 2*k-2; ++i) {
            (result[i] += beta[i]) %= mod;
        }
        a = poly(vector<int>(result.v.begin()+k-1, result.v.begin()+2*k-1));
    }

    void calc_ic() {
        ic = poly(vector<int>(1, 1));
        int t = 1;
        while(t <= k){
            t = min(2*t, k+1);
            auto cc = poly(vector<int>(c.v.begin(), c.v.begin()+t));
            auto current = cc*ic;
            (current[0] += 2) %= mod;
            ic = ic*current;
        }
        ic.cut(t);
    }

    poly kitamasa(int n){
        b = poly(vector<int>(k, 0));
        auto x = poly(vector<int>(k, 0));
        b[k-1] = 1;
        x[k-2] = 1;
        while (n != 0){
            if ((n & 1) == 1){
                multiply_mod(b, x);
            }
            n /= 2;
            multiply_mod(x, x);
        }
        return b;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

