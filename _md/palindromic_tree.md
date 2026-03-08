---
title: 回文木(Palindromic Tree)
documentation_of: //string/palindromic_tree.cpp
---
## 説明
文字列の異なる回文部分文字列を管理する eertree である。
1 文字ずつ追加しながら構築でき、全体 `O(NW)` ではなく遷移参照込みで `O(N)`、固定アルファベットなら実用上ほぼ線形で動く。

## できること
- `PalindromicTree<W, start> pt`
  空の palindromic tree を作る
- `PalindromicTree<W, start> pt(s)`
  文字列 `s` から構築する
- `void reserve(int n)`
  長さ `n` を見込んで領域を確保する
- `int add(char c)`
  末尾に文字 `c` を追加し、できた最長回文接尾辞のノード番号を返す
- `vector<int> count()`
  各ノードの出現回数を返す

## 使い方
根は 2 個あり、`0` が長さ `-1`、`1` が長さ `0` を表す。
通常の回文ノードは `2` 以降に追加される。
`path[i]` には prefix `s[0..i]` の最長回文接尾辞のノード番号が入る。

```cpp
PalindromicTree<26> pt;
for (char c : s) pt.add(c);

for (int v = 2; v < (int)pt.nodes.size(); ++v) {
    int len = pt.nodes[v].len;
    int link = pt.nodes[v].link;
}
```

## 実装上の補足
`W` はアルファベット数、`start` は最小文字である。
`PalindromicTree<26, 'a'>` なら小文字英字用になる。
