---
category: "\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0422.test.cpp
    title: test/aoj0422.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "modint(\u4EFB\u610FMOD)"
    links: []
  bundledCode: "#line 1 \"util/modint_arbitrary.cpp\"\nclass modint {\n    static\
    \ uint &mod() { static uint mod_ = 0; return mod_; }\npublic:\n    uint val;\n\
    \    modint(const uint x = 0) : val(x % M()) {}\n    uint &value() noexcept {\
    \ return val; }\n    const uint &value() const noexcept { return val; }\n    modint\
    \ operator+(const modint b) const { return modint(*this) += b; }\n    modint operator-(const\
    \ modint b) const { return modint(*this) -= b; }\n    modint operator*(const modint\
    \ b) const { return modint(*this) *= b; }\n    modint operator/(const modint b)\
    \ const { return modint(*this) /= b; }\n    modint &operator+=(const modint b)\
    \ { val += b.val; if (val >= M()) val -= M(); return *this; }\n    modint &operator-=(const\
    \ modint b) { if (val < b.val) val += M(); val -= b.val; return *this; }\n   \
    \ modint &operator*=(const modint b) { val = (ull)val * b.val % M(); return *this;\
    \ }\n    modint pow(ll n) const { modint x = *this, r = 1; while(n){ if(n&1) r\
    \ *= x; x *= x; n >>= 1; } return r; }\n    modint &operator/=(modint b) { return\
    \ *this *= b.pow(M()-2); }\n    static void set_mod(const uint x) { mod() = x;\
    \ }\n    static int M() { return mod(); }\n};\nusing mint = modint;\n\n/**\n *\
    \ @brief modint(\u4EFB\u610FMOD)\n */\n"
  code: "class modint {\n    static uint &mod() { static uint mod_ = 0; return mod_;\
    \ }\npublic:\n    uint val;\n    modint(const uint x = 0) : val(x % M()) {}\n\
    \    uint &value() noexcept { return val; }\n    const uint &value() const noexcept\
    \ { return val; }\n    modint operator+(const modint b) const { return modint(*this)\
    \ += b; }\n    modint operator-(const modint b) const { return modint(*this) -=\
    \ b; }\n    modint operator*(const modint b) const { return modint(*this) *= b;\
    \ }\n    modint operator/(const modint b) const { return modint(*this) /= b; }\n\
    \    modint &operator+=(const modint b) { val += b.val; if (val >= M()) val -=\
    \ M(); return *this; }\n    modint &operator-=(const modint b) { if (val < b.val)\
    \ val += M(); val -= b.val; return *this; }\n    modint &operator*=(const modint\
    \ b) { val = (ull)val * b.val % M(); return *this; }\n    modint pow(ll n) const\
    \ { modint x = *this, r = 1; while(n){ if(n&1) r *= x; x *= x; n >>= 1; } return\
    \ r; }\n    modint &operator/=(modint b) { return *this *= b.pow(M()-2); }\n \
    \   static void set_mod(const uint x) { mod() = x; }\n    static int M() { return\
    \ mod(); }\n};\nusing mint = modint;\n\n/**\n * @brief modint(\u4EFB\u610FMOD)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/modint_arbitrary.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0422.test.cpp
date: 2019-06-21
documentation_of: util/modint_arbitrary.cpp
layout: document
tags: "\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
title: "modint\u69CB\u9020\u4F53(\u5B9F\u884C\u6642MOD)"
---

## 説明
テンプレートにMODを指定すると、いちいち剰余を取ることなくMOD上の演算ができる。
