---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_xor_basis.test.cpp
    title: test/yosupo_aplusb_xor_basis.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_xor_basis_intersection.test.cpp
    title: test/yosupo_aplusb_xor_basis_intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_intersection_of_f2_vector_spaces.test.cpp
    title: test/yosupo_intersection_of_f2_vector_spaces.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki2672_xor_basis.test.cpp
    title: test/yuki2672_xor_basis.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "XOR\u57FA\u5E95(Linear Basis)"
    links: []
  bundledCode: "#line 1 \"math/xor_basis.cpp\"\ntemplate<class T>\nstruct XorBasis\
    \ {\n    static_assert(is_integral_v<T>, \"XorBasis requires integral T\");\n\n\
    \    using U = make_unsigned_t<T>;\n    static constexpr int B = numeric_limits<U>::digits;\n\
    \n    vector<U> basis;\n    int rank = 0;\n\n    XorBasis() : basis(B, 0) {}\n\
    \n    int size() const {\n        return rank;\n    }\n\n    bool empty() const\
    \ {\n        return rank == 0;\n    }\n\n    bool add(T x) {\n        U y = reduce_unsigned(static_cast<U>(x));\n\
    \        if (y == 0) return false;\n\n        int p = B - 1;\n        while (((y\
    \ >> p) & 1) == 0) --p;\n        for (int i = 0; i < p; ++i) {\n            if\
    \ ((y >> i) & 1) y ^= basis[i];\n        }\n        basis[p] = y;\n        ++rank;\n\
    \        for (int i = p + 1; i < B; ++i) {\n            if ((basis[i] >> p) &\
    \ 1) basis[i] ^= y;\n        }\n        return true;\n    }\n\n    bool contains(T\
    \ x) const {\n        return reduce_unsigned(static_cast<U>(x)) == 0;\n    }\n\
    \n    T get_min(T x = 0) const {\n        return static_cast<T>(reduce_unsigned(static_cast<U>(x)));\n\
    \    }\n\n    T get_max(T x = 0) const {\n        U y = static_cast<U>(x);\n \
    \       for (int i = B - 1; i >= 0; --i) {\n            if (basis[i] == 0) continue;\n\
    \            U z = y ^ basis[i];\n            if (z > y) y = z;\n        }\n \
    \       return static_cast<T>(y);\n    }\n\n    optional<T> kth(U k) const {\n\
    \        if (rank < B && k >= (U(1) << rank)) return nullopt;\n        U value\
    \ = 0;\n        for (int i = 0; i < B; ++i) {\n            if (basis[i] == 0)\
    \ continue;\n            if (k & 1) value ^= basis[i];\n            k >>= 1;\n\
    \        }\n        return static_cast<T>(value);\n    }\n\n    U order_of_key(T\
    \ x) const {\n        U target = static_cast<U>(x), value = 0, result = 0;\n \
    \       int remaining = rank;\n        for (int i = B - 1; i >= 0; --i) {\n  \
    \          if (basis[i] != 0) {\n                --remaining;\n              \
    \  if ((target >> i) & 1) {\n                    result += U(1) << remaining;\n\
    \                    value ^= basis[i];\n                }\n            } else\
    \ if (((value ^ target) >> i) & 1) {\n                if ((target >> i) & 1) result\
    \ += U(1) << remaining;\n                break;\n            }\n        }\n  \
    \      return result;\n    }\n\n    void merge(const XorBasis &other) {\n    \
    \    for (int i = 0; i < B; ++i) {\n            if (other.basis[i] != 0) add(static_cast<T>(other.basis[i]));\n\
    \        }\n    }\n\n    XorBasis intersection(const XorBasis &other) const {\n\
    \        U row[B], from_a[B];\n        for (int i = 0; i < B; ++i) row[i] = from_a[i]\
    \ = basis[i];\n        XorBasis result;\n        for (int i = 0; i < B; ++i) {\n\
    \            U x = other.basis[i], y = 0;\n            if (x == 0) continue;\n\
    \            for (int j = B - 1; j >= 0; --j) {\n                if (((x >> j)\
    \ & 1) == 0) continue;\n                if (row[j] == 0) {\n                 \
    \   row[j] = x;\n                    from_a[j] = y;\n                    break;\n\
    \                }\n                x ^= row[j];\n                y ^= from_a[j];\n\
    \            }\n            if (x == 0) result.add(static_cast<T>(y));\n     \
    \   }\n        return result;\n    }\n\nprivate:\n    U reduce_unsigned(U x) const\
    \ {\n        for (int i = B - 1; i >= 0; --i) {\n            if (((x >> i) & 1)\
    \ == 0 || basis[i] == 0) continue;\n            x ^= basis[i];\n        }\n  \
    \      return x;\n    }\n};\n\n/**\n * @brief XOR\u57FA\u5E95(Linear Basis)\n\
    \ */\n"
  code: "template<class T>\nstruct XorBasis {\n    static_assert(is_integral_v<T>,\
    \ \"XorBasis requires integral T\");\n\n    using U = make_unsigned_t<T>;\n  \
    \  static constexpr int B = numeric_limits<U>::digits;\n\n    vector<U> basis;\n\
    \    int rank = 0;\n\n    XorBasis() : basis(B, 0) {}\n\n    int size() const\
    \ {\n        return rank;\n    }\n\n    bool empty() const {\n        return rank\
    \ == 0;\n    }\n\n    bool add(T x) {\n        U y = reduce_unsigned(static_cast<U>(x));\n\
    \        if (y == 0) return false;\n\n        int p = B - 1;\n        while (((y\
    \ >> p) & 1) == 0) --p;\n        for (int i = 0; i < p; ++i) {\n            if\
    \ ((y >> i) & 1) y ^= basis[i];\n        }\n        basis[p] = y;\n        ++rank;\n\
    \        for (int i = p + 1; i < B; ++i) {\n            if ((basis[i] >> p) &\
    \ 1) basis[i] ^= y;\n        }\n        return true;\n    }\n\n    bool contains(T\
    \ x) const {\n        return reduce_unsigned(static_cast<U>(x)) == 0;\n    }\n\
    \n    T get_min(T x = 0) const {\n        return static_cast<T>(reduce_unsigned(static_cast<U>(x)));\n\
    \    }\n\n    T get_max(T x = 0) const {\n        U y = static_cast<U>(x);\n \
    \       for (int i = B - 1; i >= 0; --i) {\n            if (basis[i] == 0) continue;\n\
    \            U z = y ^ basis[i];\n            if (z > y) y = z;\n        }\n \
    \       return static_cast<T>(y);\n    }\n\n    optional<T> kth(U k) const {\n\
    \        if (rank < B && k >= (U(1) << rank)) return nullopt;\n        U value\
    \ = 0;\n        for (int i = 0; i < B; ++i) {\n            if (basis[i] == 0)\
    \ continue;\n            if (k & 1) value ^= basis[i];\n            k >>= 1;\n\
    \        }\n        return static_cast<T>(value);\n    }\n\n    U order_of_key(T\
    \ x) const {\n        U target = static_cast<U>(x), value = 0, result = 0;\n \
    \       int remaining = rank;\n        for (int i = B - 1; i >= 0; --i) {\n  \
    \          if (basis[i] != 0) {\n                --remaining;\n              \
    \  if ((target >> i) & 1) {\n                    result += U(1) << remaining;\n\
    \                    value ^= basis[i];\n                }\n            } else\
    \ if (((value ^ target) >> i) & 1) {\n                if ((target >> i) & 1) result\
    \ += U(1) << remaining;\n                break;\n            }\n        }\n  \
    \      return result;\n    }\n\n    void merge(const XorBasis &other) {\n    \
    \    for (int i = 0; i < B; ++i) {\n            if (other.basis[i] != 0) add(static_cast<T>(other.basis[i]));\n\
    \        }\n    }\n\n    XorBasis intersection(const XorBasis &other) const {\n\
    \        U row[B], from_a[B];\n        for (int i = 0; i < B; ++i) row[i] = from_a[i]\
    \ = basis[i];\n        XorBasis result;\n        for (int i = 0; i < B; ++i) {\n\
    \            U x = other.basis[i], y = 0;\n            if (x == 0) continue;\n\
    \            for (int j = B - 1; j >= 0; --j) {\n                if (((x >> j)\
    \ & 1) == 0) continue;\n                if (row[j] == 0) {\n                 \
    \   row[j] = x;\n                    from_a[j] = y;\n                    break;\n\
    \                }\n                x ^= row[j];\n                y ^= from_a[j];\n\
    \            }\n            if (x == 0) result.add(static_cast<T>(y));\n     \
    \   }\n        return result;\n    }\n\nprivate:\n    U reduce_unsigned(U x) const\
    \ {\n        for (int i = B - 1; i >= 0; --i) {\n            if (((x >> i) & 1)\
    \ == 0 || basis[i] == 0) continue;\n            x ^= basis[i];\n        }\n  \
    \      return x;\n    }\n};\n\n/**\n * @brief XOR\u57FA\u5E95(Linear Basis)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/xor_basis.cpp
  requiredBy: []
  timestamp: '2026-10-18 00:53:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_intersection_of_f2_vector_spaces.test.cpp
  - test/yosupo_aplusb_xor_basis.test.cpp
  - test/yosupo_aplusb_xor_basis_intersection.test.cpp
  - test/yuki2672_xor_basis.test.cpp
