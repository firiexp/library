---
title: 弦グラフ判定、完全除去順序・誘導閉路の復元
documentation_of: //graph/chordal_graph.cpp
---

## 説明
単純無向グラフが弦グラフかを判定する。
弦グラフなら完全除去順序（PEO）、そうでなければ長さ4以上の誘導閉路を返す。
最小彩色と、その色数が必要だと示す最大クリークも求められる。

## できること
頂点数を $N$、辺数を $M$ とする。

- `ChordalResult recognize_chordal(n, edges)`
  頂点数 `n` と辺の `pair<int, int>` 列を受け取り、弦グラフかを判定する。最悪 $O(N+M)$ 時間・領域
- `result.chordal == true`
  `peo` は全頂点の順列。各頂点の、自分より後にある隣接頂点がクリークをなす。`induced_cycle` は空
- `result.chordal == false`
  `induced_cycle` は長さ4以上の誘導閉路。頂点の重複はなく、末尾と先頭を辺でつなぐ。`peo` は空
- `ChordalColoringResult chordal_coloring(n, edges)`
  判定と最小彩色・最大クリークをまとめて求める。最悪 $O(N+M)$ 時間・領域
- 彩色結果の `chordal == true`
  `color_count` は最小色数、`color[v]` は `0..color_count-1` の色番号。`max_clique` は最大クリークの頂点列で、長さは `color_count` と一致する。`induced_cycle` は空
- 彩色結果の `chordal == false`
  `induced_cycle` に誘導閉路を返す。`color_count=0`、`color` と `max_clique` は空

## 使い方
頂点番号は `0..n-1` とし、自己ループ・重複辺を含めない。
非連結グラフ・孤立点も扱う。`n=0` では `chordal=true` と空の PEO を返す。
彩色も同じ入力条件で、`n=0` では色数0と空の色・クリーク列を返す。入力の辺列は変更しない。

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

彩色は認識と同じ CSR を使い、PEO の逆順で最小の未使用色を割り当てる。
使用色は頂点番号を印にして記録するため、頂点ごとの配列初期化は不要である。
PEO 上で自分より後の隣接頂点が最も多い頂点を選び、それらと自身から最大クリークを復元する。
彩色・クリークの選び方も一意ではない。
