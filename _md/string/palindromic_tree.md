---
title: 回文木(Palindromic Tree)
documentation_of: //string/palindromic_tree.cpp
---
## 説明
文字列の異なる回文部分文字列を管理する eertree である。
1 文字ずつ追加しながら構築でき、文字種数 `W` を定数とすると長さ $N$ の文字列から全体 $O(N)$ で構築する。
各 prefix の最少回文分割数と分割位置も取得できる。

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
  各ノードの出現回数をノード数を $S$ として $O(S)$ で返す。
- `Partitions min_partitions()`
  各 prefix を非空回文へ分割する最少個数 `count` と直前の境界 `prev` を返す。時間 $O(N\log(N+1))$、返却値を含む追加領域 $O(N)$

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

`min_partitions()` の `count` / `prev` は長さ $N+1$。
`count[i]` は `[0,i)` の最少分割数で、`count[0]=0`、`prev[0]=-1`。
`i>0` では `[prev[i],i)` が最後の非空回文であり、`count[i]=count[prev[i]]+1` となる。
最適解が複数あれば任意の1つを返す。

```cpp
PalindromicTree<26> pt("abacdc");
auto dp = pt.min_partitions();
vector<pair<int, int>> ranges;
for (int r = pt.s.size(); r > 0; r = dp.prev[r]) {
    ranges.emplace_back(dp.prev[r], r);
}
reverse(ranges.begin(), ranges.end());
```

この例では `count[6]=2` で、区間 `[0,3)` と `[3,6)` に復元できる。
任意の prefix 長から同じように辿れ、復元時間は分割数に比例する。
空文字列では `count={0}`、`prev={-1}` となる。

## 実装上の補足
`W` はアルファベット数、`start` は最小文字である。
`PalindromicTree<26, 'a'>` なら小文字英字用になる。

通常ノードの suffix link は先に作られたノードを指し、`nodes[v].link < v` が成り立つ。
`count()` はこの性質を使い、ノード番号の逆順に出現回数を伝播する。
文字追加後の再集計にも対応する。根の返り値は `0` が $0$、`1` が文字列長となる。

`min_partitions()` は完成した木の `path` を prefix 順に走査する。
suffix link との長さの差が等しい回文列を series link でまとめ、過去の prefix で求めた最小値と境界を再利用する。
[EERTREE の Proposition 9](https://arxiv.org/html/1506.04862v2#S4.SS1) に基づく。
補助配列は呼出し中だけ保持し、通常の `add` / `count` に追加の DP 処理は発生しない。
`add` / `build` 後も再取得でき、既に返した結果やノード・出現回数を変更しない。
