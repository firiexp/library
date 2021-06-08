---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/factorial.cpp
    title: math/factorial.cpp
  - icon: ':warning:'
    path: math/gauss_jordan_mint.cpp
    title: math/gauss_jordan_mint.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0399.test.cpp
    title: test/aoj0399.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj2257.test.cpp
    title: test/aoj2257.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_dpl_5_a.test.cpp
    title: test/aoj_dpl_5_a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_set_range_composite.test.cpp
    title: test/yosupo_point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_queue_operate_all_composite.test.cpp
    title: test/yosupo_queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_affine_range_sum.test.cpp
    title: test/yosupo_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sum_of_totient.test.cpp
    title: test/yosupo_sum_of_totient.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/modint.md
    document_title: "modint(\u56FA\u5B9AMOD)"
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\ntemplate <u32 M>\nstruct modint {\n \
    \   u32 val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll\
    \ x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = u32(x); }\n    modint(bool v)\
    \ { val = ((unsigned int)(v) % M); }\n    modint& operator++() { val++; if (val\
    \ == M) val = 0; return *this; }\n    modint& operator--() { if (val == 0) val\
    \ = M; val--; return *this; }\n    modint operator++(int) { modint result = *this;\
    \ ++*this; return result; }\n    modint operator--(int) { modint result = *this;\
    \ --*this; return result; }\n    modint& operator+=(const modint& b) { val +=\
    \ b.val; if (val >= M) val -= M; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= M) val += M; return *this; }\n    modint&\
    \ operator*=(const modint& b) { u64 z = val; z *= b.val; val = (u32)(z % M); return\
    \ *this; }\n    modint& operator/=(const modint& b) { return *this = *this * b.inv();\
    \ }\n    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n"
  code: "template <u32 M>\nstruct modint {\n    u32 val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = u32(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M); }\n\
    \    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n  \
    \  modint& operator--() { if (val == 0) val = M; val--; return *this; }\n    modint\
    \ operator++(int) { modint result = *this; ++*this; return result; }\n    modint\
    \ operator--(int) { modint result = *this; --*this; return result; }\n    modint&\
    \ operator+=(const modint& b) { val += b.val; if (val >= M) val -= M; return *this;\
    \ }\n    modint& operator-=(const modint& b) { val -= b.val; if (val >= M) val\
    \ += M; return *this; }\n    modint& operator*=(const modint& b) { u64 z = val;\
    \ z *= b.val; val = (u32)(z % M); return *this; }\n    modint& operator/=(const\
    \ modint& b) { return *this = *this * b.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(M-2); }\n    friend modint operator+(const modint& a, const modint& b) {\
    \ return modint(a) += b; }\n    friend modint operator-(const modint& a, const\
    \ modint& b) { return modint(a) -= b; }\n    friend modint operator*(const modint&\
    \ a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */"
  dependsOn: []
  isVerificationFile: false
  path: util/modint.cpp
  requiredBy:
  - math/factorial.cpp
  - math/gauss_jordan_mint.cpp
  timestamp: '2020-09-10 16:12:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_sum_of_totient.test.cpp
  - test/aoj0399.test.cpp
  - test/aoj_dpl_5_a.test.cpp
  - test/aoj2257.test.cpp
  - test/yosupo_point_set_range_composite.test.cpp
  - test/yosupo_range_affine_range_sum.test.cpp
  - test/yosupo_queue_operate_all_composite.test.cpp
documentation_of: util/modint.cpp
layout: document
redirect_from:
- /library/util/modint.cpp
- /library/util/modint.cpp.html
title: "modint(\u56FA\u5B9AMOD)"
---
## 説明
テンプレートにMODを指定すると、いちいち剰余を取ることなくMOD上の演算ができる。

## できること
- 四則演算、二分累乗