---
title: Suffix Array
documentation_of: //string/suffix_array.cpp
---

## 説明
文字列や整数列の suffix array と LCP 配列を構築し、パターンが出現する範囲を求める。
固定テキストに複数のパターンを問い合わせるときに利用する。

## できること
入力列の長さを $N$、パターン長を $M$ とする。

- `SuffixArray sa(s)`
  `string` または `vector<T>` から構築する。時間は文字列で $O(N)$、整数列などで $O(N\log N)$、領域は $O(N)$
- `int size() const`
  suffix の個数を返す。$O(1)$
- `int operator[](int i) const`
  辞書順で `i` 番目の suffix の開始位置を返す。$O(1)$
- `const vector<int>& array() const`
  suffix array を参照で返す。$O(1)$
- `vector<int> lcp() const`
  隣り合う suffix の最長共通接頭辞長を順に返す。時間・返却領域は $O(N)$
- `pair<int, int> equal_range(pattern) const`
  パターンが出現する開始位置を持つ SA 上の半開区間 `[l,r)` を返す。一致がなければ `l == r`、空パターンなら `[0,N)`。時間 $O(M\log N)$、追加領域 $O(1)$

文字列のパターンには `string` または `string_view`、整数列などには構築時と同じ要素型の `vector<T>` を渡す。

配列だけを構築する関数も使える。

- `vector<int> suffix_array(const string& s)`
  文字列の suffix array を返す。$O(N)$
- `vector<int> suffix_array(const vector<int>& s, int upper)`
  各要素が `0..upper` に入る整数列の suffix array を返す。$O(N+\mathrm{upper})$
- `template<class T> vector<int> suffix_array(const vector<T>& s)`
  整数列などの suffix array を返す。$O(N\log N)$
- `vector<int> lcp(const string& s, const vector<int>& sa)`
- `template<class T> vector<int> lcp(const vector<T>& s, const vector<int>& sa)`
  隣り合う suffix の最長共通接頭辞長を順に返す。時間・追加領域は $O(N)$

## 使い方
```cpp
SuffixArray sa(string("banana"));
Printer out;
for (string_view pattern : {"ana", "na", "apple"}) {
    auto [l, r] = sa.equal_range(pattern);
    out.println(r - l);
    for (int i = l; i < r; ++i) out.println(sa[i]);
}
auto lc = sa.lcp();
```

出現数は順に `2, 2, 0` となる。開始位置は SA 上の順で得られる。
構築後に元の列を変更・破棄しても使える。
空 suffix は含まない。LCP 配列の長さは `max(0, N - 1)` となる。
文字列は符号なし byte 順、整数列などは要素の大小で辞書順を定める。
長さは `int` に収まることを前提とする。

整数列の値域が分かっていて配列だけ必要なら、`suffix_array(v, upper)` を使う。

## 実装上の補足
`SuffixArray` は元の列と suffix array を保持する。LCP 配列は `lcp()` の呼び出し時に構築する。
suffix array は SA-IS、LCP は Kasai 法で構築する。LCP の構築に必要な要素の比較は等値比較だけ。
SA-IS の縮約列で文字がすべて異なるときは、先頭文字だけで suffix の順序が決まるため、逆順列を作って再帰構築を省く。
