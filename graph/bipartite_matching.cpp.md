---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: graph/bipartite_matching_lexmin.cpp
    title: "\u8F9E\u66F8\u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0\
      (Lexicographically Minimum)"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj0334.test.cpp
    title: test/aoj0334.test.cpp
  - icon: ':x:'
    path: test/aoj_grl_7_a_bipartite_matching.test.cpp
    title: test/aoj_grl_7_a_bipartite_matching.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\
      \u30B0(Bipartite Matching)"
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
    \u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(Bipartite Matching)\n */\n"
  code: "class Bipartite_Matching {\nprotected:\n    vector<vector<int>> G;\n    vector<int>\
    \ used, alive;\n    int t;\n    int l, r;\n\npublic:\n    vector<int> match;\n\
    \n    explicit Bipartite_Matching(int l, int r)\n        : G(l), used(l, 0), alive(l\
    \ + r, -1), t(0), l(l), r(r), match(l + r, -1) {}\n\n    void add_edge(int a,\
    \ int b) {\n        G[a].push_back(b);\n    }\n\n    bool dfs(int x) {\n     \
    \   used[x] = t;\n        for (int y : G[x]) {\n            int ry = y + l;\n\
    \            if (alive[ry] == 0) continue;\n            int w = match[ry];\n \
    \           if (w != -1 && (alive[w] == 0 || used[w] == t || !dfs(w))) continue;\n\
    \            match[x] = ry;\n            match[ry] = x;\n            return true;\n\
    \        }\n        return false;\n    }\n\n    int matching() {\n        int\
    \ ans = 0;\n        for (int i = 0; i < l; ++i) {\n            if (alive[i] ==\
    \ 0 || match[i] != -1) continue;\n            ++t;\n            ans += dfs(i);\n\
    \        }\n        return ans;\n    }\n\n    vector<pair<int, int>> get_pairs()\
    \ const {\n        vector<pair<int, int>> res;\n        for (int i = 0; i < l;\
    \ ++i) {\n            if (match[i] == -1) continue;\n            res.emplace_back(i,\
    \ match[i] - l);\n        }\n        return res;\n    }\n};\n\n/**\n * @brief\
    \ \u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(Bipartite\
    \ Matching)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bipartite_matching.cpp
  requiredBy:
  - graph/bipartite_matching_lexmin.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj_grl_7_a_bipartite_matching.test.cpp
  - test/aoj0334.test.cpp
documentation_of: graph/bipartite_matching.cpp
layout: document
title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(Bipartite\
  \ Matching)"
---
## 説明
二部グラフの最大マッチングを単純 DFS で求める。
左頂点数を `L`、右頂点数を `R`、辺数を `M` とすると計算量は $O(LM)$。

## できること
- `Bipartite_Matching bm(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を追加する
- `int matching()`
  最大マッチング数を返す
- `vector<pair<int, int>> get_pairs()`
  現在のマッチングを `(左, 右)` の列で返す

## 使い方
辺を追加してから `matching()` を呼ぶ。
マッチ先は `match` に入り、左 `i` の相手は `match[i] - l` で取れる。

```cpp
Bipartite_Matching bm(l, r);
for (auto [a, b] : edges) bm.add_edge(a, b);

int sz = bm.matching();
auto pairs = bm.get_pairs();
```

## 実装上の補足
Hopcroft-Karp より遅いが、実装が短く拡張しやすい。
`Bipartite_Matching_LexMin` の基底クラスとしても使う。
最悪ケースが重いため、このリポでは現状 Library Checker の重い verify には載せていない。
