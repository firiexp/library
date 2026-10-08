---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/gauss_jordan_mint.cpp
    title: "Gauss-Jordan\u6D88\u53BB(modint)"
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  - icon: ':heavy_check_mark:'
    path: util/modint_base.cpp
    title: util/modint_base.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_solve_linear_system.test.cpp
    title: test/yosupo_aplusb_solve_linear_system.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_system_of_linear_equations.test.cpp
    title: test/yosupo_system_of_linear_equations.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9023\u7ACB\u4E00\u6B21\u65B9\u7A0B\u5F0F\u306E\u89E3\u7A7A\u9593"
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
    \ * @brief modint(\u56FA\u5B9AMOD)\n */\n\n\n#line 2 \"math/gauss_jordan_mint.cpp\"\
    \n\nint gauss_jordan(vector<vector<mint>> &A, bool is_extended = false) {\n  \
    \  int m = A.size(), n = A[0].size();\n    int rank = 0;\n    for (int col = 0;\
    \ col < n; ++col) {\n        if (is_extended && col == n-1) break;\n        int\
    \ pivot = -1;\n        for (int row = rank; row < m; ++row) {\n            if\
    \ (A[row][col].val) {\n                pivot = row;\n                break;\n\
    \            }\n        }\n        if (pivot == -1) continue;\n        swap(A[pivot],\
    \ A[rank]);\n        auto d = A[rank][col].inv();\n        for (int col2 = 0;\
    \ col2 < n; ++col2) A[rank][col2] *= d;\n        for (int row = 0; row < m; ++row)\
    \ {\n            if (row != rank && A[row][col].val) {\n                auto fac\
    \ = A[row][col];\n                for (int col2 = 0; col2 < n; ++col2) {\n   \
    \                 A[row][col2] -= A[rank][col2] * fac;\n                }\n  \
    \          }\n        }\n        ++rank;\n    }\n    return rank;\n}\n\n/**\n\
    \ * @brief Gauss-Jordan\u6D88\u53BB(modint)\n */\n#line 2 \"math/solve_linear_system.cpp\"\
    \n\nstruct LinearSystemSolution {\n    int rank;\n    vector<mint> particular;\n\
    \    vector<vector<mint>> basis;\n};\n\noptional<LinearSystemSolution> solve_linear_system(vector<vector<mint>>\
    \ A, const vector<mint>& b, int variables = -1) {\n    int n = A.size();\n   \
    \ assert(variables >= -1 && (int)b.size() == n);\n    int m = variables < 0 ?\
    \ (n ? (int)A[0].size() : 0) : variables;\n    for (int row = 0; row < n; ++row)\
    \ {\n        assert((int)A[row].size() == m);\n        A[row].push_back(b[row]);\n\
    \    }\n    int rank = n ? gauss_jordan(A, true) : 0;\n    for (int row = rank;\
    \ row < n; ++row) {\n        if (A[row][m].val) return nullopt;\n    }\n\n   \
    \ vector<int> pivot(rank), is_pivot(m);\n    for (int row = 0; row < rank; ++row)\
    \ {\n        for (int col = 0; col < m; ++col) {\n            if (A[row][col].val)\
    \ {\n                pivot[row] = col;\n                is_pivot[col] = 1;\n \
    \               break;\n            }\n        }\n    }\n\n    LinearSystemSolution\
    \ result{rank, vector<mint>(m), {}};\n    for (int row = 0; row < rank; ++row)\
    \ {\n        result.particular[pivot[row]] = A[row][m];\n    }\n    for (int col\
    \ = 0; col < m; ++col) {\n        if (is_pivot[col]) continue;\n        vector<mint>\
    \ v(m);\n        v[col] = 1;\n        for (int row = 0; row < rank; ++row) v[pivot[row]]\
    \ = -A[row][col];\n        result.basis.push_back(move(v));\n    }\n    return\
    \ result;\n}\n\n/**\n * @brief \u9023\u7ACB\u4E00\u6B21\u65B9\u7A0B\u5F0F\u306E\
    \u89E3\u7A7A\u9593\n */\n"
  code: "#include \"./gauss_jordan_mint.cpp\"\n\nstruct LinearSystemSolution {\n \
    \   int rank;\n    vector<mint> particular;\n    vector<vector<mint>> basis;\n\
    };\n\noptional<LinearSystemSolution> solve_linear_system(vector<vector<mint>>\
    \ A, const vector<mint>& b, int variables = -1) {\n    int n = A.size();\n   \
    \ assert(variables >= -1 && (int)b.size() == n);\n    int m = variables < 0 ?\
    \ (n ? (int)A[0].size() : 0) : variables;\n    for (int row = 0; row < n; ++row)\
    \ {\n        assert((int)A[row].size() == m);\n        A[row].push_back(b[row]);\n\
    \    }\n    int rank = n ? gauss_jordan(A, true) : 0;\n    for (int row = rank;\
    \ row < n; ++row) {\n        if (A[row][m].val) return nullopt;\n    }\n\n   \
    \ vector<int> pivot(rank), is_pivot(m);\n    for (int row = 0; row < rank; ++row)\
    \ {\n        for (int col = 0; col < m; ++col) {\n            if (A[row][col].val)\
    \ {\n                pivot[row] = col;\n                is_pivot[col] = 1;\n \
    \               break;\n            }\n        }\n    }\n\n    LinearSystemSolution\
    \ result{rank, vector<mint>(m), {}};\n    for (int row = 0; row < rank; ++row)\
    \ {\n        result.particular[pivot[row]] = A[row][m];\n    }\n    for (int col\
    \ = 0; col < m; ++col) {\n        if (is_pivot[col]) continue;\n        vector<mint>\
    \ v(m);\n        v[col] = 1;\n        for (int row = 0; row < rank; ++row) v[pivot[row]]\
    \ = -A[row][col];\n        result.basis.push_back(move(v));\n    }\n    return\
    \ result;\n}\n\n/**\n * @brief \u9023\u7ACB\u4E00\u6B21\u65B9\u7A0B\u5F0F\u306E\
    \u89E3\u7A7A\u9593\n */\n"
  dependsOn:
  - math/gauss_jordan_mint.cpp
  - util/modint.cpp
  - util/modint_base.cpp
  isVerificationFile: false
  path: math/solve_linear_system.cpp
  requiredBy: []
  timestamp: '2026-10-08 14:20:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_solve_linear_system.test.cpp
  - test/yosupo_system_of_linear_equations.test.cpp
