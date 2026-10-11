---
title: Suffix ArrayによるLCE・部分文字列比較
documentation_of: //string/suffix_array_query.cpp
---

## 説明
固定した文字列や配列について、任意の位置からの最長共通接頭辞と、部分列の辞書順比較を求める。
長さを $N$ として、構築は $O(N\log(N+1))$ 時間・領域、各クエリは $O(1)$ 時間。

## できること
- `SuffixArrayQuery q(s)`
  `string` または `vector<T>` から構築する。入力は変更しない
- `int lce(int i, int j) const`
  `s[i..N)` と `s[j..N)` の最長共通接頭辞の長さを返す
- `int compare(int l1, int r1, int l2, int r2) const`
  `s[l1..r1)` と `s[l2..r2)` を辞書順で比較し、小さい・等しい・大きい場合にそれぞれ `-1`・`0`・`1` を返す

## 使い方
添字は $0$ 以上 $N$ 以下、区間は半開区間で指定する。空区間や末尾 $N$ も指定できる。
文字列は符号なし byte 順で比較する。`vector<T>` では `<` と `==`・`!=` が整合することを前提とする。

```cpp
SuffixArrayQuery q(string("banana"));
int common = q.lce(1, 3);
int order = q.compare(1, 4, 3, 6);
```

この例では `common` は `3`、`order` は `0` となる。

## 実装上の補足
Suffix Array の逆順列と LCP 配列の Sparse Table を持つ。
比較のたびに部分文字列をコピーする必要はない。
