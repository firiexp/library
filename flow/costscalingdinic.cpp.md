---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_6_a_costscalingdinic.test.cpp
    title: test/aoj_grl_6_a_costscalingdinic.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_flow_boundaries.test.cpp
    title: test/yosupo_aplusb_flow_boundaries.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5BB9\u91CF\u30B9\u30B1\u30FC\u30EA\u30F3\u30B0Dinic(Capacity\
      \ Scaling Dinic)"
    links: []
  bundledCode: "#line 1 \"flow/costscalingdinic.cpp\"\ntemplate<class T, bool directed>\n\
    class CostScalingDinic {\n    static_assert(directed || numeric_limits<T>::is_signed,\n\
    \                  \"undirected flow requires a signed capacity type\");\n   \
    \ struct input_edge {\n        int from, index;\n        T capacity;\n    };\n\
    \    vector<input_edge> positions;\n\n    void bfs(int s, int t, T x){\n     \
    \   fill(level.begin(),level.end(), -1);\n        queue<int> Q;\n        level[s]\
    \ = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n            int v =\
    \ Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n                if(e.cap\
    \ >= x && level[e.to] < 0){\n                    level[e.to] = level[v] + 1;\n\
    \                    if(e.to == t) return;\n                    Q.emplace(e.to);\n\
    \                }\n            }\n        }\n    }\n\n    T dfs(int v, int t,\
    \ T x, T f){\n        if(v == t) return f;\n        T res = 0;\n        for(int\
    \ &i = iter[v]; i < G[v].size(); i++){\n            edge &e = G[v][i];\n     \
    \       if(e.cap >= x && level[v] < level[e.to]){\n                T d = dfs(e.to,\
    \ t, x, min<T>(f-res, e.cap));\n                if(d == 0) continue;\n       \
    \         e.cap -= d;\n                G[e.to][e.rev].cap += d;\n            \
    \    res += d;\n                if(f - res < x) break;\n            }\n      \
    \  }\n        return res;\n    }\npublic:\n    struct Edge {\n        int from,\
    \ to;\n        T capacity, flow;\n    };\n\n    struct edge {\n        int to{};\
    \ T cap; int rev{};\n        edge() = default;\n        edge(int to, T cap, int\
    \ rev) : to(to), cap(cap), rev(rev) {}\n    };\n\n    vector<vector<edge>> G;\n\
    \    vector<int> level, iter;\n    CostScalingDinic() = default;\n    explicit\
    \ CostScalingDinic(int n) : G(n), level(n), iter(n) {}\n\n    int add_edge(int\
    \ from, int to, T cap){\n        int from_id = G[from].size(), to_id = G[to].size();\n\
    \        int id = positions.size();\n        positions.push_back({from, from_id,\
    \ cap});\n        if(from == to) ++to_id;\n        G[from].emplace_back(to, cap,\
    \ to_id);\n        G[to].emplace_back(from, directed ? 0 : cap, from_id);\n  \
    \      return id;\n    }\n\n    Edge get_edge(int id) const {\n        const auto\
    \ &p = positions[id];\n        const auto &e = G[p.from][p.index];\n        return\
    \ {p.from, e.to, p.capacity, T(p.capacity - e.cap)};\n    }\n\n    vector<Edge>\
    \ edges() const {\n        vector<Edge> result;\n        result.reserve(positions.size());\n\
    \        for(int id = 0; id < int(positions.size()); ++id)\n            result.push_back(get_edge(id));\n\
    \        return result;\n    }\n\n    vector<char> min_cut(int s) const {\n  \
    \      vector<char> reachable(G.size(), false);\n        queue<int> q;\n     \
    \   reachable[s] = true;\n        q.emplace(s);\n        while(!q.empty()) {\n\
    \            int v = q.front(); q.pop();\n            for(const auto &e : G[v])\
    \ {\n                if(e.cap <= 0 || reachable[e.to]) continue;\n           \
    \     reachable[e.to] = true;\n                q.emplace(e.to);\n            }\n\
    \        }\n        return reachable;\n    }\n\n    T flow(int s, int t, T lim\
    \ = INF<T>){\n        if(lim == 0) return 0;\n        T upper = 0;\n        for(const\
    \ auto &adj : G)\n            for(const auto &e : adj) upper = max(upper, e.cap);\n\
    \        upper = min(upper, lim);\n        if(upper == 0) return 0;\n        T\
    \ ret = 0;\n        T cap = 1; while(cap <= upper / 2) cap <<= 1;\n        while(cap\
    \ && ret < lim) {\n            bfs(s, t, cap);\n            if(level[t] < 0){\n\
    \                cap >>= 1;\n                continue;\n            }\n      \
    \      fill(iter.begin(),iter.end(), 0);\n            ret += dfs(s, t, cap, lim\
    \ - ret);\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief \u5BB9\u91CF\
    \u30B9\u30B1\u30FC\u30EA\u30F3\u30B0Dinic(Capacity Scaling Dinic)\n */\n"
  code: "template<class T, bool directed>\nclass CostScalingDinic {\n    static_assert(directed\
    \ || numeric_limits<T>::is_signed,\n                  \"undirected flow requires\
    \ a signed capacity type\");\n    struct input_edge {\n        int from, index;\n\
    \        T capacity;\n    };\n    vector<input_edge> positions;\n\n    void bfs(int\
    \ s, int t, T x){\n        fill(level.begin(),level.end(), -1);\n        queue<int>\
    \ Q;\n        level[s] = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n\
    \            int v = Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n\
    \                if(e.cap >= x && level[e.to] < 0){\n                    level[e.to]\
    \ = level[v] + 1;\n                    if(e.to == t) return;\n               \
    \     Q.emplace(e.to);\n                }\n            }\n        }\n    }\n\n\
    \    T dfs(int v, int t, T x, T f){\n        if(v == t) return f;\n        T res\
    \ = 0;\n        for(int &i = iter[v]; i < G[v].size(); i++){\n            edge\
    \ &e = G[v][i];\n            if(e.cap >= x && level[v] < level[e.to]){\n     \
    \           T d = dfs(e.to, t, x, min<T>(f-res, e.cap));\n                if(d\
    \ == 0) continue;\n                e.cap -= d;\n                G[e.to][e.rev].cap\
    \ += d;\n                res += d;\n                if(f - res < x) break;\n \
    \           }\n        }\n        return res;\n    }\npublic:\n    struct Edge\
    \ {\n        int from, to;\n        T capacity, flow;\n    };\n\n    struct edge\
    \ {\n        int to{}; T cap; int rev{};\n        edge() = default;\n        edge(int\
    \ to, T cap, int rev) : to(to), cap(cap), rev(rev) {}\n    };\n\n    vector<vector<edge>>\
    \ G;\n    vector<int> level, iter;\n    CostScalingDinic() = default;\n    explicit\
    \ CostScalingDinic(int n) : G(n), level(n), iter(n) {}\n\n    int add_edge(int\
    \ from, int to, T cap){\n        int from_id = G[from].size(), to_id = G[to].size();\n\
    \        int id = positions.size();\n        positions.push_back({from, from_id,\
    \ cap});\n        if(from == to) ++to_id;\n        G[from].emplace_back(to, cap,\
    \ to_id);\n        G[to].emplace_back(from, directed ? 0 : cap, from_id);\n  \
    \      return id;\n    }\n\n    Edge get_edge(int id) const {\n        const auto\
    \ &p = positions[id];\n        const auto &e = G[p.from][p.index];\n        return\
    \ {p.from, e.to, p.capacity, T(p.capacity - e.cap)};\n    }\n\n    vector<Edge>\
    \ edges() const {\n        vector<Edge> result;\n        result.reserve(positions.size());\n\
    \        for(int id = 0; id < int(positions.size()); ++id)\n            result.push_back(get_edge(id));\n\
    \        return result;\n    }\n\n    vector<char> min_cut(int s) const {\n  \
    \      vector<char> reachable(G.size(), false);\n        queue<int> q;\n     \
    \   reachable[s] = true;\n        q.emplace(s);\n        while(!q.empty()) {\n\
    \            int v = q.front(); q.pop();\n            for(const auto &e : G[v])\
    \ {\n                if(e.cap <= 0 || reachable[e.to]) continue;\n           \
    \     reachable[e.to] = true;\n                q.emplace(e.to);\n            }\n\
    \        }\n        return reachable;\n    }\n\n    T flow(int s, int t, T lim\
    \ = INF<T>){\n        if(lim == 0) return 0;\n        T upper = 0;\n        for(const\
    \ auto &adj : G)\n            for(const auto &e : adj) upper = max(upper, e.cap);\n\
    \        upper = min(upper, lim);\n        if(upper == 0) return 0;\n        T\
    \ ret = 0;\n        T cap = 1; while(cap <= upper / 2) cap <<= 1;\n        while(cap\
    \ && ret < lim) {\n            bfs(s, t, cap);\n            if(level[t] < 0){\n\
    \                cap >>= 1;\n                continue;\n            }\n      \
    \      fill(iter.begin(),iter.end(), 0);\n            ret += dfs(s, t, cap, lim\
    \ - ret);\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief \u5BB9\u91CF\
    \u30B9\u30B1\u30FC\u30EA\u30F3\u30B0Dinic(Capacity Scaling Dinic)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/costscalingdinic.cpp
  requiredBy: []
  timestamp: '2026-10-18 00:20:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_flow_boundaries.test.cpp
  - test/aoj_grl_6_a_costscalingdinic.test.cpp
