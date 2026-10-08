---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_matrix_determinant_mod.test.cpp
    title: test/yosupo_aplusb_matrix_determinant_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_det_arbitrary_mod.test.cpp
    title: test/yosupo_matrix_det_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_det_arbitrary_mod_modint.test.cpp
    title: test/yosupo_matrix_det_arbitrary_mod_modint.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4EFB\u610F mod \u306E\u884C\u5217\u5F0F"
    links: []
  bundledCode: "#line 1 \"math/matrix_determinant_mod.cpp\"\nll matrix_determinant_mod(vector<vector<ll>>\
    \ A, int mod) {\n    assert(mod >= 1);\n    int n = A.size();\n    for (auto&\
    \ row : A) {\n        assert((int)row.size() == n);\n        for (auto& x : row)\
    \ {\n            x %= mod;\n            if (x < 0) x += mod;\n        }\n    }\n\
    \    ll det = 1 % mod;\n    for (int col = 0; col < n; ++col) {\n        for (int\
    \ row = col + 1; row < n; ++row) {\n            while (A[row][col]) {\n      \
    \          ll quotient = A[col][col] / A[row][col];\n                for (int\
    \ j = col; j < n; ++j) {\n                    A[col][j] = (A[col][j] - quotient\
    \ * A[row][j]) % mod;\n                    if (A[col][j] < 0) A[col][j] += mod;\n\
    \                }\n                swap(A[col], A[row]);\n                det\
    \ = -det;\n            }\n        }\n        if (A[col][col] == 0) return 0;\n\
    \        det = det * A[col][col] % mod;\n    }\n    if (det < 0) det += mod;\n\
    \    return det;\n}\n\ntemplate<class Mint>\nMint matrix_determinant_mod(const\
    \ vector<vector<Mint>>& A) {\n    auto mod = Mint::get_mod();\n    assert(1 <=\
    \ mod && mod <= INT_MAX);\n    int n = A.size();\n    vector<vector<ll>> values(n,\
    \ vector<ll>(n));\n    for (int i = 0; i < n; ++i) {\n        assert((int)A[i].size()\
    \ == n);\n        for (int j = 0; j < n; ++j) values[i][j] = A[i][j].value();\n\
    \    }\n    return Mint(matrix_determinant_mod(move(values), (int)mod));\n}\n\n\
    /**\n * @brief \u4EFB\u610F mod \u306E\u884C\u5217\u5F0F\n */\n"
  code: "ll matrix_determinant_mod(vector<vector<ll>> A, int mod) {\n    assert(mod\
    \ >= 1);\n    int n = A.size();\n    for (auto& row : A) {\n        assert((int)row.size()\
    \ == n);\n        for (auto& x : row) {\n            x %= mod;\n            if\
    \ (x < 0) x += mod;\n        }\n    }\n    ll det = 1 % mod;\n    for (int col\
    \ = 0; col < n; ++col) {\n        for (int row = col + 1; row < n; ++row) {\n\
    \            while (A[row][col]) {\n                ll quotient = A[col][col]\
    \ / A[row][col];\n                for (int j = col; j < n; ++j) {\n          \
    \          A[col][j] = (A[col][j] - quotient * A[row][j]) % mod;\n           \
    \         if (A[col][j] < 0) A[col][j] += mod;\n                }\n          \
    \      swap(A[col], A[row]);\n                det = -det;\n            }\n   \
    \     }\n        if (A[col][col] == 0) return 0;\n        det = det * A[col][col]\
    \ % mod;\n    }\n    if (det < 0) det += mod;\n    return det;\n}\n\ntemplate<class\
    \ Mint>\nMint matrix_determinant_mod(const vector<vector<Mint>>& A) {\n    auto\
    \ mod = Mint::get_mod();\n    assert(1 <= mod && mod <= INT_MAX);\n    int n =\
    \ A.size();\n    vector<vector<ll>> values(n, vector<ll>(n));\n    for (int i\
    \ = 0; i < n; ++i) {\n        assert((int)A[i].size() == n);\n        for (int\
    \ j = 0; j < n; ++j) values[i][j] = A[i][j].value();\n    }\n    return Mint(matrix_determinant_mod(move(values),\
    \ (int)mod));\n}\n\n/**\n * @brief \u4EFB\u610F mod \u306E\u884C\u5217\u5F0F\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix_determinant_mod.cpp
  requiredBy: []
  timestamp: '2026-10-08 23:48:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_matrix_det_arbitrary_mod.test.cpp
  - test/yosupo_aplusb_matrix_determinant_mod.test.cpp
  - test/yosupo_matrix_det_arbitrary_mod_modint.test.cpp
date: 2026-10-08
documentation_of: math/matrix_determinant_mod.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u4EFB\u610F mod \u306E\u884C\u5217\u5F0F"
---

## 説明
合成数を含む任意 mod で正方行列の行列式を求める。
逆元を使わず、整数商による行の加減算と交換で上三角化する。
時間は $O(N^3\log m)$、入力コピーを含む領域は $O(N^2)$。

## できること
- `ll matrix_determinant_mod(vector<vector<ll>> A, int mod)`
  入力を保持して行列式を `[0, mod)` に正規化して返す。空行列は `1 % mod`、mod 1 では常に0
- `Mint matrix_determinant_mod(const vector<vector<Mint>>& A)`
  `modint` 行列の行列式を同じ型で返す。mod は `Mint::get_mod()` から取得し、入力は保持する

## 使い方
正方行列 `A` と $1 \le \mathrm{mod} \le \mathrm{INT\_MAX}$ を渡す。
要素は負の値を含む `long long` の全範囲を受け取る。
整数行列では mod を第2引数に渡す。
`modint` 行列では `matrix_determinant_mod(A)` とする。固定 mod 版と実行時 mod 版の両方に対応する。
実行時 mod 版は行列を作る前に `Mint::set_mod(mod)` を呼ぶ。対応する mod の範囲は整数行列と同じとする。
`Mint` には `get_mod()`、`value()`、整数からの構築を使い、逆元や除算は要求しない。

素数 mod では $O(N^3)$ の `math/matrix_determinant.cpp` も使える。

## 例
`Mint` を `modint<6>` とした場合も、そのまま計算できる。

```cpp
using Mint = modint<6>;
vector<vector<Mint>> A = { {2, 1}, {3, 2} };
Mint det = matrix_determinant_mod(A);
Mint doubled = det * 2;
```

`det` は1、`doubled` は2になる。
