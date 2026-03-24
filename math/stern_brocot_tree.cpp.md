---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_stern_brocot_tree.test.cpp
    title: test/yosupo_stern_brocot_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Stern-Brocot\u6728"
    links: []
  bundledCode: "#line 1 \"math/stern_brocot_tree.cpp\"\nusing namespace std;\n\nnamespace\
    \ SternBrocotTree {\n\nenum Direction {\n    Left,\n    Right\n};\n\nstruct Move\
    \ {\n    Direction dir;\n    ll steps;\n};\n\nstruct Node {\n    ll p, q, r, s;\n\
    \n    Node() : p(0), q(1), r(1), s(0) {}\n    Node(ll p, ll q, ll r, ll s) : p(p),\
    \ q(q), r(r), s(s) {}\n\n    ll num() const { return p + r; }\n    ll den() const\
    \ { return q + s; }\n};\n\nNode apply(Node node, Move move) {\n    if (move.steps\
    \ == 0) return node;\n    if (move.dir == Left) {\n        node.r += node.p *\
    \ move.steps;\n        node.s += node.q * move.steps;\n    } else {\n        node.p\
    \ += node.r * move.steps;\n        node.q += node.s * move.steps;\n    }\n   \
    \ return node;\n}\n\nNode decode_path(const vector<Move>& path) {\n    Node node;\n\
    \    for (auto move : path) node = apply(node, move);\n    return node;\n}\n\n\
    vector<Move> encode_path(ll a, ll b) {\n    assert(a > 0 && b > 0);\n    vector<Move>\
    \ path;\n    while (a != b) {\n        if (a < b) {\n            ll steps = (b\
    \ - 1) / a;\n            path.push_back({Left, steps});\n            b -= steps\
    \ * a;\n        } else {\n            ll steps = (a - 1) / b;\n            path.push_back({Right,\
    \ steps});\n            a -= steps * b;\n        }\n    }\n    return path;\n\
    }\n\nll depth(const vector<Move>& path) {\n    ll ret = 0;\n    for (auto move\
    \ : path) ret += move.steps;\n    return ret;\n}\n\nvector<Move> lca_path(const\
    \ vector<Move>& a, const vector<Move>& b) {\n    vector<Move> ret;\n    int i\
    \ = 0, j = 0;\n    ll sa = 0, sb = 0;\n    while (i < (int)a.size() && j < (int)b.size())\
    \ {\n        if (sa == 0) sa = a[i].steps;\n        if (sb == 0) sb = b[j].steps;\n\
    \        if (a[i].dir != b[j].dir) break;\n        ll steps = min(sa, sb);\n \
    \       ret.push_back({a[i].dir, steps});\n        sa -= steps;\n        sb -=\
    \ steps;\n        if (sa == 0) ++i;\n        if (sb == 0) ++j;\n    }\n    return\
    \ ret;\n}\n\nvector<Move> ancestor_path(const vector<Move>& path, ll k) {\n  \
    \  vector<Move> ret;\n    for (auto move : path) {\n        if (k == 0) break;\n\
    \        ll steps = min(move.steps, k);\n        ret.push_back({move.dir, steps});\n\
    \        k -= steps;\n    }\n    if (k != 0) return {};\n    return ret;\n}\n\n\
    Node range(ll a, ll b) {\n    return decode_path(encode_path(a, b));\n}\n\nNode\
    \ lca(ll a, ll b, ll c, ll d) {\n    return decode_path(lca_path(encode_path(a,\
    \ b), encode_path(c, d)));\n}\n\n}  // namespace SternBrocotTree\n\n/**\n * @brief\
    \ Stern-Brocot\u6728\n */\n"
  code: "using namespace std;\n\nnamespace SternBrocotTree {\n\nenum Direction {\n\
    \    Left,\n    Right\n};\n\nstruct Move {\n    Direction dir;\n    ll steps;\n\
    };\n\nstruct Node {\n    ll p, q, r, s;\n\n    Node() : p(0), q(1), r(1), s(0)\
    \ {}\n    Node(ll p, ll q, ll r, ll s) : p(p), q(q), r(r), s(s) {}\n\n    ll num()\
    \ const { return p + r; }\n    ll den() const { return q + s; }\n};\n\nNode apply(Node\
    \ node, Move move) {\n    if (move.steps == 0) return node;\n    if (move.dir\
    \ == Left) {\n        node.r += node.p * move.steps;\n        node.s += node.q\
    \ * move.steps;\n    } else {\n        node.p += node.r * move.steps;\n      \
    \  node.q += node.s * move.steps;\n    }\n    return node;\n}\n\nNode decode_path(const\
    \ vector<Move>& path) {\n    Node node;\n    for (auto move : path) node = apply(node,\
    \ move);\n    return node;\n}\n\nvector<Move> encode_path(ll a, ll b) {\n    assert(a\
    \ > 0 && b > 0);\n    vector<Move> path;\n    while (a != b) {\n        if (a\
    \ < b) {\n            ll steps = (b - 1) / a;\n            path.push_back({Left,\
    \ steps});\n            b -= steps * a;\n        } else {\n            ll steps\
    \ = (a - 1) / b;\n            path.push_back({Right, steps});\n            a -=\
    \ steps * b;\n        }\n    }\n    return path;\n}\n\nll depth(const vector<Move>&\
    \ path) {\n    ll ret = 0;\n    for (auto move : path) ret += move.steps;\n  \
    \  return ret;\n}\n\nvector<Move> lca_path(const vector<Move>& a, const vector<Move>&\
    \ b) {\n    vector<Move> ret;\n    int i = 0, j = 0;\n    ll sa = 0, sb = 0;\n\
    \    while (i < (int)a.size() && j < (int)b.size()) {\n        if (sa == 0) sa\
    \ = a[i].steps;\n        if (sb == 0) sb = b[j].steps;\n        if (a[i].dir !=\
    \ b[j].dir) break;\n        ll steps = min(sa, sb);\n        ret.push_back({a[i].dir,\
    \ steps});\n        sa -= steps;\n        sb -= steps;\n        if (sa == 0) ++i;\n\
    \        if (sb == 0) ++j;\n    }\n    return ret;\n}\n\nvector<Move> ancestor_path(const\
    \ vector<Move>& path, ll k) {\n    vector<Move> ret;\n    for (auto move : path)\
    \ {\n        if (k == 0) break;\n        ll steps = min(move.steps, k);\n    \
    \    ret.push_back({move.dir, steps});\n        k -= steps;\n    }\n    if (k\
    \ != 0) return {};\n    return ret;\n}\n\nNode range(ll a, ll b) {\n    return\
    \ decode_path(encode_path(a, b));\n}\n\nNode lca(ll a, ll b, ll c, ll d) {\n \
    \   return decode_path(lca_path(encode_path(a, b), encode_path(c, d)));\n}\n\n\
    }  // namespace SternBrocotTree\n\n/**\n * @brief Stern-Brocot\u6728\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/stern_brocot_tree.cpp
  requiredBy: []
  timestamp: '2026-03-12 14:17:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_stern_brocot_tree.test.cpp
