---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0399.test.cpp
    title: test/aoj0399.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(Square Matrix)"
    links: []
  bundledCode: "#line 1 \"math/squarematrix.cpp\"\ntemplate<class H, size_t SIZE>\n\
    struct SquareMatrix {\n    using T = typename H::T;\n    using ar = array<T, SIZE>;\n\
    \    using mat = array<ar, SIZE>;\n    mat A;\n    SquareMatrix() {\n        for\
    \ (size_t i = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE; ++j)\
    \ {\n                A[i][j] = H::zero();\n            }\n        }\n    }\n \
    \   static SquareMatrix I(size_t n = SIZE){\n        SquareMatrix X;\n       \
    \ for (size_t i = 0; i < n; ++i) {\n            X[i][i] = H::one();\n        }\n\
    \        return X;\n    }\n\n    friend ar &operator*=(ar &x, const SquareMatrix\
    \ &Y) {\n        ar ans;\n        fill(begin(ans), end(ans), H::zero());\n   \
    \     for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j <\
    \ SIZE; ++j) {\n                H::add(ans[j], H::mul(x[i], Y[i][j]));\n     \
    \       }\n        }\n        x.swap(ans);\n        return x;\n    }\n    friend\
    \ ar operator*(ar x, const SquareMatrix &Y) { return x *= Y; }\n\n    inline const\
    \ ar &operator[](int k) const{ return (A.at(k)); }\n    inline ar &operator[](int\
    \ k) { return (A.at(k)); }\n    SquareMatrix &operator+= (const SquareMatrix &B){\n\
    \        for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j\
    \ < SIZE; ++j) {\n                H::add((*this)[i][j], B[i][j]);\n          \
    \  }\n        }\n        return (*this);\n    }\n\n    SquareMatrix &operator-=\
    \ (const SquareMatrix &B){\n        for (size_t i = 0; i < SIZE; ++i) {\n    \
    \        for (size_t j = 0; j < SIZE; ++j) {\n                H::add((*this)[i][j],\
    \ -B[i][j]);\n            }\n        }\n        return (*this);\n    }\n\n   \
    \ SquareMatrix &mul_assign(const SquareMatrix &B, size_t n = SIZE) {\n       \
    \ SquareMatrix C{};\n        for (size_t i = 0; i < n; ++i) {\n            for\
    \ (size_t k = 0; k < n; ++k) {\n                for (size_t j = 0; j < n; ++j)\
    \ {\n                    H::add(C[i][j],  H::mul((*this)[i][k], B[k][j]));\n \
    \               }\n            }\n        }\n        A.swap(C.A);\n        return\
    \ (*this);\n    }\n    SquareMatrix &operator*=(const SquareMatrix &B) { return\
    \ mul_assign(B); }\n\n    SquareMatrix pow(ll n, size_t dim = SIZE) const {\n\
    \        SquareMatrix a = (*this), res = I(dim);\n\n        while(n > 0){\n  \
    \          if(n & 1) res.mul_assign(a, dim);\n            a.mul_assign(a, dim);\n\
    \            n >>= 1;\n        }\n        return res;\n    }\n    SquareMatrix\
    \ operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}\n\
    \    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this)\
    \ -= B;}\n    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this)\
    \ *= B;}\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(Square\
    \ Matrix)\n */\n"
  code: "template<class H, size_t SIZE>\nstruct SquareMatrix {\n    using T = typename\
    \ H::T;\n    using ar = array<T, SIZE>;\n    using mat = array<ar, SIZE>;\n  \
    \  mat A;\n    SquareMatrix() {\n        for (size_t i = 0; i < SIZE; ++i) {\n\
    \            for (size_t j = 0; j < SIZE; ++j) {\n                A[i][j] = H::zero();\n\
    \            }\n        }\n    }\n    static SquareMatrix I(size_t n = SIZE){\n\
    \        SquareMatrix X;\n        for (size_t i = 0; i < n; ++i) {\n         \
    \   X[i][i] = H::one();\n        }\n        return X;\n    }\n\n    friend ar\
    \ &operator*=(ar &x, const SquareMatrix &Y) {\n        ar ans;\n        fill(begin(ans),\
    \ end(ans), H::zero());\n        for (size_t i = 0; i < SIZE; ++i) {\n       \
    \     for (size_t j = 0; j < SIZE; ++j) {\n                H::add(ans[j], H::mul(x[i],\
    \ Y[i][j]));\n            }\n        }\n        x.swap(ans);\n        return x;\n\
    \    }\n    friend ar operator*(ar x, const SquareMatrix &Y) { return x *= Y;\
    \ }\n\n    inline const ar &operator[](int k) const{ return (A.at(k)); }\n   \
    \ inline ar &operator[](int k) { return (A.at(k)); }\n    SquareMatrix &operator+=\
    \ (const SquareMatrix &B){\n        for (size_t i = 0; i < SIZE; ++i) {\n    \
    \        for (size_t j = 0; j < SIZE; ++j) {\n                H::add((*this)[i][j],\
    \ B[i][j]);\n            }\n        }\n        return (*this);\n    }\n\n    SquareMatrix\
    \ &operator-= (const SquareMatrix &B){\n        for (size_t i = 0; i < SIZE; ++i)\
    \ {\n            for (size_t j = 0; j < SIZE; ++j) {\n                H::add((*this)[i][j],\
    \ -B[i][j]);\n            }\n        }\n        return (*this);\n    }\n\n   \
    \ SquareMatrix &mul_assign(const SquareMatrix &B, size_t n = SIZE) {\n       \
    \ SquareMatrix C{};\n        for (size_t i = 0; i < n; ++i) {\n            for\
    \ (size_t k = 0; k < n; ++k) {\n                for (size_t j = 0; j < n; ++j)\
    \ {\n                    H::add(C[i][j],  H::mul((*this)[i][k], B[k][j]));\n \
    \               }\n            }\n        }\n        A.swap(C.A);\n        return\
    \ (*this);\n    }\n    SquareMatrix &operator*=(const SquareMatrix &B) { return\
    \ mul_assign(B); }\n\n    SquareMatrix pow(ll n, size_t dim = SIZE) const {\n\
    \        SquareMatrix a = (*this), res = I(dim);\n\n        while(n > 0){\n  \
    \          if(n & 1) res.mul_assign(a, dim);\n            a.mul_assign(a, dim);\n\
    \            n >>= 1;\n        }\n        return res;\n    }\n    SquareMatrix\
    \ operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}\n\
    \    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this)\
    \ -= B;}\n    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this)\
    \ *= B;}\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(Square\
    \ Matrix)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/squarematrix.cpp
  requiredBy: []
  timestamp: '2026-03-15 18:15:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0399.test.cpp
date: 2026-03-15
documentation_of: math/squarematrix.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u6B63\u65B9\u884C\u5217"
---

## 説明
サイズ固定になる代わりに `array` を使う正方行列。
`H` が定める加法と乗法で演算する。

## できること
- `SquareMatrix<H, SIZE> A`
  `SIZE × SIZE` 行列を 0 初期化で作る
- `SquareMatrix<H, SIZE>::I()`
  単位行列を返す
- `SquareMatrix<H, SIZE>::I(n)`
  左上 `n × n` だけを使う単位行列を返す
- `A += B`, `A -= B`, `A *= B`
  加減算、行列積を行う
- `A.pow(k)`
  $A^k$ を返す
- `A.pow(k, n)`
  左上 `n × n` だけを使って $A^k$ を返す
- `x * A`
  長さ `SIZE` の行ベクトルに右から掛ける

## 使い方
サイズが固定で、累乗や遷移行列を繰り返し回すときに使う。
実際に使うサイズが `SIZE` 未満なら `pow(k, n)` を使うと未使用領域を回さずに済む。
`H` は `using T`、`static T mul(T, T)`、`static void add(T&, T)`、`static T one()`、`static T zero()` を持てばよい。
