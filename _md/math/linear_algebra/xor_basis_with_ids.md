---
title: 入力IDの復元付きXOR基底
documentation_of: //math/linear_algebra/xor_basis_with_ids.cpp
---

## 説明
指定した値をxorで作る元入力のID集合を復元する。
`T` は `bool` 以外の64bit以下の整数型とし、符号付き型もビット列として扱う。

## できること
$B$ を整数型 `T` のビット数とする。

- `XorBasisWithIds<T> xb`
  空の基底を作る。時間・保持領域ともに $O(B)$。
- `bool add(T value, int id)`
  値と入力IDを追加する。独立なら `true`、従属または0なら `false`。IDは呼び出しごとに異なる必要がある。$O(B)$。
- `optional<vector<int>> representation(T value) const`
  xor が `value` になる入力ID列を任意に1つ返す。表せなければ `nullopt`、0なら空列。$O(B)$。
- `int size() const`
  基底の本数を返す。$O(1)$。
- `bool empty() const`
  基底が空なら `true`。$O(1)$。

## 使い方
```cpp
XorBasisWithIds<unsigned long long> xb;
for (int i = 0; i < (int)a.size(); ++i) xb.add(a[i], i);
auto ids = xb.representation(target);
if (ids) {
    for (int id : *ids) use(a[id]);
}
```

## 実装上の補足
独立な元入力を高々 $B$ 個保持し、その組合せを係数マスクで管理する。
