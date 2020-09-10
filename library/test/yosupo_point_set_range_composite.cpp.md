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


# :warning: test/yosupo_point_set_range_composite.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_point_set_range_composite.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-10 16:24:03+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :warning: <a href="../datastructure/segtree.cpp.html">datastructure/segtree.cpp</a>
* :heavy_check_mark: <a href="../util/modint.cpp.html">modint(固定MOD) <small>(util/modint.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/modint.cpp"

#include "../datastructure/segtree.cpp"

struct Monoid{
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        seg.set(i, {a, b});
    }
    seg.build();
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if(!a) seg.update(b, {c, d});
        else {
            auto ans = seg.query(b, c);
            printf("%d\n", (ans[0]*d+ans[1]).val);
        }
    }
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_point_set_range_composite.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

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
#line 21 "test/yosupo_point_set_range_composite.cpp"

#line 1 "datastructure/segtree.cpp"
template <class M>
struct SegmentTree{
    using T = typename M::T;
    int sz, n, height{};
    vector<T> seg;
    explicit SegmentTree(int n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        seg.assign(2*sz, M::e());
    }

    void set(int k, const T &x){ seg[k + sz] = x; }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);
    }

    void update(int k, const T &x){
        k += sz;
        seg[k] = x;
        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);
    }

    T query(int a, int b){
        T l = M::e(), r = M::e();
        for(a += sz, b += sz; a < b; a >>=1, b>>=1){
            if(a & 1) l = M::f(l, seg[a++]);
            if(b & 1) r = M::f(seg[--b], r);
        }
        return M::f(l, r);
    }

    template<class F>
    int search_right(int l, F cond){
        if(l == n) return n;
        T val = M::e();
        do {
            while(!(l&1)) l >>= 1;
            if(!cond(M::f(val, seg[l]))){
                while(l < sz) {
                    l <<= 1;
                    if (cond(M::f(val, seg[l]))){
                        val = M::f(val, seg[l]);
                        l++;
                    }
                }
                return l - sz;
            }
            val = M::f(val, seg[l]);
            l++;
        } while((l & -l) != l);
        return n;
    }

    template<class F>
    int search_left(int r, F cond){
        if(r == 0) return 0;
        T val = M::e();
        do {
            while(r&1) r >>= 1;
            if(!cond(M::f(val, seg[r]))){
                while(r < sz) {
                    r = ((r << 1)|1);
                    if (cond(M::f(seg[r], val))){
                        val = M::f(seg[r], val);
                        r--;
                    }
                }
                return r + 1 - sz;
            }
            val = M::f(seg[r], val);
        } while((r & -r) != r);
        return 0;
    }
    T operator[](const int &k) const { return seg[k + sz]; }
};
#line 23 "test/yosupo_point_set_range_composite.cpp"

struct Monoid{
    using T = array<mint, 2>;
    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }
    static T e() { return {1, 0}; }
};

int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree<Monoid> seg(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        seg.set(i, {a, b});
    }
    seg.build();
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if(!a) seg.update(b, {c, d});
        else {
            auto ans = seg.query(b, c);
            printf("%d\n", (ans[0]*d+ans[1]).val);
        }
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

