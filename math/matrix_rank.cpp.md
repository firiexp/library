---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  - icon: ':heavy_check_mark:'
    path: util/modint_base.cpp
    title: util/modint_base.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_matrix_rank.test.cpp
    title: test/yosupo_aplusb_matrix_rank.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_rank.test.cpp
    title: test/yosupo_matrix_rank.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u884C\u5217\u306E\u968E\u6570"
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\n\n\n\n#line 1 \"util/modint_base.cpp\"\
    \n\n\n\ntemplate <uint Mod>\nstruct modint {\n    uint val;\npublic:\n    static\
    \ modint raw(int v) { modint x; x.val = v; return x; }\n    static constexpr uint\
    \ get_mod() { return Mod; }\n    static constexpr uint M() { return Mod; }\n \
    \   modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v\
    \ % (ll)(Mod)); if (x < 0) x += Mod; val = uint(x); }\n    modint(bool v) { val\
    \ = ((unsigned int)(v) % Mod); }\n    uint &value() noexcept { return val; }\n\
    \    const uint &value() const noexcept { return val; }\n    modint& operator++()\
    \ { val++; if (val == Mod) val = 0; return *this; }\n    modint& operator--()\
    \ { if (val == 0) val = Mod; val--; return *this; }\n    modint operator++(int)\
    \ { modint result = *this; ++*this; return result; }\n    modint operator--(int)\
    \ { modint result = *this; --*this; return result; }\n    modint& operator+=(const\
    \ modint& b) { val += b.val; if (val >= Mod) val -= Mod; return *this; }\n   \
    \ modint& operator-=(const modint& b) { val -= b.val; if (val >= Mod) val += Mod;\
    \ return *this; }\n    modint& operator*=(const modint& b) { ull z = val; z *=\
    \ b.val; val = (uint)(z % Mod); return *this; }\n    modint& operator/=(const\
    \ modint& b) { return *this = *this * b.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(Mod - 2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 5 \"util/modint.cpp\"\
    \n\n#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\nusing mint = modint<MOD>;\n#define\
    \ FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n#else\nstatic_assert(mint::get_mod() ==\
    \ MOD, \"mint is already defined with a different modulus\");\n#endif\n\n/**\n\
    \ * @brief modint(\u56FA\u5B9AMOD)\n */\n\n\n#line 2 \"math/matrix_rank.cpp\"\n\
    \nint matrix_rank(vector<vector<mint>> A) {\n    int h = A.size(), w = h ? A[0].size()\
    \ : 0;\n    int rank = 0;\n    for (int col = 0; col < w && rank < h; ++col) {\n\
    \        int pivot = rank;\n        while (pivot < h && A[pivot][col] == mint(0))\
    \ ++pivot;\n        if (pivot == h) continue;\n        swap(A[pivot], A[rank]);\n\
    \        mint inv = A[rank][col].inv();\n        for (int row = rank + 1; row\
    \ < h; ++row) {\n            if (A[row][col] == mint(0)) continue;\n         \
    \   mint factor = A[row][col] * inv;\n            for (int j = col + 1; j < w;\
    \ ++j) A[row][j] -= A[rank][j] * factor;\n        }\n        ++rank;\n    }\n\
    \    return rank;\n}\n\n/**\n * @brief \u884C\u5217\u306E\u968E\u6570\n */\n"
  code: "#include \"../util/modint.cpp\"\n\nint matrix_rank(vector<vector<mint>> A)\
    \ {\n    int h = A.size(), w = h ? A[0].size() : 0;\n    int rank = 0;\n    for\
    \ (int col = 0; col < w && rank < h; ++col) {\n        int pivot = rank;\n   \
    \     while (pivot < h && A[pivot][col] == mint(0)) ++pivot;\n        if (pivot\
    \ == h) continue;\n        swap(A[pivot], A[rank]);\n        mint inv = A[rank][col].inv();\n\
    \        for (int row = rank + 1; row < h; ++row) {\n            if (A[row][col]\
    \ == mint(0)) continue;\n            mint factor = A[row][col] * inv;\n      \
    \      for (int j = col + 1; j < w; ++j) A[row][j] -= A[rank][j] * factor;\n \
    \       }\n        ++rank;\n    }\n    return rank;\n}\n\n/**\n * @brief \u884C\
    \u5217\u306E\u968E\u6570\n */\n"
  dependsOn:
  - util/modint.cpp
  - util/modint_base.cpp
  isVerificationFile: false
  path: math/matrix_rank.cpp
  requiredBy: []
  timestamp: '2026-10-18 09:26:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_matrix_rank.test.cpp
  - test/yosupo_aplusb_matrix_rank.test.cpp
date: 2026-10-18
documentation_of: math/matrix_rank.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u884C\u5217\u306E\u968E\u6570"
---

## 説明
素数を法とする `mint` の行列から、前進消去で階数を求める。
$H$ 行 $W$ 列に対し、時間 $O(HW\min(H,W))$、作業領域 $O(HW)$。

## できること
- `int matrix_rank(vector<vector<mint>> A)`
  行列の階数を返す。空行列・0列の行列では `0`

## 使い方
各行の長さが等しい行列を渡す。入力は値で受け取り、呼び出し元の行列を変更しない。
元の行列が不要なら `matrix_rank(std::move(A))` でコピーを省ける。
簡約行基本形も必要な場合は `gauss_jordan` を使う。

## 実装上の補足
pivot 行を正規化せず、下側の未確定行だけを消去する。
消去済みの列は以降参照せず、上側の行も更新しない。
