---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_fastkitamasa_fft.test.cpp
    title: test/yosupo_aplusb_fastkitamasa_fft.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_kth_term_of_linearly_recurrent_sequence_fastkitamasa.test.cpp
    title: test/yosupo_kth_term_of_linearly_recurrent_sequence_fastkitamasa.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u9805\u5F0F\u5270\u4F59\u306E\u51AA\u8A08\u7B97(\u9AD8\
      \u901FKitamasa\u6CD5)"
    links: []
  bundledCode: "#line 1 \"math/fastkitamasa.cpp\"\nclass Fast_Kitamasa {\n    poly\
    \ c, ic;\n    int k;\n\npublic:\n    explicit Fast_Kitamasa(const vector<mint>\
    \ &coefficients)\n        : c(coefficients), k((int)coefficients.size() - 1) {\n\
    \        assert(k >= 1 && c[k] != mint(0));\n        calc_ic();\n    }\n\n   \
    \ explicit Fast_Kitamasa(const vector<int> &coefficients, int mod = mint::get_mod())\n\
    \        : Fast_Kitamasa(vector<mint>(coefficients.begin(), coefficients.end()))\
    \ {\n        assert(mod == (int)mint::get_mod());\n        (void)mod;\n    }\n\
    \n    void calc_ic() {\n        if (k == 1) {\n            ic = poly();\n    \
    \        return;\n        }\n        poly reversed(vector<mint>(c.v.rbegin(),\
    \ c.v.rend()));\n        reversed.v.resize(k - 1);\n        ic = reversed.inv();\n\
    \    }\n\n    void multiply_mod(poly &a, const poly &x) const {\n        assert(a.size()\
    \ <= k && x.size() <= k);\n        poly product = a * x;\n        product.v.resize(2\
    \ * k - 1);\n        if (k == 1) {\n            a = product;\n            return;\n\
    \        }\n        poly high(vector<mint>(product.v.rbegin(), product.v.rbegin()\
    \ + k - 1));\n        poly quotient = high * ic;\n        quotient.v.resize(k\
    \ - 1);\n        reverse(quotient.v.begin(), quotient.v.end());\n        poly\
    \ removed = c * quotient;\n        a = poly(k);\n        for (int i = 0; i < k;\
    \ ++i) a[i] = product[i] - removed[i];\n    }\n\n    poly kitamasa(long long n)\
    \ const {\n        assert(n >= 0);\n        poly result(k), x(k);\n        result[0]\
    \ = 1;\n        if (k == 1) x[0] = -c[0] / c[1];\n        else x[1] = 1;\n   \
    \     while (n != 0) {\n            if (n & 1) multiply_mod(result, x);\n    \
    \        n >>= 1;\n            if (n != 0) multiply_mod(x, x);\n        }\n  \
    \      return result;\n    }\n};\n\n/**\n * @brief \u591A\u9805\u5F0F\u5270\u4F59\
    \u306E\u51AA\u8A08\u7B97(\u9AD8\u901FKitamasa\u6CD5)\n */\n"
  code: "class Fast_Kitamasa {\n    poly c, ic;\n    int k;\n\npublic:\n    explicit\
    \ Fast_Kitamasa(const vector<mint> &coefficients)\n        : c(coefficients),\
    \ k((int)coefficients.size() - 1) {\n        assert(k >= 1 && c[k] != mint(0));\n\
    \        calc_ic();\n    }\n\n    explicit Fast_Kitamasa(const vector<int> &coefficients,\
    \ int mod = mint::get_mod())\n        : Fast_Kitamasa(vector<mint>(coefficients.begin(),\
    \ coefficients.end())) {\n        assert(mod == (int)mint::get_mod());\n     \
    \   (void)mod;\n    }\n\n    void calc_ic() {\n        if (k == 1) {\n       \
    \     ic = poly();\n            return;\n        }\n        poly reversed(vector<mint>(c.v.rbegin(),\
    \ c.v.rend()));\n        reversed.v.resize(k - 1);\n        ic = reversed.inv();\n\
    \    }\n\n    void multiply_mod(poly &a, const poly &x) const {\n        assert(a.size()\
    \ <= k && x.size() <= k);\n        poly product = a * x;\n        product.v.resize(2\
    \ * k - 1);\n        if (k == 1) {\n            a = product;\n            return;\n\
    \        }\n        poly high(vector<mint>(product.v.rbegin(), product.v.rbegin()\
    \ + k - 1));\n        poly quotient = high * ic;\n        quotient.v.resize(k\
    \ - 1);\n        reverse(quotient.v.begin(), quotient.v.end());\n        poly\
    \ removed = c * quotient;\n        a = poly(k);\n        for (int i = 0; i < k;\
    \ ++i) a[i] = product[i] - removed[i];\n    }\n\n    poly kitamasa(long long n)\
    \ const {\n        assert(n >= 0);\n        poly result(k), x(k);\n        result[0]\
    \ = 1;\n        if (k == 1) x[0] = -c[0] / c[1];\n        else x[1] = 1;\n   \
    \     while (n != 0) {\n            if (n & 1) multiply_mod(result, x);\n    \
    \        n >>= 1;\n            if (n != 0) multiply_mod(x, x);\n        }\n  \
    \      return result;\n    }\n};\n\n/**\n * @brief \u591A\u9805\u5F0F\u5270\u4F59\
    \u306E\u51AA\u8A08\u7B97(\u9AD8\u901FKitamasa\u6CD5)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fastkitamasa.cpp
  requiredBy: []
  timestamp: '2026-10-10 16:31:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_kth_term_of_linearly_recurrent_sequence_fastkitamasa.test.cpp
  - test/yosupo_aplusb_fastkitamasa_fft.test.cpp
