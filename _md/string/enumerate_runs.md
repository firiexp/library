---
title: 文字列のrun列挙
documentation_of: //string/enumerate_runs.cpp
---

## 説明
文字列の中で、最小周期の2倍以上の長さを持ち、同じ周期のまま左右へ延長できない区間 (run) を列挙する。
長さを $N$ として、時間・領域は $O(N\log(N))$。

## できること
- `vector<Run> enumerate_runs(const string& s)`
  各 run を `(period, l, r)` の辞書順で、重複なく返す
- `Run::period`
  部分文字列 `s[l..r)` の最小周期
- `Run::l`, `Run::r`
  run の半開区間。`r - l >= 2 * period` を満たす

## 使い方
```cpp
auto runs = enumerate_runs("ababab");
```

この例では `(period, l, r) = (2, 0, 6)` の run を1つ返す。
文字は符号なし byte として扱う。空文字列と1文字の文字列には run がない。

## 実装上の補足
正順・逆順の文字順について Lyndon 語の候補を求め、元の文字列と反転文字列への最長共通接頭辞クエリで左右に延長する。
最長共通接頭辞クエリには Sparse Table を使う。
正順の suffix の順位は構築済みのクエリから再利用し、Suffix Array の構築は元文字列・反転文字列・逆順の文字順の計3回とする。
