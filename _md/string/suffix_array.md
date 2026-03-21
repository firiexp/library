---
title: Suffix Array
documentation_of: //string/suffix_array.cpp
---
## 説明
文字列や整数列の suffix array と LCP 配列を構築する。
suffix array は SA-IS、LCP は Kasai 法で、どちらも $O(N)$ で動く。

## できること
- `vector<int> suffix_array(const string& s)`
  文字列 `s` の suffix array を返す
- `vector<int> suffix_array(const vector<int>& s, int upper)`
  各要素が `0..upper` に入る整数列の suffix array を返す
- `template<class T> vector<int> suffix_array(const vector<T>& s)`
  比較可能な列を座圧して suffix array を返す
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
