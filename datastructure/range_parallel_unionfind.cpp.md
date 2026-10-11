---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_range_parallel_unionfind.test.cpp
    title: test/yosupo_aplusb_range_parallel_unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_parallel_unionfind.test.cpp
    title: test/yosupo_range_parallel_unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Range Parallel UnionFind
    links: []
  bundledCode: "#line 1 \"datastructure/range_parallel_unionfind.cpp\"\nclass RangeParallelUnionFind\
    \ {\n    vector<vector<int>> parent;\n    vector<int> lg;\n    int components;\n\
    \n    int leader(int level, int v) {\n        auto& p = parent[level];\n     \
    \   int r = v;\n        while (p[r] >= 0) r = p[r];\n        while (v != r) {\n\
    \            int next = p[v];\n            p[v] = r;\n            v = next;\n\
    \        }\n        return r;\n    }\n\n    template<class F>\n    int unite(int\
    \ level, int a, int b, F& on_merge) {\n        a = leader(level, a);\n       \
    \ b = leader(level, b);\n        if (a == b) return 0;\n        if (parent[level][a]\
    \ > parent[level][b]) swap(a, b);\n        if (level == 0) on_merge(a, b);\n \
    \       parent[level][a] += parent[level][b];\n        parent[level][b] = a;\n\
    \        if (level == 0) {\n            --components;\n            return 1;\n\
    \        }\n        int half = 1 << (level - 1);\n        int merged = unite(level\
    \ - 1, a, b, on_merge);\n        return merged + unite(level - 1, a + half, b\
    \ + half, on_merge);\n    }\n\npublic:\n    explicit RangeParallelUnionFind(int\
    \ n) : lg(n + 1), components(n) {\n        for (int i = 2; i <= n; ++i) lg[i]\
    \ = lg[i / 2] + 1;\n        for (int level = 0; (1LL << level) <= n; ++level)\n\
    \            parent.emplace_back(n - (1 << level) + 1, -1);\n    }\n\n    int\
    \ root(int v) { return leader(0, v); }\n    bool same(int a, int b) { return root(a)\
    \ == root(b); }\n    int size(int v) { return -parent[0][root(v)]; }\n    int\
    \ count() const { return components; }\n\n    template<class F>\n    int unite_range(int\
    \ a, int b, int k, F on_merge) {\n        if (k == 0 || a == b) return 0;\n  \
    \      int level = lg[k], length = 1 << level;\n        int merged = unite(level,\
    \ a, b, on_merge);\n        return merged + unite(level, a + k - length, b + k\
    \ - length, on_merge);\n    }\n\n    int unite_range(int a, int b, int k) {\n\
    \        return unite_range(a, b, k, [](int, int) {});\n    }\n};\n\n/**\n * @brief\
    \ Range Parallel UnionFind\n */\n"
  code: "class RangeParallelUnionFind {\n    vector<vector<int>> parent;\n    vector<int>\
    \ lg;\n    int components;\n\n    int leader(int level, int v) {\n        auto&\
    \ p = parent[level];\n        int r = v;\n        while (p[r] >= 0) r = p[r];\n\
    \        while (v != r) {\n            int next = p[v];\n            p[v] = r;\n\
    \            v = next;\n        }\n        return r;\n    }\n\n    template<class\
    \ F>\n    int unite(int level, int a, int b, F& on_merge) {\n        a = leader(level,\
    \ a);\n        b = leader(level, b);\n        if (a == b) return 0;\n        if\
    \ (parent[level][a] > parent[level][b]) swap(a, b);\n        if (level == 0) on_merge(a,\
    \ b);\n        parent[level][a] += parent[level][b];\n        parent[level][b]\
    \ = a;\n        if (level == 0) {\n            --components;\n            return\
    \ 1;\n        }\n        int half = 1 << (level - 1);\n        int merged = unite(level\
    \ - 1, a, b, on_merge);\n        return merged + unite(level - 1, a + half, b\
    \ + half, on_merge);\n    }\n\npublic:\n    explicit RangeParallelUnionFind(int\
    \ n) : lg(n + 1), components(n) {\n        for (int i = 2; i <= n; ++i) lg[i]\
    \ = lg[i / 2] + 1;\n        for (int level = 0; (1LL << level) <= n; ++level)\n\
    \            parent.emplace_back(n - (1 << level) + 1, -1);\n    }\n\n    int\
    \ root(int v) { return leader(0, v); }\n    bool same(int a, int b) { return root(a)\
    \ == root(b); }\n    int size(int v) { return -parent[0][root(v)]; }\n    int\
    \ count() const { return components; }\n\n    template<class F>\n    int unite_range(int\
    \ a, int b, int k, F on_merge) {\n        if (k == 0 || a == b) return 0;\n  \
    \      int level = lg[k], length = 1 << level;\n        int merged = unite(level,\
    \ a, b, on_merge);\n        return merged + unite(level, a + k - length, b + k\
    \ - length, on_merge);\n    }\n\n    int unite_range(int a, int b, int k) {\n\
    \        return unite_range(a, b, k, [](int, int) {});\n    }\n};\n\n/**\n * @brief\
    \ Range Parallel UnionFind\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/range_parallel_unionfind.cpp
  requiredBy: []
  timestamp: '2026-10-12 01:24:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_range_parallel_unionfind.test.cpp
  - test/yosupo_range_parallel_unionfind.test.cpp
documentation_of: datastructure/range_parallel_unionfind.cpp
layout: document
title: Range Parallel UnionFind
---

## 説明
長さ $k$ の2区間について、対応する頂点 $(a+i,b+i)$ をまとめて同じ集合にする。
階層ごとに併合済みの区間を記録し、同じ対応を繰り返し処理する手間を省く。

## できること
- `RangeParallelUnionFind uf(n)`
  頂点 $0,1,\ldots,n-1$ を、それぞれ独立した集合として構築する
- `int unite_range(int a, int b, int k)`
  $0\leq i<k$ のすべての頂点対 $(a+i,b+i)$ を併合し、新たに成立した成分の併合数を返す
- `int unite_range(int a, int b, int k, F on_merge)`
  異なる頂点成分を併合する直前に `on_merge(keep, absorbed)` を呼ぶ。引数は併合前の代表元で、`keep` が併合後の代表元になる
- `int root(int v)` / `bool same(int a, int b)`
  代表元の取得と、同じ集合に属するかの判定を行う
- `int size(int v)` / `int count() const`
  頂点 `v` の成分の頂点数と、全体の成分数を返す

## 使い方
$0\leq k\leq n$、$0\leq a,b\leq n-k$ とする。区間が重なっていてもよい。
callback で成分ごとの値を更新できる。callback 内では、この UnionFind の新たな併合は行わない。

```cpp
RangeParallelUnionFind uf(n);
vector<long long> component_sum = weights;
uf.unite_range(a, b, k, [&](int keep, int absorbed) {
    component_sum[keep] += component_sum[absorbed];
});
```

## 実装上の補足
構築と保持領域は $O(N\log(N+1))$。$Q$ 回の区間併合の合計は償却 $O((N\log(N+1)+Q)\alpha(N))$ 時間で、callback の実行時間は別途加わる。
callback の呼出総数は高々 $\max(0,N-1)$ 回。1回の区間併合が常に対数時間で終わるという保証ではない。
`root`・`same`・`size` は償却 $O(\alpha(N))$、`count` は $O(1)$ 時間。
