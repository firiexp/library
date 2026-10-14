---
category: "\u30AF\u30A8\u30EA"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_offline_time_intervals.test.cpp
    title: test/yosupo_aplusb_offline_time_intervals.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u8FFD\u52A0\u30FB\u524A\u9664\u30AF\u30A8\u30EA\u306E\u30AA\u30D5\
      \u30E9\u30A4\u30F3\u51E6\u7406"
    links: []
  bundledCode: "#line 1 \"util/offline_time_intervals.cpp\"\n\n\n\nclass OfflineTimeIntervals\
    \ {\n    struct Interval {\n        int l, r, id;\n    };\n    int q;\n    vector<Interval>\
    \ intervals;\n\npublic:\n    explicit OfflineTimeIntervals(int q) : q(q) { assert(q\
    \ >= 0); }\n\n    void add_interval(int l, int r, int event_id) {\n        assert(0\
    \ <= l && l <= r && r <= q);\n        if (l < r) intervals.push_back({l, r, event_id});\n\
    \    }\n\n    template<class Snapshot, class Apply, class Rollback, class Answer>\n\
    \    void run(Snapshot snapshot, Apply apply, Rollback rollback, Answer answer)\
    \ const {\n        if (q == 0) return;\n        size_t size = 1;\n        while\
    \ (size < (size_t)q) size *= 2;\n        auto decompose = [&](const Interval &interval,\
    \ auto visit) {\n            size_t l = size + interval.l, r = size + interval.r;\n\
    \            while (l < r) {\n                if (l & 1) visit(l++);\n       \
    \         if (r & 1) visit(--r);\n                l /= 2;\n                r /=\
    \ 2;\n            }\n        };\n        vector<size_t> offset(2 * size + 1);\n\
    \        for (const auto &interval : intervals) {\n            decompose(interval,\
    \ [&](size_t node) { ++offset[node + 1]; });\n        }\n        for (size_t i\
    \ = 1; i < offset.size(); ++i) offset[i] += offset[i - 1];\n        vector<int>\
    \ events(offset.back());\n        {\n            auto cursor = offset;\n     \
    \       for (const auto &interval : intervals) {\n                decompose(interval,\
    \ [&](size_t node) { events[cursor[node]++] = interval.id; });\n            }\n\
    \        }\n        auto dfs = [&](auto &&self, size_t node, size_t l, size_t\
    \ r) -> void {\n            if (l >= (size_t)q) return;\n            auto state\
    \ = snapshot();\n            for (size_t i = offset[node]; i < offset[node + 1];\
    \ ++i) apply(events[i]);\n            if (r - l == 1) answer((int)l);\n      \
    \      else {\n                size_t mid = l + (r - l) / 2;\n               \
    \ self(self, node * 2, l, mid);\n                self(self, node * 2 + 1, mid,\
    \ r);\n            }\n            rollback(state);\n        };\n        dfs(dfs,\
    \ 1, 0, size);\n    }\n};\n\n\n\n/**\n * @brief \u8FFD\u52A0\u30FB\u524A\u9664\
    \u30AF\u30A8\u30EA\u306E\u30AA\u30D5\u30E9\u30A4\u30F3\u51E6\u7406\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_UTIL_OFFLINE_TIME_INTERVALS_CPP\n#define FIRIEXP_LIBRARY_UTIL_OFFLINE_TIME_INTERVALS_CPP\n\
    \nclass OfflineTimeIntervals {\n    struct Interval {\n        int l, r, id;\n\
    \    };\n    int q;\n    vector<Interval> intervals;\n\npublic:\n    explicit\
    \ OfflineTimeIntervals(int q) : q(q) { assert(q >= 0); }\n\n    void add_interval(int\
    \ l, int r, int event_id) {\n        assert(0 <= l && l <= r && r <= q);\n   \
    \     if (l < r) intervals.push_back({l, r, event_id});\n    }\n\n    template<class\
    \ Snapshot, class Apply, class Rollback, class Answer>\n    void run(Snapshot\
    \ snapshot, Apply apply, Rollback rollback, Answer answer) const {\n        if\
    \ (q == 0) return;\n        size_t size = 1;\n        while (size < (size_t)q)\
    \ size *= 2;\n        auto decompose = [&](const Interval &interval, auto visit)\
    \ {\n            size_t l = size + interval.l, r = size + interval.r;\n      \
    \      while (l < r) {\n                if (l & 1) visit(l++);\n             \
    \   if (r & 1) visit(--r);\n                l /= 2;\n                r /= 2;\n\
    \            }\n        };\n        vector<size_t> offset(2 * size + 1);\n   \
    \     for (const auto &interval : intervals) {\n            decompose(interval,\
    \ [&](size_t node) { ++offset[node + 1]; });\n        }\n        for (size_t i\
    \ = 1; i < offset.size(); ++i) offset[i] += offset[i - 1];\n        vector<int>\
    \ events(offset.back());\n        {\n            auto cursor = offset;\n     \
    \       for (const auto &interval : intervals) {\n                decompose(interval,\
    \ [&](size_t node) { events[cursor[node]++] = interval.id; });\n            }\n\
    \        }\n        auto dfs = [&](auto &&self, size_t node, size_t l, size_t\
    \ r) -> void {\n            if (l >= (size_t)q) return;\n            auto state\
    \ = snapshot();\n            for (size_t i = offset[node]; i < offset[node + 1];\
    \ ++i) apply(events[i]);\n            if (r - l == 1) answer((int)l);\n      \
    \      else {\n                size_t mid = l + (r - l) / 2;\n               \
    \ self(self, node * 2, l, mid);\n                self(self, node * 2 + 1, mid,\
    \ r);\n            }\n            rollback(state);\n        };\n        dfs(dfs,\
    \ 1, 0, size);\n    }\n};\n\n#endif\n\n/**\n * @brief \u8FFD\u52A0\u30FB\u524A\
    \u9664\u30AF\u30A8\u30EA\u306E\u30AA\u30D5\u30E9\u30A4\u30F3\u51E6\u7406\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/offline_time_intervals.cpp
  requiredBy: []
  timestamp: '2026-10-15 00:51:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_offline_time_intervals.test.cpp