documentation_of: flow/costscalingdinic.cpp
layout: document
title: "\u5BB9\u91CF\u30B9\u30B1\u30FC\u30EA\u30F3\u30B0Dinic(Capacity Scaling Dinic)"
---
## 説明
capacity scaling を入れた Dinic 法による最大流である。
大きい容量から順に流すことで、容量が大きいケースで定数倍を改善する。
辺 ID と登録時の容量の保持を含め、領域は $O(V+E)$。

## できること
- `CostScalingDinic<T, directed> mf(n)`
  頂点数 `n` のフローグラフを作る
- `int add_edge(int from, int to, T cap)`
  容量 `cap` の辺を追加し、0からの追加順の ID を返す。`directed=false` なら無向辺。償却 $O(1)$
- `T flow(int s, int t, T lim = INF<T>)`
  現在の残余グラフで `s` から `t` へ最大 `lim` だけ流し、今回追加した流量を返す
- `Edge get_edge(int id) const`
  `from, to, capacity, flow` を返す。`capacity` は登録時の容量、`flow` は登録方向への正味流量。$O(1)$
- `vector<Edge> edges() const`
  追加順で全辺の情報を返す。逆辺は含めない。時間・返却領域 $O(E)$
- `vector<char> min_cut(int s) const`
  現在の残余グラフで `s` から到達できる頂点を `true` で返す。時間 $O(V+E)$、追加領域 $O(V)$

