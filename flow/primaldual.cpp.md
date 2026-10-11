---
category: "\u30D5\u30ED\u30FC"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0274.test.cpp
    title: test/aoj0274.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_6_b_slope.test.cpp
    title: test/aoj_grl_6_b_slope.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_flow_boundaries.test.cpp
    title: test/yosupo_aplusb_flow_boundaries.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_primaldual_slope.test.cpp
    title: test/yosupo_aplusb_primaldual_slope.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u8CBB\u7528\u6D41(Primal-Dual)"
    links: []
  bundledCode: "#line 1 \"flow/primaldual.cpp\"\ntemplate<typename F, typename C>\n\
    struct PrimalDual {\n    struct edge {\n        int to; F cap; C cost; int rev;\n\
    \        edge() = default;\n        edge(int to, F cap, C cost, int rev):to(to),\
    \ cap(cap), cost(cost), rev(rev) {};\n    };\n    vector<vector<edge>> G;\n  \
    \  vector<C> potential, min_cost;\n    vector<int> prevv, preve;\n\n    explicit\
    \ PrimalDual(int n) : G(n), potential(n), min_cost(n), prevv(n), preve(n) {}\n\
    \n    void add_edge(int u, int v, F cap, C cost){\n        int from_id = G[u].size(),\
    \ to_id = G[v].size();\n        if(u == v) ++to_id;\n        G[u].emplace_back(v,\
    \ cap, cost, to_id);\n        G[v].emplace_back(u, 0, -cost, from_id);\n    }\n\
    \n    struct P{\n        C first; int second;\n        P(C first,int second):first(first),second(second){}\n\
    \        bool operator<(const P&a) const{return a.first<first;}\n    };\n    void\
    \ dijkstra(int s){\n\n        priority_queue<P> Q;\n        fill(min_cost.begin(),min_cost.end(),\
    \ INF<C>);\n        min_cost[s] = 0;\n        Q.emplace(0, s);\n        while(!Q.empty()){\n\
    \            P p = Q.top(); Q.pop();\n            int v = p.second;\n        \
    \    if(min_cost[v] < p.first) continue;\n            for(int i = 0; i < (int)G[v].size();\
    \ ++i){\n                edge &e=G[v][i];\n                if(e.cap==0) continue;\n\
    \                if(min_cost[v]+e.cost+potential[v]-potential[e.to] < min_cost[e.to]){\n\
    \                    min_cost[e.to] = min_cost[v]+e.cost+potential[v]-potential[e.to];\n\
    \                    prevv[e.to] = v;\n                    preve[e.to] = i;\n\
    \                    Q.emplace(min_cost[e.to], e.to);\n                }\n   \
    \         }\n        }\n    }\n\n    C flow(int s, int t, F fl, int &ok){\n  \
    \      auto result = run_flow(s, t, fl, [](F, C, C) {});\n        ok = result.first\
    \ == fl;\n        return result.second;\n    }\n\n    vector<pair<F, C>> slope(int\
    \ s, int t, F limit = INF<F>) {\n        vector<pair<F, C>> result{{0, 0}};\n\
    \        C previous = 0;\n        run_flow(s, t, limit, [&](F amount, C cost,\
    \ C marginal) {\n            if (result.size() > 1 && marginal == previous) result.pop_back();\n\
    \            result.emplace_back(amount, cost);\n            previous = marginal;\n\
    \        });\n        return result;\n    }\n\nprivate:\n    template<class Output>\n\
    \    pair<F, C> run_flow(int s, int t, F limit, Output output) {\n        F amount\
    \ = 0;\n        C res = 0;\n        fill(potential.begin(),potential.end(), 0);\n\
    \        while(amount < limit){\n            dijkstra(s);\n            if(min_cost[t]\
    \ == INF<C>) break;\n            for (int i = 0; i < (int)potential.size(); ++i)\
    \ {\n                if(min_cost[i] < INF<C>) potential[i] += min_cost[i];\n \
    \           }\n\n            F d = limit - amount;\n            for(int v = t;\
    \ v != s; v = prevv[v]){\n                d = min(d, G[prevv[v]][preve[v]].cap);\n\
    \            }\n            amount += d;\n            res += potential[t]*d;\n\
    \            for(int v = t; v != s; v = prevv[v]){\n                G[prevv[v]][preve[v]].cap\
    \ -= d;\n                G[v][G[prevv[v]][preve[v]].rev].cap += d;\n         \
    \   }\n            output(amount, res, potential[t]);\n        }\n        return\
    \ {amount, res};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528\u6D41(Primal-Dual)\n\
    \ */\n"
  code: "template<typename F, typename C>\nstruct PrimalDual {\n    struct edge {\n\
    \        int to; F cap; C cost; int rev;\n        edge() = default;\n        edge(int\
    \ to, F cap, C cost, int rev):to(to), cap(cap), cost(cost), rev(rev) {};\n   \
    \ };\n    vector<vector<edge>> G;\n    vector<C> potential, min_cost;\n    vector<int>\
    \ prevv, preve;\n\n    explicit PrimalDual(int n) : G(n), potential(n), min_cost(n),\
    \ prevv(n), preve(n) {}\n\n    void add_edge(int u, int v, F cap, C cost){\n \
    \       int from_id = G[u].size(), to_id = G[v].size();\n        if(u == v) ++to_id;\n\
    \        G[u].emplace_back(v, cap, cost, to_id);\n        G[v].emplace_back(u,\
    \ 0, -cost, from_id);\n    }\n\n    struct P{\n        C first; int second;\n\
    \        P(C first,int second):first(first),second(second){}\n        bool operator<(const\
    \ P&a) const{return a.first<first;}\n    };\n    void dijkstra(int s){\n\n   \
    \     priority_queue<P> Q;\n        fill(min_cost.begin(),min_cost.end(), INF<C>);\n\
    \        min_cost[s] = 0;\n        Q.emplace(0, s);\n        while(!Q.empty()){\n\
    \            P p = Q.top(); Q.pop();\n            int v = p.second;\n        \
    \    if(min_cost[v] < p.first) continue;\n            for(int i = 0; i < (int)G[v].size();\
    \ ++i){\n                edge &e=G[v][i];\n                if(e.cap==0) continue;\n\
    \                if(min_cost[v]+e.cost+potential[v]-potential[e.to] < min_cost[e.to]){\n\
    \                    min_cost[e.to] = min_cost[v]+e.cost+potential[v]-potential[e.to];\n\
    \                    prevv[e.to] = v;\n                    preve[e.to] = i;\n\
    \                    Q.emplace(min_cost[e.to], e.to);\n                }\n   \
    \         }\n        }\n    }\n\n    C flow(int s, int t, F fl, int &ok){\n  \
    \      auto result = run_flow(s, t, fl, [](F, C, C) {});\n        ok = result.first\
    \ == fl;\n        return result.second;\n    }\n\n    vector<pair<F, C>> slope(int\
    \ s, int t, F limit = INF<F>) {\n        vector<pair<F, C>> result{{0, 0}};\n\
    \        C previous = 0;\n        run_flow(s, t, limit, [&](F amount, C cost,\
    \ C marginal) {\n            if (result.size() > 1 && marginal == previous) result.pop_back();\n\
    \            result.emplace_back(amount, cost);\n            previous = marginal;\n\
    \        });\n        return result;\n    }\n\nprivate:\n    template<class Output>\n\
    \    pair<F, C> run_flow(int s, int t, F limit, Output output) {\n        F amount\
    \ = 0;\n        C res = 0;\n        fill(potential.begin(),potential.end(), 0);\n\
    \        while(amount < limit){\n            dijkstra(s);\n            if(min_cost[t]\
    \ == INF<C>) break;\n            for (int i = 0; i < (int)potential.size(); ++i)\
    \ {\n                if(min_cost[i] < INF<C>) potential[i] += min_cost[i];\n \
    \           }\n\n            F d = limit - amount;\n            for(int v = t;\
    \ v != s; v = prevv[v]){\n                d = min(d, G[prevv[v]][preve[v]].cap);\n\
    \            }\n            amount += d;\n            res += potential[t]*d;\n\
    \            for(int v = t; v != s; v = prevv[v]){\n                G[prevv[v]][preve[v]].cap\
    \ -= d;\n                G[v][G[prevv[v]][preve[v]].rev].cap += d;\n         \
    \   }\n            output(amount, res, potential[t]);\n        }\n        return\
    \ {amount, res};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528\u6D41(Primal-Dual)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/primaldual.cpp
  requiredBy: []
  timestamp: '2026-10-12 01:36:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_flow_boundaries.test.cpp
  - test/aoj0274.test.cpp
  - test/aoj_grl_6_b_slope.test.cpp
  - test/yosupo_aplusb_primaldual_slope.test.cpp
