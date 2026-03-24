---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching.cpp
    title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0\
      (Bipartite Matching)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0334.test.cpp
    title: test/aoj0334.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u8F9E\u66F8\u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\
      \u30B0(Lexicographically Minimum Bipartite Matching)"
    links: []
  bundledCode: "#line 1 \"graph/bipartite_matching.cpp\"\nclass Bipartite_Matching\
    \ {\nprotected:\n    vector<vector<int>> G;\n    vector<int> used, alive;\n  \
    \  int t;\n    int l, r;\n\npublic:\n    vector<int> match;\n\n    explicit Bipartite_Matching(int\
    \ l, int r)\n        : G(l), used(l, 0), alive(l + r, -1), t(0), l(l), r(r), match(l\
    \ + r, -1) {}\n\n    void add_edge(int a, int b) {\n        G[a].push_back(b);\n\
    \    }\n\n    bool dfs(int x) {\n        used[x] = t;\n        for (int y : G[x])\
    \ {\n            int ry = y + l;\n            if (alive[ry] == 0) continue;\n\
    \            int w = match[ry];\n            if (w != -1 && (alive[w] == 0 ||\
    \ used[w] == t || !dfs(w))) continue;\n            match[x] = ry;\n          \
    \  match[ry] = x;\n            return true;\n        }\n        return false;\n\
    \    }\n\n    int matching() {\n        int ans = 0;\n        for (int i = 0;\
    \ i < l; ++i) {\n            if (alive[i] == 0 || match[i] != -1) continue;\n\
    \            ++t;\n            ans += dfs(i);\n        }\n        return ans;\n\
    \    }\n\n    vector<pair<int, int>> get_pairs() const {\n        vector<pair<int,\
    \ int>> res;\n        for (int i = 0; i < l; ++i) {\n            if (match[i]\
    \ == -1) continue;\n            res.emplace_back(i, match[i] - l);\n        }\n\
    \        return res;\n    }\n};\n\n/**\n * @brief \u4E8C\u90E8\u30B0\u30E9\u30D5\
    \u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(Bipartite Matching)\n */\n#line 2 \"\
    graph/bipartite_matching_lexmin.cpp\"\nclass Bipartite_Matching_LexMin : public\
    \ Bipartite_Matching {\npublic:\n    using Bipartite_Matching::Bipartite_Matching;\n\
    \n    int solve_LexMin() { // check sorted edge no\n        int res = matching();\n\
    \        for (int i = 0; i < l; ++i) {\n            if(!~match[i]) continue;\n\
    \            match[match[i]] = -1;\n            match[i] = -1;\n            ++t;\n\
    \            dfs(i);\n            alive[match[i]] = 0;\n            alive[i] =\
    \ 0;\n        }\n        return res;\n    }\n};\n\n/**\n * @brief \u8F9E\u66F8\
    \u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically\
    \ Minimum Bipartite Matching)\n */\n"
  code: "#include \"./bipartite_matching.cpp\"\nclass Bipartite_Matching_LexMin :\
    \ public Bipartite_Matching {\npublic:\n    using Bipartite_Matching::Bipartite_Matching;\n\
    \n    int solve_LexMin() { // check sorted edge no\n        int res = matching();\n\
    \        for (int i = 0; i < l; ++i) {\n            if(!~match[i]) continue;\n\
    \            match[match[i]] = -1;\n            match[i] = -1;\n            ++t;\n\
    \            dfs(i);\n            alive[match[i]] = 0;\n            alive[i] =\
    \ 0;\n        }\n        return res;\n    }\n};\n\n/**\n * @brief \u8F9E\u66F8\
    \u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically\
    \ Minimum Bipartite Matching)\n */\n"
  dependsOn:
  - graph/bipartite_matching.cpp
  isVerificationFile: false
  path: graph/bipartite_matching_lexmin.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0334.test.cpp
documentation_of: graph/bipartite_matching_lexmin.cpp
layout: document
title: "\u8F9E\u66F8\u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically\
  \ Minimum Bipartite Matching)"
---
## 説明
二部グラフの最大マッチングのうち、左側頂点の対応先列を辞書順最小にしたものを求める。
先に通常の最大マッチングを作り、その後に左側を小さい順に確定していく。

## できること
- `Bipartite_Matching_LexMin bm(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を張る
- `int solve_LexMin()`
  辞書順最小の最大マッチングを構成して、そのサイズを返す
- `vector<int> match`
  `match[v]` に対応先頂点番号が入る。未マッチは `-1`

## 使い方
左側の各頂点について、辺を右頂点番号の昇順で `add_edge` してから `solve_LexMin()` を呼ぶ。
辞書順最小性は辺の追加順に依存する。

```cpp
Bipartite_Matching_LexMin bm(l, r);
for (int u = 0; u < l; ++u) {
    for (int v : candidates[u]) bm.add_edge(u, v);
}
int sz = bm.solve_LexMin();
```

## 実装上の補足
内部の右側頂点は `l` 個ぶんオフセットされた番号で管理する。
`match[u]` が右側頂点を指すとき、元の右頂点番号は `match[u] - l` で取り出せる。