date: 2026-03-12
documentation_of: math/xor_basis.cpp
layout: document
tags: "\u6570\u5B66"
title: "XOR\u57FA\u5E95(Linear Basis)"
---

## 説明
整数列から xor 基底を構築する。
基底の本数を $k$ とすると、表現できる相異なる値の個数は $2^k$。

## できること
- `XorBasis<T> xb`
  空の xor 基底を作る
- `int size()`
  基底の本数を返す
- `bool empty()`
  基底が空なら `true`
- `bool add(T x)`
  `x` を基底に追加する。独立なら `true`、追加されなければ `false`
- `bool contains(T x)`
  `x` を基底で表せるなら `true`、表せなければ `false`
- `T get_min(T x = 0)`
  `x xor y` を最小にする `y` を基底の生成する空間から選んだ結果を返す
- `T get_max(T x = 0)`
  `x xor y` を最大にする `y` を基底の生成する空間から選んだ結果を返す
- `optional<T> kth(U k) const`
  表現できる相異なる値のうち、小さい順で `k` 番目を返す。0-indexed で、範囲外なら `nullopt`
- `U order_of_key(T x) const`
  表現できる相異なる値のうち、`x` 未満の個数を返す。`U = make_unsigned_t<T>` とし、`kth` とともに時間 $O(B)$、追加領域 $O(1)$。$B$ は `T` の bit 幅
- `void merge(const XorBasis<T>& other)`
  `other` の基底を併合する
- `XorBasis<T> intersection(const XorBasis<T>& other) const`
  両方の生成空間に属する値全体の基底を返す。入力は変更しない。片方が空なら空の基底を返す。bit 幅を $B$ として時間 $O(B^2)$、返却値を含む追加領域 $O(B)$

## 使い方
`add` で値を順に入れて使う。
空の基底が表す集合は `{0}` であり、`kth(0)` は `0` を返す。
`contains(x)` で表現可能性を判定でき、`get_min(x)` と `get_max(x)` で
$$
\min_{y \in \langle S \rangle} (x \oplus y), \quad \max_{y \in \langle S \rangle} (x \oplus y)
$$
を求められる。
`{1, 2}` と `{3, 4}` が生成する空間の共通部分は `{0, 3}` であり、`intersection` はこれを生成する基底を返す。

## 実装上の補足
- `T` は `bool` 以外の整数型を使う。値は `make_unsigned_t<T>` の bit 列として扱い、大小は符号なしで比較する
- `get_min` と `get_max` は `x xor y` そのものを返す
