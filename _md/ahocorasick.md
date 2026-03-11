---
title: Aho-Corasick法
documentation_of: //datastructure/ahocorasick.cpp
---
## 説明
Trie木に対応するパターンマッチングオートマトンを構築する。

## 操作
- $\operatorname{add}(s, \mathrm{cur})$ : Trie 木の位置 `cur` に文字列 $s$ を追加し、そのノードを返す
- $\operatorname{build}()$ : パターンマッチングオートマトンを構築する
- $\operatorname{next}(x, c)$ : 位置 $x$ に文字 $c$ を与えたときの行き先を返す
