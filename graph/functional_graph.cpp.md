---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_aplusb_functional_graph.test.cpp
    title: test/yosupo_aplusb_functional_graph.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u95A2\u6570\u30B0\u30E9\u30D5(Functional Graph)"
    links: []
  bundledCode: "#line 1 \"graph/functional_graph.cpp\"\nstruct FunctionalGraph {\n\
    \    static constexpr int LOG = 63;\n\n    int n;\n    vector<int> to;\n    vector<vector<int>>\
    \ up;\n    vector<int> comp_id;\n    vector<int> cycle_pos;\n    vector<int> cycle_len;\n\
    \    vector<int> dist_to_cycle;\n    vector<int> cycle_entry;\n    vector<vector<int>>\
    \ cycles;\n\n    explicit FunctionalGraph(int n)\n        : n(n),\n          to(n,\
    \ -1),\n          up(LOG, vector<int>(n, -1)),\n          comp_id(n, -1),\n  \
    \        cycle_pos(n, -1),\n          cycle_len(n, 0),\n          dist_to_cycle(n,\
    \ -1),\n          cycle_entry(n, -1) {}\n\n    explicit FunctionalGraph(const\
    \ vector<int> &to)\n        : FunctionalGraph((int)to.size()) {\n        this->to\
    \ = to;\n        build();\n    }\n\n    void set_edge(int v, int nxt) {\n    \
    \    to[v] = nxt;\n    }\n\n    void build() {\n        up.assign(LOG, vector<int>(n,\
    \ -1));\n        for (int v = 0; v < n; ++v) up[0][v] = to[v];\n        for (int\
    \ k = 0; k + 1 < LOG; ++k) {\n            for (int v = 0; v < n; ++v) {\n    \
    \            up[k + 1][v] = up[k][up[k][v]];\n            }\n        }\n\n   \
    \     vector<int> indeg(n);\n        for (int v = 0; v < n; ++v) ++indeg[to[v]];\n\
    \n        vector<int> que, order;\n        que.reserve(n);\n        order.reserve(n);\n\
    \        for (int v = 0; v < n; ++v) {\n            if (indeg[v] == 0) que.push_back(v);\n\
    \        }\n        for (int head = 0; head < (int)que.size(); ++head) {\n   \
    \         int v = que[head];\n            order.push_back(v);\n            int\
    \ nxt = to[v];\n            if (--indeg[nxt] == 0) que.push_back(nxt);\n     \
    \   }\n\n        comp_id.assign(n, -1);\n        cycle_pos.assign(n, -1);\n  \
    \      cycle_len.assign(n, 0);\n        dist_to_cycle.assign(n, -1);\n       \
    \ cycle_entry.assign(n, -1);\n        cycles.clear();\n\n        vector<int> seen(n);\n\
    \        for (int v = 0; v < n; ++v) {\n            if (indeg[v] == 0 || seen[v])\
    \ continue;\n            int cid = cycles.size();\n            vector<int> cyc;\n\
    \            int cur = v;\n            do {\n                seen[cur] = 1;\n\
    \                comp_id[cur] = cid;\n                cycle_pos[cur] = cyc.size();\n\
    \                dist_to_cycle[cur] = 0;\n                cycle_entry[cur] = cur;\n\
    \                cyc.push_back(cur);\n                cur = to[cur];\n       \
    \     } while (cur != v);\n            for (int x : cyc) cycle_len[x] = cyc.size();\n\
    \            cycles.push_back(cyc);\n        }\n\n        for (int i = (int)order.size()\
    \ - 1; i >= 0; --i) {\n            int v = order[i];\n            int nxt = to[v];\n\
    \            comp_id[v] = comp_id[nxt];\n            cycle_pos[v] = cycle_pos[nxt];\n\
    \            cycle_len[v] = cycle_len[nxt];\n            dist_to_cycle[v] = dist_to_cycle[nxt]\
    \ + 1;\n            cycle_entry[v] = cycle_entry[nxt];\n        }\n    }\n\n \
    \   int jump(int v, long long k) const {\n        for (int i = 0; i < LOG; ++i)\
    \ {\n            if ((k >> i) & 1) v = up[i][v];\n        }\n        return v;\n\
    \    }\n\n    bool in_cycle(int v) const {\n        return dist_to_cycle[v] ==\
    \ 0;\n    }\n\n    int cycle_id(int v) const {\n        return comp_id[v];\n \
    \   }\n\n    int cycle_size(int v) const {\n        return cycle_len[v];\n   \
    \ }\n\n    int steps_to_cycle(int v) const {\n        return dist_to_cycle[v];\n\
    \    }\n\n    int cycle_vertex(int v) const {\n        return cycle_entry[v];\n\
    \    }\n\n    int cycle_index(int v) const {\n        return cycle_pos[v];\n \
    \   }\n\n    const vector<int> &cycle(int id) const {\n        return cycles[id];\n\
    \    }\n};\n\n/**\n * @brief \u95A2\u6570\u30B0\u30E9\u30D5(Functional Graph)\n\
    \ */\n"
  code: "struct FunctionalGraph {\n    static constexpr int LOG = 63;\n\n    int n;\n\
    \    vector<int> to;\n    vector<vector<int>> up;\n    vector<int> comp_id;\n\
    \    vector<int> cycle_pos;\n    vector<int> cycle_len;\n    vector<int> dist_to_cycle;\n\
    \    vector<int> cycle_entry;\n    vector<vector<int>> cycles;\n\n    explicit\
    \ FunctionalGraph(int n)\n        : n(n),\n          to(n, -1),\n          up(LOG,\
    \ vector<int>(n, -1)),\n          comp_id(n, -1),\n          cycle_pos(n, -1),\n\
    \          cycle_len(n, 0),\n          dist_to_cycle(n, -1),\n          cycle_entry(n,\
    \ -1) {}\n\n    explicit FunctionalGraph(const vector<int> &to)\n        : FunctionalGraph((int)to.size())\
    \ {\n        this->to = to;\n        build();\n    }\n\n    void set_edge(int\
    \ v, int nxt) {\n        to[v] = nxt;\n    }\n\n    void build() {\n        up.assign(LOG,\
    \ vector<int>(n, -1));\n        for (int v = 0; v < n; ++v) up[0][v] = to[v];\n\
    \        for (int k = 0; k + 1 < LOG; ++k) {\n            for (int v = 0; v <\
    \ n; ++v) {\n                up[k + 1][v] = up[k][up[k][v]];\n            }\n\
    \        }\n\n        vector<int> indeg(n);\n        for (int v = 0; v < n; ++v)\
    \ ++indeg[to[v]];\n\n        vector<int> que, order;\n        que.reserve(n);\n\
    \        order.reserve(n);\n        for (int v = 0; v < n; ++v) {\n          \
    \  if (indeg[v] == 0) que.push_back(v);\n        }\n        for (int head = 0;\
    \ head < (int)que.size(); ++head) {\n            int v = que[head];\n        \
    \    order.push_back(v);\n            int nxt = to[v];\n            if (--indeg[nxt]\
    \ == 0) que.push_back(nxt);\n        }\n\n        comp_id.assign(n, -1);\n   \
    \     cycle_pos.assign(n, -1);\n        cycle_len.assign(n, 0);\n        dist_to_cycle.assign(n,\
    \ -1);\n        cycle_entry.assign(n, -1);\n        cycles.clear();\n\n      \
    \  vector<int> seen(n);\n        for (int v = 0; v < n; ++v) {\n            if\
    \ (indeg[v] == 0 || seen[v]) continue;\n            int cid = cycles.size();\n\
    \            vector<int> cyc;\n            int cur = v;\n            do {\n  \
    \              seen[cur] = 1;\n                comp_id[cur] = cid;\n         \
    \       cycle_pos[cur] = cyc.size();\n                dist_to_cycle[cur] = 0;\n\
    \                cycle_entry[cur] = cur;\n                cyc.push_back(cur);\n\
    \                cur = to[cur];\n            } while (cur != v);\n           \
    \ for (int x : cyc) cycle_len[x] = cyc.size();\n            cycles.push_back(cyc);\n\
    \        }\n\n        for (int i = (int)order.size() - 1; i >= 0; --i) {\n   \
    \         int v = order[i];\n            int nxt = to[v];\n            comp_id[v]\
    \ = comp_id[nxt];\n            cycle_pos[v] = cycle_pos[nxt];\n            cycle_len[v]\
    \ = cycle_len[nxt];\n            dist_to_cycle[v] = dist_to_cycle[nxt] + 1;\n\
    \            cycle_entry[v] = cycle_entry[nxt];\n        }\n    }\n\n    int jump(int\
    \ v, long long k) const {\n        for (int i = 0; i < LOG; ++i) {\n         \
    \   if ((k >> i) & 1) v = up[i][v];\n        }\n        return v;\n    }\n\n \
    \   bool in_cycle(int v) const {\n        return dist_to_cycle[v] == 0;\n    }\n\
    \n    int cycle_id(int v) const {\n        return comp_id[v];\n    }\n\n    int\
    \ cycle_size(int v) const {\n        return cycle_len[v];\n    }\n\n    int steps_to_cycle(int\
    \ v) const {\n        return dist_to_cycle[v];\n    }\n\n    int cycle_vertex(int\
    \ v) const {\n        return cycle_entry[v];\n    }\n\n    int cycle_index(int\
    \ v) const {\n        return cycle_pos[v];\n    }\n\n    const vector<int> &cycle(int\
    \ id) const {\n        return cycles[id];\n    }\n};\n\n/**\n * @brief \u95A2\u6570\
    \u30B0\u30E9\u30D5(Functional Graph)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/functional_graph.cpp
  requiredBy: []
  timestamp: '2026-03-12 19:34:31+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_aplusb_functional_graph.test.cpp
