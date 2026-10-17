---
title: 回文木(Palindromic Tree)
documentation_of: //string/palindromic_tree.cpp
---

## 説明

文字列に含まれる異なる回文部分文字列と、その出現回数を管理する。
文字列を非空の回文に分割するときの最少個数と分割位置も求められる。
1 文字ずつ追加しながら構築でき、文字種数 `W` を定数とすると長さ $N$ の文字列から全体 $O(N)$ で構築する。

## できること

- `PalindromicTree<W, start> pt` : 空の回文木を作る
- `PalindromicTree<W, start> pt(s)` : 文字列 `s` から構築する
- `void reserve(int n)` : 長さ `n` を見込んで領域を確保する
- `int add(char c)` : 末尾に文字 `c` を追加し、追加後の最長回文接尾辞のノード番号を返す
- `void build(const string &t)` : 末尾に文字列 `t` を追加する
- `vector<int> count()` : 各ノードの出現回数を返す。ノード数を $S$ として $O(S)$
- `Partitions min_partitions()` : 文字列の各接頭辞を非空回文に分割する最少個数 `count` と、分割位置を復元するための `prev` を返す

`min_partitions()` の計算量は時間 $O(N\log(N+1))$、返却値を含む追加領域 $O(N)$。

## 使い方

`W` に文字種数、`start` に最小文字を指定する。
小文字英字なら `PalindromicTree<26, 'a'> pt(s);` で構築する。
空の木を作り、`add(c)` で1文字ずつ追加してもよい。

最少回文分割は `auto dp = pt.min_partitions();` で求める。
返り値の `count` / `prev` はどちらも長さ $N+1$ で、長さ `i` の接頭辞 `[0,i)` に対する結果を持つ。
`dp.count[i]` が最少分割数を表す。`i>0` では `[dp.prev[i],i)` が最後の非空回文となる。

```cpp
PalindromicTree<26> pt("abacdc");
auto dp = pt.min_partitions();
vector<pair<int, int>> ranges;
for (int r = pt.s.size(); r > 0; r = dp.prev[r]) {
    ranges.emplace_back(dp.prev[r], r);
}
reverse(ranges.begin(), ranges.end());
```

この例では `dp.count[6]=2` で、`"aba"` と `"cdc"` に分割できる。
`ranges` には半開区間 `[0,3)` と `[3,6)` が入る。
任意の接頭辞を復元するときは、その長さから `r` を辿ればよい。復元時間は分割数に比例する。
最適な分割が複数あれば任意の1つを返す。

`dp.count[0]=0`、`dp.prev[0]=-1` とし、`i>0` では `dp.count[i]=dp.count[dp.prev[i]]+1` となる。
空文字列の場合は `count={0}`、`prev={-1}` を返す。
`add` / `build` 後は再度 `min_partitions()` を呼べば更新後の結果を取得できる。既に返した結果やノード・出現回数は変更しない。

## 実装上の補足

回文木は eertree とも呼ぶ。根は 2 個あり、`0` が長さ `-1`、`1` が長さ `0` を表す。
回文に対応するノードは `2` 以降に追加される。
`nodes[v].len` は回文の長さ、`nodes[v].link` は suffix link。
`path[i]` は接頭辞 `s[0..i]` の最長回文接尾辞のノード番号を持つ。

通常ノードの suffix link は先に作られたノードを指し、`nodes[v].link < v` が成り立つ。
`count()` はノード番号の逆順に出現回数を伝播する。文字追加後も再集計できる。
返り値のうち、根 `0` の出現回数は $0$、根 `1` の出現回数は文字列長となる。

`min_partitions()` は `path` を接頭辞の短い順に走査する。
suffix link との長さの差が等しい回文列を series link でまとめ、過去の接頭辞で求めた最小値と境界を再利用する。
[EERTREE の Proposition 9](https://arxiv.org/html/1506.04862v2#S4.SS1) に基づく。
補助配列は呼出し中だけ保持し、通常の `add` / `count` に追加の DP 処理は発生しない。
