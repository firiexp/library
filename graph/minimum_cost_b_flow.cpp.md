---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_min_cost_b_flow.test.cpp
    title: test/yosupo_min_cost_b_flow.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u8CBB\u7528b-flow(Min-Cost b-Flow)"
    links: []
  bundledCode: "#line 1 \"graph/minimum_cost_b_flow.cpp\"\ntemplate<class Flow, class\
    \ Cost>\nstruct MinimumCostBFlow {\n    using Sum = __int128_t;\n    struct Edge\
    \ {\n        int from, to, rev;\n        Flow flow, cap;\n        Cost cost;\n\
    \n        Flow residual_cap() const {\n            return cap - flow;\n      \
    \  }\n    };\n\n    struct EdgeRef {\n        int from, idx;\n    };\n\n    int\
    \ n;\n    vector<vector<Edge>> g;\n    vector<Flow> b;\n    vector<EdgeRef> edges;\n\
    \    vector<Cost> potential;\n\n    explicit MinimumCostBFlow(int n) : n(n), g(n),\
    \ b(n, 0), potential(n, 0) {}\n\n    void add_supply(int v, Flow x) {\n      \
    \  b[v] += x;\n    }\n\n    void add_demand(int v, Flow x) {\n        b[v] -=\
    \ x;\n    }\n\n    int add_edge(int from, int to, Flow lower, Flow upper, Cost\
    \ cost) {\n        assert(lower <= upper);\n        int idx = (int)g[from].size();\n\
    \        int rev = from == to ? idx + 1 : (int)g[to].size();\n        g[from].push_back({from,\
    \ to, rev, 0, upper, cost});\n        g[to].push_back({to, from, idx, 0, -lower,\
    \ -cost});\n        edges.push_back({from, idx});\n        return (int)edges.size()\
    \ - 1;\n    }\n\n    Edge& rev_edge(const Edge& e) {\n        return g[e.to][e.rev];\n\
    \    }\n\n    const Edge& get_edge(int i) const {\n        return g[edges[i].from][edges[i].idx];\n\
    \    }\n\n    vector<Flow> get_flows() const {\n        vector<Flow> ret(edges.size());\n\
    \        for (int i = 0; i < (int)edges.size(); ++i) ret[i] = get_edge(i).flow;\n\
    \        return ret;\n    }\n\n    vector<Cost> get_potential() const {\n    \
    \    vector<Cost> ret(n, 0);\n        for (int iter = 0; iter < n; ++iter) {\n\
    \            bool updated = false;\n            for (int v = 0; v < n; ++v) {\n\
    \                for (auto&& e : g[v]) {\n                    if(e.residual_cap()\
    \ <= 0) continue;\n                    if(ret[e.to] > ret[e.from] + e.cost) {\n\
    \                        ret[e.to] = ret[e.from] + e.cost;\n                 \
    \       updated = true;\n                    }\n                }\n          \
    \  }\n            if(!updated) break;\n        }\n        return ret;\n    }\n\
    \n    pair<bool, Sum> solve() {\n        const Cost unreachable = numeric_limits<Cost>::max();\n\
    \        vector<Cost> dist(n);\n        vector<Edge*> parent(n);\n        vector<int>\
    \ excess, deficit;\n        priority_queue<pair<Cost, int>, vector<pair<Cost,\
    \ int>>, greater<pair<Cost, int>>> pq;\n        Cost farthest = 0;\n\n       \
    \ auto push = [&](Edge& e, Flow amount) {\n            e.flow += amount;\n   \
    \         rev_edge(e).flow -= amount;\n        };\n        auto residual_cost\
    \ = [&](const Edge& e) {\n            return e.cost + potential[e.from] - potential[e.to];\n\
    \        };\n\n        auto saturate_negative = [&](Flow delta) {\n          \
    \  excess.clear();\n            deficit.clear();\n            for (auto&& es :\
    \ g) {\n                for (auto&& e : es) {\n                    Flow rcap =\
    \ e.residual_cap();\n                    if(rcap < delta) continue;\n        \
    \            if(residual_cost(e) < 0) {\n                        push(e, rcap);\n\
    \                        b[e.from] -= rcap;\n                        b[e.to] +=\
    \ rcap;\n                    }\n                }\n            }\n           \
    \ for (int v = 0; v < n; ++v) {\n                if(b[v] > 0) excess.push_back(v);\n\
    \                if(b[v] < 0) deficit.push_back(v);\n            }\n        };\n\
    \n        auto dual = [&](Flow delta) {\n            fill(dist.begin(), dist.end(),\
    \ unreachable);\n            fill(parent.begin(), parent.end(), nullptr);\n\n\
    \            excess.erase(remove_if(excess.begin(), excess.end(), [&](int v) {\n\
    \                return b[v] < delta;\n            }), excess.end());\n      \
    \      deficit.erase(remove_if(deficit.begin(), deficit.end(), [&](int v) {\n\
    \                return b[v] > -delta;\n            }), deficit.end());\n\n  \
    \          while(!pq.empty()) pq.pop();\n            for (int v : excess) {\n\
    \                dist[v] = 0;\n                pq.emplace(0, v);\n           \
    \ }\n\n            farthest = 0;\n            int reached = 0;\n            while(!pq.empty())\
    \ {\n                auto [d, v] = pq.top();\n                pq.pop();\n    \
    \            if(dist[v] != d) continue;\n                farthest = d;\n     \
    \           if(b[v] <= -delta) ++reached;\n                if(reached >= (int)deficit.size())\
    \ break;\n                for (auto&& e : g[v]) {\n                    if(e.residual_cap()\
    \ < delta) continue;\n                    Cost nd = d + residual_cost(e);\n  \
    \                  if(nd >= dist[e.to]) continue;\n                    dist[e.to]\
    \ = nd;\n                    parent[e.to] = &e;\n                    pq.emplace(nd,\
    \ e.to);\n                }\n            }\n\n            for (int v = 0; v <\
    \ n; ++v) {\n                potential[v] += min(dist[v], farthest);\n       \
    \     }\n            return reached > 0;\n        };\n\n        auto primal =\
    \ [&](Flow delta) {\n            for (int t : deficit) {\n                if(dist[t]\
    \ > farthest) continue;\n                Flow f = -b[t];\n                int\
    \ v = t;\n                while(parent[v] != nullptr && f >= delta) {\n      \
    \              f = min(f, parent[v]->residual_cap());\n                    v =\
    \ parent[v]->from;\n                }\n                f = min(f, b[v]);\n   \
    \             if(f < delta) continue;\n                v = t;\n              \
    \  while(parent[v] != nullptr) {\n                    Edge& e = *parent[v];\n\
    \                    push(e, f);\n                    int u = e.from;\n      \
    \              parent[v] = nullptr;\n                    v = u;\n            \
    \    }\n                b[t] += f;\n                b[v] -= f;\n            }\n\
    \        };\n\n        for (auto&& es : g) {\n            for (auto&& e : es)\
    \ {\n                Flow rcap = e.residual_cap();\n                if(rcap <\
    \ 0) {\n                    push(e, rcap);\n                    b[e.from] -= rcap;\n\
    \                    b[e.to] += rcap;\n                }\n            }\n    \
    \    }\n\n        Flow max_cap = 1;\n        for (auto&& es : g) {\n         \
    \   for (auto&& e : es) {\n                max_cap = max(max_cap, e.residual_cap());\n\
    \            }\n        }\n        Flow delta = 1;\n        while(delta <= max_cap\
    \ / 2) delta <<= 1;\n        for (delta >>= 1; delta > 0; delta >>= 1) {\n   \
    \         saturate_negative(delta);\n            while(dual(delta)) primal(delta);\n\
    \        }\n\n        Sum value = 0;\n        bool ok = true;\n        for (int\
    \ v = 0; v < n; ++v) {\n            if(b[v] != 0) ok = false;\n        }\n   \
    \     for (int i = 0; i < (int)edges.size(); ++i) {\n            auto&& e = get_edge(i);\n\
    \            value += (Sum)e.flow * (Sum)e.cost;\n        }\n        return {ok,\
    \ value};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528b-flow(Min-Cost\
    \ b-Flow)\n */\n"
  code: "template<class Flow, class Cost>\nstruct MinimumCostBFlow {\n    using Sum\
    \ = __int128_t;\n    struct Edge {\n        int from, to, rev;\n        Flow flow,\
    \ cap;\n        Cost cost;\n\n        Flow residual_cap() const {\n          \
    \  return cap - flow;\n        }\n    };\n\n    struct EdgeRef {\n        int\
    \ from, idx;\n    };\n\n    int n;\n    vector<vector<Edge>> g;\n    vector<Flow>\
    \ b;\n    vector<EdgeRef> edges;\n    vector<Cost> potential;\n\n    explicit\
    \ MinimumCostBFlow(int n) : n(n), g(n), b(n, 0), potential(n, 0) {}\n\n    void\
    \ add_supply(int v, Flow x) {\n        b[v] += x;\n    }\n\n    void add_demand(int\
    \ v, Flow x) {\n        b[v] -= x;\n    }\n\n    int add_edge(int from, int to,\
    \ Flow lower, Flow upper, Cost cost) {\n        assert(lower <= upper);\n    \
    \    int idx = (int)g[from].size();\n        int rev = from == to ? idx + 1 :\
    \ (int)g[to].size();\n        g[from].push_back({from, to, rev, 0, upper, cost});\n\
    \        g[to].push_back({to, from, idx, 0, -lower, -cost});\n        edges.push_back({from,\
    \ idx});\n        return (int)edges.size() - 1;\n    }\n\n    Edge& rev_edge(const\
    \ Edge& e) {\n        return g[e.to][e.rev];\n    }\n\n    const Edge& get_edge(int\
    \ i) const {\n        return g[edges[i].from][edges[i].idx];\n    }\n\n    vector<Flow>\
    \ get_flows() const {\n        vector<Flow> ret(edges.size());\n        for (int\
    \ i = 0; i < (int)edges.size(); ++i) ret[i] = get_edge(i).flow;\n        return\
    \ ret;\n    }\n\n    vector<Cost> get_potential() const {\n        vector<Cost>\
    \ ret(n, 0);\n        for (int iter = 0; iter < n; ++iter) {\n            bool\
    \ updated = false;\n            for (int v = 0; v < n; ++v) {\n              \
    \  for (auto&& e : g[v]) {\n                    if(e.residual_cap() <= 0) continue;\n\
    \                    if(ret[e.to] > ret[e.from] + e.cost) {\n                \
    \        ret[e.to] = ret[e.from] + e.cost;\n                        updated =\
    \ true;\n                    }\n                }\n            }\n           \
    \ if(!updated) break;\n        }\n        return ret;\n    }\n\n    pair<bool,\
    \ Sum> solve() {\n        const Cost unreachable = numeric_limits<Cost>::max();\n\
    \        vector<Cost> dist(n);\n        vector<Edge*> parent(n);\n        vector<int>\
    \ excess, deficit;\n        priority_queue<pair<Cost, int>, vector<pair<Cost,\
    \ int>>, greater<pair<Cost, int>>> pq;\n        Cost farthest = 0;\n\n       \
    \ auto push = [&](Edge& e, Flow amount) {\n            e.flow += amount;\n   \
    \         rev_edge(e).flow -= amount;\n        };\n        auto residual_cost\
    \ = [&](const Edge& e) {\n            return e.cost + potential[e.from] - potential[e.to];\n\
    \        };\n\n        auto saturate_negative = [&](Flow delta) {\n          \
    \  excess.clear();\n            deficit.clear();\n            for (auto&& es :\
    \ g) {\n                for (auto&& e : es) {\n                    Flow rcap =\
    \ e.residual_cap();\n                    if(rcap < delta) continue;\n        \
    \            if(residual_cost(e) < 0) {\n                        push(e, rcap);\n\
    \                        b[e.from] -= rcap;\n                        b[e.to] +=\
    \ rcap;\n                    }\n                }\n            }\n           \
    \ for (int v = 0; v < n; ++v) {\n                if(b[v] > 0) excess.push_back(v);\n\
    \                if(b[v] < 0) deficit.push_back(v);\n            }\n        };\n\
    \n        auto dual = [&](Flow delta) {\n            fill(dist.begin(), dist.end(),\
    \ unreachable);\n            fill(parent.begin(), parent.end(), nullptr);\n\n\
    \            excess.erase(remove_if(excess.begin(), excess.end(), [&](int v) {\n\
    \                return b[v] < delta;\n            }), excess.end());\n      \
    \      deficit.erase(remove_if(deficit.begin(), deficit.end(), [&](int v) {\n\
    \                return b[v] > -delta;\n            }), deficit.end());\n\n  \
    \          while(!pq.empty()) pq.pop();\n            for (int v : excess) {\n\
    \                dist[v] = 0;\n                pq.emplace(0, v);\n           \
    \ }\n\n            farthest = 0;\n            int reached = 0;\n            while(!pq.empty())\
    \ {\n                auto [d, v] = pq.top();\n                pq.pop();\n    \
    \            if(dist[v] != d) continue;\n                farthest = d;\n     \
    \           if(b[v] <= -delta) ++reached;\n                if(reached >= (int)deficit.size())\
    \ break;\n                for (auto&& e : g[v]) {\n                    if(e.residual_cap()\
    \ < delta) continue;\n                    Cost nd = d + residual_cost(e);\n  \
    \                  if(nd >= dist[e.to]) continue;\n                    dist[e.to]\
    \ = nd;\n                    parent[e.to] = &e;\n                    pq.emplace(nd,\
    \ e.to);\n                }\n            }\n\n            for (int v = 0; v <\
    \ n; ++v) {\n                potential[v] += min(dist[v], farthest);\n       \
    \     }\n            return reached > 0;\n        };\n\n        auto primal =\
    \ [&](Flow delta) {\n            for (int t : deficit) {\n                if(dist[t]\
    \ > farthest) continue;\n                Flow f = -b[t];\n                int\
    \ v = t;\n                while(parent[v] != nullptr && f >= delta) {\n      \
    \              f = min(f, parent[v]->residual_cap());\n                    v =\
    \ parent[v]->from;\n                }\n                f = min(f, b[v]);\n   \
    \             if(f < delta) continue;\n                v = t;\n              \
    \  while(parent[v] != nullptr) {\n                    Edge& e = *parent[v];\n\
    \                    push(e, f);\n                    int u = e.from;\n      \
    \              parent[v] = nullptr;\n                    v = u;\n            \
    \    }\n                b[t] += f;\n                b[v] -= f;\n            }\n\
    \        };\n\n        for (auto&& es : g) {\n            for (auto&& e : es)\
    \ {\n                Flow rcap = e.residual_cap();\n                if(rcap <\
    \ 0) {\n                    push(e, rcap);\n                    b[e.from] -= rcap;\n\
    \                    b[e.to] += rcap;\n                }\n            }\n    \
    \    }\n\n        Flow max_cap = 1;\n        for (auto&& es : g) {\n         \
    \   for (auto&& e : es) {\n                max_cap = max(max_cap, e.residual_cap());\n\
    \            }\n        }\n        Flow delta = 1;\n        while(delta <= max_cap\
    \ / 2) delta <<= 1;\n        for (delta >>= 1; delta > 0; delta >>= 1) {\n   \
    \         saturate_negative(delta);\n            while(dual(delta)) primal(delta);\n\
    \        }\n\n        Sum value = 0;\n        bool ok = true;\n        for (int\
    \ v = 0; v < n; ++v) {\n            if(b[v] != 0) ok = false;\n        }\n   \
    \     for (int i = 0; i < (int)edges.size(); ++i) {\n            auto&& e = get_edge(i);\n\
    \            value += (Sum)e.flow * (Sum)e.cost;\n        }\n        return {ok,\
    \ value};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528b-flow(Min-Cost\
    \ b-Flow)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/minimum_cost_b_flow.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_min_cost_b_flow.test.cpp