date: 2026-03-12
documentation_of: flow/primaldual.cpp
layout: document
tags: "\u30D5\u30ED\u30FC"
title: "\u6700\u5C0F\u8CBB\u7528\u6D41(Primal-Dual)"
---
## 説明
`s` から `t` へ指定した流量を流すときの最小費用を求める。
流量ごとの最小費用を、折れ点の列としてまとめて求めることもできる。

## できること
- `PrimalDual<F, C> mf(n)`
  頂点数 `n` のネットワークを作る
- `void add_edge(int u, int v, F cap, C cost)`
  容量 `cap`、費用 `cost` の有向辺を張る
- `C flow(int s, int t, F fl, int& ok)`
  流せた分の最小費用を返す。`ok` に `fl` を流し切れたかを代入する（流し切れれば `1`、そうでなければ `0`）
- `vector<pair<F, C>> slope(int s, int t, F limit = INF<F>)`
  流量と最小費用の折れ点を返す。先頭は `(0, 0)`、末尾は `limit` 以下で流せた最大流量とその費用。同じ傾きが続く区間はまとめる

頂点数を $N$、辺数を $M$、流量の上限（`fl` または `limit`）を $f$ として、`flow` / `slope` は最悪 $O(N+f(N+M)\log(N+M+1))$ 時間。
`slope` の返却値は $O(f+1)$ 領域。

## 使い方
辺を張ってから `flow` または `slope` を1回呼ぶ。
容量と指定する流量は非負整数、初期辺費用は非負、`s != t` とする。

```cpp
PrimalDual<long long, long long> mf(2);
mf.add_edge(0, 1, 2, 3);
mf.add_edge(0, 1, 1, 5);
auto curve = mf.slope(0, 1);
```

この例では `{(0, 0), (2, 6), (3, 11)}` を返す。
折れ点の間の整数流量に対する費用は線形補間で求められる。流量の上限が $0$ の場合や、流せる経路がない場合は `{(0, 0)}` を返す。

## 実装上の補足
各増加路は Dijkstra で求める。
整数容量では1回の増加で1以上流せるため、増加回数は流量の上限 $f$ 以下となる。
ポテンシャルを使って残余逆辺の負費用を扱う。実行後の残余グラフに対する `flow` / `slope` の再実行は扱わない。
総流量は `F`、総費用・被約費用・ポテンシャル・途中の加算と乗算は `C` に収まることが必要。Dijkstra の有限距離は `INF<C>` 未満とする。