date: 2026-03-12
documentation_of: graph/functional_graph.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u95A2\u6570\u30B0\u30E9\u30D5(Functional Graph)"
---

## 説明
各頂点の出次数が 1 の有向グラフを扱う。
cycle 分解と doubling を前計算し、`k` 個先の頂点と各頂点が属する閉路情報を取る。
前処理 $O(N \log K)$、`jump` は $O(\log K)$、それ以外は $O(1)$。

## できること
- `FunctionalGraph fg(n)`
  `n` 頂点の関数グラフを作る
- `FunctionalGraph fg(to)`
  遷移先配列 `to` から作ってそのまま `build` する
- `void set_edge(int v, int nxt)`
  `v -> nxt` を設定する
- `void build()`
  閉路分解と doubling を前計算する
- `int jump(int v, long long k)`
  `v` から `k` 回遷移した先を返す
- `bool in_cycle(int v)`
  `v` が閉路上なら `true`
- `int cycle_id(int v)`
  `v` が属する連結成分の閉路 id を返す
- `int cycle_size(int v)`
  `v` が流れ込む閉路の長さを返す
- `int steps_to_cycle(int v)`
  `v` から閉路に入るまでの遷移回数を返す
- `int cycle_vertex(int v)`
  `v` から進んで最初に到達する閉路頂点を返す
- `int cycle_index(int v)`
  `cycle_vertex(v)` の閉路内 index を返す
- `const vector<int> &cycle(int id)`
  閉路 `id` の頂点列を返す。辺の向き順に並ぶ

## 使い方
各頂点の遷移先を `set_edge` で入れてから `build()` を呼ぶ。
`jump(v, k)` で `k` 個先を求め、`steps_to_cycle(v)` や `cycle_size(v)` で構造情報を使う。

```cpp
FunctionalGraph fg(n);
for (int v = 0; v < n; ++v) {
    fg.set_edge(v, to[v]);
}
fg.build();

int x = fg.jump(v, k);
int len = fg.cycle_size(v);
```

## 実装上の補足
- `cycle(id)` の先頭は実装依存だが、並び順は常に遷移先方向にそろう
- `cycle_index(v)` は非閉路頂点でも使え、`cycle_vertex(v)` の位置を返す
