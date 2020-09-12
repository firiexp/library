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


# :heavy_check_mark: test/yosupo_convolution.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_convolution.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-12 12:50:53+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod">https://judge.yosupo.jp/problem/convolution_mod</a>


## Depends on

* :heavy_check_mark: <a href="../../library/math/ntt.cpp.html">math/ntt.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"


#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../math/ntt.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    poly a(n), b(m);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        b[i] = x;
    }
    a *= b;
    for (int i = 0; i < n+m-1; ++i) {
        if(i) printf(" ");
        printf("%d", a[i].val);
    }
    puts("");
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_convolution.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"


#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#line 1 "math/ntt.cpp"
constexpr int ntt_mod = 998244353, ntt_root = 3;
// 1012924417 -> 5, 924844033 -> 5
// 998244353  -> 3, 897581057 -> 3
// 645922817  -> 3;
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
    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val -= M; return *this; }
    modint& operator-=(const modint& rhs) { val -= rhs.val; if (val >= M) val += M; return *this; }
    modint& operator*=(const modint& rhs) { u64 z = val; z *= rhs.val; val = (u32)(z % M); return *this; }
    modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(M-2); }
    friend modint operator+(const modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }
    friend modint operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs; }
    friend modint operator*(const modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }
    friend modint operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs; }
    friend bool operator==(const modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }
    friend bool operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val; }
};
using mint = modint<998244353>;

class NTT {
    static constexpr int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2
    mint sum_e[30], sum_ie[30];

public:
    mint es[30], ies[30];
    NTT() {
        int cnt2 = __builtin_ctz(ntt_mod-1);

        mint e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 0; i--){
            es[i] = e;
            ies[i] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1, nowi = 1;
        for (int i = 0; i < cnt2 - 2; i++) {
            sum_e[i] = es[i+2] * now;
            now *= ies[i+2];
            sum_ie[i] = ies[i+2] * nowi;
            nowi *= es[i+2];
        }
    }

    void transform(vector<mint> &a, int sign){
        const int n = a.size();
        int h = 0;
        while ((1U << h) < (unsigned int)(n)) h++;
        if(!sign){ // fft
            for (int ph = 1; ph <= h; ph++) {
                int w = 1 << (ph-1), p = 1 << (h-ph);
                mint now = 1;
                for (int s = 0; s < w; s++) {
                    int offset = s << (h-ph+1);
                    for (int i = 0; i < p; i++) {
                        auto l = a[i+offset], r = a[i+offset+p]*now;
                        a[i+offset] = l+r;
                        a[i+offset+p] = l-r;
                    }
                    now *= sum_e[__builtin_ctz(~(unsigned int)(s))];
                }
            }
        }else { // ifft
            for (int ph = h; ph >= 1; ph--) {
                int w = 1 << (ph-1), p = 1 << (h-ph);
                mint inow = 1;
                for (int s = 0; s < w; s++) {
                    int offset = s << (h-ph+1);
                    for (int i = 0; i < p; i++) {
                        auto l = a[i+offset], r = a[i+offset+p];
                        a[i+offset] = l+r;
                        a[i+offset+p] = (l-r)*inow;
                    }
                    inow *= sum_ie[__builtin_ctz(~(unsigned int)(s))];
                }
            }
        }
    }
};

NTT ntt;

struct poly {
    vector<mint> v;
    poly() = default;
    explicit poly(int n) : v(n) {};
    explicit poly(vector<mint> vv) : v(std::move(vv)) {};
    int size() const {return (int)v.size(); }
    poly cut(int len){
        if(len < v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline mint& operator[] (int i) {return v[i]; }
    poly& operator+=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];
        return *this;
    }
    poly& operator-=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];
        return *this;
    }

    poly& operator*=(poly a) {
        int N = size()+a.size()-1;
        int sz = 1;
        while(sz < N) sz <<= 1;
        this->v.resize(sz); a.v.resize(sz);
        ntt.transform(this->v, 0); ntt.transform(a.v, 0);
        for(int i = 0; i < sz; ++i) this->v[i] *= a.v[i];
        ntt.transform(this->v, 1);
        this->v.resize(N);
        mint iz = mint(sz).inv();
        for (int i = 0; i < N; i++) this->v[i] *= iz;
        return *this;
    }
    poly& operator/=(const poly &a){ return (*this *= a.inv()); }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }

    poly inv() const {
        int n = size();
        poly r(1);
        r[0] = (this->v[0]).inv();
        int k = 1;
        while(k < n){
            k *= 2;
            poly ff(k);
            for (int i = 0; i < min(k, n); ++i) {
                ff[i] = this->v[i];
            }
            poly nr = (r*r*ff).cut(k);
            for (int i = 0; i < k/2; ++i) {
                nr[i] = (r[i]+r[i]-nr[i]);
                nr[i+k/2] = -nr[i+k/2];
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }
};

mint nth_term(poly p, poly q, ll n){
    if(!n) return p[0]/q[0];
    int sz = 1, h = 0;
    int k = max(p.size(), q.size());
    while(sz < 2*k-1) sz <<= 1, h++;
    p.v.resize(sz); q.v.resize(sz);
    mint x = mint(sz>>1).inv();
    vector<mint> y(sz>>1, 0);
    for (int j = sz>>2, i = h; j; j >>= 1, i--) y[j] = ntt.ies[i];
    y[0] = 1;
    for (int i = 2; i < sz>>1; i <<= 1) {
        for (int j = i+1; j < 2*i; ++j) {
            y[j] = y[j-i]*y[i];
        }
    }
    ntt.transform(p.v, 0);
    ntt.transform(q.v, 0);
    poly tmp(sz>>1);
    auto up = [&](poly &A){
        for (int i = 0; i < sz>>1; ++i) tmp[i] = A[i];
        ntt.transform(tmp.v, 1);
        mint now = x;
        for (int i = 0; i < sz>>1; ++i) tmp[i] *= now, now *= ntt.es[h];
        ntt.transform(tmp.v, 0);
        for (int i = 0; i < sz>>1; ++i) A[i|(sz>>1)] = tmp[i];
    };
    int ika = h;
    while(n){
        for (int i = 0; i < sz; ++i) p[i] *= q[i^1];
        if(n&1) for (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];
        else for (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);
        ika++;
        if(n == 1) break;
        up(p);
        for (int i = 0; i < sz>>1; ++i) q[i] = q[i<<1]*q[(i<<1)|1];
        up(q);
        n >>= 1;
    }
    for (int i = 0; i < sz>>1; ++i) tmp[i] = p[i];
    ntt.transform(tmp.v, 1);
    return mint(2).pow(ntt_mod-ika)*tmp[0];
}
#line 23 "test/yosupo_convolution.test.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    poly a(n), b(m);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        b[i] = x;
    }
    a *= b;
    for (int i = 0; i < n+m-1; ++i) {
        if(i) printf(" ");
        printf("%d", a[i].val);
    }
    puts("");
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