## 使い方
容量型 `T` と有向・無向の別をテンプレート引数で与える。

```cpp
CostScalingDinic<long long, true> mf(n);
int id = mf.add_edge(u, v, c);
long long ans = mf.flow(s, t);
auto e = mf.get_edge(id);
auto source_side = mf.min_cut(s);
```

## 実装上の補足
容量は非負整数で、流量と計算中の残余容量は `T` に収まる必要がある。
無向版の `T` は符号付き整数型を使う。流量は `-capacity` から `capacity` の範囲を取り、残余容量は元容量の2倍になる場合がある。
辺情報の取得は、対象辺の登録容量と残余容量の対応が保たれていることを前提とする。
`min_cut(s)` は終点が到達不能になったとき最小カットの始点側を表す。流量上限による途中停止では、最小カットとは限らない。
`s != t`、`lim >= 0` とする。再実行では前回の残余グラフを引き継ぐ。
`flow` の開始時に全残余辺を $O(V+E)$ 時間で走査し、最大残余容量と `lim` の小さい方以下の最大2冪から scaling を始める。
正の残余容量がない場合は `0` を返す。容量が小さい入力では、使える辺がない高位の幅での BFS を省ける。
BFS は終点の距離が決まった時点で終了する。同じ最短距離の増加路に必要な層は保持する。