date: 2026-10-14
documentation_of: util/offline_time_intervals.cpp
layout: document
tags: "\u30AF\u30A8\u30EA"
title: "\u8FFD\u52A0\u30FB\u524A\u9664\u30AF\u30A8\u30EA\u306E\u30AA\u30D5\u30E9\u30A4\
  \u30F3\u51E6\u7406"
---

## 説明
辺の追加・削除を含むグラフの連結性判定などを、rollback 可能なデータ構造でオフラインに処理する。
例えば、クエリ `l` で追加し、クエリ `r` で削除する辺は、区間 `[l,r)` で有効なイベントとして登録する。
各クエリへの回答時には、その時点で有効なイベントだけが適用された状態になる。

イベントの適用順序が変わってもクエリの答えが変わらない操作を扱う。

## できること
- `OfflineTimeIntervals tm(q)`
  `q` 個のクエリを処理する。追加・削除もクエリ数に含める
- `tm.add_interval(l, r, event_id)`
  半開区間 `[l,r)` で有効なイベント ID を登録する。空区間は無視し、同じ ID の複数区間も別々に適用する
- `tm.run(snapshot, apply, rollback, answer)`
  登録した区間を処理し、`answer(t)` をクエリ番号順に呼ぶ。終了時には開始時の状態へ戻す。同じ登録内容で再実行できる

## 使い方
イベント本体は利用側の配列で保持する。区間は `0 <= l <= r <= q` とする。
`tm.run` は区間をセグメント木に分け、各ノードで `snapshot()` により状態を記録してから `apply(id)` でイベントを適用する。
そのノード内の処理が終わると `rollback(state)` で記録した状態へ戻す。
葉では `answer(t)` でクエリに答える。`answer` は状態の意味を変更せず、回答が不要なクエリでは何もしなくてよい。

```cpp
tm.add_interval(l, r, id);
tm.run([&] { return uf.get_state(); },
       [&](int id) { uf.unite(edges[id].u, edges[id].v, edges[id].w); },
       [&](int state) { uf.rollback(state); },
       [&](int t) { answer[t] = uf.consistent(); });
```

`q=0` では callback を呼ばない。登録後に別途 build や reserve を呼ぶ必要はない。

## 実装上の補足
登録する区間数を $K$、クエリ数を $Q$ とする。

- `tm.add_interval` は1回あたり償却 $O(1)$。登録内容の保持に $O(K)$ の領域を使う
- `tm.run` は callback を除いて $O(Q+K\log Q)$ 時間、作業領域も $O(Q+K\log Q)$

`tm.run` は `snapshot` と `rollback` をそれぞれ $O(Q)$ 回、`apply` を $O(K\log Q)$ 回、`answer` を $Q$ 回呼ぶ。
`rollback` が操作を1つずつ取り消す実装なら、取り消す操作の総数は `apply` の呼び出し回数と同じとなる。
