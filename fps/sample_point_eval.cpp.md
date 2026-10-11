---
category: FPS
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factorial.cpp
    title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
  - icon: ':heavy_check_mark:'
    path: util/modint_base.cpp
    title: util/modint_base.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_sample_point_eval.test.cpp
    title: test/yosupo_aplusb_sample_point_eval.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9023\u7D9A\u6A19\u672C\u70B9\u304B\u3089\u306E1\u70B9\u8A55\
      \u4FA1"
    links: []
  bundledCode: "#line 1 \"fps/sample_point_eval.cpp\"\n\n\n\n#line 1 \"math/factorial.cpp\"\
    \n\n\n\n#line 1 \"util/modint_base.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    static constexpr uint get_mod() { return Mod; }\n    static\
    \ constexpr uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class\
    \ T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val =\
    \ uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint\
    \ &value() noexcept { return val; }\n    const uint &value() const noexcept {\
    \ return val; }\n    modint& operator++() { val++; if (val == Mod) val = 0; return\
    \ *this; }\n    modint& operator--() { if (val == 0) val = Mod; val--; return\
    \ *this; }\n    modint operator++(int) { modint result = *this; ++*this; return\
    \ result; }\n    modint operator--(int) { modint result = *this; --*this; return\
    \ result; }\n    modint& operator+=(const modint& b) { val += b.val; if (val >=\
    \ Mod) val -= Mod; return *this; }\n    modint& operator-=(const modint& b) {\
    \ val -= b.val; if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const\
    \ modint& b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n\
    \    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(Mod - 2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 5 \"math/factorial.cpp\"\
    \n\n#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\nusing mint = modint<MOD>;\n#define\
    \ FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n#endif\n\ntemplate <class Mint = mint>\n\
    class Factorial {\n    inline static vector<Mint> facts, factinv, invs;\n\n  \
    \  static void init() {\n        if (!facts.empty()) return;\n        facts.push_back(Mint(1));\n\
    \        factinv.push_back(Mint(1));\n        invs.push_back(Mint(0));\n     \
    \   invs.push_back(Mint(1));\n    }\n\n    static void expand(int n) {\n     \
    \   init();\n        if (n < (int)facts.size()) return;\n        int old = facts.size();\n\
    \        int mod = Mint::get_mod();\n        facts.resize(n + 1);\n        factinv.resize(n\
    \ + 1);\n        invs.resize(n + 1);\n        for (int i = max(2, old); i <= n;\
    \ ++i) {\n            invs[i] = -Mint(mod / i) * invs[mod % i];\n        }\n \
    \       for (int i = old; i <= n; ++i) {\n            facts[i] = facts[i - 1]\
    \ * Mint(i);\n            factinv[i] = factinv[i - 1] * invs[i];\n        }\n\
    \    }\npublic:\n    explicit Factorial(int n = 0) {\n        expand(n);\n   \
    \ }\n    void ensure(int n) const {\n        if (n >= 0) expand(n);\n    }\n \
    \   int max_n() const {\n        init();\n        return (int)facts.size() - 1;\n\
    \    }\n    Mint fact(int k) const {\n        if (k < 0) return inv_fact(-k);\n\
    \        expand(k);\n        return facts[k];\n    }\n    Mint inv_fact(int k)\
    \ const {\n        if (k < 0) return 0;\n        expand(k);\n        return factinv[k];\n\
    \    }\n    Mint inv(int k) const {\n        if (k < 0) return 0;\n        expand(k);\n\
    \        return invs[k];\n    }\n    Mint operator[](int k) const {\n        return\
    \ k >= 0 ? fact(k) : inv_fact(-k);\n    }\n    Mint C(int n, int k) const {\n\
    \        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n        return\
    \ facts[n] * factinv[k] * factinv[n - k];\n    }\n    Mint P(int n, int k) const\
    \ {\n        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n    \
    \    return facts[n] * factinv[n - k];\n    }\n    Mint H(int n, int k) const\
    \ {\n        if (n < 0 || k < 0) return 0;\n        if (k == 0) return 1;\n  \
    \      if (n == 0) return 0;\n        return C(n + k - 1, k);\n    }\n};\n\n/**\n\
    \ * @brief \u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)\n */\n\n\n#line\
    \ 5 \"fps/sample_point_eval.cpp\"\n\ntemplate <class Mint>\nMint sample_point_eval(const\
    \ vector<Mint>& ys, Mint x) {\n    int n = ys.size();\n    if (n == 0) return\
    \ Mint(0);\n    assert(ys.size() <= Mint::get_mod());\n    if (x.val < ys.size())\
    \ return ys[x.val];\n    Factorial<Mint> factorial(n - 1);\n    vector<Mint> prefix(n\
    \ + 1, Mint(1));\n    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] *\
    \ (x - Mint(i));\n    Mint result = 0, suffix = 1;\n    for (int i = n - 1; i\
    \ >= 0; --i) {\n        Mint term = ys[i] * prefix[i] * suffix * factorial.inv_fact(i)\
    \ * factorial.inv_fact(n - 1 - i);\n        if ((n - 1 - i) & 1) result -= term;\n\
    \        else result += term;\n        suffix *= x - Mint(i);\n    }\n    return\
    \ result;\n}\n\n\n\n/**\n * @brief \u9023\u7D9A\u6A19\u672C\u70B9\u304B\u3089\u306E\
    1\u70B9\u8A55\u4FA1\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_FPS_SAMPLE_POINT_EVAL_CPP\n#define FIRIEXP_LIBRARY_FPS_SAMPLE_POINT_EVAL_CPP\n\
    \n#include \"../math/factorial.cpp\"\n\ntemplate <class Mint>\nMint sample_point_eval(const\
    \ vector<Mint>& ys, Mint x) {\n    int n = ys.size();\n    if (n == 0) return\
    \ Mint(0);\n    assert(ys.size() <= Mint::get_mod());\n    if (x.val < ys.size())\
    \ return ys[x.val];\n    Factorial<Mint> factorial(n - 1);\n    vector<Mint> prefix(n\
    \ + 1, Mint(1));\n    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] *\
    \ (x - Mint(i));\n    Mint result = 0, suffix = 1;\n    for (int i = n - 1; i\
    \ >= 0; --i) {\n        Mint term = ys[i] * prefix[i] * suffix * factorial.inv_fact(i)\
    \ * factorial.inv_fact(n - 1 - i);\n        if ((n - 1 - i) & 1) result -= term;\n\
    \        else result += term;\n        suffix *= x - Mint(i);\n    }\n    return\
    \ result;\n}\n\n#endif\n\n/**\n * @brief \u9023\u7D9A\u6A19\u672C\u70B9\u304B\u3089\
    \u306E1\u70B9\u8A55\u4FA1\n */\n"
  dependsOn:
  - math/factorial.cpp
  - util/modint_base.cpp
  isVerificationFile: false
  path: fps/sample_point_eval.cpp
  requiredBy: []
  timestamp: '2026-10-11 14:34:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_sample_point_eval.test.cpp
date: 2026-10-11
documentation_of: fps/sample_point_eval.cpp
layout: document
tags: FPS
title: "\u9023\u7D9A\u6A19\u672C\u70B9\u304B\u3089\u306E1\u70B9\u8A55\u4FA1"
---

## 説明
次数 $N$ 未満の多項式の値 $f(0),\ldots,f(N-1)$ から、任意の1点 $f(x)$ を Lagrange 補間で求める。

## できること
- `Mint sample_point_eval(const vector<Mint>& ys, Mint x)`
  `ys[i] = f(i)` として `f(x)` を返す。時間・作業領域は $O(N)$、既知点への評価は $O(1)$

## 使い方
`fps/sample_point_eval.cpp` を読み込み、値列と評価点を同じ `modint<P>` 型で渡す。
`P` は $2^{31}$ 未満の固定素数、$N\leq P$ を前提とする。
法 `998244353` と `1000000007` のどちらも使える。

```cpp
vector<mint> ys = {1, 4, 9};
mint value = sample_point_eval(ys, mint(5));
```

この例の返り値は `36`。
階乗逆元は `Factorial<Mint>` の共有キャッシュを内部で用意して再利用する。
