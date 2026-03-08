---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/persistent_segtree.cpp
    title: Persistent Segment Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/yosupo_point_add_range_sum_persistent.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"datastructure/persistent_segtree.cpp\"\
    \ntemplate <class M>\nstruct PersistentSegmentTree{\n    using T = typename M::T;\n\
    \    struct Node{\n        T val;\n        int l, r;\n    };\n\n    int n{};\n\
    \    vector<Node> node;\n    vector<int> root;\n\n    explicit PersistentSegmentTree(int\
    \ n): n(n){\n        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n\
    \            root.push_back(0);\n        }else{\n            root.push_back(build(0,\
    \ n));\n        }\n    }\n    explicit PersistentSegmentTree(const vector<T> &v):\
    \ n(v.size()){\n        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n\
    \            root.push_back(0);\n        }else{\n            root.push_back(build(0,\
    \ n, v));\n        }\n    }\n\n    int latest_version() const { return root.size()-1;\
    \ }\n    int versions() const { return root.size(); }\n\n    int update(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(update_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int update(int k,\
    \ const T &x){ return update(latest_version(), k, x); }\n\n    int add(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(add_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int add(int k, const\
    \ T &x){ return add(latest_version(), k, x); }\n\n    T query(int t, int a, int\
    \ b) const {\n        if(n == 0 || b <= a) return M::e();\n        return query_(root[t],\
    \ a, b, 0, n);\n    }\n    T query(int a, int b) const { return query(latest_version(),\
    \ a, b); }\n\n    T get(int t, int k) const { return query(t, k, k+1); }\n   \
    \ T operator[](const int &k) const { return get(latest_version(), k); }\n\nprivate:\n\
    \    int make_node(const T &v, int l, int r){\n        node.push_back({v, l, r});\n\
    \        return node.size()-1;\n    }\n\n    int build(int l, int r){\n      \
    \  if(l+1 == r) return make_node(M::e(), -1, -1);\n        int m = (l+r)>>1;\n\
    \        int ll = build(l, m), rr = build(m, r);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n    int build(int l, int r, const vector<T>\
    \ &v){\n        if(l+1 == r) return make_node(v[l], -1, -1);\n        int m =\
    \ (l+r)>>1;\n        int ll = build(l, m, v), rr = build(m, r, v);\n        return\
    \ make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n    int update_(int\
    \ id, int k, const T &x, int l, int r){\n        if(l+1 == r) return make_node(x,\
    \ -1, -1);\n        int m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n\
    \        if(k < m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr,\
    \ k, x, m, r);\n        return make_node(M::f(node[ll].val, node[rr].val), ll,\
    \ rr);\n    }\n\n    int add_(int id, int k, const T &x, int l, int r){\n    \
    \    if(l+1 == r) return make_node(M::f(node[id].val, x), -1, -1);\n        int\
    \ m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n        if(k <\
    \ m) ll = add_(ll, k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n   \
    \     return make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n \
    \   T query_(int id, int a, int b, int l, int r) const {\n        if(r <= a ||\
    \ b <= l) return M::e();\n        if(a <= l && r <= b) return node[id].val;\n\
    \        int m = (l+r)>>1;\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n};\n\n/*\nstruct Monoid{\n    using\
    \ T = long long;\n    static T f(T a, T b) { return a + b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief \u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Persistent Segment Tree)\n */\n#line 22 \"test/yosupo_point_add_range_sum_persistent.test.cpp\"\
    \n\nstruct Monoid{\n    using T = long long;\n    static T f(T a, T b) { return\
    \ a + b; }\n    static T e() { return 0; }\n};\n\nint main() {\n    int n, q;\n\
    \    cin >> n >> q;\n    vector<ll> a(n);\n    for (auto &&i : a) scanf(\"%lld\"\
    , &i);\n\n    PersistentSegmentTree<Monoid> seg(a);\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, x, y;\n        scanf(\"%d %d %d\", &t, &x, &y);\n   \
    \     if(t == 0) seg.add(x, y);\n        else printf(\"%lld\\n\", seg.query(x,\
    \ y));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #include \"../datastructure/persistent_segtree.cpp\"\n\nstruct Monoid{\n    using\
    \ T = long long;\n    static T f(T a, T b) { return a + b; }\n    static T e()\
    \ { return 0; }\n};\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    vector<ll>\
    \ a(n);\n    for (auto &&i : a) scanf(\"%lld\", &i);\n\n    PersistentSegmentTree<Monoid>\
    \ seg(a);\n    for (int i = 0; i < q; ++i) {\n        int t, x, y;\n        scanf(\"\
    %d %d %d\", &t, &x, &y);\n        if(t == 0) seg.add(x, y);\n        else printf(\"\
    %lld\\n\", seg.query(x, y));\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/persistent_segtree.cpp
  isVerificationFile: true
  path: test/yosupo_point_add_range_sum_persistent.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_point_add_range_sum_persistent.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_add_range_sum_persistent.test.cpp
- /verify/test/yosupo_point_add_range_sum_persistent.test.cpp.html
title: test/yosupo_point_add_range_sum_persistent.test.cpp
---
