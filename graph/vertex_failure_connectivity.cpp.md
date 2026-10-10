---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/biconnected_components.cpp
    title: "\u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)"
  - icon: ':heavy_check_mark:'
    path: graph/block_cut_tree.cpp
    title: "\u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut Tree)"
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: "HL\u5206\u89E3(HL Decomposition)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_vertex_failure_connectivity.test.cpp
    title: test/yosupo_aplusb_vertex_failure_connectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9802\u70B9\u9664\u53BB\u5F8C\u306E\u9023\u7D50\u5224\u5B9A"
    links: []
  bundledCode: "#line 1 \"graph/block_cut_tree.cpp\"\nusing namespace std;\n\n#line\
    \ 1 \"graph/biconnected_components.cpp\"\n\n\n\nclass BiconnectedComponents {\n\
    \    struct CSR {\n        vector<int> start, elist;\n\n        CSR() = default;\n\
    \n        CSR(int n, const vector<pair<int, int>> &edges) : start(n + 1), elist(edges.size()\
    \ * 2) {\n            for (auto &&[u, v] : edges) {\n                ++start[u\
    \ + 1];\n                ++start[v + 1];\n            }\n            for (int\
    \ i = 0; i < n; ++i) start[i + 1] += start[i];\n            auto counter = start;\n\
    \            for (int id = 0; id < (int)edges.size(); ++id) {\n              \
    \  auto &&[u, v] = edges[id];\n                elist[counter[u]++] = id;\n   \
    \             elist[counter[v]++] = id;\n            }\n        }\n    };\n\n\
    \    int n = 0;\n    vector<int> st;\n\n    struct Frame {\n        int v, parent_edge,\
    \ next;\n    };\n\n    int other(int id, int v) const {\n        return edges[id].first\
    \ ^ edges[id].second ^ v;\n    }\n\n    void dfs(int i, const CSR &G, int &pos,\
    \ vector<Frame> &stack){\n        ord[i] = low[i] = pos++;\n        stack.push_back({i,\
    \ -1, G.start[i]});\n        while (!stack.empty()) {\n            auto &frame\
    \ = stack.back();\n            int v = frame.v;\n            if (frame.next ==\
    \ G.start[v + 1]) {\n                int pe = frame.parent_edge, p = par[v];\n\
    \                stack.pop_back();\n                if (p == -1) continue;\n \
    \               low[p] = min(low[p], low[v]);\n                if (ord[p] <= low[v])\
    \ {\n                    bcc_edges.emplace_back();\n                    while\
    \ (true) {\n                        int k = st.back();\n                     \
    \   st.pop_back();\n                        bcc_edges.back().emplace_back(min(edges[k].first,\
    \ edges[k].second), max(edges[k].first, edges[k].second));\n                 \
    \       if (k == pe) break;\n                    }\n                }\n      \
    \          continue;\n            }\n            int id = G.elist[frame.next++];\n\
    \            if (id == frame.parent_edge) continue;\n            int j = other(id,\
    \ v);\n            if(ord[j] < ord[v]) st.emplace_back(id);\n            if(~ord[j]){\n\
    \                low[v] = min(low[v], ord[j]);\n                continue;\n  \
    \          }\n            par[j] = v;\n            ord[j] = low[j] = pos++;\n\
    \            stack.push_back({j, id, G.start[j]});\n        }\n    }\npublic:\n\
    \    vector<int> ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> bcc_edges;\n    vector<vector<int>> bcc_vertices;\n    explicit BiconnectedComponents(int\
    \ n): n(n), ord(n, -1), low(n), par(n, -1){}\n\n    void add_edge(int u, int v){\n\
    \        if(u == v) return;\n        edges.emplace_back(u, v);\n    }\n\n    int\
    \ build(){\n        CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(),\
    \ ord.end(), -1);\n        fill(par.begin(), par.end(), -1);\n        bcc_edges.clear();\n\
    \        bcc_vertices.clear();\n        st.clear();\n        vector<Frame> stack;\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, G, pos,\
    \ stack);\n        }\n        vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(std::move(now));\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G.start[i] ==\
    \ G.start[i + 1]){\n                bcc_edges.emplace_back();\n              \
    \  bcc_vertices.push_back({i});\n            }\n        }\n        return bcc_vertices.size();\n\
    \    }\n};\n\n/**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3\
    (Biconnected Components)\n */\n\n\n#line 4 \"graph/block_cut_tree.cpp\"\n\nstruct\
    \ BlockCutTree {\n    int n, block_count;\n    BiconnectedComponents bcc;\n  \
    \  vector<vector<int>> tree, nodes;\n    vector<int> id, rev;\n    vector<char>\
    \ is_articulation;\n\n    explicit BlockCutTree(int n) : n(n), block_count(0),\
    \ bcc(n), id(n, -1), is_articulation(n, 0) {}\n\n    void add_edge(int u, int\
    \ v) {\n        bcc.add_edge(u, v);\n    }\n\n    int build() {\n        block_count\
    \ = bcc.build();\n        vector<int> cnt(n);\n        for (auto &&vs : bcc.bcc_vertices)\
    \ {\n            for (auto &&v : vs) ++cnt[v];\n        }\n\n        int m = block_count;\n\
    \        id.assign(n, -1);\n        is_articulation.assign(n, 0);\n        for\
    \ (int v = 0; v < n; ++v) {\n            if (cnt[v] > 1) {\n                is_articulation[v]\
    \ = 1;\n                id[v] = m++;\n            }\n        }\n\n        tree.assign(m,\
    \ {});\n        nodes.assign(m, {});\n        rev.assign(m, -1);\n        for\
    \ (int i = 0; i < block_count; ++i) {\n            nodes[i] = bcc.bcc_vertices[i];\n\
    \            for (auto &&v : bcc.bcc_vertices[i]) {\n                if (cnt[v]\
    \ > 1) {\n                    tree[i].push_back(id[v]);\n                    tree[id[v]].push_back(i);\n\
    \                } else {\n                    id[v] = i;\n                }\n\
    \            }\n        }\n        for (int v = 0; v < n; ++v) {\n           \
    \ if (is_articulation[v]) {\n                nodes[id[v]].push_back(v);\n    \
    \            rev[id[v]] = v;\n            }\n        }\n        return m;\n  \
    \  }\n};\n\n/**\n * @brief \u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut\
    \ Tree)\n */\n#line 1 \"tree/hld.cpp\"\n\n\n\nclass HeavyLightDecomposition {\n\
    \    void dfs_sz(int root, vector<int> &order){\n        order.clear();\n    \
    \    order.push_back(root);\n        for (int i = 0; i < (int)order.size(); ++i)\
    \ {\n            int v = order[i];\n            for (int u : G[v]) {\n       \
    \         if (u == par[v]) continue;\n                par[u] = v;\n          \
    \      dep[u] = dep[v] + 1;\n                order.push_back(u);\n           \
    \ }\n        }\n        for (int i = (int)order.size() - 1; i >= 0; --i) {\n \
    \           int v = order[i], heavy = -1;\n            for (int u : G[v]) {\n\
    \                if (u == par[v]) continue;\n                sub_size[v] += sub_size[u];\n\
    \                if (heavy == -1 || sub_size[u] > sub_size[heavy]) heavy = u;\n\
    \            }\n            if (heavy != -1 && G[v][0] != heavy) {\n         \
    \       for (auto &u : G[v]) {\n                    if (u == heavy) {\n      \
    \                  swap(u, G[v][0]);\n                        break;\n       \
    \             }\n                }\n            }\n        }\n    }\n    void\
    \ dfs_hld(int root, int c, int &pos, vector<int> &stack){\n        stack.clear();\n\
    \        stack.push_back(root);\n        while (!stack.empty()) {\n          \
    \  int v = stack.back();\n            stack.pop_back();\n            id[v] = pos++;\n\
    \            id_inv[id[v]] = v;\n            tree_id[v] = c;\n            for\
    \ (int i = (int)G[v].size() - 1; i >= 0; --i) {\n                int u = G[v][i];\n\
    \                if (u == par[v]) continue;\n                head[u] = (u == G[v][0]\
    \ ? head[v] : u);\n                stack.push_back(u);\n            }\n      \
    \  }\n    }\npublic:\n    int n;\n    vector<vector<int>> G;\n    vector<int>\
    \ par, dep, sub_size, id, id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int\
    \ n) : n(n), G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n),\
    \ head(n){}\n    explicit HeavyLightDecomposition(vector<vector<int>> &G) : n(G.size()),\
    \ G(G), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n)\
    \ {}\n\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n    \
    \    G[v].emplace_back(u);\n    }\n\n    void build(vector<int> roots = {0}){\n\
    \        if (n == 0) return;\n        fill(par.begin(), par.end(), -1);\n    \
    \    fill(dep.begin(), dep.end(), 0);\n        fill(sub_size.begin(), sub_size.end(),\
    \ 1);\n        int c = 0, pos = 0;\n        vector<int> order;\n        for (auto\
    \ &&i : roots) {\n            dfs_sz(i, order);\n            head[i] = i;\n  \
    \          dfs_hld(i, c++, pos, order);\n        }\n    }\n\n    int lca(int u,\
    \ int v){\n        while(true){\n            if(id[u] > id[v]) swap(u, v);\n \
    \           if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int parent(int v) const {\n        return par[v];\n \
    \   }\n\n    int ancestor(int v, int k) {\n        if(dep[v] < k) return -1;\n\
    \        while(true) {\n            int u = head[v];\n            if(id[v] - k\
    \ >= id[u]) return id_inv[id[v] - k];\n            k -= id[v]-id[u]+1;\n     \
    \       v = par[u];\n        }\n    }\n\n    int distance(int u, int v){ return\
    \ dep[u] + dep[v] - 2*dep[lca(u, v)]; }\n\n    pair<int, int> subtree(int v, bool\
    \ edge = false) const {\n        return {id[v] + edge, id[v] + sub_size[v]};\n\
    \    }\n\n    template<typename F>\n    void add(int u, int v, const F &f, bool\
    \ edge){\n        while (head[u] != head[v]){\n            if(id[u] > id[v]) swap(u,\
    \ v);\n            f(id[head[v]], id[v]+1);\n            v = par[head[v]];\n \
    \       }\n        if(id[u] > id[v]) swap(u, v);\n        f(id[u]+edge, id[v]+1);\n\
    \    }\n\n    template<typename F>\n    void path(int u, int v, const F &f, bool\
    \ edge = false){\n        add(u, v, f, edge);\n    }\n\n    template<typename\
    \ F>\n    void apply_subtree(int v, const F &f, bool edge = false){\n        auto\
    \ [l, r] = subtree(v, edge);\n        f(l, r);\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T query(int u, int v, const T &e, const Q &q,\
    \ const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v), swap(l, r);\n            l = f(l, q(id[head[v]],\
    \ id[v]+1));\n            v = par[head[v]];\n        }\n        if(id[u] > id[v])\
    \ swap(u, v), swap(l, r);\n        return f(q(id[u]+edge, id[v]+1), f(l, r));\n\
    \    }\n\n    template<typename T, typename Q, typename F>\n    T path_query(int\
    \ u, int v, const T &e, const Q &q, const F &f, bool edge = false){\n        return\
    \ query(u, v, e, q, f, edge);\n    }\n\n    template<typename T, typename QL,\
    \ typename QR, typename F>\n    T query_order(int u, int v, const T &e, const\
    \ QL &ql, const QR &qr, const F &f, bool edge){\n        T l = e, r = e;\n   \
    \     while(head[u] != head[v]){\n            if(id[u] > id[v]) {\n          \
    \      l = f(l, qr(id[head[u]], id[u]+1));\n                u = par[head[u]];\n\
    \            }else {\n                r = f(ql(id[head[v]], id[v]+1), r);\n  \
    \              v = par[head[v]];\n            }\n        }\n        T mid = (id[u]\
    \ > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));\n        return\
    \ f(f(l, mid), r);\n    }\n\n    template<typename T, typename QL, typename QR,\
    \ typename F>\n    T path_query_ordered(int u, int v, const T &e, const QL &ql,\
    \ const QR &qr, const F &f, bool edge = false){\n        return query_order(u,\
    \ v, e, ql, qr, f, edge);\n    }\n\n    template<typename Q>\n    decltype(auto)\
    \ subtree_query(int v, const Q &q, bool edge = false){\n        auto [l, r] =\
    \ subtree(v, edge);\n        return q(l, r);\n    }\n};\n\n/**\n * @brief HL\u5206\
    \u89E3(HL Decomposition)\n */\n\n\n#line 3 \"graph/vertex_failure_connectivity.cpp\"\
    \n\nclass VertexFailureConnectivity {\n    BlockCutTree bct;\n    HeavyLightDecomposition\
    \ hld;\n\npublic:\n    explicit VertexFailureConnectivity(int n) : bct(n), hld(0)\
    \ {}\n\n    void add_edge(int u, int v) {\n        bct.add_edge(u, v);\n    }\n\
    \n    void build() {\n        int n = bct.build();\n        hld = HeavyLightDecomposition(bct.tree);\n\
    \        vector<char> seen(n);\n        vector<int> roots, stack;\n        for\
    \ (int v = 0; v < n; ++v) {\n            if (seen[v]) continue;\n            roots.push_back(v);\n\
    \            seen[v] = 1;\n            stack.push_back(v);\n            while\
    \ (!stack.empty()) {\n                int x = stack.back();\n                stack.pop_back();\n\
    \                for (int u : bct.tree[x]) {\n                    if (seen[u])\
    \ continue;\n                    seen[u] = 1;\n                    stack.push_back(u);\n\
    \                }\n            }\n        }\n        hld.build(roots);\n    }\n\
    \n    bool connected_without_vertex(int u, int v, int x) {\n        if (u == x\
    \ || v == x) return false;\n        int a = bct.id[u], b = bct.id[v], c = bct.id[x];\n\
    \        if (hld.tree_id[a] != hld.tree_id[b]) return false;\n        if (!bct.is_articulation[x]\
    \ || hld.tree_id[a] != hld.tree_id[c]) return true;\n        return hld.distance(a,\
    \ b) != hld.distance(a, c) + hld.distance(c, b);\n    }\n};\n\n/**\n * @brief\
    \ \u9802\u70B9\u9664\u53BB\u5F8C\u306E\u9023\u7D50\u5224\u5B9A\n */\n"
  code: "#include \"block_cut_tree.cpp\"\n#include \"../tree/hld.cpp\"\n\nclass VertexFailureConnectivity\
    \ {\n    BlockCutTree bct;\n    HeavyLightDecomposition hld;\n\npublic:\n    explicit\
    \ VertexFailureConnectivity(int n) : bct(n), hld(0) {}\n\n    void add_edge(int\
    \ u, int v) {\n        bct.add_edge(u, v);\n    }\n\n    void build() {\n    \
    \    int n = bct.build();\n        hld = HeavyLightDecomposition(bct.tree);\n\
    \        vector<char> seen(n);\n        vector<int> roots, stack;\n        for\
    \ (int v = 0; v < n; ++v) {\n            if (seen[v]) continue;\n            roots.push_back(v);\n\
    \            seen[v] = 1;\n            stack.push_back(v);\n            while\
    \ (!stack.empty()) {\n                int x = stack.back();\n                stack.pop_back();\n\
    \                for (int u : bct.tree[x]) {\n                    if (seen[u])\
    \ continue;\n                    seen[u] = 1;\n                    stack.push_back(u);\n\
    \                }\n            }\n        }\n        hld.build(roots);\n    }\n\
    \n    bool connected_without_vertex(int u, int v, int x) {\n        if (u == x\
    \ || v == x) return false;\n        int a = bct.id[u], b = bct.id[v], c = bct.id[x];\n\
    \        if (hld.tree_id[a] != hld.tree_id[b]) return false;\n        if (!bct.is_articulation[x]\
    \ || hld.tree_id[a] != hld.tree_id[c]) return true;\n        return hld.distance(a,\
    \ b) != hld.distance(a, c) + hld.distance(c, b);\n    }\n};\n\n/**\n * @brief\
    \ \u9802\u70B9\u9664\u53BB\u5F8C\u306E\u9023\u7D50\u5224\u5B9A\n */\n"
  dependsOn:
  - graph/block_cut_tree.cpp
  - graph/biconnected_components.cpp
  - tree/hld.cpp
  isVerificationFile: false
  path: graph/vertex_failure_connectivity.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:54:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_vertex_failure_connectivity.test.cpp
