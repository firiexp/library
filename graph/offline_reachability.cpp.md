---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/SCC.cpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_offline_reachability.test.cpp
    title: test/yosupo_aplusb_offline_reachability.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6709\u5411\u30B0\u30E9\u30D5\u306E\u4E00\u62EC\u5230\u9054\u5224\
      \u5B9A"
    links: []
  bundledCode: "#line 1 \"graph/SCC.cpp\"\nclass SCC {\n    struct CSR {\n       \
    \ vector<int> start, elist;\n\n        CSR() = default;\n\n        CSR(int n,\
    \ const vector<pair<int, int>> &edges, bool rev) : start(n + 1), elist(edges.size())\
    \ {\n            for (auto &&[a, b] : edges) {\n                ++start[(rev ?\
    \ b : a) + 1];\n            }\n            for (int i = 0; i < n; ++i) start[i\
    \ + 1] += start[i];\n            auto counter = start;\n            for (auto\
    \ &&[a, b] : edges) {\n                int from = rev ? b : a;\n             \
    \   int to = rev ? a : b;\n                elist[counter[from]++] = to;\n    \
    \        }\n        }\n    };\n\n    int n = 0;\n    vector<pair<int, int>> edges;\n\
    \npublic:\n    vector<vector<int>> G_out;\n    vector<int> vs, used, cmp, sz;\n\
    \    SCC() = default;\n    explicit SCC(int n) : n(n), used(n), cmp(n), sz(n)\
    \ {}\n\n    void add_edge(int a, int b){\n        edges.emplace_back(a, b);\n\
    \    }\n\n    int build() {\n        CSR G(n, edges, false), G_r(n, edges, true);\n\
    \        vs.clear();\n        vs.reserve(n);\n        fill(used.begin(), used.end(),\
    \ 0);\n        auto dfs = [&](auto &&self, int v) -> void {\n            used[v]\
    \ = 1;\n            for (int ei = G.start[v]; ei < G.start[v + 1]; ++ei) {\n \
    \               int u = G.elist[ei];\n                if(!used[u]) self(self,\
    \ u);\n            }\n            vs.emplace_back(v);\n        };\n        for\
    \ (int i = 0; i < n; ++i) {\n            if(!used[i]) dfs(dfs, i);\n        }\n\
    \        fill(used.begin(), used.end(), 0);\n        sz.resize(n);\n        fill(sz.begin(),\
    \ sz.end(), 0);\n        int k = 0;\n        auto dfs_r = [&](auto &&self, int\
    \ v, int c) -> void {\n            used[v] = 1;\n            cmp[v] = c;\n   \
    \         sz[c]++;\n            for (int ei = G_r.start[v]; ei < G_r.start[v +\
    \ 1]; ++ei) {\n                int u = G_r.elist[ei];\n                if(!used[u])\
    \ self(self, u, c);\n            }\n        };\n        for (int i = n - 1; i\
    \ >= 0; --i) {\n            if(!used[vs[i]]){\n                dfs_r(dfs_r, vs[i],\
    \ k++);\n            }\n        }\n        G_out.assign(k, {});\n        sz.resize(k);\n\
    \        if (k <= 1) return k;\n        vector<int> head(k, -1), next(n), seen(k,\
    \ -1);\n        for (int v = 0; v < n; ++v) {\n            next[v] = head[cmp[v]];\n\
    \            head[cmp[v]] = v;\n        }\n        for (int to = 0; to < k; ++to)\
    \ {\n            for (int v = head[to]; v != -1; v = next[v]) {\n            \
    \    for (int ei = G_r.start[v]; ei < G_r.start[v + 1]; ++ei) {\n            \
    \        int from = cmp[G_r.elist[ei]];\n                    if (from == to ||\
    \ seen[from] == to) continue;\n                    seen[from] = to;\n        \
    \            G_out[from].push_back(to);\n                }\n            }\n  \
    \      }\n        return k;\n    }\n\n    int operator[](int k) const { return\
    \ cmp[k]; }\n};\n\n/**\n * @brief \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)\n\
    \ */\n#line 2 \"graph/offline_reachability.cpp\"\n\nvector<char> offline_reachability(int\
    \ n, const vector<pair<int, int>> &edges,\n                                  const\
    \ vector<pair<int, int>> &queries) {\n    vector<char> answer(queries.size());\n\
    \    if (queries.empty()) return answer;\n    SCC scc(n);\n    for (auto [u, v]\
    \ : edges) scc.add_edge(u, v);\n    int count = scc.build();\n    vector<int>\
    \ sources(count, -1), targets(count, -1);\n    int ns = 0, nt = 0;\n    for (int\
    \ i = 0; i < (int)queries.size(); ++i) {\n        auto [u, v] = queries[i];\n\
    \        int s = scc[u], t = scc[v];\n        if (s == t) answer[i] = 1;\n   \
    \     if (s >= t) continue;\n        if (sources[s] == -1) sources[s] = ns++;\n\
    \        if (targets[t] == -1) targets[t] = nt++;\n    }\n    bool forward = ns\
    \ <= nt;\n    auto &group = forward ? sources : targets;\n    int k = forward\
    \ ? ns : nt;\n    vector<int> component(k), head(k, -1), next(queries.size());\n\
    \    for (int v = 0; v < count; ++v)\n        if (group[v] != -1) component[group[v]]\
    \ = v;\n    for (int i = 0; i < (int)queries.size(); ++i) {\n        auto [u,\
    \ v] = queries[i];\n        int s = scc[u], t = scc[v];\n        if (s >= t) continue;\n\
    \        int id = group[forward ? s : t];\n        next[i] = head[id];\n     \
    \   head[id] = i;\n    }\n    vector<unsigned long long> mask(count);\n    for\
    \ (int begin = 0; begin < k; begin += 64) {\n        int end = min(begin + 64,\
    \ k);\n        fill(mask.begin(), mask.end(), 0);\n        for (int id = begin;\
    \ id < end; ++id)\n            mask[component[id]] = 1ULL << (id - begin);\n \
    \       if (forward) {\n            for (int v = 0; v < count; ++v)\n        \
    \        for (int u : scc.G_out[v]) mask[u] |= mask[v];\n        } else {\n  \
    \          for (int v = count - 1; v >= 0; --v)\n                for (int u :\
    \ scc.G_out[v]) mask[v] |= mask[u];\n        }\n        for (int id = begin; id\
    \ < end; ++id) {\n            for (int i = head[id]; i != -1; i = next[i]) {\n\
    \                auto [u, v] = queries[i];\n                answer[i] = (mask[scc[forward\
    \ ? v : u]] >> (id - begin)) & 1;\n            }\n        }\n    }\n    return\
    \ answer;\n}\n\n/**\n * @brief \u6709\u5411\u30B0\u30E9\u30D5\u306E\u4E00\u62EC\
    \u5230\u9054\u5224\u5B9A\n */\n"
  code: "#include \"SCC.cpp\"\n\nvector<char> offline_reachability(int n, const vector<pair<int,\
    \ int>> &edges,\n                                  const vector<pair<int, int>>\
    \ &queries) {\n    vector<char> answer(queries.size());\n    if (queries.empty())\
    \ return answer;\n    SCC scc(n);\n    for (auto [u, v] : edges) scc.add_edge(u,\
    \ v);\n    int count = scc.build();\n    vector<int> sources(count, -1), targets(count,\
    \ -1);\n    int ns = 0, nt = 0;\n    for (int i = 0; i < (int)queries.size();\
    \ ++i) {\n        auto [u, v] = queries[i];\n        int s = scc[u], t = scc[v];\n\
    \        if (s == t) answer[i] = 1;\n        if (s >= t) continue;\n        if\
    \ (sources[s] == -1) sources[s] = ns++;\n        if (targets[t] == -1) targets[t]\
    \ = nt++;\n    }\n    bool forward = ns <= nt;\n    auto &group = forward ? sources\
    \ : targets;\n    int k = forward ? ns : nt;\n    vector<int> component(k), head(k,\
    \ -1), next(queries.size());\n    for (int v = 0; v < count; ++v)\n        if\
    \ (group[v] != -1) component[group[v]] = v;\n    for (int i = 0; i < (int)queries.size();\
    \ ++i) {\n        auto [u, v] = queries[i];\n        int s = scc[u], t = scc[v];\n\
    \        if (s >= t) continue;\n        int id = group[forward ? s : t];\n   \
    \     next[i] = head[id];\n        head[id] = i;\n    }\n    vector<unsigned long\
    \ long> mask(count);\n    for (int begin = 0; begin < k; begin += 64) {\n    \
    \    int end = min(begin + 64, k);\n        fill(mask.begin(), mask.end(), 0);\n\
    \        for (int id = begin; id < end; ++id)\n            mask[component[id]]\
    \ = 1ULL << (id - begin);\n        if (forward) {\n            for (int v = 0;\
    \ v < count; ++v)\n                for (int u : scc.G_out[v]) mask[u] |= mask[v];\n\
    \        } else {\n            for (int v = count - 1; v >= 0; --v)\n        \
    \        for (int u : scc.G_out[v]) mask[v] |= mask[u];\n        }\n        for\
    \ (int id = begin; id < end; ++id) {\n            for (int i = head[id]; i !=\
    \ -1; i = next[i]) {\n                auto [u, v] = queries[i];\n            \
    \    answer[i] = (mask[scc[forward ? v : u]] >> (id - begin)) & 1;\n         \
    \   }\n        }\n    }\n    return answer;\n}\n\n/**\n * @brief \u6709\u5411\u30B0\
    \u30E9\u30D5\u306E\u4E00\u62EC\u5230\u9054\u5224\u5B9A\n */\n"
  dependsOn:
  - graph/SCC.cpp
  isVerificationFile: false
  path: graph/offline_reachability.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:45:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_offline_reachability.test.cpp
documentation_of: graph/offline_reachability.cpp
layout: document
title: "\u6709\u5411\u30B0\u30E9\u30D5\u306E\u4E00\u62EC\u5230\u9054\u5224\u5B9A"
---

## 説明
有向グラフの指定した頂点対について、到達できるかをまとめて求める。
強連結成分を縮約し、始点・終点の種類が少ない側を64個ずつ伝播する。

## できること
頂点数を $V$、辺数を $E$、クエリ数を $Q$ とする。

- `vector<char> offline_reachability(n, edges, queries)`
  `queries` の各 `(s, t)` に対し、到達可能なら `1`、不可能なら `0` を入力順に返す。
  最悪時間は $O((V+E)\lceil V/64\rceil+Q)$、返却値を含む追加領域は $O(V+E+Q)$

## 使い方
頂点番号は `0` 以上 `n` 未満。`edges` と `queries` は `vector<pair<int, int>>` で渡す。
長さ0の経路を認めるので、同じ頂点への答えは `1` となる。
自己ループ・多重辺・非連結グラフに対応し、入力は変更しない。
空クエリの結果は空。`n == 0` なら辺とクエリも空とする。

## 実装上の補足
各クエリは所属するバッチでだけ調べ、全頂点対の到達表は保持しない。
