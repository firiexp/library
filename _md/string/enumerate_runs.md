---
title: 文字列のrun列挙
documentation_of: //string/enumerate_runs.cpp
---

## 説明
文字列の中で、最小周期の2倍以上の長さを持ち、同じ周期のまま左右へ延長できない区間 (run) を列挙する。

## できること
文字列長を $N$ とする。

- `vector<Run> enumerate_runs(const string& s)`
  各 run を `(period, l, r)` の辞書順で、重複なく返す。時間・領域は $O(N\log N)$
- `Run::period`
  部分文字列 `s[l..r)` の最小周期
- `Run::l`, `Run::r`
  run の半開区間。`r - l >= 2 * period` を満たす

## 使い方
```cpp
auto runs = enumerate_runs("ababab");
```

この例では `(period, l, r) = (2, 0, 6)` の run を1つ返す。
文字は符号なし byte として扱う。

## 実装上の補足
元の文字列と反転文字列に Suffix Array と Sparse Table を構築する。
文字の昇順と降順で Lyndon 語の候補を求め、最長共通接頭辞クエリで左右に延長する。降順での接尾辞比較にも元の文字列のクエリを使う。
