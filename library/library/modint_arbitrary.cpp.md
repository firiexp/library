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


# :warning: library/modint_arbitrary.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/modint_arbitrary.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct modint {
    ll val;
    static ll &mod(){
        static ll mod_ = 0;
        return mod_;
    }

    static void set_mod(const ll x) { mod() = x; }
    static ll M() {return mod(); }

    modint(const ll x) : val(x) {
        val = x%M();
        while(val < 0) val += M();
    }

    modint operator+(const modint a) const { return modint(*this) += a; }
    modint operator-(const modint a) const { return modint(*this) -= a; }
    modint operator*(const modint a) const { return modint(*this) *= a; }
    modint operator/(const modint a) const { return modint(*this) /= a; }
    modint operator-() const { return {M()-val}; }
    modint inv() const {
        ll u = 1, v = 0, s = 0, t = 1, m = M(), x = val;
        while (x) {ll q = M()/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }
        if(s < 0) s += M();
        return modint(s);
    }
    modint pow(ll n){
        ll u = 1, xx = val;
        while (n > 0){ if (n&1) u = u * xx % M(); xx = xx * xx % M(); n >>= 1; }
        return modint(u);
    }
    modint& operator+=(const modint a){ val += a.val; if(val >= M()) val -= M(); return *this; }
    modint& operator-=(const modint a){ val += a.val; if(val < 0) val += M(); return *this; }
    modint& operator*=(const modint a){ val = val * a.val % M(); return *this; }
    modint& operator/=(const modint a){ val = val * a.inv().val % M(); return *this;}

    modint& operator=(const int& x){
        val = x%M();
        while(val < 0) val += M();
        return *this;
    }
};
using mint = modint;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/modint_arbitrary.cpp"
struct modint {
    ll val;
    static ll &mod(){
        static ll mod_ = 0;
        return mod_;
    }

    static void set_mod(const ll x) { mod() = x; }
    static ll M() {return mod(); }

    modint(const ll x) : val(x) {
        val = x%M();
        while(val < 0) val += M();
    }

    modint operator+(const modint a) const { return modint(*this) += a; }
    modint operator-(const modint a) const { return modint(*this) -= a; }
    modint operator*(const modint a) const { return modint(*this) *= a; }
    modint operator/(const modint a) const { return modint(*this) /= a; }
    modint operator-() const { return {M()-val}; }
    modint inv() const {
        ll u = 1, v = 0, s = 0, t = 1, m = M(), x = val;
        while (x) {ll q = M()/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }
        if(s < 0) s += M();
        return modint(s);
    }
    modint pow(ll n){
        ll u = 1, xx = val;
        while (n > 0){ if (n&1) u = u * xx % M(); xx = xx * xx % M(); n >>= 1; }
        return modint(u);
    }
    modint& operator+=(const modint a){ val += a.val; if(val >= M()) val -= M(); return *this; }
    modint& operator-=(const modint a){ val += a.val; if(val < 0) val += M(); return *this; }
    modint& operator*=(const modint a){ val = val * a.val % M(); return *this; }
    modint& operator/=(const modint a){ val = val * a.inv().val % M(); return *this;}

    modint& operator=(const int& x){
        val = x%M();
        while(val < 0) val += M();
        return *this;
    }
};
using mint = modint;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

