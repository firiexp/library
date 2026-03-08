---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: datastructure/segtree.cpp
    title: datastructure/segtree.cpp
  - icon: ':question:'
    path: tree/hld.cpp
    title: tree/hld.cpp
  - icon: ':heavy_check_mark:'
    path: tree/hld_edge.cpp
    title: "\u8FBA\u30AF\u30A8\u30EA\u5411\u3051\u91CD\u8EFD\u5206\u89E3"
  - icon: ':question:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_hld_edge.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <limits>\n#include <random>\n#include <utility>\n#include\
    \ <vector>\nusing namespace std;\n\nusing ll = long long;\n\n#line 1 \"util/fastio.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    using namespace std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n  \
    \  constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline char skip() {\n\
    \        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n          \
    \  ++idx;\n            ensure();\n        }\n        return buf[idx++];\n    }\n\
    \n    template<class T, typename enable_if<is_integral<T>::value, int>::type =\
    \ 0>\n    void read(T &x) {\n        char c = skip();\n        bool neg = false;\n\
    \        if constexpr (is_signed<T>::value) {\n            if (c == '-') {\n \
    \               neg = true;\n                c = buf[idx++];\n            }\n\
    \        }\n        x = 0;\n        while (c >= '0') {\n            x = x * 10\
    \ + (c & 15);\n            c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (buf[idx] > ' ') ++idx;\n            s.append(buf + start,\
    \ idx - start);\n            if (buf[idx] <= ' ') break;\n            load();\n\
    \        }\n        ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n    \
    \    if (idx) {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n\
    \        }\n    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE -\
    \ OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n    inline void write_range(const\
    \ char *s, size_t n) {\n        size_t pos = 0;\n        while (pos < n) {\n \
    \           if (idx == BUFSIZE) flush();\n            size_t chunk = min(n - pos,\
    \ (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s + pos, chunk);\n\
    \            idx += (int)chunk;\n            pos += chunk;\n        }\n    }\n\
    \n    void write(const char *s) {\n        write_range(s, strlen(s));\n    }\n\
    \n    void write(const string &s) {\n        write_range(s.data(), s.size());\n\
    \    }\n\n    void write(char c) {\n        pc(c);\n    }\n\n    void write(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void write(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
    \ U = typename make_unsigned<T>::type;\n        U y;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (x < 0) {\n                buf[idx++] = '-';\n           \
    \     y = U(0) - static_cast<U>(x);\n            } else {\n                y =\
    \ static_cast<U>(x);\n            }\n        } else {\n            y = x;\n  \
    \      }\n        if (y == 0) {\n            buf[idx++] = '0';\n            return;\n\
    \        }\n        static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n    \
    \    char tmp[TMP_SIZE];\n        int pos = TMP_SIZE;\n        while (y >= 10000)\
    \ {\n            pos -= 4;\n            memcpy(tmp + pos, table.num + (y % 10000)\
    \ * 4, 4);\n            y /= 10000;\n        }\n        if (y >= 1000) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2), 4);\n            idx += 4;\n\
    \        } else if (y >= 100) {\n            memcpy(buf + idx, table.num + (y\
    \ << 2) + 1, 3);\n            idx += 3;\n        } else if (y >= 10) {\n     \
    \       unsigned q = (unsigned(y) * 205) >> 11;\n            buf[idx] = char('0'\
    \ + q);\n            buf[idx + 1] = char('0' + (unsigned(y) - q * 10));\n    \
    \        idx += 2;\n        } else {\n            buf[idx++] = char('0' + y);\n\
    \        }\n        memcpy(buf + idx, tmp + pos, TMP_SIZE - pos);\n        idx\
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T>\n    void writeln(const T\
    \ &x) {\n        write(x);\n        pc('\\n');\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void writeln(const Head &head, const Tail &...tail) {\n\
    \        write(head);\n        ((pc(' '), write(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n#line 1 \"\
    tree/hld.cpp\"\n\nclass HeavyLightDecomposition {\n    void dfs_sz(int v){\n \
    \       int heavy = -1;\n        for (auto &&u : G[v]) {\n            if(u ==\
    \ par[v]) continue;\n            par[u] = v; dep[u] = dep[v] + 1;\n          \
    \  dfs_sz(u);\n            sub_size[v] += sub_size[u];\n            if(heavy ==\
    \ -1 || sub_size[u] > sub_size[heavy]) heavy = u;\n        }\n        if (heavy\
    \ != -1 && G[v][0] != heavy) {\n            for (auto &&u : G[v]) {\n        \
    \        if (u == heavy) {\n                    swap(u, G[v][0]);\n          \
    \          break;\n                }\n            }\n        }\n    }\n    void\
    \ dfs_hld(int v, int c, int &pos){\n        id[v] = pos++;\n        id_inv[id[v]]=\
    \ v;\n        tree_id[v] = c;\n        for (auto &&u : G[v]) {\n            if(u\
    \ == par[v]) continue;\n            head[u] = (u == G[v][0] ? head[v] : u);\n\
    \            dfs_hld(u, c, pos);\n        }\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G;\n    vector<int> par, dep, sub_size, id, id_inv, tree_id, head;\n    explicit\
    \ HeavyLightDecomposition(int n) : n(n), G(n), par(n), dep(n), sub_size(n, 1),\
    \ id(n), id_inv(n), tree_id(n), head(n){}\n    explicit HeavyLightDecomposition(vector<vector<int>>\
    \ &G) : n(G.size()), G(G), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n),\
    \ head(n) {}\n\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n\
    \        G[v].emplace_back(u);\n    }\n\n    void build(vector<int> roots = {0}){\n\
    \        fill(par.begin(), par.end(), -1);\n        fill(dep.begin(), dep.end(),\
    \ 0);\n        fill(sub_size.begin(), sub_size.end(), 1);\n        int c = 0,\
    \ pos = 0;\n        for (auto &&i : roots) {\n            dfs_sz(i);\n       \
    \     head[i] = i;\n            dfs_hld(i, c++, pos);\n        }\n    }\n\n  \
    \  int lca(int u, int v){\n        while(true){\n            if(id[u] > id[v])\
    \ swap(u, v);\n            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
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
    \ v, e, ql, qr, f, edge);\n    }\n\n    template<typename T, typename Q>\n   \
    \ T subtree_query(int v, const Q &q, bool edge = false){\n        auto [l, r]\
    \ = subtree(v, edge);\n        return q(l, r);\n    }\n};\n#line 2 \"tree/hld_edge.cpp\"\
    \n\nstruct HeavyLightDecompositionEdge {\n    HeavyLightDecomposition hld;\n\n\
    \    explicit HeavyLightDecompositionEdge(int n) : hld(n) {}\n    explicit HeavyLightDecompositionEdge(vector<vector<int>>\
    \ &g) : hld(g) {}\n\n    void add_edge(int u, int v) {\n        hld.add_edge(u,\
    \ v);\n    }\n\n    void build(vector<int> roots = {0}) {\n        hld.build(roots);\n\
    \    }\n\n    int lca(int u, int v) {\n        return hld.lca(u, v);\n    }\n\n\
    \    int parent(int v) const {\n        return hld.parent(v);\n    }\n\n    int\
    \ ancestor(int v, int k) {\n        return hld.ancestor(v, k);\n    }\n\n    int\
    \ distance(int u, int v) {\n        return hld.distance(u, v);\n    }\n\n    int\
    \ edge_index(int v) const {\n        if (hld.par[v] == -1) return -1;\n      \
    \  return hld.id[v];\n    }\n\n    pair<int, int> subtree(int v) const {\n   \
    \     return hld.subtree(v, true);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f) {\n        hld.path(u, v, f, true);\n    }\n\n\
    \    template<typename F>\n    void apply_subtree(int v, const F &f) {\n     \
    \   hld.apply_subtree(v, f, true);\n    }\n\n    template<typename T, typename\
    \ Q, typename F>\n    T path_query(int u, int v, const T &e, const Q &q, const\
    \ F &f) {\n        return hld.path_query(u, v, e, q, f, true);\n    }\n\n    template<typename\
    \ T, typename QL, typename QR, typename F>\n    T path_query_ordered(int u, int\
    \ v, const T &e, const QL &ql, const QR &qr, const F &f) {\n        return hld.path_query_ordered(u,\
    \ v, e, ql, qr, f, true);\n    }\n\n    template<typename T, typename Q>\n   \
    \ T subtree_query(int v, const Q &q) {\n        return hld.subtree_query<T>(v,\
    \ q, true);\n    }\n};\n\n/**\n * @brief \u8FBA\u30AF\u30A8\u30EA\u5411\u3051\u91CD\
    \u8EFD\u5206\u89E3\n * @docs _md/hld_edge.md\n */\n#line 1 \"datastructure/segtree.cpp\"\
    \ntemplate <class M>\nstruct SegmentTree{\n    using T = typename M::T;\n    int\
    \ sz, n, height{};\n    vector<T> seg;\n    explicit SegmentTree(int n) : n(n)\
    \ {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz,\
    \ M::e());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i],\
    \ seg[2*i+1]);\n    }\n\n    void update(int k, const T &x){\n        k += sz;\n\
    \        seg[k] = x;\n        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n\
    \    }\n\n    T query(int a, int b){\n        T l = M::e(), r = M::e();\n    \
    \    for(a += sz, b += sz; a < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l,\
    \ seg[a++]);\n            if(b & 1) r = M::f(seg[--b], r);\n        }\n      \
    \  return M::f(l, r);\n    }\n\n    template<class F>\n    int search_right(int\
    \ l, F cond){\n        if(l == n) return n;\n        T val = M::e();\n       \
    \ l += sz;\n        do {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val,\
    \ seg[l]))){\n                while(l < sz) {\n                    l <<= 1;\n\
    \                    if (cond(M::f(val, seg[l]))){\n                        val\
    \ = M::f(val, seg[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - sz;\n            }\n          \
    \  val = M::f(val, seg[l]);\n            l++;\n        } while((l & -l) != l);\n\
    \        return n;\n    }\n\n    template<class F>\n    int search_left(int r,\
    \ F cond){\n        if(r == 0) return 0;\n        T val = M::e();\n        r +=\
    \ sz;\n        do {\n            r--;\n            while(r&1) r >>= 1;\n     \
    \       if(!cond(M::f(seg[r], val))){\n                while(r < sz) {\n     \
    \               r = ((r << 1)|1);\n                    if (cond(M::f(seg[r], val))){\n\
    \                        val = M::f(seg[r], val);\n                        r--;\n\
    \                    }\n                }\n                return r + 1 - sz;\n\
    \            }\n            val = M::f(seg[r], val);\n        } while((r & -r)\
    \ != r);\n        return 0;\n    }\n    T operator[](const int &k) const { return\
    \ seg[k + sz]; }\n};\n\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n\
    \    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n*/\n#line 16 \"test/yosupo_many_aplusb_hld_edge.test.cpp\"\
    \n\nstruct Ml {\n    using T = array<ll, 2>;\n    static T f(T a, T b) { return\
    \ {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return {1, 0}; }\n\
    };\n\nstruct Mr {\n    using T = array<ll, 2>;\n    static T f(T b, T a) { return\
    \ {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return {1, 0}; }\n\
    };\n\nstruct Sum {\n    using T = ll;\n    static T f(T a, T b) { return a + b;\
    \ }\n    static T e() { return 0; }\n};\n\nstatic array<ll, 2> compose(array<ll,\
    \ 2> a, array<ll, 2> b) {\n    return {a[0] * b[0], a[1] * b[0] + b[1]};\n}\n\n\
    int main() {\n    {\n        mt19937 rng(123456789);\n        for (int n = 1;\
    \ n <= 50; ++n) {\n            for (int trial = 0; trial < 150; ++trial) {\n \
    \               vector<vector<int>> g(n);\n                for (int v = 1; v <\
    \ n; ++v) {\n                    int p = uniform_int_distribution<int>(0, v -\
    \ 1)(rng);\n                    g[p].push_back(v);\n                    g[v].push_back(p);\n\
    \                }\n\n                vector<int> parent(n, -1), depth(n, 0),\
    \ order = {0};\n                for (int i = 0; i < n; ++i) {\n              \
    \      int v = order[i];\n                    for (auto &&u : g[v]) {\n      \
    \                  if (u == parent[v]) continue;\n                        parent[u]\
    \ = v;\n                        depth[u] = depth[v] + 1;\n                   \
    \     order.push_back(u);\n                    }\n                }\n\n      \
    \          HeavyLightDecompositionEdge hld(n);\n                for (int v = 0;\
    \ v < n; ++v) {\n                    for (auto &&u : g[v]) {\n               \
    \         if (v < u) hld.add_edge(v, u);\n                    }\n            \
    \    }\n                hld.build();\n\n                SegmentTree<Ml> segl(n);\n\
    \                SegmentTree<Mr> segr(n);\n                SegmentTree<Sum> segsum(n);\n\
    \                vector<array<ll, 2>> aff(n, {1, 0});\n                vector<ll>\
    \ weight(n, 0);\n                for (int v = 1; v < n; ++v) {\n             \
    \       aff[v] = {uniform_int_distribution<int>(-3, 3)(rng), uniform_int_distribution<int>(-5,\
    \ 5)(rng)};\n                    weight[v] = uniform_int_distribution<int>(-10,\
    \ 10)(rng);\n                }\n                for (int v = 0; v < n; ++v) {\n\
    \                    int p = hld.edge_index(v);\n                    if (p ==\
    \ -1) continue;\n                    segl.set(p, aff[v]);\n                  \
    \  segr.set(p, aff[v]);\n                    segsum.set(p, weight[v]);\n     \
    \           }\n                segl.build();\n                segr.build();\n\
    \                segsum.build();\n\n                auto ql = [&](int l, int r)\
    \ { return segl.query(l, r); };\n                auto qr = [&](int l, int r) {\
    \ return segr.query(l, r); };\n                auto merge = [&](Ml::T x, Ml::T\
    \ y) -> Ml::T { return compose(x, y); };\n\n                auto lca = [&](int\
    \ a, int b) {\n                    while (depth[a] > depth[b]) a = parent[a];\n\
    \                    while (depth[b] > depth[a]) b = parent[b];\n            \
    \        while (a != b) a = parent[a], b = parent[b];\n                    return\
    \ a;\n                };\n\n                auto naive_path = [&](int a, int b)\
    \ {\n                    int c = lca(a, b);\n                    vector<int> vs;\n\
    \                    for (int v = a; v != c; v = parent[v]) vs.push_back(v);\n\
    \                    vector<int> down;\n                    for (int v = b; v\
    \ != c; v = parent[v]) down.push_back(v);\n                    reverse(down.begin(),\
    \ down.end());\n                    for (auto &&v : down) vs.push_back(v);\n \
    \                   array<ll, 2> ret = {1, 0};\n                    for (auto\
    \ &&v : vs) ret = compose(ret, aff[v]);\n                    return ret;\n   \
    \             };\n\n                vector<int> tin(n), tout(n);\n           \
    \     int timer = 0;\n                auto dfs = [&](auto &&self, int v) -> void\
    \ {\n                    tin[v] = timer++;\n                    for (auto &&u\
    \ : g[v]) {\n                        if (u == parent[v]) continue;\n         \
    \               self(self, u);\n                    }\n                    tout[v]\
    \ = timer;\n                };\n                dfs(dfs, 0);\n\n             \
    \   auto naive_subtree_sum = [&](int v) {\n                    ll ret = 0;\n \
    \                   for (int u = 0; u < n; ++u) {\n                        if\
    \ (u == v) continue;\n                        if (tin[v] <= tin[u] && tin[u] <\
    \ tout[v]) ret += weight[u];\n                    }\n                    return\
    \ ret;\n                };\n\n                for (int iter = 0; iter < 200; ++iter)\
    \ {\n                    int type = uniform_int_distribution<int>(0, 2)(rng);\n\
    \                    if (type == 0 && n >= 2) {\n                        int v\
    \ = uniform_int_distribution<int>(1, n - 1)(rng);\n                        aff[v]\
    \ = {uniform_int_distribution<int>(-3, 3)(rng), uniform_int_distribution<int>(-5,\
    \ 5)(rng)};\n                        weight[v] = uniform_int_distribution<int>(-10,\
    \ 10)(rng);\n                        int p = hld.edge_index(v);\n            \
    \            segl.update(p, aff[v]);\n                        segr.update(p, aff[v]);\n\
    \                        segsum.update(p, weight[v]);\n                    } else\
    \ if (type == 1) {\n                        int a = uniform_int_distribution<int>(0,\
    \ n - 1)(rng);\n                        int b = uniform_int_distribution<int>(0,\
    \ n - 1)(rng);\n                        auto got = hld.path_query_ordered(a, b,\
    \ Ml::e(), ql, qr, merge);\n                        auto expect = naive_path(a,\
    \ b);\n                        if (got != expect) return 1;\n                \
    \    } else {\n                        int v = uniform_int_distribution<int>(0,\
    \ n - 1)(rng);\n                        ll got = hld.subtree_query<ll>(v, [&](int\
    \ l, int r) { return segsum.query(l, r); });\n                        ll expect\
    \ = naive_subtree_sum(v);\n                        if (got != expect) return 1;\n\
    \                    }\n                }\n            }\n        }\n    }\n\n\
    \    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--)\
    \ {\n        long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <algorithm>\n#include <array>\n#include <limits>\n#include <random>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\nusing ll = long long;\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../tree/hld_edge.cpp\"\n#include\
    \ \"../datastructure/segtree.cpp\"\n\nstruct Ml {\n    using T = array<ll, 2>;\n\
    \    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n\nstruct Mr {\n    using T = array<ll, 2>;\n \
    \   static T f(T b, T a) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n\nstruct Sum {\n    using T = ll;\n    static\
    \ T f(T a, T b) { return a + b; }\n    static T e() { return 0; }\n};\n\nstatic\
    \ array<ll, 2> compose(array<ll, 2> a, array<ll, 2> b) {\n    return {a[0] * b[0],\
    \ a[1] * b[0] + b[1]};\n}\n\nint main() {\n    {\n        mt19937 rng(123456789);\n\
    \        for (int n = 1; n <= 50; ++n) {\n            for (int trial = 0; trial\
    \ < 150; ++trial) {\n                vector<vector<int>> g(n);\n             \
    \   for (int v = 1; v < n; ++v) {\n                    int p = uniform_int_distribution<int>(0,\
    \ v - 1)(rng);\n                    g[p].push_back(v);\n                    g[v].push_back(p);\n\
    \                }\n\n                vector<int> parent(n, -1), depth(n, 0),\
    \ order = {0};\n                for (int i = 0; i < n; ++i) {\n              \
    \      int v = order[i];\n                    for (auto &&u : g[v]) {\n      \
    \                  if (u == parent[v]) continue;\n                        parent[u]\
    \ = v;\n                        depth[u] = depth[v] + 1;\n                   \
    \     order.push_back(u);\n                    }\n                }\n\n      \
    \          HeavyLightDecompositionEdge hld(n);\n                for (int v = 0;\
    \ v < n; ++v) {\n                    for (auto &&u : g[v]) {\n               \
    \         if (v < u) hld.add_edge(v, u);\n                    }\n            \
    \    }\n                hld.build();\n\n                SegmentTree<Ml> segl(n);\n\
    \                SegmentTree<Mr> segr(n);\n                SegmentTree<Sum> segsum(n);\n\
    \                vector<array<ll, 2>> aff(n, {1, 0});\n                vector<ll>\
    \ weight(n, 0);\n                for (int v = 1; v < n; ++v) {\n             \
    \       aff[v] = {uniform_int_distribution<int>(-3, 3)(rng), uniform_int_distribution<int>(-5,\
    \ 5)(rng)};\n                    weight[v] = uniform_int_distribution<int>(-10,\
    \ 10)(rng);\n                }\n                for (int v = 0; v < n; ++v) {\n\
    \                    int p = hld.edge_index(v);\n                    if (p ==\
    \ -1) continue;\n                    segl.set(p, aff[v]);\n                  \
    \  segr.set(p, aff[v]);\n                    segsum.set(p, weight[v]);\n     \
    \           }\n                segl.build();\n                segr.build();\n\
    \                segsum.build();\n\n                auto ql = [&](int l, int r)\
    \ { return segl.query(l, r); };\n                auto qr = [&](int l, int r) {\
    \ return segr.query(l, r); };\n                auto merge = [&](Ml::T x, Ml::T\
    \ y) -> Ml::T { return compose(x, y); };\n\n                auto lca = [&](int\
    \ a, int b) {\n                    while (depth[a] > depth[b]) a = parent[a];\n\
    \                    while (depth[b] > depth[a]) b = parent[b];\n            \
    \        while (a != b) a = parent[a], b = parent[b];\n                    return\
    \ a;\n                };\n\n                auto naive_path = [&](int a, int b)\
    \ {\n                    int c = lca(a, b);\n                    vector<int> vs;\n\
    \                    for (int v = a; v != c; v = parent[v]) vs.push_back(v);\n\
    \                    vector<int> down;\n                    for (int v = b; v\
    \ != c; v = parent[v]) down.push_back(v);\n                    reverse(down.begin(),\
    \ down.end());\n                    for (auto &&v : down) vs.push_back(v);\n \
    \                   array<ll, 2> ret = {1, 0};\n                    for (auto\
    \ &&v : vs) ret = compose(ret, aff[v]);\n                    return ret;\n   \
    \             };\n\n                vector<int> tin(n), tout(n);\n           \
    \     int timer = 0;\n                auto dfs = [&](auto &&self, int v) -> void\
    \ {\n                    tin[v] = timer++;\n                    for (auto &&u\
    \ : g[v]) {\n                        if (u == parent[v]) continue;\n         \
    \               self(self, u);\n                    }\n                    tout[v]\
    \ = timer;\n                };\n                dfs(dfs, 0);\n\n             \
    \   auto naive_subtree_sum = [&](int v) {\n                    ll ret = 0;\n \
    \                   for (int u = 0; u < n; ++u) {\n                        if\
    \ (u == v) continue;\n                        if (tin[v] <= tin[u] && tin[u] <\
    \ tout[v]) ret += weight[u];\n                    }\n                    return\
    \ ret;\n                };\n\n                for (int iter = 0; iter < 200; ++iter)\
    \ {\n                    int type = uniform_int_distribution<int>(0, 2)(rng);\n\
    \                    if (type == 0 && n >= 2) {\n                        int v\
    \ = uniform_int_distribution<int>(1, n - 1)(rng);\n                        aff[v]\
    \ = {uniform_int_distribution<int>(-3, 3)(rng), uniform_int_distribution<int>(-5,\
    \ 5)(rng)};\n                        weight[v] = uniform_int_distribution<int>(-10,\
    \ 10)(rng);\n                        int p = hld.edge_index(v);\n            \
    \            segl.update(p, aff[v]);\n                        segr.update(p, aff[v]);\n\
    \                        segsum.update(p, weight[v]);\n                    } else\
    \ if (type == 1) {\n                        int a = uniform_int_distribution<int>(0,\
    \ n - 1)(rng);\n                        int b = uniform_int_distribution<int>(0,\
    \ n - 1)(rng);\n                        auto got = hld.path_query_ordered(a, b,\
    \ Ml::e(), ql, qr, merge);\n                        auto expect = naive_path(a,\
    \ b);\n                        if (got != expect) return 1;\n                \
    \    } else {\n                        int v = uniform_int_distribution<int>(0,\
    \ n - 1)(rng);\n                        ll got = hld.subtree_query<ll>(v, [&](int\
    \ l, int r) { return segsum.query(l, r); });\n                        ll expect\
    \ = naive_subtree_sum(v);\n                        if (got != expect) return 1;\n\
    \                    }\n                }\n            }\n        }\n    }\n\n\
    \    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--)\
    \ {\n        long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/hld_edge.cpp
  - tree/hld.cpp
  - datastructure/segtree.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_hld_edge.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 18:33:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_hld_edge.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_hld_edge.test.cpp
- /verify/test/yosupo_many_aplusb_hld_edge.test.cpp.html
title: test/yosupo_many_aplusb_hld_edge.test.cpp
---
