---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: tree/centroid_decomposition_query_helper.cpp
    title: "\u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\u88DC\u52A9(Centroid Query\
      \ Helper)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_range_contour_sum.test.cpp
    title: test/yosupo_aplusb_range_contour_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/yosupo_vertex_add_range_contour_sum_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\
      \u548C"
    links: []
  bundledCode: "#line 1 \"tree/centroid_decomposition_query_helper.cpp\"\nusing namespace\
    \ std;\n\nstruct CentroidDecompositionQueryHelper {\n    int n, root;\n    vector<vector<int>>\
    \ G, tree, path, dist;\n    vector<int> sz, parent, depth;\n    vector<char> used;\n\
    \n    explicit CentroidDecompositionQueryHelper(int n)\n        : n(n), root(-1),\
    \ G(n), tree(n), path(n), dist(n), sz(n), parent(n, -1), depth(n), used(n, 0)\
    \ {}\n\n    void add_edge(int u, int v) {\n        G[u].push_back(v);\n      \
    \  G[v].push_back(u);\n    }\n\n    int build(int start = 0) {\n        tree.assign(n,\
    \ {});\n        path.assign(n, {});\n        dist.assign(n, {});\n        fill(parent.begin(),\
    \ parent.end(), -1);\n        fill(depth.begin(), depth.end(), 0);\n        fill(used.begin(),\
    \ used.end(), 0);\n        dfs_parent.resize(n);\n        order.reserve(n);\n\
    \        if (n == 0) return root = -1;\n        return root = decompose(start,\
    \ -1, 0);\n    }\n\nprivate:\n    vector<int> dfs_parent, order;\n\n    int dfs_size(int\
    \ v, int p) {\n        order.clear();\n        order.push_back(v);\n        dfs_parent[v]\
    \ = p;\n        for (int i = 0; i < (int)order.size(); ++i) {\n            int\
    \ x = order[i];\n            sz[x] = 1;\n            for (int u : G[x]) {\n  \
    \              if (u == dfs_parent[x] || used[u]) continue;\n                dfs_parent[u]\
    \ = x;\n                order.push_back(u);\n            }\n        }\n      \
    \  for (int i = (int)order.size() - 1; i > 0; --i)\n            sz[dfs_parent[order[i]]]\
    \ += sz[order[i]];\n        return sz[v];\n    }\n\n    int find_centroid(int\
    \ v, int p, int half) {\n        while (true) {\n            int next = -1;\n\
    \            for (int u : G[v]) {\n                if (u != p && !used[u] && sz[u]\
    \ > half) {\n                    next = u;\n                    break;\n     \
    \           }\n            }\n            if (next == -1) return v;\n        \
    \    p = v;\n            v = next;\n        }\n    }\n\n    void collect(int v,\
    \ int p, int d, vector<pair<int, int>> &buf) {\n        buf.emplace_back(v, d);\n\
    \        dfs_parent[v] = p;\n        for (int i = 0; i < (int)buf.size(); ++i)\
    \ {\n            auto [x, distance] = buf[i];\n            for (int u : G[x])\
    \ {\n                if (u == dfs_parent[x] || used[u]) continue;\n          \
    \      dfs_parent[u] = x;\n                buf.emplace_back(u, distance + 1);\n\
    \            }\n        }\n    }\n\n    int decompose(int start, int p, int dep)\
    \ {\n        int centroid = find_centroid(start, -1, dfs_size(start, -1) / 2);\n\
    \        used[centroid] = 1;\n        parent[centroid] = p;\n        depth[centroid]\
    \ = dep;\n        path[centroid].push_back(centroid);\n        dist[centroid].push_back(0);\n\
    \        for (auto &&u : G[centroid]) {\n            if (used[u]) continue;\n\
    \            vector<pair<int, int>> buf;\n            collect(u, centroid, 1,\
    \ buf);\n            int child = decompose(u, centroid, dep + 1);\n          \
    \  tree[centroid].push_back(child);\n            for (auto &&[v, d] : buf) {\n\
    \                path[v].push_back(centroid);\n                dist[v].push_back(d);\n\
    \            }\n        }\n        return centroid;\n    }\n};\n\n/**\n * @brief\
    \ \u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\u88DC\u52A9(Centroid Query Helper)\n\
    \ */\n#line 1 \"datastructure/binaryindexedtree.cpp\"\n\n\n\ntemplate<class T>\n\
    class BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n): bit(n),\
    \ m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    explicit BIT(const\
    \ vector<T> &values): bit(values), m(1), n(values.size()) {\n        while (m\
    \ < n) m <<= 1;\n        for (int i = 1; i <= n; ++i) {\n            int parent\
    \ = i + (i & -i);\n            if (parent <= n) bit[parent - 1] += bit[i - 1];\n\
    \        }\n    }\n\n    T sum(int k){\n        T ret = 0;\n        for (; k >\
    \ 0; k -= (k & -k)) ret += bit[k - 1];\n        return ret;\n    }\n\n    void\
    \ add(int k, T x){\n        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n\
    \    }\n\n    int lower_bound(T x) {\n        if (x <= 0) return 0;\n        int\
    \ i = 0;\n        for (int j = m; j; j >>= 1) {\n            if (i + j <= n &&\
    \ bit[i + j - 1] < x) x -= bit[i + j - 1], i += j;\n        }\n        return\
    \ min(i + 1, n);\n    }\n};\n\n/**\n * @brief Binary Indexed Tree(BIT)\n */\n\n\
    \n#line 3 \"tree/range_contour_sum.cpp\"\n\nclass RangeContourSum {\n    CentroidDecompositionQueryHelper\
    \ cd;\n    vector<BIT<long long>> all, branch;\n    vector<int> all_size, branch_size;\n\
    \n    long long sum(BIT<long long> &bit, int size, long long l, long long r) {\n\
    \        int left = (int)max(0LL, min((long long)size, l));\n        int right\
    \ = (int)max(0LL, min((long long)size, r));\n        return bit.sum(right) - bit.sum(left);\n\
    \    }\n\npublic:\n    RangeContourSum(const vector<vector<int>> &g, const vector<long\
    \ long> &values)\n        : cd((int)g.size()), all_size(g.size()), branch_size(g.size())\
    \ {\n        cd.G = g;\n        cd.build();\n        int n = g.size();\n     \
    \   vector<vector<long long>> a(n), b(n);\n        for (int v = 0; v < n; ++v)\
    \ {\n            for (int i = 0; i < (int)cd.path[v].size(); ++i) {\n        \
    \        int c = cd.path[v][i], d = cd.dist[v][i];\n                if ((int)a[c].size()\
    \ <= d) a[c].resize(d + 1);\n                a[c][d] += values[v];\n         \
    \       if (i == 0) continue;\n                int child = cd.path[v][i - 1];\n\
    \                if ((int)b[child].size() <= d) b[child].resize(d + 1);\n    \
    \            b[child][d] += values[v];\n            }\n        }\n        all.reserve(n);\n\
    \        branch.reserve(n);\n        for (int c = 0; c < n; ++c) {\n         \
    \   all_size[c] = a[c].size();\n            branch_size[c] = b[c].size();\n  \
    \          all.emplace_back(a[c]);\n            branch.emplace_back(b[c]);\n \
    \       }\n    }\n\n    void add(int v, long long x) {\n        for (int i = 0;\
    \ i < (int)cd.path[v].size(); ++i) {\n            all[cd.path[v][i]].add(cd.dist[v][i],\
    \ x);\n            if (i > 0) branch[cd.path[v][i - 1]].add(cd.dist[v][i], x);\n\
    \        }\n    }\n\n    long long query(int v, int l, int r) {\n        if (l\
    \ >= r) return 0;\n        long long answer = 0;\n        for (int i = 0; i <\
    \ (int)cd.path[v].size(); ++i) {\n            int c = cd.path[v][i], d = cd.dist[v][i];\n\
    \            answer += sum(all[c], all_size[c], (long long)l - d, (long long)r\
    \ - d);\n            if (i == 0) continue;\n            int child = cd.path[v][i\
    \ - 1];\n            answer -= sum(branch[child], branch_size[child], (long long)l\
    \ - d, (long long)r - d);\n        }\n        return answer;\n    }\n};\n\n/**\n\
    \ * @brief \u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\u548C\
    \n */\n"
  code: "#include \"centroid_decomposition_query_helper.cpp\"\n#include \"../datastructure/binaryindexedtree.cpp\"\
    \n\nclass RangeContourSum {\n    CentroidDecompositionQueryHelper cd;\n    vector<BIT<long\
    \ long>> all, branch;\n    vector<int> all_size, branch_size;\n\n    long long\
    \ sum(BIT<long long> &bit, int size, long long l, long long r) {\n        int\
    \ left = (int)max(0LL, min((long long)size, l));\n        int right = (int)max(0LL,\
    \ min((long long)size, r));\n        return bit.sum(right) - bit.sum(left);\n\
    \    }\n\npublic:\n    RangeContourSum(const vector<vector<int>> &g, const vector<long\
    \ long> &values)\n        : cd((int)g.size()), all_size(g.size()), branch_size(g.size())\
    \ {\n        cd.G = g;\n        cd.build();\n        int n = g.size();\n     \
    \   vector<vector<long long>> a(n), b(n);\n        for (int v = 0; v < n; ++v)\
    \ {\n            for (int i = 0; i < (int)cd.path[v].size(); ++i) {\n        \
    \        int c = cd.path[v][i], d = cd.dist[v][i];\n                if ((int)a[c].size()\
    \ <= d) a[c].resize(d + 1);\n                a[c][d] += values[v];\n         \
    \       if (i == 0) continue;\n                int child = cd.path[v][i - 1];\n\
    \                if ((int)b[child].size() <= d) b[child].resize(d + 1);\n    \
    \            b[child][d] += values[v];\n            }\n        }\n        all.reserve(n);\n\
    \        branch.reserve(n);\n        for (int c = 0; c < n; ++c) {\n         \
    \   all_size[c] = a[c].size();\n            branch_size[c] = b[c].size();\n  \
    \          all.emplace_back(a[c]);\n            branch.emplace_back(b[c]);\n \
    \       }\n    }\n\n    void add(int v, long long x) {\n        for (int i = 0;\
    \ i < (int)cd.path[v].size(); ++i) {\n            all[cd.path[v][i]].add(cd.dist[v][i],\
    \ x);\n            if (i > 0) branch[cd.path[v][i - 1]].add(cd.dist[v][i], x);\n\
    \        }\n    }\n\n    long long query(int v, int l, int r) {\n        if (l\
    \ >= r) return 0;\n        long long answer = 0;\n        for (int i = 0; i <\
    \ (int)cd.path[v].size(); ++i) {\n            int c = cd.path[v][i], d = cd.dist[v][i];\n\
    \            answer += sum(all[c], all_size[c], (long long)l - d, (long long)r\
    \ - d);\n            if (i == 0) continue;\n            int child = cd.path[v][i\
    \ - 1];\n            answer -= sum(branch[child], branch_size[child], (long long)l\
    \ - d, (long long)r - d);\n        }\n        return answer;\n    }\n};\n\n/**\n\
    \ * @brief \u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\u548C\
    \n */\n"
  dependsOn:
  - tree/centroid_decomposition_query_helper.cpp
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: false
  path: tree/range_contour_sum.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:50:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_vertex_add_range_contour_sum_on_tree.test.cpp
  - test/yosupo_aplusb_range_contour_sum.test.cpp