date: 2026-10-08
documentation_of: math/solve_linear_system.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u9023\u7ACB\u4E00\u6B21\u65B9\u7A0B\u5F0F\u306E\u89E3\u7A7A\u9593"
---

## 説明
素数 mod の `mint` 上で、$Ax=b$ を満たす解を1つと、そこからすべての解を表すためのベクトル列を求める。
$N$ 行 $M$ 列の消去に $O(NM\min(N,M))$、基底の出力に $O(M(M-\mathrm{rank}))$ かかる。
入力のコピーと拡大係数列の作成に $O(NM)$、解ベクトルの確保に $O(M)$ を使う。

## できること
- `optional<LinearSystemSolution> solve_linear_system(A, b, int variables = -1)`
  入力 `A`, `b` を保持し、$Ax=b$ の解を1つと、すべての解を表すためのベクトル列を返す。解がなければ `nullopt`
- `LinearSystemSolution::rank`
  係数行列 `A` の階数
- `LinearSystemSolution::particular`
  $Ax=b$ を満たす長さ $M$ のベクトルを1つ持つ。消去で自由に選べる変数を0にした解
- `LinearSystemSolution::basis`
  $Av=0$ を満たす、互いに一次独立な長さ $M$ のベクトルを $M-\mathrm{rank}$ 本持つ。各ベクトルに任意の係数を掛けて `particular` に加えると、すべての解を表せる

## 使い方
`A` は `vector<vector<mint>>`、`b` は行数と同じ長さの `vector<mint>` で渡す。
通常は `auto sol = solve_linear_system(A, b);` とする。
成功時の全解は `sol->particular` に `sol->basis` の任意の線形結合を加えたものになる。
一意解では `basis` が空になる。

行数0では省略時の変数数を0とする。正の変数数が必要なら第3引数に指定する。
行数が正の場合は列数を自動で推論し、第3引数を渡す場合は列数と一致させる。
変数数0では `b` が全零のときだけ成功し、`particular` と `basis` はともに空になる。

## 例
mod 5 で $x+y=3$ を解くと、`particular = {3, 0}`、`basis = { {4, 1} }` になる。
すべての解は $(x,y)=(3,0)+t(4,1) \pmod 5$ と表せる。
例えば $t=1$ なら $(2,1)$、$t=3$ なら $(0,3)$ が得られる。
