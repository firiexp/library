---
title: Suffix Array
documentation_of: //string/suffix_array.cpp
---

## 説明
固定した文字列や整数列の suffix array と LCP 配列を構築する。
同じ列に対して、パターンの出現範囲の検索や、異なる非空の部分列の辞書順 $k$ 番目検索を行える。

## できること
入力列の長さを $N$、パターン長を $M$ とする。

### `SuffixArray` クラス
- `SuffixArray sa(s)`
  `string`（文字列リテラルを含む）または `vector<T>` から構築する。文字列は $O(N)$、整数列などは $O(N \log N)$、領域は $O(N)$
- `int size() const`
  suffix の個数 $N$ を返す。$O(1)$
- `int operator[](int i) const`
  辞書順で `i` 番目の suffix の開始位置を返す。$O(1)$
- `const vector<int>& array() const`
  suffix array への参照を返す。$O(1)$
- `vector<int> lcp() const`
  長さ $\max(0, N - 1)$ の LCP 配列を返す。要素 `i` は `sa[i]` と `sa[i + 1]` から始まる suffix の最長共通接頭辞長。時間・領域は $O(N)$
- `pair<int, int> equal_range(pattern) const`
  `pattern` を接頭辞に持つ suffix の SA 上の半開区間 `[l, r)` を返す。出現個数は `r - l`、開始位置は `sa[l], ..., sa[r - 1]`。一致がなければ `l == r`、空パターンなら `[0, N)`。時間 $O(M \log N)$、追加領域 $O(1)$
- `pair<int, int> kth_substring(long long k) const`
  異なる非空の連続部分列のうち、辞書順で `k` 番目（0 始まり）のものが現れる元の列上の半開区間 `[l, r)` を1つ返す。`k` が負または総数以上なら `{-1, -1}`。初回のみ $O(N)$ 時間・追加領域で前処理し、以後は $O(\log N)$

`equal_range` に渡す `pattern` は、文字列なら `string` または `string_view`、整数列などなら構築時と同じ要素型の `vector<T>` とする。

### 関数
配列だけが必要な場合は次の関数も使える。

- `vector<int> suffix_array(const string& s)`
  文字列の suffix array を返す。$O(N)$
- `vector<int> suffix_array(const vector<int>& s, int upper)`
  各要素が `0..upper` に収まる整数列の suffix array を返す。$O(N + \mathrm{upper})$
- `template<class T> vector<int> suffix_array(const vector<T>& s)`
  整数列などの suffix array を返す。$O(N \log N)$
- `vector<int> lcp(const string& s, const vector<int>& sa)`
- `template<class T> vector<int> lcp(const vector<T>& s, const vector<int>& sa)`
  `s` とその suffix array `sa` から LCP 配列を返す。時間・領域は $O(N)$

## 使い方
```cpp
SuffixArray sa("banana");
Printer out;
for (string_view pattern : {"ana", "na", "apple"}) {
    auto [l, r] = sa.equal_range(pattern);
    out.println(r - l);
    for (int i = l; i < r; ++i) out.println(sa[i]);
}
auto lc = sa.lcp();
auto [sub_l, sub_r] = sa.kth_substring(2);  // "ana" の出現区間 [3, 6)
```

上の例では、各パターンの出現数は順に `2, 2, 0` となる。`equal_range` が返すのは SA 上の区間であり、開始位置は SA 上の順（辞書順）で得られる。一方、`kth_substring` が返すのは元の列上の半開区間である。

利用上の前提・仕様は次の通り。

- 空 suffix は含まない。
- 文字列は符号なし byte 順、整数列などは要素の `<` で辞書順を定める。
- 入力列の長さは `int` に収まることを前提とする。
- `SuffixArray` は元の列を内部に保持するため、構築後に元の列を変更・破棄しても使える。
- 整数列の値域が分かっていて配列だけ必要なら、`suffix_array(v, upper)` を使うと座標圧縮を省ける。

## 実装上の補足
- `SuffixArray` は元の列と suffix array を保持する。LCP 配列は `lcp()` の呼び出しごとに構築し、`kth_substring` 用の累積和は初回呼び出し時に構築して保持する。
- suffix array は SA-IS、LCP 配列は Kasai 法で構築する。LCP の構築に必要な要素の比較は等値比較のみ。
- SA-IS の縮約列で文字がすべて異なるときは、先頭文字だけで suffix の順序が決まるため、逆順列を作って再帰構築を省く。
- 開始位置 $p$ の suffix と辞書順で直前の suffix との LCP 長を $h$ とする（先頭の suffix では $h = 0$）。この suffix で初めて現れる部分列は長さ $h + 1$ から $N - p$ までの接頭辞であり、個数は $N - p - h$ 個となる。`kth_substring` はこの個数を suffix ごとに `long long` で累積し、累積和が `k` を超える最初の suffix を二分探索する。
