---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/lazysegtree.cpp
    title: datastructure/lazysegtree.cpp
  - icon: ':question:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"test/yosupo_range_affine_range_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\nusing namespace std;\n#line 1 \"datastructure/lazysegtree.cpp\"\
    \ntemplate <class M>\nstruct LazySegmentTree{\n    using T = typename M::T;\n\
    \    using L = typename M::L;\n    int sz, n, height{};\n    vector<T> seg; vector<L>\
    \ lazy;\n    explicit LazySegmentTree(int n) : n(n) {\n        sz = 1; while(sz\
    \ < n) sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n        lazy.assign(2*sz,\
    \ M::l());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1],\
    \ seg[(i<<1)|1]);\n    }\n\n    T reflect(int k){ return lazy[k] == M::l() ? seg[k]\
    \ : M::g(seg[k], lazy[k]); }\n\n    void eval(int k){\n        if(lazy[k] == M::l())\
    \ return;\n        if(k < sz){\n            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0],\
    \ lazy[k]);\n            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);\n   \
    \     }\n        seg[k] = reflect(k);\n        lazy[k] = M::l();\n    }\n    void\
    \ thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n    void recalc(int\
    \ k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}\n\n\
    \    void update(int a, const T &x){\n        thrust(a += sz);\n        seg[a]\
    \ = x;\n        recalc(a);\n    }\n\n    void update(int a, int b, const L &x){\n\
    \        thrust(a += sz); thrust(b += sz-1);\n        for (int l = a, r = b+1;l\
    \ < r; l >>=1, r >>= 1) {\n            if(l&1) lazy[l] = M::h(lazy[l], x), l++;\n\
    \            if(r&1) --r, lazy[r] = M::h(lazy[r], x);\n        }\n        recalc(a);\n\
    \        recalc(b);\n    }\n\n    T query(int a, int b){ // [l, r)\n        thrust(a\
    \ += sz);\n        thrust(b += sz-1);\n        T ll = M::e(), rr = M::e();\n \
    \       for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {\n            if (l & 1)\
    \ ll = M::f(ll, reflect(l++));\n            if (r & 1) rr = M::f(reflect(--r),\
    \ rr);\n        }\n        return M::f(ll, rr);\n    }\n\n    template<class F>\n\
    \    int search_right(int l, F cond){\n        if(l == n) return n;\n        thrust(l\
    \ += sz);\n        T val = M::e();\n        do {\n            while(!(l&1)) l\
    \ >>= 1;\n            if(!cond(M::f(val, seg[l]))){\n                while(l <\
    \ sz) {\n                    eval(l); l <<= 1;\n                    if (cond(M::f(val,\
    \ reflect(l)))){\n                        val = M::f(val, reflect(l++));\n   \
    \                 }\n                }\n                return l - sz;\n     \
    \       }\n            val = M::f(val, reflect(l++));\n        } while((l & -l)\
    \ != l);\n        return n;\n    }\n\n    template<class F>\n    int search_left(int\
    \ r, F cond){\n        if(r <= 0) return 0;\n        thrust((r += sz)-1);\n  \
    \      T val = M::e();\n        do {\n            r--;\n            while(r >\
    \ 1 && r&1) r >>= 1;\n            if(!cond(M::f(reflect(r), val))){\n        \
    \        while(r < sz) {\n                    eval(r);\n                    r\
    \ = ((r << 1)|1);\n                    if (cond(M::f(reflect(r), val))){\n   \
    \                     val = M::f(reflect(r--), val);\n                    }\n\
    \                }\n                return r + 1 - sz;\n            }\n      \
    \      val = M::f(reflect(r), val);\n        } while((r & -r) != r);\n       \
    \ return 0;\n    }\n};\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n\
    \    using L = array<mint, 2>;\n    static T f(T a, T b) { return {a[0]+b[0],\
    \ a[1]+b[1]}; }\n    static T g(T a, L b) {\n        return {a[0] * b[0] + a[1]\
    \ * b[1], a[1]};\n    }\n    static L h(L a, L b) {\n        return {a[0]*b[0],\
    \ a[1]*b[0]+b[1]};\n    }\n    static T e() { return {0, 0}; }\n    static L l()\
    \ { return {1, 0}; }\n};\n*/\n#line 1 \"util/modint.cpp\"\ntemplate <uint M>\n\
    struct modint {\n    uint val;\npublic:\n    static modint raw(int v) { modint\
    \ x; x.val = v; return x; }\n    modint() : val(0) {}\n    template <class T>\n\
    \    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }\n\
    \    modint(bool v) { val = ((unsigned int)(v) % M); }\n    modint& operator++()\
    \ { val++; if (val == M) val = 0; return *this; }\n    modint& operator--() {\
    \ if (val == 0) val = M; val--; return *this; }\n    modint operator++(int) {\
    \ modint result = *this; ++*this; return result; }\n    modint operator--(int)\
    \ { modint result = *this; --*this; return result; }\n    modint& operator+=(const\
    \ modint& b) { val += b.val; if (val >= M) val -= M; return *this; }\n    modint&\
    \ operator-=(const modint& b) { val -= b.val; if (val >= M) val += M; return *this;\
    \ }\n    modint& operator*=(const modint& b) { ull z = val; z *= b.val; val =\
    \ (uint)(z % M); return *this; }\n    modint& operator/=(const modint& b) { return\
    \ *this = *this * b.inv(); }\n    modint operator+() const { return *this; }\n\
    \    modint operator-() const { return modint() - *this; }\n    modint pow(long\
    \ long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *=\
    \ x; n >>= 1; } return r; }\n    modint inv() const { return pow(M-2); }\n   \
    \ friend modint operator+(const modint& a, const modint& b) { return modint(a)\
    \ += b; }\n    friend modint operator-(const modint& a, const modint& b) { return\
    \ modint(a) -= b; }\n    friend modint operator*(const modint& a, const modint&\
    \ b) { return modint(a) *= b; }\n    friend modint operator/(const modint& a,\
    \ const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 19\
    \ \"test/yosupo_range_affine_range_sum.test.cpp\"\n\nstruct Monoid{\n    using\
    \ T = array<mint, 2>;\n    using L = array<mint, 2>;\n    static T f(T a, T b)\
    \ { return {a[0]+b[0], a[1]+b[1]}; }\n    static T g(T a, L b) {\n        return\
    \ {a[0] * b[0] + a[1] * b[1], a[1]};\n    }\n    static L h(L a, L b) {\n    \
    \    return {a[0]*b[0], a[1]*b[0]+b[1]};\n    }\n    static T e() { return {0,\
    \ 0}; }\n    static L l() { return {1, 0}; }\n};\nint main() {\n    int n, q;\n\
    \    cin >> n >> q;\n    vector<int> v(n);\n    for (auto &&i : v) scanf(\"%d\"\
    , &i);\n    LazySegmentTree<Monoid> seg(n);\n    for (int i = 0; i < n; ++i) seg.set(i,\
    \ {v[i], 1});\n    seg.build();\n    for (int i = 0; i < q; ++i) {\n        int\
    \ t;\n        scanf(\"%d\", &t);\n        if(!t){\n            int l, r, b, c;\n\
    \            scanf(\"%d %d %d %d\\n\", &l, &r, &b, &c);\n            seg.update(l,\
    \ r, {b, c});\n        }else {\n            int l, r;\n            scanf(\"%d\
    \ %d\", &l, &r);\n            printf(\"%d\\n\", seg.query(l, r)[0].val);\n   \
    \     }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 998244353;\nusing ll = long long;\nusing uint\
    \ = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n#include\
    \ \"../datastructure/lazysegtree.cpp\"\n#include \"../util/modint.cpp\"\n\nstruct\
    \ Monoid{\n    using T = array<mint, 2>;\n    using L = array<mint, 2>;\n    static\
    \ T f(T a, T b) { return {a[0]+b[0], a[1]+b[1]}; }\n    static T g(T a, L b) {\n\
    \        return {a[0] * b[0] + a[1] * b[1], a[1]};\n    }\n    static L h(L a,\
    \ L b) {\n        return {a[0]*b[0], a[1]*b[0]+b[1]};\n    }\n    static T e()\
    \ { return {0, 0}; }\n    static L l() { return {1, 0}; }\n};\nint main() {\n\
    \    int n, q;\n    cin >> n >> q;\n    vector<int> v(n);\n    for (auto &&i :\
    \ v) scanf(\"%d\", &i);\n    LazySegmentTree<Monoid> seg(n);\n    for (int i =\
    \ 0; i < n; ++i) seg.set(i, {v[i], 1});\n    seg.build();\n    for (int i = 0;\
    \ i < q; ++i) {\n        int t;\n        scanf(\"%d\", &t);\n        if(!t){\n\
    \            int l, r, b, c;\n            scanf(\"%d %d %d %d\\n\", &l, &r, &b,\
    \ &c);\n            seg.update(l, r, {b, c});\n        }else {\n            int\
    \ l, r;\n            scanf(\"%d %d\", &l, &r);\n            printf(\"%d\\n\",\
    \ seg.query(l, r)[0].val);\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - datastructure/lazysegtree.cpp
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_range_affine_range_sum.test.cpp
- /verify/test/yosupo_range_affine_range_sum.test.cpp.html
title: test/yosupo_range_affine_range_sum.test.cpp
---
