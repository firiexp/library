---
category: "\u30AF\u30A8\u30EA"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_parallel_binary_search.test.cpp
    title: test/yosupo_aplusb_parallel_binary_search.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E26\u5217\u4E8C\u5206\u63A2\u7D22"
    links: []
  bundledCode: "#line 1 \"util/parallel_binary_search.cpp\"\n\n\n\ntemplate<class\
    \ Reset, class Apply, class Check>\nvector<int> parallel_binary_search(int m,\
    \ int q, Reset reset, Apply apply, Check check) {\n    if (q == 0) return {};\n\
    \    vector<int> lo(q, -1), hi(q, m + 1), head(m + 1), next(q);\n    while (true)\
    \ {\n        fill(head.begin(), head.end(), -1);\n        int last = -1;\n   \
    \     for (int i = 0; i < q; ++i) {\n            if (lo[i] + 1 == hi[i]) continue;\n\
    \            int mid = lo[i] + ((long long)hi[i] - lo[i]) / 2;\n            next[i]\
    \ = head[mid];\n            head[mid] = i;\n            last = max(last, mid);\n\
    \        }\n        if (last == -1) break;\n        reset();\n        for (int\
    \ t = 0; t <= last; ++t) {\n            if (t) apply(t - 1);\n            for\
    \ (int i = head[t]; i != -1; i = next[i]) {\n                if (check(i)) hi[i]\
    \ = t;\n                else lo[i] = t;\n            }\n        }\n    }\n   \
    \ return hi;\n}\n\n\n\n/**\n * @brief \u4E26\u5217\u4E8C\u5206\u63A2\u7D22\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_UTIL_PARALLEL_BINARY_SEARCH_CPP\n#define FIRIEXP_LIBRARY_UTIL_PARALLEL_BINARY_SEARCH_CPP\n\
    \ntemplate<class Reset, class Apply, class Check>\nvector<int> parallel_binary_search(int\
    \ m, int q, Reset reset, Apply apply, Check check) {\n    if (q == 0) return {};\n\
    \    vector<int> lo(q, -1), hi(q, m + 1), head(m + 1), next(q);\n    while (true)\
    \ {\n        fill(head.begin(), head.end(), -1);\n        int last = -1;\n   \
    \     for (int i = 0; i < q; ++i) {\n            if (lo[i] + 1 == hi[i]) continue;\n\
    \            int mid = lo[i] + ((long long)hi[i] - lo[i]) / 2;\n            next[i]\
    \ = head[mid];\n            head[mid] = i;\n            last = max(last, mid);\n\
    \        }\n        if (last == -1) break;\n        reset();\n        for (int\
    \ t = 0; t <= last; ++t) {\n            if (t) apply(t - 1);\n            for\
    \ (int i = head[t]; i != -1; i = next[i]) {\n                if (check(i)) hi[i]\
    \ = t;\n                else lo[i] = t;\n            }\n        }\n    }\n   \
    \ return hi;\n}\n\n#endif\n\n/**\n * @brief \u4E26\u5217\u4E8C\u5206\u63A2\u7D22\
    \n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/parallel_binary_search.cpp
  requiredBy: []
  timestamp: '2026-10-15 00:51:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_parallel_binary_search.test.cpp
date: 2026-10-14
documentation_of: util/parallel_binary_search.cpp
layout: document
tags: "\u30AF\u30A8\u30EA"
title: "\u4E26\u5217\u4E8C\u5206\u63A2\u7D22"
---

## 説明
更新列の先頭から何個を適用すれば条件が初めて成立するかを、複数のクエリについてまとめて求める。
各条件は更新数 $t=0,\ldots,M$ に対して false から true へ単調に変わるものとする。

## できること
- `parallel_binary_search(m, q, reset, apply, check)`
  各クエリの最初の成立時刻を `vector<int>` で返す。初期状態で成立すれば `0`、最後まで不成立なら `m+1`
- `reset()`
  更新を適用していない初期状態を作る
- `apply(i)`
  0-based の更新 `i` を適用する。各ラウンドで `0` から順に呼ぶ
- `check(id)`
  現在の状態でクエリ `id` が成立するかを返す

## 使い方
状態を扱う3つの callback を渡す。`check` は更新 prefix の意味を変えてはならないが、UnionFind の経路圧縮など内部表現の変更はよい。
`0 <= m < INT_MAX`、`q >= 0` とし、補助配列を確保できる範囲で使う。
`q=0` では callback を呼ばない。`m=0` では1回だけ初期化し、各条件を初期状態で判定する。
終了後の状態は最後に判定した prefix のままとなる。

```cpp
auto answer = parallel_binary_search(m, q,
    [&] { uf = UnionFind(n); },
    [&](int i) { uf.unite(edges[i].first, edges[i].second); },
    [&](int id) { return uf.same(queries[id].first, queries[id].second); });
```

## 実装上の補足
更新数を $M$、クエリ数を $Q$ とする。
$O(\log M)$ ラウンドの二分探索を行い、各ラウンドで `reset` を1回、`apply` を高々 $M$ 回、`check` を高々 $Q$ 回呼ぶ。
callback 以外の処理は $O((M+Q)\log M)$ 時間、補助領域は $O(M+Q)$。
