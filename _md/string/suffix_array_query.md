---
title: 最長共通接頭辞・部分文字列の辞書順比較
documentation_of: //string/suffix_array_query.cpp
---

## 説明
与えられた文字列や配列を前処理し、指定した2つの位置からの最長共通接頭辞の長さを求める。
部分文字列の辞書順比較にも対応する。
長さを $N$ として、構築は $O(N\log(N))$ 時間・領域、各クエリは $O(1)$ 時間。

## できること
- `SuffixArrayQuery q(s)`
  `string` または `vector<T>` から構築する。入力は変更しない
- `int suffix_rank(int i) const`
  `s[i..N)` の辞書順の順位を $0$ 以上 $N$ 未満で返す。$0\le i<N$ が必要
- `int lce(int i, int j) const`
  `s[i..N)` と `s[j..N)` の最長共通接頭辞の長さを返す
- `int compare(int l1, int r1, int l2, int r2) const`
  `s[l1..r1)` と `s[l2..r2)` を辞書順で比較し、小さい・等しい・大きい場合にそれぞれ `-1`・`0`・`1` を返す

## 使い方
`lce` と `compare` の添字は $0$ 以上 $N$ 以下、区間は半開区間で指定する。空区間や末尾 $N$ も指定できる。
文字列は符号なし byte 順で比較する。`vector<T>` では `<` と `==`・`!=` が整合することを前提とする。

```cpp
SuffixArrayQuery q(string("banana"));
int common = q.lce(1, 3);
int order = q.compare(1, 4, 3, 6);
```

この例では `common` は `3`、`order` は `0` となる。

## 実装上の補足
Suffix Array の逆順列を使い、指定された2つの位置を suffix の順位に変換する。
構築済みの逆順列は LCP の構築にも使い、同じ配列の再構築を省く。
隣り合う suffix の最長共通接頭辞長を配列に持ち、その区間最小値を Sparse Table で $O(1)$ 時間で求める。
比較のたびに部分文字列をコピーする必要はない。
