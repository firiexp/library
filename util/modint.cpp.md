---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/factorial.cpp
    title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
  - icon: ':heavy_check_mark:'
    path: math/fft.cpp
    title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
  - icon: ':heavy_check_mark:'
    path: math/gauss_jordan_mint.cpp
    title: "Gauss-Jordan\u6D88\u53BB(modint)"
  - icon: ':heavy_check_mark:'
    path: math/inverse_matrix.cpp
    title: "\u9006\u884C\u5217(Inverse Matrix)"
  - icon: ':heavy_check_mark:'
    path: math/matrix_determinant.cpp
    title: "\u884C\u5217\u5F0F(Matrix Determinant)"
  - icon: ':warning:'
    path: math/powk_all.cpp
    title: math/powk_all.cpp
  - icon: ':heavy_check_mark:'
    path: math/squarematrix_mint.cpp
    title: "\u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\u7528)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0399.test.cpp
    title: test/aoj0399.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj2257.test.cpp
    title: test/aoj2257.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_dpl_5_a.test.cpp
    title: test/aoj_dpl_5_a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bitwise_and_convolution.test.cpp
    title: test/yosupo_bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bitwise_or_convolution.test.cpp
    title: test/yosupo_bitwise_or_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bitwise_xor_convolution.test.cpp
    title: test/yosupo_bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_convolution_mod_1000000007_fft.test.cpp
    title: test/yosupo_convolution_mod_1000000007_fft.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_deque_operate_all_composite.test.cpp
    title: test/yosupo_deque_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_find_linear_recurrence.test.cpp
    title: test/yosupo_find_linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_inverse_matrix.test.cpp
    title: test/yosupo_inverse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_modint_interface.test.cpp
    title: test/yosupo_many_aplusb_modint_interface.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_det.test.cpp
    title: test/yosupo_matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_product.test.cpp
    title: test/yosupo_matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_matrix_rank.test.cpp
    title: test/yosupo_matrix_rank.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_set_range_composite.test.cpp
    title: test/yosupo_point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_pow_of_matrix.test.cpp
    title: test/yosupo_pow_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_queue_operate_all_composite.test.cpp
    title: test/yosupo_queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
    title: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_affine_range_sum.test.cpp
    title: test/yosupo_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_subset_convolution.test.cpp
    title: test/yosupo_subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sum_of_totient.test.cpp
    title: test/yosupo_sum_of_totient.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_system_of_linear_equations.test.cpp
    title: test/yosupo_system_of_linear_equations.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite.test.cpp
    title: test/yosupo_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
    title: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki650_hld_edge.test.cpp
    title: test/yuki650_hld_edge.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "modint(\u56FA\u5B9AMOD)"
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint\
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
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n"
  code: "#ifndef FIRIEXP_LIBRARY_UTIL_MODINT_CPP\n#define FIRIEXP_LIBRARY_UTIL_MODINT_CPP\n\
    \ntemplate <uint Mod>\nstruct modint {\n    uint val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    static constexpr uint get_mod()\
    \ { return Mod; }\n    static constexpr uint M() { return Mod; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod));\
    \ if (x < 0) x += Mod; val = uint(x); }\n    modint(bool v) { val = ((unsigned\
    \ int)(v) % Mod); }\n    uint &value() noexcept { return val; }\n    const uint\
    \ &value() const noexcept { return val; }\n    modint& operator++() { val++; if\
    \ (val == Mod) val = 0; return *this; }\n    modint& operator--() { if (val ==\
    \ 0) val = Mod; val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint& operator+=(const modint& b)\
    \ { val += b.val; if (val >= Mod) val -= Mod; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= Mod) val += Mod; return *this; }\n   \
    \ modint& operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z\
    \ % Mod); return *this; }\n    modint& operator/=(const modint& b) { return *this\
    \ = *this * b.inv(); }\n    modint operator+() const { return *this; }\n    modint\
    \ operator-() const { return modint() - *this; }\n    modint pow(long long n)\
    \ const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>=\
    \ 1; } return r; }\n    modint inv() const { return pow(Mod - 2); }\n    friend\
    \ modint operator+(const modint& a, const modint& b) { return modint(a) += b;\
    \ }\n    friend modint operator-(const modint& a, const modint& b) { return modint(a)\
    \ -= b; }\n    friend modint operator*(const modint& a, const modint& b) { return\
    \ modint(a) *= b; }\n    friend modint operator/(const modint& a, const modint&\
    \ b) { return modint(a) /= b; }\n    friend bool operator==(const modint& a, const\
    \ modint& b) { return a.val == b.val; }\n    friend bool operator!=(const modint&\
    \ a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: util/modint.cpp
  requiredBy:
  - math/gauss_jordan_mint.cpp
  - math/matrix_determinant.cpp
  - math/fft.cpp
  - math/powk_all.cpp
  - math/squarematrix_mint.cpp
  - math/factorial.cpp
  - math/inverse_matrix.cpp
  timestamp: '2026-03-14 20:56:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0399.test.cpp
  - test/yosupo_pow_of_matrix.test.cpp
  - test/yosupo_point_set_range_composite.test.cpp
  - test/yosupo_deque_operate_all_composite.test.cpp
  - test/yosupo_system_of_linear_equations.test.cpp
  - test/yosupo_many_aplusb_modint_interface.test.cpp
  - test/yosupo_inverse_matrix.test.cpp
  - test/yosupo_bitwise_and_convolution.test.cpp
  - test/yosupo_range_affine_range_sum.test.cpp
  - test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - test/yosupo_sum_of_totient.test.cpp
  - test/yosupo_convolution_mod_1000000007_fft.test.cpp
  - test/yosupo_bitwise_xor_convolution.test.cpp
  - test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
  - test/aoj2257.test.cpp
  - test/aoj_dpl_5_a.test.cpp
  - test/yosupo_subset_convolution.test.cpp
  - test/yosupo_matrix_product.test.cpp
  - test/yosupo_matrix_rank.test.cpp
  - test/yosupo_matrix_det.test.cpp
  - test/yosupo_find_linear_recurrence.test.cpp
  - test/yosupo_bitwise_or_convolution.test.cpp
  - test/yuki650_hld_edge.test.cpp
  - test/yosupo_vertex_set_path_composite.test.cpp
  - test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
  - test/yosupo_range_affine_point_get_dualsegtree.test.cpp
  - test/yosupo_queue_operate_all_composite.test.cpp
date: 2026-03-14
documentation_of: util/modint.cpp
layout: document
tags: "\u6570\u5B66"
title: "modint(\u56FA\u5B9AMOD)"
---
## 説明
テンプレート引数で MOD を固定した剰余整数を扱う。
`+ - * /`、累乗、逆元、インクリメントを持つ。

## できること
- `modint<MOD> x`, `mint x`
  `MOD` 上の値を作る。負数もそのまま渡せる
- `modint<MOD>::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る
- `modint<MOD>::get_mod()`, `modint<MOD>::M()`
  MOD を返す
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
`MOD` を定義してから `#include "../util/modint.cpp"` し、`mint` か `modint<MOD>` を使う。
`/` と `inv()` は `MOD` が素数で、対象が `0` でない状況を前提にしている。
