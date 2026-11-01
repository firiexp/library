---
title: 最長共通部分列の添字復元
documentation_of: //string/lcs_restore.cpp
---

## 説明
2つの文字列の最長共通部分列（LCS）を、両入力の添字の組として復元する。
連続区間である必要はなく、最適解が複数ある場合は任意の1つを返す。
長さだけが必要な場合は、bit並列の `lcs_bit.cpp` を使う。

## できること

- `vector<pair<int, int>> lcs_restore(const string& a, const string& b)`
  LCSをなす `(a側の添字, b側の添字)` の列を返す。どちらの添字も狭義増加で、対応する文字は等しい。共通文字がない場合や片方が空の場合は空列。

文字列長を $N,M$、LCSの長さを $L$ とする。非空入力で時間 $O(NM)$。
DPバッファは $O(\min(N,M))$、再帰スタックは $O(\log(\max(N,M)+1))$、返却列は $O(L)$ の領域を使う。
文字列のコピーや、再帰の各段でのDPバッファの保持は行わない。

## 使い方

```cpp
auto indices = lcs_restore(a, b);
string common;
for (auto [i, j] : indices) common += a[i];
```

引数の長さによらず、第1成分は元の `a`、第2成分は元の `b` の添字を表す。
辞書順最小や最も早い添字列は保証しない。

## 実装上の補足
Hirschberg法で、長い側を半分に分割する。
前半・後半それぞれのLCS長を2本の1行DPで求め、和が最大になる短い側の分割位置を選ぶ。
分割位置を決めた後は同じバッファを再帰先で再利用する。