documentation_of: tree/range_contour_sum.cpp
layout: document
title: "\u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\u548C"
---

## 説明
固定された重みなし木の頂点値を更新し、指定した頂点からの距離が範囲内にある頂点の値を合計する。
重心分解と距離ごとの BIT を使う。

## できること
頂点数を $V$ とする。

- `RangeContourSum(g, values)`
  無向木の隣接リスト `g` と `vector<long long>` の初期値から構築する。時間・領域は $O(V\log(V+1))$
- `void add(int v, long long x)`
  頂点 `v` の値に `x` を加える。時間は $O(\log^2(V+1))$
- `long long query(int v, int l, int r)`
  頂点 `v` からの距離が `[l, r)` の頂点値の和を返す。空区間は `0`。時間は $O(\log^2(V+1))$

## 使い方
`g.size() == values.size()` とし、頂点番号は `0` 以上 `g.size()` 未満とする。
負の初期値・加算も使える。合計と中間計算は `long long` に収まるものとする。
距離0は `v` 自身を含み、負の半径や木の直径を超える範囲は有効な距離へ切り詰める。
空の木は構築できるが、頂点を指定する操作は行わない。

## 実装上の補足
重心ごとの和から同じ子枝に含まれる和を引き、二重計上を避ける。
初期値は距離ごとに集めてから BIT を線形構築する。木の深さに比例する再帰は使わない。
