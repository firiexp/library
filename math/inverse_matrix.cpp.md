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
    path: test/yosupo_inverse_matrix.test.cpp
    title: test/yosupo_inverse_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9006\u884C\u5217(Inverse Matrix)"
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint M>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T\
    \ v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }\n    modint(bool\
    \ v) { val = ((unsigned int)(v) % M); }\n    modint& operator++() { val++; if\
    \ (val == M) val = 0; return *this; }\n    modint& operator--() { if (val == 0)\
    \ val = M; val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint& operator+=(const modint& b)\
    \ { val += b.val; if (val >= M) val -= M; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= M) val += M; return *this; }\n    modint&\
    \ operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z % M);\
    \ return *this; }\n    modint& operator/=(const modint& b) { return *this = *this\
    \ * b.inv(); }\n    modint operator+() const { return *this; }\n    modint operator-()\
    \ const { return modint() - *this; }\n    modint pow(long long n) const { modint\
    \ x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r;\
    \ }\n    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n */\n\n\n#line 2 \"math/inverse_matrix.cpp\"\
    \n\nvector<vector<mint>> inverse_matrix(const vector<vector<mint>> &A) {\n   \
    \ int n = A.size();\n    vector<vector<mint>> B(n, vector<mint>(2 * n));\n   \
    \ for (int i = 0; i < n; ++i) {\n        for (int j = 0; j < n; ++j) B[i][j] =\
    \ A[i][j];\n        B[i][n + i] = 1;\n    }\n    int rank = 0;\n    for (int col\
    \ = 0; col < n; ++col) {\n        int pivot = -1;\n        for (int row = rank;\
    \ row < n; ++row) {\n            if (B[row][col].val) {\n                pivot\
    \ = row;\n                break;\n            }\n        }\n        if (pivot\
    \ == -1) return {};\n        swap(B[pivot], B[rank]);\n        mint inv = B[rank][col].inv();\n\
    \        for (int j = 0; j < 2 * n; ++j) B[rank][j] *= inv;\n        for (int\
    \ row = 0; row < n; ++row) {\n            if (row != rank && B[row][col].val)\
    \ {\n                mint coeff = B[row][col];\n                for (int j = 0;\
    \ j < 2 * n; ++j) {\n                    B[row][j] -= B[rank][j] * coeff;\n  \
    \              }\n            }\n        }\n        ++rank;\n    }\n    vector<vector<mint>>\
    \ res(n, vector<mint>(n));\n    for (int i = 0; i < n; ++i) {\n        for (int\
    \ j = 0; j < n; ++j) res[i][j] = B[i][n + j];\n    }\n    return res;\n}\n\n/**\n\
    \ * @brief \u9006\u884C\u5217(Inverse Matrix)\n */\n"
  code: "#include \"../util/modint.cpp\"\n\nvector<vector<mint>> inverse_matrix(const\
    \ vector<vector<mint>> &A) {\n    int n = A.size();\n    vector<vector<mint>>\
    \ B(n, vector<mint>(2 * n));\n    for (int i = 0; i < n; ++i) {\n        for (int\
    \ j = 0; j < n; ++j) B[i][j] = A[i][j];\n        B[i][n + i] = 1;\n    }\n   \
    \ int rank = 0;\n    for (int col = 0; col < n; ++col) {\n        int pivot =\
    \ -1;\n        for (int row = rank; row < n; ++row) {\n            if (B[row][col].val)\
    \ {\n                pivot = row;\n                break;\n            }\n   \
    \     }\n        if (pivot == -1) return {};\n        swap(B[pivot], B[rank]);\n\
    \        mint inv = B[rank][col].inv();\n        for (int j = 0; j < 2 * n; ++j)\
    \ B[rank][j] *= inv;\n        for (int row = 0; row < n; ++row) {\n          \
    \  if (row != rank && B[row][col].val) {\n                mint coeff = B[row][col];\n\
    \                for (int j = 0; j < 2 * n; ++j) {\n                    B[row][j]\
    \ -= B[rank][j] * coeff;\n                }\n            }\n        }\n      \
    \  ++rank;\n    }\n    vector<vector<mint>> res(n, vector<mint>(n));\n    for\
    \ (int i = 0; i < n; ++i) {\n        for (int j = 0; j < n; ++j) res[i][j] = B[i][n\
    \ + j];\n    }\n    return res;\n}\n\n/**\n * @brief \u9006\u884C\u5217(Inverse\
    \ Matrix)\n */\n"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/inverse_matrix.cpp
  requiredBy: []
  timestamp: '2026-03-11 00:57:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_inverse_matrix.test.cpp
date: 2026-03-11
documentation_of: math/inverse_matrix.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u9006\u884C\u5217(Inverse Matrix)"
---

## 説明
`modint` 行列の逆行列を計算する。
Gauss-Jordan 消去を使い、計算量は `O(N^3)`。

## できること
- `vector<vector<mint>> inverse_matrix(const vector<vector<mint>>& A)`
  正方行列 `A` の逆行列を返す。存在しなければ空行列を返す

## 使い方
`A` を `vector<vector<mint>>` で渡す。
返り値が空でなければ `A^{-1}` が入っている。
