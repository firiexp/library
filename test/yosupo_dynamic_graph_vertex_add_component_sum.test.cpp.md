---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dynamic_graph_vertex_add_component_sum.cpp
    title: "\u52D5\u7684\u30B0\u30E9\u30D5\u9023\u7D50\u6210\u5206\u548C(Dynamic Graph\
      \ Vertex Add Component Sum)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
  bundledCode: "#line 1 \"test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n\n#include <algorithm>\n#include <map>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    struct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load() {\n  \
    \      int len = size - idx;\n        memmove(buf, buf + idx, len);\n        size\
    \ = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n\
    \        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if (idx\
    \ + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
    \        write_range(s.data(), s.size());\n    }\n\n    void write(char c) {\n\
    \        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void write(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line\
    \ 1 \"graph/dynamic_graph_vertex_add_component_sum.cpp\"\nusing namespace std;\n\
    \nstruct RollbackUnionFindComponentSum {\n    struct History {\n        int child,\
    \ parent;\n        int parent_size, child_size;\n        long long parent_sum,\
    \ child_sum;\n    };\n\n    vector<int> parent_or_size;\n    vector<long long>\
    \ comp_sum;\n    vector<History> history;\n\n    explicit RollbackUnionFindComponentSum(int\
    \ n, const vector<long long> &a)\n        : parent_or_size(n, -1), comp_sum(a)\
    \ {}\n\n    int root(int v) const {\n        while (parent_or_size[v] >= 0) v\
    \ = parent_or_size[v];\n        return v;\n    }\n\n    int snapshot() const {\n\
    \        return (int)history.size();\n    }\n\n    void rollback(int snap) {\n\
    \        while ((int)history.size() > snap) {\n            auto h = history.back();\n\
    \            history.pop_back();\n            if (h.parent == -1) continue;\n\
    \            parent_or_size[h.parent] = h.parent_size;\n            parent_or_size[h.child]\
    \ = h.child_size;\n            comp_sum[h.parent] = h.parent_sum;\n          \
    \  comp_sum[h.child] = h.child_sum;\n        }\n    }\n\n    void unite(int a,\
    \ int b) {\n        a = root(a), b = root(b);\n        if (a == b) {\n       \
    \     history.push_back({-1, -1, 0, 0, 0, 0});\n            return;\n        }\n\
    \        if (parent_or_size[a] > parent_or_size[b]) swap(a, b);\n        history.push_back({b,\
    \ a, parent_or_size[a], parent_or_size[b], comp_sum[a], comp_sum[b]});\n     \
    \   parent_or_size[a] += parent_or_size[b];\n        parent_or_size[b] = a;\n\
    \        comp_sum[a] += comp_sum[b];\n    }\n\n    void add_value(int v, long\
    \ long x) {\n        int r = root(v);\n        history.push_back({r, r, parent_or_size[r],\
    \ parent_or_size[r], comp_sum[r], comp_sum[r]});\n        comp_sum[r] += x;\n\
    \    }\n\n    long long get_sum(int v) const {\n        return comp_sum[root(v)];\n\
    \    }\n};\n\nstruct DynamicGraphVertexAddComponentSum {\n    struct Query {\n\
    \        int type, u, v;\n        long long x;\n    };\n    struct EdgeEvent {\n\
    \        int u, v;\n    };\n    struct AddEvent {\n        int v;\n        long\
    \ long x;\n    };\n\n    int n, q, sz;\n    vector<Query> queries;\n    vector<vector<EdgeEvent>>\
    \ seg_edges;\n    vector<vector<AddEvent>> seg_adds;\n    vector<long long> initial;\n\
    \n    DynamicGraphVertexAddComponentSum(const vector<long long> &a, int q)\n \
    \       : n((int)a.size()), q(q), initial(a) {\n        sz = 1;\n        while\
    \ (sz < q) sz <<= 1;\n        seg_edges.resize(2 * sz);\n        seg_adds.resize(2\
    \ * sz);\n        queries.reserve(q);\n    }\n\n    void add_edge(int u, int v)\
    \ {\n        queries.push_back({0, u, v, 0});\n    }\n\n    void erase_edge(int\
    \ u, int v) {\n        queries.push_back({1, u, v, 0});\n    }\n\n    void add_vertex(int\
    \ v, long long x) {\n        queries.push_back({2, v, 0, x});\n    }\n\n    void\
    \ add_component_query(int v) {\n        queries.push_back({3, v, 0, 0});\n   \
    \ }\n\n    template<class T>\n    void add_segment(vector<vector<T>> &seg, int\
    \ l, int r, const T &event) {\n        for (l += sz, r += sz; l < r; l >>= 1,\
    \ r >>= 1) {\n            if (l & 1) seg[l++].push_back(event);\n            if\
    \ (r & 1) seg[--r].push_back(event);\n        }\n    }\n\n    vector<long long>\
    \ solve() {\n        map<pair<int, int>, int> appear;\n        for (int t = 0;\
    \ t < q; ++t) {\n            auto query = queries[t];\n            if (query.type\
    \ == 0) {\n                appear[minmax(query.u, query.v)] = t;\n           \
    \ } else if (query.type == 1) {\n                auto e = minmax(query.u, query.v);\n\
    \                add_segment(seg_edges, appear[e], t, {e.first, e.second});\n\
    \                appear.erase(e);\n            } else if (query.type == 2) {\n\
    \                add_segment(seg_adds, t, q, {query.u, query.x});\n          \
    \  }\n        }\n        for (auto &&[e, l] : appear) add_segment(seg_edges, l,\
    \ q, {e.first, e.second});\n\n        RollbackUnionFindComponentSum uf(n, initial);\n\
    \        vector<long long> ans;\n        ans.reserve(q);\n        auto dfs = [&](auto\
    \ &&self, int k) -> void {\n            int snap = uf.snapshot();\n          \
    \  for (auto &&e : seg_edges[k]) uf.unite(e.u, e.v);\n            for (auto &&a\
    \ : seg_adds[k]) uf.add_value(a.v, a.x);\n            if (k < sz) {\n        \
    \        self(self, k << 1);\n                self(self, k << 1 | 1);\n      \
    \      } else {\n                int t = k - sz;\n                if (t < q &&\
    \ queries[t].type == 3) ans.push_back(uf.get_sum(queries[t].u));\n           \
    \ }\n            uf.rollback(snap);\n        };\n        dfs(dfs, 1);\n      \
    \  return ans;\n    }\n};\n\n/**\n * @brief \u52D5\u7684\u30B0\u30E9\u30D5\u9023\
    \u7D50\u6210\u5206\u548C(Dynamic Graph Vertex Add Component Sum)\n */\n#line 16\
    \ \"test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp\"\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n \
    \   vector<long long> a(n);\n    for (auto &x : a) sc.read(x);\n\n    DynamicGraphVertexAddComponentSum\
    \ solver(a, q);\n    for (int i = 0; i < q; ++i) {\n        int t;\n        sc.read(t);\n\
    \        if (t == 0) {\n            int u, v;\n            sc.read(u, v);\n  \
    \          solver.add_edge(u, v);\n        } else if (t == 1) {\n            int\
    \ u, v;\n            sc.read(u, v);\n            solver.erase_edge(u, v);\n  \
    \      } else if (t == 2) {\n            int v;\n            long long x;\n  \
    \          sc.read(v, x);\n            solver.add_vertex(v, x);\n        } else\
    \ {\n            int v;\n            sc.read(v);\n            solver.add_component_query(v);\n\
    \        }\n    }\n\n    auto ans = solver.solve();\n    for (auto &&x : ans)\
    \ pr.writeln(x);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n\n#include <algorithm>\n#include <map>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../graph/dynamic_graph_vertex_add_component_sum.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n,\
    \ q);\n    vector<long long> a(n);\n    for (auto &x : a) sc.read(x);\n\n    DynamicGraphVertexAddComponentSum\
    \ solver(a, q);\n    for (int i = 0; i < q; ++i) {\n        int t;\n        sc.read(t);\n\
    \        if (t == 0) {\n            int u, v;\n            sc.read(u, v);\n  \
    \          solver.add_edge(u, v);\n        } else if (t == 1) {\n            int\
    \ u, v;\n            sc.read(u, v);\n            solver.erase_edge(u, v);\n  \
    \      } else if (t == 2) {\n            int v;\n            long long x;\n  \
    \          sc.read(v, x);\n            solver.add_vertex(v, x);\n        } else\
    \ {\n            int v;\n            sc.read(v);\n            solver.add_component_query(v);\n\
    \        }\n    }\n\n    auto ans = solver.solve();\n    for (auto &&x : ans)\
    \ pr.writeln(x);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/dynamic_graph_vertex_add_component_sum.cpp
  isVerificationFile: true
  path: test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
- /verify/test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp.html
title: test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
---
