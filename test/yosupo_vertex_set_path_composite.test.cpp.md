---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segtree.cpp
    title: datastructure/segtree.cpp
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: tree/hld.cpp
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "#line 1 \"test/yosupo_vertex_set_path_composite.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <bitset>\n\nstatic const int MOD = 998244353;\nusing\
    \ ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing\
    \ namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#line 1 \"util/modint.cpp\"\ntemplate <uint M>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T\
    \ v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }\n    modint(bool\
    \ v) { val = ((unsigned int)(v) % M); }\n    modint& operator++() { val++; if\
    \ (val == M) val = 0; return *this; }\n    modint& operator--() { if (val == 0)\
    \ val = M; val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint& operator+=(const modint& b)\
    \ { val += b.val; if (val >= M) val -= M; return *this; }\n    modint& operator-=(const\
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
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 19\
    \ \"test/yosupo_vertex_set_path_composite.test.cpp\"\n\n#line 1 \"tree/hld.cpp\"\
    \n\nclass HeavyLightDecomposition {\n    void dfs_sz(int v){\n        for (auto\
    \ &&u : G[v]) {\n            if(u == par[v]) continue;\n            par[u] = v;\
    \ dep[u] = dep[v] + 1;\n            dfs_sz(u);\n            sub_size[v] += sub_size[u];\n\
    \            if(sub_size[u] > sub_size[G[v][0]]) swap(u, G[v][0]);\n        }\n\
    \    }\n    void dfs_hld(int v, int c, int &pos){\n        id[v] = pos++;\n  \
    \      id_inv[id[v]]= v;\n        tree_id[v] = c;\n        for (auto &&u : G[v])\
    \ {\n            if(u == par[v]) continue;\n            head[u] = (u == G[v][0]\
    \ ? head[v] : u);\n            dfs_hld(u, c, pos);\n        }\n    }\npublic:\n\
    \    int n;\n    vector<vector<int>> G;\n    vector<int> par, dep, sub_size, id,\
    \ id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int n) : n(n),\
    \ G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n){}\n\
    \    explicit HeavyLightDecomposition(vector<vector<int>> &G) :G(G), n(G.size()),\
    \ par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n) {}\n\n\
    \    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n        G[v].emplace_back(u);\n\
    \    }\n\n    void build(vector<int> roots = {0}){\n        int c = 0, pos = 0;\n\
    \        for (auto &&i : roots) {\n            dfs_sz(i);\n            head[i]\
    \ = i;\n            dfs_hld(i, c++, pos);\n        }\n    }\n\n    int lca(int\
    \ u, int v){\n        while(true){\n            if(id[u] > id[v]) swap(u, v);\n\
    \            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int distance(int u, int v){ return dep[u] + dep[v] -\
    \ 2*dep[lca(u, v)]; }\n\n    template<typename F>\n    void add(int u, int v,\
    \ const F &f, bool edge){\n        while (head[u] != head[v]){\n            if(id[u]\
    \ > id[v]) swap(u, v);\n            f(id[head[v]], id[v]+1);\n            v =\
    \ par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v);\n        f(id[u]+edge,\
    \ id[v]+1);\n    }\n\n    template<typename T, typename Q, typename F>\n    T\
    \ query(int u, int v, const T &e, const Q &q, const F &f, bool edge){\n      \
    \  T l = e, r = e;\n        while(head[u] != head[v]){\n            if(id[u] >\
    \ id[v]) swap(u, v), swap(l, r);\n            l = f(l, q(id[head[v]], id[v]+1));\n\
    \            v = par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v),\
    \ swap(l, r);\n        return f(q(id[u]+edge, id[v]+1), f(l, r));\n    }\n\n \
    \   template<typename T, typename QL, typename QR, typename F>\n    T query_order(int\
    \ u, int v, const T &e, const QL &ql, const QR &qr, const F &f, bool edge){\n\
    \        T l = e, r = e;\n        while(head[u] != head[v]){\n            if(id[u]\
    \ > id[v]) {\n                l = f(l, qr(id[head[u]], id[u]+1));\n          \
    \      u = par[head[u]];\n            }else {\n                r = f(ql(id[head[v]],\
    \ id[v]+1), r);\n                v = par[head[v]];\n            }\n        }\n\
    \        T mid = (id[u] > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));\n\
    \        return f(f(l, mid), r);\n    }\n};\n#line 21 \"test/yosupo_vertex_set_path_composite.test.cpp\"\
    \n\n#line 1 \"datastructure/segtree.cpp\"\ntemplate <class M>\nstruct SegmentTree{\n\
    \    using T = typename M::T;\n    int sz, n, height{};\n    vector<T> seg;\n\
    \    explicit SegmentTree(int n) : n(n) {\n        sz = 1; while(sz < n) sz <<=\
    \ 1, height++;\n        seg.assign(2*sz, M::e());\n    }\n\n    void set(int k,\
    \ const T &x){ seg[k + sz] = x; }\n\n    void build(){\n        for (int i = sz-1;\
    \ i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);\n    }\n\n    void update(int\
    \ k, const T &x){\n        k += sz;\n        seg[k] = x;\n        while (k >>=\
    \ 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n    }\n\n    T query(int a, int b){\n\
    \        T l = M::e(), r = M::e();\n        for(a += sz, b += sz; a < b; a >>=1,\
    \ b>>=1){\n            if(a & 1) l = M::f(l, seg[a++]);\n            if(b & 1)\
    \ r = M::f(seg[--b], r);\n        }\n        return M::f(l, r);\n    }\n\n   \
    \ template<class F>\n    int search_right(int l, F cond){\n        if(l == n)\
    \ return n;\n        T val = M::e();\n        l += sz;\n        do {\n       \
    \     while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val, seg[l]))){\n    \
    \            while(l < sz) {\n                    l <<= 1;\n                 \
    \   if (cond(M::f(val, seg[l]))){\n                        val = M::f(val, seg[l]);\n\
    \                        l++;\n                    }\n                }\n    \
    \            return l - sz;\n            }\n            val = M::f(val, seg[l]);\n\
    \            l++;\n        } while((l & -l) != l);\n        return n;\n    }\n\
    \n    template<class F>\n    int search_left(int r, F cond){\n        if(r ==\
    \ 0) return 0;\n        T val = M::e();\n        r += sz;\n        do {\n    \
    \        r--;\n            while(r&1) r >>= 1;\n            if(!cond(M::f(seg[r],\
    \ val))){\n                while(r < sz) {\n                    r = ((r << 1)|1);\n\
    \                    if (cond(M::f(seg[r], val))){\n                        val\
    \ = M::f(seg[r], val);\n                        r--;\n                    }\n\
    \                }\n                return r + 1 - sz;\n            }\n      \
    \      val = M::f(seg[r], val);\n        } while((r & -r) != r);\n        return\
    \ 0;\n    }\n    T operator[](const int &k) const { return seg[k + sz]; }\n};\n\
    \n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n    static T f(T a, T b)\
    \ { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static T e() { return {1, 0}; }\n\
    };\n*/\n#line 23 \"test/yosupo_vertex_set_path_composite.test.cpp\"\n\nstruct\
    \ Ml {\n    using T = array<mint, 2>;\n    static T f(T a, T b) { return {a[0]*b[0],\
    \ a[1]*b[0]+b[1]}; }\n    static T e() { return {1, 0}; }\n};\n\nstruct Mr {\n\
    \    using T = array<mint, 2>;\n    static T f(T b, T a) { return {a[0]*b[0],\
    \ a[1]*b[0]+b[1]}; }\n    static T e() { return {1, 0}; }\n};\n\nint main() {\n\
    \    int n, q;\n    cin >> n >> q;\n    HeavyLightDecomposition G(n);\n    SegmentTree<Ml>\
    \ segl(n);\n    SegmentTree<Mr> segr(n);\n    {\n        vector<int> a(n), b(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            scanf(\"%d %d\", &a[i], &b[i]);\n\
    \        }\n        for (int i = 0; i < n - 1; ++i) {\n            int l, r;\n\
    \            scanf(\"%d %d\", &l, &r);\n            G.add_edge(l, r);\n      \
    \  }\n        G.build();\n        for (int i = 0; i < n; ++i) {\n            int\
    \ id = G.id[i];\n            segl.set(id, {a[i], b[i]});\n            segr.set(id,\
    \ {a[i], b[i]});\n        }\n        segl.build(); segr.build();\n    }\n    auto\
    \ fl = [&](int l, int r){ return segl.query(l, r); };\n    auto fr = [&](int l,\
    \ int r){ return segr.query(l, r); };\n    auto merge = [&](Ml::T a, Ml::T b)\
    \ -> Ml::T { return {a[0]*b[0], a[1]*b[0]+b[1]}; };\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        scanf(\"%d %d %d %d\", &t, &a, &b,\
    \ &c);\n        if(t == 0){\n            a = G.id[a];\n            segl.update(a,\
    \ {b, c});\n            segr.update(a, {b, c});\n        }else {\n           \
    \ auto val = G.query_order(a, b, Ml::e(), fl, fr, merge, false);\n           \
    \ printf(\"%d\\n\", (val[0]*c + val[1]).val);\n        }\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <bitset>\n\nstatic const int MOD\
    \ = 998244353;\nusing ll = long long;\nusing uint = unsigned;\nusing ull = unsigned\
    \ long long;\nusing namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include \"../util/modint.cpp\"\n\n#include \"../tree/hld.cpp\"\
    \n\n#include \"../datastructure/segtree.cpp\"\n\nstruct Ml {\n    using T = array<mint,\
    \ 2>;\n    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n\nstruct Mr {\n    using T = array<mint, 2>;\n\
    \    static T f(T b, T a) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n\nint main() {\n    int n, q;\n    cin >> n >>\
    \ q;\n    HeavyLightDecomposition G(n);\n    SegmentTree<Ml> segl(n);\n    SegmentTree<Mr>\
    \ segr(n);\n    {\n        vector<int> a(n), b(n);\n        for (int i = 0; i\
    \ < n; ++i) {\n            scanf(\"%d %d\", &a[i], &b[i]);\n        }\n      \
    \  for (int i = 0; i < n - 1; ++i) {\n            int l, r;\n            scanf(\"\
    %d %d\", &l, &r);\n            G.add_edge(l, r);\n        }\n        G.build();\n\
    \        for (int i = 0; i < n; ++i) {\n            int id = G.id[i];\n      \
    \      segl.set(id, {a[i], b[i]});\n            segr.set(id, {a[i], b[i]});\n\
    \        }\n        segl.build(); segr.build();\n    }\n    auto fl = [&](int\
    \ l, int r){ return segl.query(l, r); };\n    auto fr = [&](int l, int r){ return\
    \ segr.query(l, r); };\n    auto merge = [&](Ml::T a, Ml::T b) -> Ml::T { return\
    \ {a[0]*b[0], a[1]*b[0]+b[1]}; };\n    for (int i = 0; i < q; ++i) {\n       \
    \ int t, a, b, c;\n        scanf(\"%d %d %d %d\", &t, &a, &b, &c);\n        if(t\
    \ == 0){\n            a = G.id[a];\n            segl.update(a, {b, c});\n    \
    \        segr.update(a, {b, c});\n        }else {\n            auto val = G.query_order(a,\
    \ b, Ml::e(), fl, fr, merge, false);\n            printf(\"%d\\n\", (val[0]*c\
    \ + val[1]).val);\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - util/modint.cpp
  - tree/hld.cpp
  - datastructure/segtree.cpp
  isVerificationFile: true
  path: test/yosupo_vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2021-07-22 12:32:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_vertex_set_path_composite.test.cpp
- /verify/test/yosupo_vertex_set_path_composite.test.cpp.html
title: test/yosupo_vertex_set_path_composite.test.cpp
---
