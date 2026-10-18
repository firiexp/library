---
title: 弦グラフ認識と証明書
documentation_of: //graph/chordal_graph.cpp
---

## 説明
単純無向グラフが弦グラフかを判定する。
弦グラフなら完全除去順序（PEO）、そうでなければ長さ4以上の誘導閉路を返す。
入力から証明書の復元まで、最悪 $O(N+M)$ 時間・領域。

## できること
- `ChordalResult recognize_chordal(n, edges)`
  頂点数 `n` と辺の pair 列を受け取り、入力を変更せず判定する
- `result.chordal == true`
  `peo` は全頂点の順列。各頂点の、自分より後にある隣接頂点がクリークをなす。`induced_cycle` は空
- `result.chordal == false`
  `induced_cycle` は長さ4以上の誘導閉路。頂点の重複はなく、末尾と先頭を辺でつなぐ。`peo` は空

## 使い方
頂点番号は `0..n-1` とし、自己ループ・重複辺を含めない。
非連結グラフ・孤立点も扱う。`n=0` では `chordal=true` と空の PEO を返す。

```cpp
auto result = recognize_chordal(n, edges);
if (result.chordal) {
    auto order = result.peo;
} else {
    auto cycle = result.induced_cycle;
}
```

## 実装上の補足
CSR の隣接表を構築し、bucket と配列の双方向リストによる Maximum Cardinality Search を行う。
各頂点の既選択隣接頂点のうち最も新しいものを親とし、同じ親を持つ頂点をまとめてクリーク条件を調べる。
失敗時は MCS 順で最初の違反を選び、違反頂点とその隣接頂点を内部に含めない最短路を1回の BFS で復元する。
再帰・heap・hash table は使わない。PEO と誘導閉路の選び方は一意ではない。