date: 2018-04-28
documentation_of: math/fastkitamasa.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u591A\u9805\u5F0F\u5270\u4F59\u306E\u51AA\u8A08\u7B97(\u9AD8\u901FKitamasa\u6CD5\
  )"
---

## 説明
多項式 $f(x)$ に対する $x^K \bmod f(x)$ の係数列を求める。
次数を $N \ge 1$ として、前処理は $O(N \log(N+1))$、冪計算は $O(N \log(N+1)\log(K+2))$、作業領域は $O(N)$。

## できること
- `Fast_Kitamasa solver(coefficients)`
  `vector<mint>` の係数列から構築する。`coefficients[i]` は $x^i$ の係数で、末尾は非零とする
- `Fast_Kitamasa solver(coefficients, mod)`
  既存の `vector<int>` 入力を受け付ける。`mod` は使用する `mint::get_mod()` と一致させる。省略時も同じ法を使う
- `poly kitamasa(long long k) const`
  $x^k \bmod f(x)$ を低次から長さ $N$ で返す。`k >= 0` を前提とし、指数0では定数1を返す
- `void multiply_mod(poly &a, const poly &b) const`
  `a` を $ab \bmod f(x)$ にする。両入力の長さは $N$ 以下とする。空入力は零として扱う

## 使い方
先に `math/ntt.cpp` または `math/fft.cpp` のいずれかを include し、続けて `math/fastkitamasa.cpp` を include する。
NTT 版は法998244353、任意 mod 版は利用側で設定した素数 `MOD` を使う。両方の `poly` は同時に include しない。

```cpp
vector<mint> f = {-1, -1, 1};
Fast_Kitamasa solver(f);
poly remainder = solver.kitamasa(10);
```

$f(x)=x^2-x-1$ に対し、結果は $34+55x$、係数列は `{34, 55}` となる。
返り値の順序は現在の `poly` と同じ低次からの順である。
線形漸化式の値だけが必要なら `fps/linear_recurrence.cpp` を使い、剰余の全係数を再利用する場合はこのクラスを使う。

## 実装上の補足
反転した $f$ の逆多項式を前計算し、積の高次部分から商を求めて剰余を計算する。
定数項が0の多項式や非モニック多項式にも対応する。法は実行時には切り替えず、係数演算と畳み込みは選択した `mint` / `poly` に従う。
