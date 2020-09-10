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


# :warning: math/factorial.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/factorial.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-10 16:12:25+09:00




## Depends on

* :heavy_check_mark: <a href="../util/modint.cpp.html">modint(固定MOD) <small>(util/modint.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../util/modint.cpp"

class Factorial {
    vector<mint> facts, factinv;
public:
    explicit Factorial(int n) : facts(n+1), factinv(n+1) {
        facts[0] = 1;
        for (int i = 1; i < n+1; ++i) facts[i] = facts[i-1] * mint(i);
        factinv[n] = facts[n].inv();
        for (int i = n-1; i >= 0; --i) factinv[i] = factinv[i+1] * mint(i+1);
    }
    mint fact(int k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint operator[](const int &k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint C(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[q] * factinv[p-q];
    }
    mint P(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[p-q];
    }
    mint H(int p, int q) const {
        if(p < 0 || q < 0) return 0;
        return q == 0 ? 1 : C(p+q-1, q);
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "util/modint.cpp"
template <u32 M>
struct modint {
    u32 val;
public:
    static modint raw(int v) { modint x; x.val = v; return x; }
    modint() : val(0) {}
    template <class T>
    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = u32(x); }
    modint(bool v) { val = ((unsigned int)(v) % M); }
    modint& operator++() { val++; if (val == M) val = 0; return *this; }
    modint& operator--() { if (val == 0) val = M; val--; return *this; }
    modint operator++(int) { modint result = *this; ++*this; return result; }
    modint operator--(int) { modint result = *this; --*this; return result; }
    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -= M; return *this; }
    modint& operator-=(const modint& b) { val -= b.val; if (val >= M) val += M; return *this; }
    modint& operator*=(const modint& b) { u64 z = val; z *= b.val; val = (u32)(z % M); return *this; }
    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(M-2); }
    friend modint operator+(const modint& a, const modint& b) { return modint(a) += b; }
    friend modint operator-(const modint& a, const modint& b) { return modint(a) -= b; }
    friend modint operator*(const modint& a, const modint& b) { return modint(a) *= b; }
    friend modint operator/(const modint& a, const modint& b) { return modint(a) /= b; }
    friend bool operator==(const modint& a, const modint& b) { return a.val == b.val; }
    friend bool operator!=(const modint& a, const modint& b) { return a.val != b.val; }
};
using mint = modint<MOD>;

/**
 * @brief modint(固定MOD)
 * @docs _md/modint.md
 */
#line 2 "math/factorial.cpp"

class Factorial {
    vector<mint> facts, factinv;
public:
    explicit Factorial(int n) : facts(n+1), factinv(n+1) {
        facts[0] = 1;
        for (int i = 1; i < n+1; ++i) facts[i] = facts[i-1] * mint(i);
        factinv[n] = facts[n].inv();
        for (int i = n-1; i >= 0; --i) factinv[i] = factinv[i+1] * mint(i+1);
    }
    mint fact(int k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint operator[](const int &k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint C(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[q] * factinv[p-q];
    }
    mint P(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[p-q];
    }
    mint H(int p, int q) const {
        if(p < 0 || q < 0) return 0;
        return q == 0 ? 1 : C(p+q-1, q);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