date: 2026-03-08
documentation_of: graph/minimum_cost_b_flow.cpp
layout: document
tags: "\u6700\u5C0F\u8CBB\u7528\u6D41"
title: Minimum Cost B-Flow
---

## 説明
各頂点に需要 `b[v]`、各有向辺に下限 `lower`・上限 `upper`・単位費用 `cost` を持つ最小費用 `b-flow` を解く。
頂点 `v` では

- `sum(outgoing flow) - sum(incoming flow) = b[v]`

を満たす流れを探し、その中で総費用を最小化する。

## できること
- `MinimumCostBFlow<Flow, Cost> g(n)`
  頂点数 `n` のインスタンスを作る
- `void add_supply(int v, Flow x)`
  頂点 `v` に供給 `x` を足す
- `void add_demand(int v, Flow x)`
  頂点 `v` に需要 `x` を足す
- `int add_edge(int from, int to, Flow lower, Flow upper, Cost cost)`
  下限・上限・費用付き有向辺を追加する
- `pair<bool, __int128_t> solve()`
  実行可能なら `{true, 最小費用}`、不可能なら `{false, 計算された費用}` を返す
- `vector<Flow> get_flows()`
  追加順の各辺の流量を返す
- `vector<Cost> get_potential()`
  最適解に対応するポテンシャルの一例を返す

## 使い方
1. `MinimumCostBFlow<long long, long long> g(n);` を作る
2. 各頂点の収支を `add_supply` / `add_demand` で入れる
3. 各辺を `add_edge(from, to, lower, upper, cost)` で追加する
4. `auto [ok, cost] = g.solve();` を呼ぶ
5. `ok == true` なら `get_flows()` で各辺流量を取得する

## 実装上の補足
cost scaling による最小費用 circulaton 法をベースにしている。
負費用辺と下限制約をそのまま扱える。
