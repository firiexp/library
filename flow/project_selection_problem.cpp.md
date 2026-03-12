---
category: "\u30D5\u30ED\u30FC"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/dinic.cpp
    title: "Dinic(\u6700\u5927\u6D41)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yuki957_project_selection_problem.test.cpp
    title: test/yuki957_project_selection_problem.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Project Selection Problem
    links: []
  bundledCode: "#line 1 \"flow/dinic.cpp\"\ntemplate<class T, bool directed>\nclass\
    \ Dinic {\n    void bfs(int s){\n        fill(level.begin(),level.end(), -1);\n\
    \        queue<int> Q;\n        level[s] = 0;\n        Q.emplace(s);\n       \
    \ while(!Q.empty()){\n            int v = Q.front(); Q.pop();\n            for\
    \ (auto &&e : G[v]){\n                if(e.cap > 0 && level[e.to] < 0){\n    \
    \                level[e.to] = level[v] + 1;\n                    Q.emplace(e.to);\n\
    \                }\n            }\n        }\n    }\n \n    T dfs(int v, int t,\
    \ T f){\n        if(v == t) return f;\n        for(int &i = iter[v]; i < G[v].size();\
    \ i++){\n            edge &e = G[v][i];\n            if(e.cap > 0 && level[v]\
    \ < level[e.to]){\n                T d = dfs(e.to, t, min(f,  e.cap));\n     \
    \           if(d == 0) continue;\n                e.cap -= d;\n              \
    \  G[e.to][e.rev].cap += d;\n                return d;\n            }\n      \
    \  }\n        return 0;\n    }\npublic:\n    struct edge {\n        int to{};\
    \ T cap; int rev{};\n        edge() = default;\n        edge(int to, T cap, int\
    \ rev) : to(to), cap(cap), rev(rev) {}\n    };\n \n    vector<vector<edge>> G;\n\
    \    vector<int> level, iter;\n    Dinic() = default;\n    explicit Dinic(int\
    \ n) : G(n), level(n), iter(n) {}\n \n    void add_edge(int from, int to, T cap){\n\
    \        G[from].emplace_back(to, cap, G[to].size());\n        G[to].emplace_back(from,\
    \ directed ? 0 : cap,  G[from].size()-1);\n    }\n \n \n    T flow(int s, int\
    \ t, T lim = INF<T>){\n        T ret = 0;\n        while(true) {\n           \
    \ bfs(s);\n            if(level[t] < 0 || lim == 0) break;\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            while(true){\n                T f = dfs(s, t, lim);\n     \
    \           if(f == 0) break;\n                ret += f;\n                lim\
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Dinic\u6CD5(Dinic)\n */\n#line 2 \"flow/project_selection_problem.cpp\"\n\n\
    template<class T>\nclass ProjectSelectionProblem {\n    int n;\n    T base_score{};\n\
    \    vector<T> weight;\n    vector<tuple<int, int, T>> penalty;\n    vector<int>\
    \ selected;\n\npublic:\n    ProjectSelectionProblem() : n(0) {}\n    explicit\
    \ ProjectSelectionProblem(int n) : n(n), base_score(0), weight(n, 0), selected(n,\
    \ 0) {}\n\n    int add_vertex() {\n        weight.emplace_back(0);\n        selected.emplace_back(0);\n\
    \        return n++;\n    }\n\n    int size() const {\n        return n;\n   \
    \ }\n\n    void add_true_profit(int v, T x) {\n        weight[v] += x;\n    }\n\
    \n    void add_false_profit(int v, T x) {\n        base_score += x;\n        weight[v]\
    \ -= x;\n    }\n\n    void add_penalty(int x, int y, T cost) {\n        penalty.emplace_back(x,\
    \ y, cost);\n    }\n\n    void add_if_then(int x, int y) {\n        add_penalty(x,\
    \ y, INF<T>);\n    }\n\n    void force_true(int v) {\n        add_true_profit(v,\
    \ INF<T>);\n    }\n\n    void force_false(int v) {\n        add_false_profit(v,\
    \ INF<T>);\n    }\n\n    T solve() {\n        int s = n, t = n + 1;\n        Dinic<T,\
    \ true> mf(n + 2);\n        T offset = base_score;\n        for (int v = 0; v\
    \ < n; ++v) {\n            if (weight[v] >= 0) {\n                offset += weight[v];\n\
    \                mf.add_edge(s, v, weight[v]);\n            } else {\n       \
    \         mf.add_edge(v, t, -weight[v]);\n            }\n        }\n        for\
    \ (auto&& [x, y, cost] : penalty) {\n            mf.add_edge(x, y, cost);\n  \
    \      }\n        T cut = mf.flow(s, t);\n\n        fill(selected.begin(), selected.end(),\
    \ 0);\n        queue<int> q;\n        q.emplace(s);\n        vector<int> vis(n\
    \ + 2, 0);\n        vis[s] = 1;\n        while (!q.empty()) {\n            int\
    \ v = q.front();\n            q.pop();\n            for (auto&& e : mf.G[v]) {\n\
    \                if (e.cap <= 0 || vis[e.to]) continue;\n                vis[e.to]\
    \ = 1;\n                q.emplace(e.to);\n            }\n        }\n        for\
    \ (int v = 0; v < n; ++v) {\n            selected[v] = vis[v];\n        }\n  \
    \      return offset - cut;\n    }\n\n    const vector<int>& get_selected() const\
    \ {\n        return selected;\n    }\n};\n\n/**\n * @brief Project Selection Problem\n\
    \ */\n"
  code: "#include \"./dinic.cpp\"\n\ntemplate<class T>\nclass ProjectSelectionProblem\
    \ {\n    int n;\n    T base_score{};\n    vector<T> weight;\n    vector<tuple<int,\
    \ int, T>> penalty;\n    vector<int> selected;\n\npublic:\n    ProjectSelectionProblem()\
    \ : n(0) {}\n    explicit ProjectSelectionProblem(int n) : n(n), base_score(0),\
    \ weight(n, 0), selected(n, 0) {}\n\n    int add_vertex() {\n        weight.emplace_back(0);\n\
    \        selected.emplace_back(0);\n        return n++;\n    }\n\n    int size()\
    \ const {\n        return n;\n    }\n\n    void add_true_profit(int v, T x) {\n\
    \        weight[v] += x;\n    }\n\n    void add_false_profit(int v, T x) {\n \
    \       base_score += x;\n        weight[v] -= x;\n    }\n\n    void add_penalty(int\
    \ x, int y, T cost) {\n        penalty.emplace_back(x, y, cost);\n    }\n\n  \
    \  void add_if_then(int x, int y) {\n        add_penalty(x, y, INF<T>);\n    }\n\
    \n    void force_true(int v) {\n        add_true_profit(v, INF<T>);\n    }\n\n\
    \    void force_false(int v) {\n        add_false_profit(v, INF<T>);\n    }\n\n\
    \    T solve() {\n        int s = n, t = n + 1;\n        Dinic<T, true> mf(n +\
    \ 2);\n        T offset = base_score;\n        for (int v = 0; v < n; ++v) {\n\
    \            if (weight[v] >= 0) {\n                offset += weight[v];\n   \
    \             mf.add_edge(s, v, weight[v]);\n            } else {\n          \
    \      mf.add_edge(v, t, -weight[v]);\n            }\n        }\n        for (auto&&\
    \ [x, y, cost] : penalty) {\n            mf.add_edge(x, y, cost);\n        }\n\
    \        T cut = mf.flow(s, t);\n\n        fill(selected.begin(), selected.end(),\
    \ 0);\n        queue<int> q;\n        q.emplace(s);\n        vector<int> vis(n\
    \ + 2, 0);\n        vis[s] = 1;\n        while (!q.empty()) {\n            int\
    \ v = q.front();\n            q.pop();\n            for (auto&& e : mf.G[v]) {\n\
    \                if (e.cap <= 0 || vis[e.to]) continue;\n                vis[e.to]\
    \ = 1;\n                q.emplace(e.to);\n            }\n        }\n        for\
    \ (int v = 0; v < n; ++v) {\n            selected[v] = vis[v];\n        }\n  \
    \      return offset - cut;\n    }\n\n    const vector<int>& get_selected() const\
    \ {\n        return selected;\n    }\n};\n\n/**\n * @brief Project Selection Problem\n\
    \ */\n"
  dependsOn:
  - flow/dinic.cpp
  isVerificationFile: false
  path: flow/project_selection_problem.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yuki957_project_selection_problem.test.cpp
