---
title: Suffix Array
documentation_of: //string/suffix_array.cpp
---
## 説明
文字列や整数列の suffix array と LCP 配列を構築する。
suffix array は SA-IS、LCP は Kasai 法で構築する。文字列ではどちらも $O(N)$ で動く。

## できること
- `vector<int> suffix_array(const string& s)`
  文字列 `s` を符号なし byte 順で比較した suffix array を返す
- `vector<int> suffix_array(const vector<int>& s, int upper)`
  各要素が `0..upper` に入る整数列の suffix array を $O(N+\mathrm{upper})$ 時間で返す
- `template<class T> vector<int> suffix_array(const vector<T>& s)`
  比較可能な列を座圧して suffix array を $O(N\log N)$ 時間で返す
- `vector<int> lcp(const string& s, const vector<int>& sa)`
  隣接 suffix の LCP 配列を返す
- `template<class T> vector<int> lcp(const vector<T>& s, const vector<int>& sa)`
  一般列に対する LCP 配列を返す

## 使い方
```cpp
string s = "mississippi";
auto sa = suffix_array(s);
auto lc = lcp(s, sa);
```

整数列を直接渡す場合は、値域が分かっているなら `suffix_array(v, upper)` を使うとよい。

## 実装上の補足
空列でも使える。
`lcp` の返り値の長さは `max(0, N - 1)` である。
LCP の構築は要素の等値比較だけを使い、入力列を直接参照する。文字列の整数列へのコピーは行わない。
時間・追加領域は $O(N)$ で、入力列と `sa` は変更しない。
SA-IS の縮約列で文字がすべて異なるときは、先頭文字だけで suffix の順序が決まるため、逆順列を作って再帰構築を省く。
