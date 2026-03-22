---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0422.test.cpp
    title: test/aoj0422.test.cpp
  - icon: ':x:'
    path: test/yosupo_many_aplusb_modint_interface.test.cpp
    title: test/yosupo_many_aplusb_modint_interface.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "modint(\u4EFB\u610FMOD)"
    links: []
  bundledCode: "#line 1 \"util/modint_arbitrary.cpp\"\n\n\n\nclass modint {\n    static\
    \ uint &mod() { static uint mod_ = 0; return mod_; }\npublic:\n    uint val;\n\
    \    static modint raw(int v) { modint x; x.val = v; return x; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v % (ll)(M()));\
    \ if (x < 0) x += M(); val = uint(x); }\n    modint(bool v) { val = ((unsigned\
    \ int)(v) % M()); }\n    static uint get_mod() { return M(); }\n    static uint\
    \ M() { return mod(); }\n    static void set_mod(uint x) { mod() = x; }\n    uint\
    \ &value() noexcept { return val; }\n    const uint &value() const noexcept {\
    \ return val; }\n    modint &operator++() { val++; if (val == M()) val = 0; return\
    \ *this; }\n    modint &operator--() { if (val == 0) val = M(); val--; return\
    \ *this; }\n    modint operator++(int) { modint result = *this; ++*this; return\
    \ result; }\n    modint operator--(int) { modint result = *this; --*this; return\
    \ result; }\n    modint &operator+=(const modint &b) { val += b.val; if (val >=\
    \ M()) val -= M(); return *this; }\n    modint &operator-=(const modint &b) {\
    \ val -= b.val; if (val >= M()) val += M(); return *this; }\n    modint &operator*=(const\
    \ modint &b) { val = (ull)val * b.val % M(); return *this; }\n    modint &operator/=(const\
    \ modint &b) { return *this = *this * b.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(M() - 2); }\n    friend modint operator+(const modint &a, const modint &b)\
    \ { return modint(a) += b; }\n    friend modint operator-(const modint &a, const\
    \ modint &b) { return modint(a) -= b; }\n    friend modint operator*(const modint\
    \ &a, const modint &b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint &a, const modint &b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint &a, const modint &b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint &a, const modint &b) { return a.val != b.val; }\n};\nusing mint = modint;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u4EFB\u610F\
    MOD)\n */\n\n\n"
  code: "#ifndef FIRIEXP_LIBRARY_UTIL_MODINT_ARBITRARY_CPP\n#define FIRIEXP_LIBRARY_UTIL_MODINT_ARBITRARY_CPP\n\
    \nclass modint {\n    static uint &mod() { static uint mod_ = 0; return mod_;\
    \ }\npublic:\n    uint val;\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T\
    \ v) { ll x = (ll)(v % (ll)(M())); if (x < 0) x += M(); val = uint(x); }\n   \
    \ modint(bool v) { val = ((unsigned int)(v) % M()); }\n    static uint get_mod()\
    \ { return M(); }\n    static uint M() { return mod(); }\n    static void set_mod(uint\
    \ x) { mod() = x; }\n    uint &value() noexcept { return val; }\n    const uint\
    \ &value() const noexcept { return val; }\n    modint &operator++() { val++; if\
    \ (val == M()) val = 0; return *this; }\n    modint &operator--() { if (val ==\
    \ 0) val = M(); val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint &operator+=(const modint &b)\
    \ { val += b.val; if (val >= M()) val -= M(); return *this; }\n    modint &operator-=(const\
    \ modint &b) { val -= b.val; if (val >= M()) val += M(); return *this; }\n   \
    \ modint &operator*=(const modint &b) { val = (ull)val * b.val % M(); return *this;\
    \ }\n    modint &operator/=(const modint &b) { return *this = *this * b.inv();\
    \ }\n    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(M() - 2); }\n    friend modint operator+(const\
    \ modint &a, const modint &b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint &a, const modint &b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint &a, const modint &b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint &a, const modint &b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint &a, const modint &b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint &a, const modint &b) { return a.val != b.val; }\n};\nusing mint = modint;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u4EFB\u610F\
    MOD)\n */\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: util/modint_arbitrary.cpp
  requiredBy: []
  timestamp: '2026-03-14 20:56:35+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_many_aplusb_modint_interface.test.cpp
  - test/aoj0422.test.cpp
date: 2026-03-14
documentation_of: util/modint_arbitrary.cpp
layout: document
tags: "\u6570\u5B66"
title: "modint\u69CB\u9020\u4F53(\u5B9F\u884C\u6642MOD)"
---

## 説明
実行時に MOD を設定する剰余整数を扱う。
固定 MOD 版と同じ演算を持ち、`set_mod` だけが追加で必要になる。

## できること
- `mint::set_mod(mod)`
  MOD を設定する。使う前に 1 回以上呼ぶ
- `modint x`, `mint x`
  現在の MOD 上の値を作る。負数もそのまま渡せる
- `modint::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る
- `modint::get_mod()`, `modint::M()`
  現在の MOD を返す
- `x.value()`, `x.val`
  保持している値を返す
- `++x`, `--x`, `x += y`, `x -= y`, `x *= y`, `x /= y`
  各演算を行う
- `x.pow(n)`
  $x^n$ を返す
- `x.inv()`
  逆元を返す。逆元が存在しない場合は壊れる
- `x == y`, `x != y`
  値を比較する

## 使い方
先に `mint::set_mod(mod);` を呼んでから値を作る。
`/` と `inv()` は現在の MOD が素数で、対象が `0` でない状況を前提にしている。