date: 2026-03-08
documentation_of: flow/project_selection_problem.cpp
layout: document
tags: "\u30D5\u30ED\u30FC"
title: ProjectSelectionProblem
---

## 説明
二値変数 `x_i in {0, 1}` に対する project selection problem を最大流で解く。
扱えるのは次の形の利益の和の最大化。

- `x_i = 1` のとき得る利益
- `x_i = 0` のとき得る利益
- `x_u = 1, x_v = 0` のとき払う罰金

`x_u = 1 -> x_v = 1` の依存制約もこの特別ケースとして表せる。

## できること
- `ProjectSelectionProblem<T> psp(n)`
  変数数 `n` で初期化する
- `int add_vertex()`
  補助変数を 1 つ追加して番号を返す
- `void add_true_profit(int v, T x)`
  `x_v = 1` のとき利益 `x` を足す
- `void add_false_profit(int v, T x)`
  `x_v = 0` のとき利益 `x` を足す
- `void add_penalty(int x, int y, T cost)`
  `x_x = 1, x_y = 0` のとき罰金 `cost` を足す
- `void add_if_then(int x, int y)`
  `x_x = 1 -> x_y = 1` を課す
- `void force_true(int v)`
  `x_v = 1` を強制する
- `void force_false(int v)`
  `x_v = 0` を強制する
- `T solve()`
  最大利益を返す
- `const vector<int>& get_selected() const`
  最適解で `x_i = 1` なら `1`、そうでなければ `0`

## 使い方
各利益と制約を追加してから `solve()` を呼ぶ。
行や列、区間などのボーナスを表す補助頂点が必要なら `add_vertex()` で増やす。

## 実装上の補足
正の利益を始点側、負の利益を終点側に張り、`x=1, y=0` の罰金を `x -> y` の辺に乗せる最大重み閉包として解く。
`get_selected()` は最小カット後に始点側へ残った頂点集合を返す。
