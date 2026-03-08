---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_stern_brocot_tree.test.cpp
    title: test/yosupo_stern_brocot_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/stern_brocot_tree.cpp\"\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\nnamespace SternBrocotTree\
    \ {\n\nusing ll = long long;\n\nenum Direction {\n    Left,\n    Right\n};\n\n\
    struct Move {\n    Direction dir;\n    ll steps;\n};\n\nstruct Node {\n    ll\
    \ p, q, r, s;\n\n    Node() : p(0), q(1), r(1), s(0) {}\n    Node(ll p, ll q,\
    \ ll r, ll s) : p(p), q(q), r(r), s(s) {}\n\n    ll num() const { return p + r;\
    \ }\n    ll den() const { return q + s; }\n};\n\nNode apply(Node node, Move move)\
    \ {\n    if (move.steps == 0) return node;\n    if (move.dir == Left) {\n    \
    \    node.r += node.p * move.steps;\n        node.s += node.q * move.steps;\n\
    \    } else {\n        node.p += node.r * move.steps;\n        node.q += node.s\
    \ * move.steps;\n    }\n    return node;\n}\n\nNode decode_path(const vector<Move>&\
    \ path) {\n    Node node;\n    for (auto move : path) node = apply(node, move);\n\
    \    return node;\n}\n\nvector<Move> encode_path(ll a, ll b) {\n    assert(a >\
    \ 0 && b > 0);\n    vector<Move> path;\n    while (a != b) {\n        if (a <\
    \ b) {\n            ll steps = (b - 1) / a;\n            path.push_back({Left,\
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
    }  // namespace SternBrocotTree\n"
  code: "#include <cassert>\n#include <utility>\n#include <vector>\nusing namespace\
    \ std;\n\nnamespace SternBrocotTree {\n\nusing ll = long long;\n\nenum Direction\
    \ {\n    Left,\n    Right\n};\n\nstruct Move {\n    Direction dir;\n    ll steps;\n\
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
    }  // namespace SternBrocotTree\n"
  dependsOn: []
  isVerificationFile: false
  path: math/stern_brocot_tree.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:57:33+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_stern_brocot_tree.test.cpp
documentation_of: math/stern_brocot_tree.cpp
layout: document
redirect_from:
- /library/math/stern_brocot_tree.cpp
- /library/math/stern_brocot_tree.cpp.html
title: math/stern_brocot_tree.cpp
---
