---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/link_cut_tree.cpp
    title: Link-Cut Tree
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
  bundledCode: "#line 1 \"test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n#include <bits/stdc++.h>\n\nstatic const int MOD = 998244353;\nusing ll = long\
    \ long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#line 1 \"util/modint.cpp\"\ntemplate <uint M>\nstruct modint {\n  \
    \  uint val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll\
    \ x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }\n    modint(bool v)\
    \ { val = ((unsigned int)(v) % M); }\n    modint& operator++() { val++; if (val\
    \ == M) val = 0; return *this; }\n    modint& operator--() { if (val == 0) val\
    \ = M; val--; return *this; }\n    modint operator++(int) { modint result = *this;\
    \ ++*this; return result; }\n    modint operator--(int) { modint result = *this;\
    \ --*this; return result; }\n    modint& operator+=(const modint& b) { val +=\
    \ b.val; if (val >= M) val -= M; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= M) val += M; return *this; }\n    modint&\
    \ operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z % M);\
    \ return *this; }\n    modint& operator/=(const modint& b) { return *this = *this\
    \ * b.inv(); }\n    modint operator+() const { return *this; }\n    modint operator-()\
    \ const { return modint() - *this; }\n    modint pow(long long n) const { modint\
    \ x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r;\
    \ }\n    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 1\
    \ \"tree/link_cut_tree.cpp\"\ntemplate <class M>\nstruct LinkCutTree {\n    using\
    \ T = typename M::T;\n\n    struct Node {\n        int l, r, p, sz;\n        bool\
    \ rev;\n        T val, sum, rsum;\n        Node() : l(-1), r(-1), p(-1), sz(1),\
    \ rev(false), val(M::e()), sum(M::e()), rsum(M::e()) {}\n    };\n\n    int n;\n\
    \    vector<Node> nodes;\n\n    explicit LinkCutTree(int n) : n(n), nodes(n) {}\n\
    \n    bool is_root(int x) const {\n        int p = nodes[x].p;\n        return\
    \ p == -1 || (nodes[p].l != x && nodes[p].r != x);\n    }\n\n    void reverse(int\
    \ x) {\n        if (x == -1) return;\n        swap(nodes[x].l, nodes[x].r);\n\
    \        swap(nodes[x].sum, nodes[x].rsum);\n        nodes[x].rev ^= 1;\n    }\n\
    \n    void push(int x) {\n        if (x == -1 || !nodes[x].rev) return;\n    \
    \    reverse(nodes[x].l);\n        reverse(nodes[x].r);\n        nodes[x].rev\
    \ = false;\n    }\n\n    void pull(int x) {\n        nodes[x].sz = 1;\n      \
    \  nodes[x].sum = nodes[x].val;\n        nodes[x].rsum = nodes[x].val;\n     \
    \   if (nodes[x].l != -1) {\n            int y = nodes[x].l;\n            nodes[x].sz\
    \ += nodes[y].sz;\n            nodes[x].sum = M::f(nodes[y].sum, nodes[x].sum);\n\
    \            nodes[x].rsum = M::f(nodes[x].rsum, nodes[y].rsum);\n        }\n\
    \        if (nodes[x].r != -1) {\n            int y = nodes[x].r;\n          \
    \  nodes[x].sz += nodes[y].sz;\n            nodes[x].sum = M::f(nodes[x].sum,\
    \ nodes[y].sum);\n            nodes[x].rsum = M::f(nodes[y].rsum, nodes[x].rsum);\n\
    \        }\n    }\n\n    void rotate(int x) {\n        int p = nodes[x].p;\n \
    \       int g = nodes[p].p;\n        if (nodes[p].l == x) {\n            int b\
    \ = nodes[x].r;\n            nodes[x].r = p;\n            nodes[p].l = b;\n  \
    \          if (b != -1) nodes[b].p = p;\n        } else {\n            int b =\
    \ nodes[x].l;\n            nodes[x].l = p;\n            nodes[p].r = b;\n    \
    \        if (b != -1) nodes[b].p = p;\n        }\n        nodes[p].p = x;\n  \
    \      nodes[x].p = g;\n        if (g != -1) {\n            if (nodes[g].l ==\
    \ p) nodes[g].l = x;\n            if (nodes[g].r == p) nodes[g].r = x;\n     \
    \   }\n        pull(p);\n        pull(x);\n    }\n\n    void splay(int x) {\n\
    \        vector<int> st(1, x);\n        for (int y = x; !is_root(y); y = nodes[y].p)\
    \ st.emplace_back(nodes[y].p);\n        while (!st.empty()) {\n            push(st.back());\n\
    \            st.pop_back();\n        }\n        while (!is_root(x)) {\n      \
    \      int p = nodes[x].p;\n            int g = nodes[p].p;\n            if (!is_root(p))\
    \ {\n                bool zigzig = (nodes[p].l == x) == (nodes[g].l == p);\n \
    \               rotate(zigzig ? p : x);\n            }\n            rotate(x);\n\
    \        }\n    }\n\n    int expose(int x) {\n        int rp = -1;\n        for\
    \ (int cur = x; cur != -1; cur = nodes[cur].p) {\n            splay(cur);\n  \
    \          nodes[cur].r = rp;\n            pull(cur);\n            rp = cur;\n\
    \        }\n        splay(x);\n        return rp;\n    }\n\n    void evert(int\
    \ x) {\n        expose(x);\n        reverse(x);\n        push(x);\n    }\n\n \
    \   int get_root(int x) {\n        expose(x);\n        while (nodes[x].l != -1)\
    \ {\n            push(x);\n            x = nodes[x].l;\n        }\n        splay(x);\n\
    \        return x;\n    }\n\n    bool connected(int u, int v) {\n        return\
    \ get_root(u) == get_root(v);\n    }\n\n    bool link(int u, int v) {\n      \
    \  evert(u);\n        if (get_root(v) == u) return false;\n        expose(v);\n\
    \        nodes[u].p = v;\n        nodes[v].r = u;\n        pull(v);\n        return\
    \ true;\n    }\n\n    bool cut(int u, int v) {\n        evert(u);\n        expose(v);\n\
    \        if (nodes[v].l != u || nodes[u].r != -1) return false;\n        nodes[v].l\
    \ = -1;\n        nodes[u].p = -1;\n        pull(v);\n        return true;\n  \
    \  }\n\n    int lca(int u, int v) {\n        if (!connected(u, v)) return -1;\n\
    \        expose(u);\n        return expose(v);\n    }\n\n    int parent(int x)\
    \ {\n        expose(x);\n        if (nodes[x].l == -1) return -1;\n        x =\
    \ nodes[x].l;\n        push(x);\n        while (nodes[x].r != -1) {\n        \
    \    x = nodes[x].r;\n            push(x);\n        }\n        splay(x);\n   \
    \     return x;\n    }\n\n    void set(int x, const T &val) {\n        expose(x);\n\
    \        nodes[x].val = val;\n        pull(x);\n    }\n\n    T get(int x) {\n\
    \        expose(x);\n        return nodes[x].val;\n    }\n\n    T fold(int u,\
    \ int v) {\n        evert(u);\n        expose(v);\n        return nodes[v].sum;\n\
    \    }\n\n    int dist(int u, int v) {\n        evert(u);\n        expose(v);\n\
    \        return nodes[v].sz - 1;\n    }\n};\n\n/**\n * @brief Link-Cut Tree\n\
    \ * @docs _md/link_cut_tree.md\n */\n#line 12 \"test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n\nstruct Monoid {\n    using T = array<mint, 2>;\n    static T f(T a, T b) {\
    \ return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return {1, 0};\
    \ }\n};\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    LinkCutTree<Monoid>\
    \ lct(n);\n    for (int i = 0; i < n; ++i) {\n        int a, b;\n        cin >>\
    \ a >> b;\n        lct.set(i, {a, b});\n    }\n    for (int i = 0; i < n - 1;\
    \ ++i) {\n        int u, v;\n        cin >> u >> v;\n        lct.link(u, v);\n\
    \    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n        cin >> t;\n\
    \        if (t == 0) {\n            int u, v, w, x;\n            cin >> u >> v\
    \ >> w >> x;\n            lct.cut(u, v);\n            lct.link(w, x);\n      \
    \  } else if (t == 1) {\n            int p, c, d;\n            cin >> p >> c >>\
    \ d;\n            lct.set(p, {c, d});\n        } else {\n            int u, v,\
    \ x;\n            cin >> u >> v >> x;\n            auto f = lct.fold(u, v);\n\
    \            cout << (f[0] * x + f[1]).val << '\\n';\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n#include <bits/stdc++.h>\n\nstatic const int MOD = 998244353;\nusing ll = long\
    \ long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#include \"../util/modint.cpp\"\n#include \"../tree/link_cut_tree.cpp\"\
    \n\nstruct Monoid {\n    using T = array<mint, 2>;\n    static T f(T a, T b) {\
    \ return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return {1, 0};\
    \ }\n};\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    LinkCutTree<Monoid>\
    \ lct(n);\n    for (int i = 0; i < n; ++i) {\n        int a, b;\n        cin >>\
    \ a >> b;\n        lct.set(i, {a, b});\n    }\n    for (int i = 0; i < n - 1;\
    \ ++i) {\n        int u, v;\n        cin >> u >> v;\n        lct.link(u, v);\n\
    \    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n        cin >> t;\n\
    \        if (t == 0) {\n            int u, v, w, x;\n            cin >> u >> v\
    \ >> w >> x;\n            lct.cut(u, v);\n            lct.link(w, x);\n      \
    \  } else if (t == 1) {\n            int p, c, d;\n            cin >> p >> c >>\
    \ d;\n            lct.set(p, {c, d});\n        } else {\n            int u, v,\
    \ x;\n            cin >> u >> v >> x;\n            auto f = lct.fold(u, v);\n\
    \            cout << (f[0] * x + f[1]).val << '\\n';\n        }\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/modint.cpp
  - tree/link_cut_tree.cpp
  isVerificationFile: true
  path: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 11:18:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
- /verify/test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp.html
title: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
---