documentation_of: graph/vertex_failure_connectivity.cpp
layout: document
title: "\u9802\u70B9\u9664\u53BB\u5F8C\u306E\u9023\u7D50\u5224\u5B9A"
---

## 説明
無向グラフで、指定した頂点を通らずに2頂点間を移動できるかを求める。
ブロックカット木と HL 分解を内部で構築する。

## できること
頂点数を $V$、辺数を $E$ とする。

- `VertexFailureConnectivity g(n)`
  `n` 頂点のグラフを作る。時間・領域は $O(V)$
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループと平行辺も受け付ける。時間は償却 $O(1)$
- `void build()`
  全連結成分を前処理する。辺の追加後は再度呼ぶ。時間・領域は $O(V+E)$
- `bool connected_without_vertex(int u, int v, int x)`
  頂点 `x` を除いたグラフで `u` と `v` が連結なら `true`。端点が `x` なら `false`。時間は $O(\log(V+1))$

## 使い方
元の頂点番号 `0, ..., n-1` で辺を追加し、`build()` 後に問い合わせる。
`u == v` は `u != x` なら `true`。もともと非連結の2頂点は `false` となる。
孤立点や非連結グラフ、空グラフも構築できる。問い合わせで実際のグラフは変更しない。

## 実装上の補足
除去頂点が関節点の場合だけ、ブロックカット木の端点間パスに含まれるかを調べる。
森の根は内部で選ぶ。前処理は再帰を使わず、長い道でもスタック設定の変更は不要。