date: 2026-03-08
documentation_of: math/stern_brocot_tree.cpp
layout: document
tags: "\u6570\u5B66"
title: "Stern-Brocot\u6728"
---

## 説明
Stern-Brocot 木上の有理数の位置を、連続した `L` / `R` 移動列として扱う。
分数と経路の相互変換、LCA、祖先、担当区間の取得に使える。

## できること
- `vector<Move> encode_path(ll a, ll b)`
  既約分数 `a / b` への経路を run-length 圧縮して返す
- `Node decode_path(const vector<Move>& path)`
  経路から節点を復元する
- `Node apply(Node node, Move move)`
  節点から `move` 回だけ下る
- `vector<Move> lca_path(const vector<Move>& a, const vector<Move>& b)`
  2 つの経路の共通接頭辞を返す
- `vector<Move> ancestor_path(const vector<Move>& path, ll k)`
  根から深さ `k` の祖先への経路を返す。深さが足りなければ空
- `ll depth(const vector<Move>& path)`
  経路長を返す
- `Node range(ll a, ll b)`
  `a / b` を根とする部分木が表す開区間 `(p / q, r / s)` を返す
- `Node lca(ll a, ll b, ll c, ll d)`
  2 つの分数の LCA を返す

## 使い方
`Node` は部分木の境界 `(p / q, r / s)` を持ち、現在の節点は mediant `(p + r) / (q + s)` で取れる。
経路は `Move{Left, x}` や `Move{Right, x}` の列で扱う。

`encode_path(a, b)` は既約分数を想定する。
`ancestor_path(path, k)` の `k` は根からの深さで、`depth(path)` を超えると空を返す。
