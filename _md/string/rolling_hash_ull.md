---
title: Rolling Hash(mod 2^61-1)
documentation_of: //string/rolling_hash_ull.cpp
---

## 説明
mod $2^{61}-1$ で文字列や整数列の区間のハッシュを求める。

## できること
`s` には文字列リテラル、`string`、`string_view`、または 64 ビット以下の整数型を要素とする `vector<T>` を渡せる。
文字列と `char`、`signed char`、`unsigned char` の配列は符号なしバイト列として扱う。他の整数は mod $2^{61}-1$ の最小非負剰余として扱う。
結合や比較には同じ mod と base で計算したハッシュを使う。

- `rolling_hash_ull rh(s)`
  列 `s` の prefix hash を構築する。$O(|s|)$
- `rolling_hash_ull rh(n)`
  base の $n$ 乗までを共有の冪テーブルに用意する。$O(n)$
- `ull get(int l, int r) const`
  半開区間 `s[l, r)` のハッシュを返す。$O(1)$
- `static ull val(s)`
  列全体のハッシュを返す。時間 $O(|s|)$、追加領域 $O(1)$
- `static ull concat(ull h1, ull h2, int len2)`
  ハッシュ `h1` の列に、長さ `len2`、ハッシュ `h2` の列をつないだときのハッシュを返す。冪テーブルに `len2` 乗まであれば $O(1)$、拡張する場合は $O(\mathrm{len2})$
- `int lcp(int l1, int r1, const rolling_hash_ull& other, int l2, int r2) const`
  自分の列の `[l1, r1)` と `other` の列の `[l2, r2)` の最長共通接頭辞長を返す。短い方の区間長を $L$ として $O(\log L)$
- `static ull& B()`
  使用中の base を返す。$O(1)$
- `static vector<ull>& p()`
  添字 $i$ に base の $i$ 乗を mod $2^{61}-1$ で格納した冪テーブルを返す。$O(1)$

## 使い方
```cpp
const rolling_hash_ull a("banana"), b("ananas");
int length = a.lcp(1, 6, b, 0, 6);  // 5
```

## 実装上の補足
すべての `rolling_hash_ull` インスタンスは初回に乱択した base と冪テーブルを共有する。
計算済みのハッシュを使う間は base を変えない。ハッシュが衝突すると、異なる区間を等しいと判定することがある。
