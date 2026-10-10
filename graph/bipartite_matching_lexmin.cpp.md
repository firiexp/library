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
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
    title: test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
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
    \n    int solve_LexMin() {\n        matching();\n        int res = 0;\n      \
    \  for (int i = 0; i < l; ++i) res += match[i] != -1;\n        int source = l\
    \ + r, sink = source + 1;\n        vector<vector<int>> reverse(sink + 1);\n  \
    \      vector<int> next(sink + 1), queue;\n        vector<pair<int, int>> added;\n\
    \        for (int i = 0; i < l; ++i) {\n            if (match[i] == -1) continue;\n\
    \            for (auto &edges : reverse) edges.clear();\n            auto edge\
    \ = [&](int u, int v) { reverse[v].push_back(u); };\n            for (int u =\
    \ i; u < l; ++u) {\n                if (match[u] == -1) edge(source, u);\n   \
    \             else edge(u, source);\n                for (int v : G[u]) {\n  \
    \                  int w = l + v;\n                    if (match[u] == w) edge(w,\
    \ u);\n                    else edge(u, w);\n                }\n            }\n\
    \            for (int v = l; v < l + r; ++v) {\n                if (match[v] ==\
    \ -1) edge(v, sink);\n                else edge(sink, v);\n            }\n   \
    \         next.assign(sink + 1, -1);\n            next[i] = i;\n            queue.clear();\n\
    \            queue.push_back(i);\n            for (int k = 0; k < (int)queue.size();\
    \ ++k) {\n                int v = queue[k];\n                for (int u : reverse[v])\
    \ {\n                    if (next[u] != -1) continue;\n                    next[u]\
    \ = v;\n                    queue.push_back(u);\n                }\n         \
    \   }\n            int chosen = source;\n            if (next[source] == -1) {\n\
    \                chosen = match[i];\n                for (int v : G[i]) {\n  \
    \                  int w = l + v;\n                    if (w < chosen && next[w]\
    \ != -1) chosen = w;\n                }\n            }\n            if (chosen\
    \ == match[i]) continue;\n            added.clear();\n            int u = i, v\
    \ = chosen;\n            do {\n                if (u < l && l <= v && v < source)\
    \ added.emplace_back(u, v);\n                if (l <= u && u < source && v < l)\
    \ match[u] = match[v] = -1;\n                u = v;\n                v = next[u];\n\
    \            } while (u != i);\n            for (auto [a, b] : added) {\n    \
    \            match[a] = b;\n                match[b] = a;\n            }\n   \
    \     }\n        return res;\n    }\n};\n\n/**\n * @brief \u8F9E\u66F8\u9806\u6700\
    \u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically Minimum Bipartite\
    \ Matching)\n */\n"
  code: "#include \"./bipartite_matching.cpp\"\nclass Bipartite_Matching_LexMin :\
    \ public Bipartite_Matching {\npublic:\n    using Bipartite_Matching::Bipartite_Matching;\n\
    \n    int solve_LexMin() {\n        matching();\n        int res = 0;\n      \
    \  for (int i = 0; i < l; ++i) res += match[i] != -1;\n        int source = l\
    \ + r, sink = source + 1;\n        vector<vector<int>> reverse(sink + 1);\n  \
    \      vector<int> next(sink + 1), queue;\n        vector<pair<int, int>> added;\n\
    \        for (int i = 0; i < l; ++i) {\n            if (match[i] == -1) continue;\n\
    \            for (auto &edges : reverse) edges.clear();\n            auto edge\
    \ = [&](int u, int v) { reverse[v].push_back(u); };\n            for (int u =\
    \ i; u < l; ++u) {\n                if (match[u] == -1) edge(source, u);\n   \
    \             else edge(u, source);\n                for (int v : G[u]) {\n  \
    \                  int w = l + v;\n                    if (match[u] == w) edge(w,\
    \ u);\n                    else edge(u, w);\n                }\n            }\n\
    \            for (int v = l; v < l + r; ++v) {\n                if (match[v] ==\
    \ -1) edge(v, sink);\n                else edge(sink, v);\n            }\n   \
    \         next.assign(sink + 1, -1);\n            next[i] = i;\n            queue.clear();\n\
    \            queue.push_back(i);\n            for (int k = 0; k < (int)queue.size();\
    \ ++k) {\n                int v = queue[k];\n                for (int u : reverse[v])\
    \ {\n                    if (next[u] != -1) continue;\n                    next[u]\
    \ = v;\n                    queue.push_back(u);\n                }\n         \
    \   }\n            int chosen = source;\n            if (next[source] == -1) {\n\
    \                chosen = match[i];\n                for (int v : G[i]) {\n  \
    \                  int w = l + v;\n                    if (w < chosen && next[w]\
    \ != -1) chosen = w;\n                }\n            }\n            if (chosen\
    \ == match[i]) continue;\n            added.clear();\n            int u = i, v\
    \ = chosen;\n            do {\n                if (u < l && l <= v && v < source)\
    \ added.emplace_back(u, v);\n                if (l <= u && u < source && v < l)\
    \ match[u] = match[v] = -1;\n                u = v;\n                v = next[u];\n\
    \            } while (u != i);\n            for (auto [a, b] : added) {\n    \
    \            match[a] = b;\n                match[b] = a;\n            }\n   \
    \     }\n        return res;\n    }\n};\n\n/**\n * @brief \u8F9E\u66F8\u9806\u6700\
    \u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically Minimum Bipartite\
    \ Matching)\n */\n"
  dependsOn:
  - graph/bipartite_matching.cpp
  isVerificationFile: false
  path: graph/bipartite_matching_lexmin.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:44:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
  - test/aoj0334.test.cpp
documentation_of: graph/bipartite_matching_lexmin.cpp
layout: document
title: "\u8F9E\u66F8\u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically\
  \ Minimum Bipartite Matching)"
---
## 説明
二部グラフの最大マッチングのうち、左側頂点の対応先列を辞書順最小にしたものを求める。
先に通常の最大マッチングを作り、その後に左側を小さい順に確定していく。
未マッチを `-1` とし、右頂点番号 `0, 1, ...` より小さいものとして比較する。
時間は $O(L(M+L+R))$、領域は $O(M+L+R)$。

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
辺を `add_edge` してから `solve_LexMin()` を呼ぶ。辺の追加順は任意でよい。
完全マッチングがなくても、最大サイズを保って左側の対応先列を最小にする。

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
