---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/nth_term.cpp
    title: fps/nth_term.cpp
  - icon: ':heavy_check_mark:'
    path: math/berlekamp_massey.cpp
    title: Berlekamp-Massey algorithm
  - icon: ':heavy_check_mark:'
    path: math/ntt.cpp
    title: math/ntt.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/linear_recurrence.md
    document_title: linear recurrence
    links: []
  bundledCode: "#line 1 \"math/ntt.cpp\"\nconstexpr int ntt_mod = 998244353, ntt_root\
    \ = 3;\n// 1012924417 -> 5, 924844033 -> 5\n// 998244353  -> 3, 897581057 -> 3\n\
    // 645922817  -> 3;\ntemplate <uint M>\nstruct modint {\n    uint val;\npublic:\n\
    \    static modint raw(int v) { modint x; x.val = v; return x; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val\
    \ -= M; return *this; }\n    modint& operator-=(const modint& rhs) { val -= rhs.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ rhs) { ull z = val; z *= rhs.val; val = (uint)(z % M); return *this; }\n   \
    \ modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }\n    friend modint\
    \ operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs;\
    \ }\n    friend modint operator*(const modint& lhs, const modint& rhs) { return\
    \ modint(lhs) *= rhs; }\n    friend modint operator/(const modint& lhs, const\
    \ modint& rhs) { return modint(lhs) /= rhs; }\n    friend bool operator==(const\
    \ modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }\n    friend bool\
    \ operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val;\
    \ }\n};\nusing mint = modint<998244353>;\n\nclass NTT {\n    static constexpr\
    \ int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2\n    mint sum_e[30],\
    \ sum_ie[30];\npublic:\n    mint es[30], ies[30];\n    NTT() {\n        int cnt2\
    \ = __builtin_ctz(ntt_mod-1);\n        mint e = mint(ntt_root).pow((ntt_mod-1)\
    \ >> cnt2), ie = e.inv();\n        for (int i = cnt2; i >= 0; i--){\n        \
    \    es[i] = e; ies[i] = ie;\n            e *= e; ie *= ie;\n        }\n     \
    \   mint now = 1, nowi = 1;\n        for (int i = 0; i < cnt2 - 2; i++) {\n  \
    \          sum_e[i] = es[i+2] * now; now *= ies[i+2];\n            sum_ie[i] =\
    \ ies[i+2] * nowi; nowi *= es[i+2];\n        }\n    }\n\n    void transform(vector<mint>\
    \ &a, int sign){\n        const int n = a.size();\n        int h = 0;\n      \
    \  while ((1U << h) < (unsigned int)(n)) h++;\n        if(!sign){ // fft\n   \
    \         for (int ph = 1; ph <= h; ph++) {\n                int w = 1 << (ph-1),\
    \ p = 1 << (h-ph);\n                mint now = 1;\n                for (int s\
    \ = 0; s < w; s++) {\n                    int offset = s << (h-ph+1);\n      \
    \              for (int i = 0; i < p; i++) {\n                        auto l =\
    \ a[i+offset], r = a[i+offset+p]*now;\n                        a[i+offset] = l+r,\
    \ a[i+offset+p] = l-r;\n                    }\n                    now *= sum_e[__builtin_ctz(~(unsigned\
    \ int)(s))];\n                }\n            }\n        }else { // ifft\n    \
    \        for (int ph = h; ph >= 1; ph--) {\n                int w = 1 << (ph-1),\
    \ p = 1 << (h-ph);\n                mint inow = 1;\n                for (int s\
    \ = 0; s < w; s++) {\n                    int offset = s << (h-ph+1);\n      \
    \              for (int i = 0; i < p; i++) {\n                        auto l =\
    \ a[i+offset], r = a[i+offset+p];\n                        a[i+offset] = l+r,\
    \ a[i+offset+p] = (l-r)*inow;\n                    }\n                    inow\
    \ *= sum_ie[__builtin_ctz(~(unsigned int)(s))];\n                }\n         \
    \   }\n        }\n    }\n};\n\nNTT ntt;\n\nstruct poly {\n    vector<mint> v;\n\
    \    poly() = default;\n    explicit poly(int n) : v(n) {};\n    explicit poly(vector<mint>\
    \ vv) : v(std::move(vv)) {};\n    int size() const {return (int)v.size(); }\n\
    \    poly cut(int len){\n        if(len < v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly& operator-=(const poly &a) {\n       \
    \ this->v.resize(max(size(), a.size()));\n        for (int i = 0; i < a.size();\
    \ ++i) this->v[i] -= a.v[i];\n        return *this;\n    }\n    poly& operator*=(poly\
    \ a) {\n        int N = size()+a.size()-1;\n        int sz = 1;\n        while(sz\
    \ < N) sz <<= 1;\n        this->v.resize(sz); a.v.resize(sz);\n        ntt.transform(this->v,\
    \ 0); ntt.transform(a.v, 0);\n        for(int i = 0; i < sz; ++i) this->v[i] *=\
    \ a.v[i];\n        ntt.transform(this->v, 1);\n        this->v.resize(N);\n  \
    \      mint iz = mint(sz).inv();\n        for (int i = 0; i < N; i++) this->v[i]\
    \ *= iz;\n        return *this;\n    }\n    poly& operator/=(const poly &a){ return\
    \ (*this *= a.inv()); }\n    poly operator+(const poly &a) const { return poly(*this)\
    \ += a; }\n    poly operator-(const poly &a) const { return poly(*this) -= a;\
    \ }\n    poly operator*(const poly &a) const { return poly(*this) *= a; }\n\n\
    \    poly inv() const {\n        int n = size();\n        poly r(1);\n       \
    \ r[0] = (this->v[0]).inv();\n        for (int k = 1; k < n; k <<= 1) {\n    \
    \        poly ff(2*k);\n            for (int i = 0; i < min(k*2, n); ++i) ff[i]\
    \ = this->v[i];\n            poly nr = (r*r*ff).cut(k*2);\n            for (int\
    \ i = 0; i < k; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n         \
    \       nr[i+k] = -nr[i+k];\n            }\n            r = nr;\n        }\n \
    \       r.v.resize(n);\n        return r;\n    }\n};\n#line 2 \"fps/nth_term.cpp\"\
    \nmint nth_term(poly p, poly q, ll n){\n    if(!n) return p[0]/q[0];\n    int\
    \ sz = 1, h = 0;\n    int k = max(p.size(), q.size());\n    while(sz < 2*k-1)\
    \ sz <<= 1, h++;\n    p.v.resize(sz); q.v.resize(sz);\n    mint x = mint(sz>>1).inv();\n\
    \    vector<mint> y(sz>>1, 0);\n    for (int j = sz>>2, i = h; j; j >>= 1, i--)\
    \ y[j] = ntt.ies[i];\n    y[0] = 1;\n    for (int i = 2; i < sz>>1; i <<= 1) {\n\
    \        for (int j = i+1; j < 2*i; ++j) {\n            y[j] = y[j-i]*y[i];\n\
    \        }\n    }\n    ntt.transform(p.v, 0);\n    ntt.transform(q.v, 0);\n  \
    \  poly tmp(sz>>1);\n    auto up = [&](poly &A){\n        for (int i = 0; i <\
    \ sz>>1; ++i) tmp[i] = A[i];\n        ntt.transform(tmp.v, 1);\n        mint now\
    \ = x;\n        for (int i = 0; i < sz>>1; ++i) tmp[i] *= now, now *= ntt.es[h];\n\
    \        ntt.transform(tmp.v, 0);\n        for (int i = 0; i < sz>>1; ++i) A[i|(sz>>1)]\
    \ = tmp[i];\n    };\n    int ika = h;\n    while(n){\n        for (int i = 0;\
    \ i < sz; ++i) p[i] *= q[i^1];\n        if(n&1) for (int i = 0; i < sz>>1; ++i)\
    \ p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];\n        else for (int i = 0; i < sz>>1;\
    \ ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);\n        ika++;\n        if(n == 1) break;\n\
    \        up(p);\n        for (int i = 0; i < sz>>1; ++i) q[i] = q[i<<1]*q[(i<<1)|1];\n\
    \        up(q);\n        n >>= 1;\n    }\n    for (int i = 0; i < sz>>1; ++i)\
    \ tmp[i] = p[i];\n    ntt.transform(tmp.v, 1);\n    return mint(2).pow(ntt_mod-ika)*tmp[0];\n\
    }\n#line 1 \"math/berlekamp_massey.cpp\"\ntemplate<class T>\nvector<T> berlekamp_massey(const\
    \ vector<T> &s) {\n    vector<T> c(1, T(1)), b(1, T(1));\n    int l = 0, m = 1;\n\
    \    T y = T(1);\n    for (int n = 0; n < (int)s.size(); ++n) {\n        T d =\
    \ T(0);\n        for (int i = 0; i <= l; ++i) d += c[i] * s[n - i];\n        if\
    \ (d == T(0)) {\n            ++m;\n            continue;\n        }\n        auto\
    \ t = c;\n        T coef = d / y;\n        if ((int)c.size() < (int)b.size() +\
    \ m) c.resize((int)b.size() + m, T(0));\n        for (int i = 0; i < (int)b.size();\
    \ ++i) c[i + m] -= coef * b[i];\n        if (2 * l <= n) {\n            l = n\
    \ + 1 - l;\n            b = t;\n            y = d;\n            m = 1;\n     \
    \   } else {\n            ++m;\n        }\n    }\n    c.erase(c.begin());\n  \
    \  for (auto &x : c) x = -x;\n    return c;\n}\n\n/**\n * @brief Berlekamp-Massey\
    \ algorithm\n * @docs _md/berlekamp_massey.md\n */\n#line 3 \"fps/linear_recurrence.cpp\"\
    \n\nmint linear_recurrence(const vector<mint> &a, const vector<mint> &c, ll n)\
    \ {\n    if (n < (ll)a.size()) return a[(int)n];\n    int k = (int)c.size();\n\
    \    if (k == 0) return mint(0);\n    poly q(k + 1);\n    q[0] = 1;\n    for (int\
    \ i = 0; i < k; ++i) q[i + 1] = -c[i];\n    vector<mint> aa(k, mint(0));\n   \
    \ for (int i = 0; i < min(k, (int)a.size()); ++i) aa[i] = a[i];\n    poly p =\
    \ (poly(aa) * q).cut(k);\n    return nth_term(p, q, n);\n}\n\nmint linear_recurrence(const\
    \ vector<mint> &a, ll n) {\n    return linear_recurrence(a, berlekamp_massey(a),\
    \ n);\n}\n\n/**\n * @brief linear recurrence\n * @docs _md/linear_recurrence.md\n\
    \ */\n"
  code: "#include \"nth_term.cpp\"\n#include \"../math/berlekamp_massey.cpp\"\n\n\
    mint linear_recurrence(const vector<mint> &a, const vector<mint> &c, ll n) {\n\
    \    if (n < (ll)a.size()) return a[(int)n];\n    int k = (int)c.size();\n   \
    \ if (k == 0) return mint(0);\n    poly q(k + 1);\n    q[0] = 1;\n    for (int\
    \ i = 0; i < k; ++i) q[i + 1] = -c[i];\n    vector<mint> aa(k, mint(0));\n   \
    \ for (int i = 0; i < min(k, (int)a.size()); ++i) aa[i] = a[i];\n    poly p =\
    \ (poly(aa) * q).cut(k);\n    return nth_term(p, q, n);\n}\n\nmint linear_recurrence(const\
    \ vector<mint> &a, ll n) {\n    return linear_recurrence(a, berlekamp_massey(a),\
    \ n);\n}\n\n/**\n * @brief linear recurrence\n * @docs _md/linear_recurrence.md\n\
    \ */\n"
  dependsOn:
  - fps/nth_term.cpp
  - math/ntt.cpp
  - math/berlekamp_massey.cpp
  isVerificationFile: false
  path: fps/linear_recurrence.cpp
  requiredBy: []
  timestamp: '2026-03-07 19:40:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
documentation_of: fps/linear_recurrence.cpp
layout: document
redirect_from:
- /library/fps/linear_recurrence.cpp
- /library/fps/linear_recurrence.cpp.html
title: linear recurrence
---
---
layout: post
title: 線形漸化式
date: 2026-03-07
category: 数学
tags: 数学
---

## 概要
線形漸化式

`a_n = c_0 a_{n-1} + c_1 a_{n-2} + ... + c_{k-1} a_{n-k}`

の第 `n` 項を `O(k log k log n)` で計算する。

`linear_recurrence(a, c, n)` は初項 `a` と係数 `c` が与えられたときの第 `n` 項を返す。

`linear_recurrence(a, n)` は Berlekamp-Massey で `a` の最小線形漸化式を復元して第 `n` 項を返す。

{% include a.html code="linear_recurrence.cpp" %}
