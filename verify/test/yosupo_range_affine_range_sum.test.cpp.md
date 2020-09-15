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


# :heavy_check_mark: test/yosupo_range_affine_range_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_range_affine_range_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-15 21:59:19+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/datastructure/lazysegtree.cpp.html">datastructure/lazysegtree.cpp</a>
* :heavy_check_mark: <a href="../../library/util/modint.cpp.html">modint(固定MOD) <small>(util/modint.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 998244353;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;
#include "../datastructure/lazysegtree.cpp"
#include "../util/modint.cpp"

struct Monoid{
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0]+b[0], a[1]+b[1]}; }
    static T g(T a, L b) {
        return {a[0] * b[0] + a[1] * b[1], a[1]};
    }
    static L h(L a, L b) {
        return {a[0]*b[0], a[1]*b[0]+b[1]};
    }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (auto &&i : v) scanf("%d", &i);
    LazySegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) seg.set(i, {v[i], 1});
    seg.build();
    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);
        if(!t){
            int l, r, b, c;
            scanf("%d %d %d %d\n", &l, &r, &b, &c);
            seg.update(l, r, {b, c});
        }else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", seg.query(l, r)[0].val);
        }
    }
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_range_affine_range_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 998244353;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;
#line 1 "datastructure/lazysegtree.cpp"
template <class M>
struct LazySegmentTree{
    using T = typename M::T;
    using L = typename M::L;
    int sz, n, height{};
    vector<T> seg; vector<L> lazy;
    explicit LazySegmentTree(int n) : n(n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        seg.assign(2*sz, M::e());
        lazy.assign(2*sz, M::l());
    }

    void set(int k, const T &x){ seg[k + sz] = x; }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);
    }

    T reflect(int k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k], lazy[k]); }

    void eval(int k){
        if(lazy[k] == M::l()) return;
        if(k < sz){
            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);
            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);
        }
        seg[k] = reflect(k);
        lazy[k] = M::l();
    }
    void thrust(int k){ for (int i = height; i; --i) eval(k>>i); }
    void recalc(int k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}

    void update(int a, const T &x){
        thrust(a += sz);
        seg[a] = x;
        recalc(a);
    }

    void update(int a, int b, const L &x){
        thrust(a += sz); thrust(b += sz-1);
        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {
            if(l&1) lazy[l] = M::h(lazy[l], x), l++;
            if(r&1) --r, lazy[r] = M::h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }

    T query(int a, int b){ // [l, r)
        thrust(a += sz);
        thrust(b += sz-1);
        T ll = M::e(), rr = M::e();
        for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {
            if (l & 1) ll = M::f(ll, reflect(l++));
            if (r & 1) rr = M::f(reflect(--r), rr);
        }
        return M::f(ll, rr);
    }

    template<class F>
    int search_right(int l, F cond){
        if(l == n) return n;
        thrust(l += sz);
        T val = M::e();
        do {
            while(!(l&1)) l >>= 1;
            if(!cond(M::f(val, seg[l]))){
                while(l < sz) {
                    eval(l); l <<= 1;
                    if (cond(M::f(val, reflect(l)))){
                        val = M::f(val, reflect(l++));
                    }
                }
                return l - sz;
            }
            val = M::f(val, reflect(l++));
        } while((l & -l) != l);
        return n;
    }

    template<class F>
    int search_left(int r, F cond){
        if(r <= 0) return 0;
        thrust((r += sz)-1);
        T val = M::e();
        do {
            r--;
            while(r > 1 && r&1) r >>= 1;
            if(!cond(M::f(reflect(r), val))){
                while(r < sz) {
                    eval(r);
                    r = ((r << 1)|1);
                    if (cond(M::f(reflect(r), val))){
                        val = M::f(reflect(r--), val);
                    }
                }
                return r + 1 - sz;
            }
            val = M::f(reflect(r), val);
        } while((r & -r) != r);
        return 0;
    }
};
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
#line 19 "test/yosupo_range_affine_range_sum.test.cpp"

struct Monoid{
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0]+b[0], a[1]+b[1]}; }
    static T g(T a, L b) {
        return {a[0] * b[0] + a[1] * b[1], a[1]};
    }
    static L h(L a, L b) {
        return {a[0]*b[0], a[1]*b[0]+b[1]};
    }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (auto &&i : v) scanf("%d", &i);
    LazySegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) seg.set(i, {v[i], 1});
    seg.build();
    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);
        if(!t){
            int l, r, b, c;
            scanf("%d %d %d %d\n", &l, &r, &b, &c);
            seg.update(l, r, {b, c});
        }else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", seg.query(l, r)[0].val);
        }
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

