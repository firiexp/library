---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_det.test.cpp
    title: test/yosupo_matrix_det.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u884C\u5217\u5F0F(Matrix Determinant)"
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint M>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    static constexpr uint get_mod() { return M; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
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
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 2 \"math/matrix_determinant.cpp\"\n\nmint matrix_determinant(vector<vector<mint>>\
    \ A) {\n    int n = A.size();\n    mint det = 1;\n    for (int col = 0; col <\
    \ n; ++col) {\n        int pivot = col;\n        while (pivot < n && !A[pivot][col].val)\
    \ ++pivot;\n        if (pivot == n) return 0;\n        if (pivot != col) {\n \
    \           swap(A[pivot], A[col]);\n            det = -det;\n        }\n    \
    \    det *= A[col][col];\n        mint inv = A[col][col].inv();\n        for (int\
    \ row = col + 1; row < n; ++row) {\n            if (!A[row][col].val) continue;\n\
    \            mint coeff = A[row][col] * inv;\n            for (int j = col; j\
    \ < n; ++j) {\n                A[row][j] -= A[col][j] * coeff;\n            }\n\
    \        }\n    }\n    return det;\n}\n\n/**\n * @brief \u884C\u5217\u5F0F(Matrix\
    \ Determinant)\n */\n"
  code: "#include \"../util/modint.cpp\"\n\nmint matrix_determinant(vector<vector<mint>>\
    \ A) {\n    int n = A.size();\n    mint det = 1;\n    for (int col = 0; col <\
    \ n; ++col) {\n        int pivot = col;\n        while (pivot < n && !A[pivot][col].val)\
    \ ++pivot;\n        if (pivot == n) return 0;\n        if (pivot != col) {\n \
    \           swap(A[pivot], A[col]);\n            det = -det;\n        }\n    \
    \    det *= A[col][col];\n        mint inv = A[col][col].inv();\n        for (int\
    \ row = col + 1; row < n; ++row) {\n            if (!A[row][col].val) continue;\n\
    \            mint coeff = A[row][col] * inv;\n            for (int j = col; j\
    \ < n; ++j) {\n                A[row][j] -= A[col][j] * coeff;\n            }\n\
    \        }\n    }\n    return det;\n}\n\n/**\n * @brief \u884C\u5217\u5F0F(Matrix\
    \ Determinant)\n */\n"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/matrix_determinant.cpp
  requiredBy: []
  timestamp: '2026-03-11 21:27:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_matrix_det.test.cpp
date: 2026-03-11
documentation_of: math/matrix_determinant.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u884C\u5217\u5F0F(Matrix Determinant)"
---

## 説明
`modint` 行列の行列式を計算する。
Gaussian elimination を使い、計算量は `O(N^3)`。

## できること
- `mint matrix_determinant(vector<vector<mint>> A)`
  正方行列 `A` の行列式を返す。特異行列なら `0`

## 使い方
`A` を `vector<vector<mint>>` で渡す。
入力は値渡しなので、呼び出し元の行列は壊れない。
