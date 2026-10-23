---
title: 最小巡回シフト
documentation_of: //string/minimum_rotation.cpp
---

## 説明
列を巡回シフトしたとき、辞書順で最小になる開始位置を求める。
長さを $N$ として時間 $O(N)$、追加領域 $O(1)$。入力列は変更しない。

## できること
- `int minimum_rotation_index(const string& s)`
  符号なし byte 順で最小になる巡回シフトの開始位置を返す
- `int minimum_rotation_index(const vector<T>& s)`
  要素の `<` による順序で最小になる開始位置を返す。`vector<char>` は `char` 本来の順序を使う
- 最小の巡回シフトが複数なら最小の元添字を返す。空列は `0`

## 使い方
```cpp
string s = "baba";
int i = minimum_rotation_index(s);
string smallest = s.substr(i) + s.substr(0, i);
```

この例では `i` は `1`、`smallest` は `"abab"` となる。
要素の大小比較は厳密弱順序とし、長さは `INT_MAX` 以下とする。
NUL や負の整数も通常の要素として扱い、番兵は不要。

## 実装上の補足
2つの候補位置と一致長を持ち、不一致になったら劣る側の候補を一致長より1つ多く進める。
添字計算には `size_t` を使い、2周目の添字は長さを引いて戻す。
`s + s` の実体や suffix array は作らない。上の出力列の生成には別途 $O(N)$ 領域が必要。
