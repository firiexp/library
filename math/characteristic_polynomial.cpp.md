---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_characteristic_polynomial.test.cpp
    title: test/yosupo_aplusb_characteristic_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_characteristic_polynomial.test.cpp
    title: test/yosupo_characteristic_polynomial.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7279\u6027\u591A\u9805\u5F0F"
    links: []
  bundledCode: "#line 1 \"math/characteristic_polynomial.cpp\"\ntemplate<class T>\n\
    vector<T> characteristic_polynomial(vector<vector<T>> a) {\n    int n = (int)a.size();\n\
    \    for (int k = 0; k + 2 < n; ++k) {\n        int pivot = k + 1;\n        while\
    \ (pivot < n && a[pivot][k] == T(0)) ++pivot;\n        if (pivot == n) continue;\n\
    \        if (pivot != k + 1) {\n            swap(a[pivot], a[k + 1]);\n      \
    \      for (auto& row : a) swap(row[pivot], row[k + 1]);\n        }\n        T\
    \ inv = T(1) / a[k + 1][k];\n        for (int i = k + 2; i < n; ++i) {\n     \
    \       if (a[i][k] == T(0)) continue;\n            T factor = a[i][k] * inv;\n\
    \            a[i][k] = 0;\n            for (int j = k + 1; j < n; ++j) a[i][j]\
    \ -= factor * a[k + 1][j];\n            for (int j = 0; j < n; ++j) a[j][k + 1]\
    \ += factor * a[j][i];\n        }\n    }\n    vector<vector<T>> p(n + 1);\n  \
    \  p[0] = {T(1)};\n    for (int i = 0; i < n; ++i) {\n        p[i + 1].resize(i\
    \ + 2);\n        for (int j = 0; j <= i; ++j) {\n            p[i + 1][j + 1] +=\
    \ p[i][j];\n            p[i + 1][j] -= a[i][i] * p[i][j];\n        }\n       \
    \ T product = 1;\n        for (int k = i - 1; k >= 0; --k) {\n            product\
    \ *= a[k + 1][k];\n            T factor = product * a[k][i];\n            for\
    \ (int j = 0; j <= k; ++j) p[i + 1][j] -= factor * p[k][j];\n        }\n    }\n\
    \    return p[n];\n}\n\n/**\n * @brief \u7279\u6027\u591A\u9805\u5F0F\n */\n"
  code: "template<class T>\nvector<T> characteristic_polynomial(vector<vector<T>>\
    \ a) {\n    int n = (int)a.size();\n    for (int k = 0; k + 2 < n; ++k) {\n  \
    \      int pivot = k + 1;\n        while (pivot < n && a[pivot][k] == T(0)) ++pivot;\n\
    \        if (pivot == n) continue;\n        if (pivot != k + 1) {\n          \
    \  swap(a[pivot], a[k + 1]);\n            for (auto& row : a) swap(row[pivot],\
    \ row[k + 1]);\n        }\n        T inv = T(1) / a[k + 1][k];\n        for (int\
    \ i = k + 2; i < n; ++i) {\n            if (a[i][k] == T(0)) continue;\n     \
    \       T factor = a[i][k] * inv;\n            a[i][k] = 0;\n            for (int\
    \ j = k + 1; j < n; ++j) a[i][j] -= factor * a[k + 1][j];\n            for (int\
    \ j = 0; j < n; ++j) a[j][k + 1] += factor * a[j][i];\n        }\n    }\n    vector<vector<T>>\
    \ p(n + 1);\n    p[0] = {T(1)};\n    for (int i = 0; i < n; ++i) {\n        p[i\
    \ + 1].resize(i + 2);\n        for (int j = 0; j <= i; ++j) {\n            p[i\
    \ + 1][j + 1] += p[i][j];\n            p[i + 1][j] -= a[i][i] * p[i][j];\n   \
    \     }\n        T product = 1;\n        for (int k = i - 1; k >= 0; --k) {\n\
    \            product *= a[k + 1][k];\n            T factor = product * a[k][i];\n\
    \            for (int j = 0; j <= k; ++j) p[i + 1][j] -= factor * p[k][j];\n \
    \       }\n    }\n    return p[n];\n}\n\n/**\n * @brief \u7279\u6027\u591A\u9805\
    \u5F0F\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/characteristic_polynomial.cpp
  requiredBy: []
  timestamp: '2026-10-11 20:42:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_characteristic_polynomial.test.cpp
  - test/yosupo_characteristic_polynomial.test.cpp
documentation_of: math/characteristic_polynomial.cpp
layout: document
title: "\u7279\u6027\u591A\u9805\u5F0F"
---

## 説明
正方行列 $A$ の特性多項式 $\det(xI-A)$ を求める。
$N\times N$ 行列に対して時間 $O(N^3)$、補助領域 $O(N^2)$。

## できること
- `vector<T> characteristic_polynomial(vector<vector<T>> a)`
  特性多項式の係数を定数項から順に返す。返り値は $N+1$ 要素で、最高次の係数は `1`

## 使い方
`T` には、非零要素で除算できる体の型を使う。例えば素数を法とする `modint` を指定できる。
入力の行列は変更されない。

```cpp
vector<vector<mint>> a = { {1, 2}, {3, 4} };
auto p = characteristic_polynomial(a);
```

この例では $x^2-5x-2$ の係数が返る。
空行列の特性多項式は $1$ とする。

## 実装上の補足
相似変換で上 Hessenberg 形にし、先頭主小行列の特性多項式を順に計算する。
整数 $1,\ldots,N$ による除算は使わず、標数が $N$ 以下の体にも対応する。
