---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segtree.cpp
    title: datastructure/segtree.cpp
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/yosupo_point_set_range_composite.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"util/modint.cpp\"\
    \ntemplate <uint M>\nstruct modint {\n    uint val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M);\
    \ }\n    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n\
    \    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n  \
    \  modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -=\
    \ M; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % M); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(M-2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 21\
    \ \"test/yosupo_point_set_range_composite.test.cpp\"\n\n#line 1 \"datastructure/segtree.cpp\"\
    \ntemplate <class M>\nstruct SegmentTree{\n    using T = typename M::T;\n    int\
    \ sz, n, height{};\n    vector<T> seg;\n    explicit SegmentTree(int n) : n(n)\
    \ {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz,\
    \ M::e());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i],\
    \ seg[2*i+1]);\n    }\n\n    void update(int k, const T &x){\n        k += sz;\n\
    \        seg[k] = x;\n        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n\
    \    }\n\n    T query(int a, int b){\n        T l = M::e(), r = M::e();\n    \
    \    for(a += sz, b += sz; a < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l,\
    \ seg[a++]);\n            if(b & 1) r = M::f(seg[--b], r);\n        }\n      \
    \  return M::f(l, r);\n    }\n\n    template<class F>\n    int search_right(int\
    \ l, F cond){\n        if(l == n) return n;\n        T val = M::e();\n       \
    \ l += sz;\n        do {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val,\
    \ seg[l]))){\n                while(l < sz) {\n                    l <<= 1;\n\
    \                    if (cond(M::f(val, seg[l]))){\n                        val\
    \ = M::f(val, seg[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - sz;\n            }\n          \
    \  val = M::f(val, seg[l]);\n            l++;\n        } while((l & -l) != l);\n\
    \        return n;\n    }\n\n    template<class F>\n    int search_left(int r,\
    \ F cond){\n        if(r == 0) return 0;\n        T val = M::e();\n        r +=\
    \ sz;\n        do {\n            r--;\n            while(r&1) r >>= 1;\n     \
    \       if(!cond(M::f(seg[r], val))){\n                while(r < sz) {\n     \
    \               r = ((r << 1)|1);\n                    if (cond(M::f(seg[r], val))){\n\
    \                        val = M::f(seg[r], val);\n                        r--;\n\
    \                    }\n                }\n                return r + 1 - sz;\n\
    \            }\n            val = M::f(seg[r], val);\n        } while((r & -r)\
    \ != r);\n        return 0;\n    }\n    T operator[](const int &k) const { return\
    \ seg[k + sz]; }\n};\n\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n\
    \    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n*/\n#line 23 \"test/yosupo_point_set_range_composite.test.cpp\"\
    \n\nstruct Monoid{\n    using T = array<mint, 2>;\n    static T f(T a, T b) {\
    \ return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static T e() { return {1, 0}; }\n\
    };\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    SegmentTree<Monoid>\
    \ seg(n);\n    for (int i = 0; i < n; ++i) {\n        int a, b;\n        scanf(\"\
    %d %d\", &a, &b);\n        seg.set(i, {a, b});\n    }\n    seg.build();\n    for\
    \ (int i = 0; i < q; ++i) {\n        int a, b, c, d;\n        scanf(\"%d %d %d\
    \ %d\", &a, &b, &c, &d);\n        if(!a) seg.update(b, {c, d});\n        else\
    \ {\n            auto ans = seg.query(b, c);\n            printf(\"%d\\n\", (ans[0]*d+ans[1]).val);\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 998244353;\nusing ll = long long;\nusing uint\
    \ = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../util/modint.cpp\"\
    \n\n#include \"../datastructure/segtree.cpp\"\n\nstruct Monoid{\n    using T =\
    \ array<mint, 2>;\n    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]};\
    \ }\n    static T e() { return {1, 0}; }\n};\n\nint main() {\n    int n, q;\n\
    \    cin >> n >> q;\n    SegmentTree<Monoid> seg(n);\n    for (int i = 0; i <\
    \ n; ++i) {\n        int a, b;\n        scanf(\"%d %d\", &a, &b);\n        seg.set(i,\
    \ {a, b});\n    }\n    seg.build();\n    for (int i = 0; i < q; ++i) {\n     \
    \   int a, b, c, d;\n        scanf(\"%d %d %d %d\", &a, &b, &c, &d);\n       \
    \ if(!a) seg.update(b, {c, d});\n        else {\n            auto ans = seg.query(b,\
    \ c);\n            printf(\"%d\\n\", (ans[0]*d+ans[1]).val);\n        }\n    }\n\
    \    return 0;\n}"
  dependsOn:
  - util/modint.cpp
  - datastructure/segtree.cpp
  isVerificationFile: true
  path: test/yosupo_point_set_range_composite.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_point_set_range_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_set_range_composite.test.cpp
- /verify/test/yosupo_point_set_range_composite.test.cpp.html
title: test/yosupo_point_set_range_composite.test.cpp
---
