---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/kruskal.cpp
    title: "Kruskal\u6CD5"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/minimum_spanning_tree
    links:
    - https://judge.yosupo.jp/problem/minimum_spanning_tree
  bundledCode: "#line 1 \"test/yosupo_minimum_spanning_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/minimum_spanning_tree\"\n\n#include <algorithm>\n\
    #include <vector>\nusing namespace std;\n\nusing ll = long long;\n\n#line 1 \"\
    util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable {\n  \
    \  char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for\
    \ (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int\
    \ j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n\
    \                x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner\
    \ {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner() : idx(0),\
    \ size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n    \
    \    memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf + len,\
    \ 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n    }\n\
    \n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\
    \n    inline char skip() {\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        return\
    \ buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
    \ int>::type = 0>\n    void read(T &x) {\n        char c = skip();\n        bool\
    \ neg = false;\n        if constexpr (is_signed<T>::value) {\n            if (c\
    \ == '-') {\n                neg = true;\n                c = buf[idx++];\n  \
    \          }\n        }\n        x = 0;\n        while (c >= '0') {\n        \
    \    x = x * 10 + (c & 15);\n            c = buf[idx++];\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg) x = -x;\n        }\n\
    \    }\n\n    template<class Head, class... Tail>\n    void read(Head &head, Tail\
    \ &...tail) {\n        read(head);\n        (read(tail), ...);\n    }\n\n    void\
    \ read(char &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n\
    \        s.clear();\n        ensure();\n        while (buf[idx] && buf[idx] <=\
    \ ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 1 \"graph/kruskal.cpp\"\ntemplate <class T>\nstruct edge {\n    int from,\
    \ to, idx;\n    T cost;\n\n    edge(int from, int to, T cost, int idx = -1) :\
    \ from(from), to(to), idx(idx), cost(cost) {}\n};\n\nclass KruskalUnionFind {\n\
    \    vector<int> p;\n\npublic:\n    explicit KruskalUnionFind(int n) : p(n, -1)\
    \ {}\n\n    int root(int x) {\n        if (p[x] < 0) return x;\n        return\
    \ p[x] = root(p[x]);\n    }\n\n    bool unite(int a, int b) {\n        a = root(a);\n\
    \        b = root(b);\n        if (a == b) return false;\n        if (p[a] > p[b])\
    \ swap(a, b);\n        p[a] += p[b];\n        p[b] = a;\n        return true;\n\
    \    }\n};\n\ntemplate <class T>\nstruct KruskalResult {\n    bool exists;\n \
    \   T cost;\n    vector<int> edge_id;\n};\n\ntemplate <class T>\nKruskalResult<T>\
    \ kruskal(vector<edge<T>> edges, int n) {\n    for (int i = 0; i < (int)edges.size();\
    \ ++i) {\n        if (edges[i].idx == -1) edges[i].idx = i;\n    }\n    sort(edges.begin(),\
    \ edges.end(), [](const edge<T> &a, const edge<T> &b) {\n        if (a.cost !=\
    \ b.cost) return a.cost < b.cost;\n        return a.idx < b.idx;\n    });\n\n\
    \    KruskalUnionFind uf(n);\n    T cost = T(0);\n    vector<int> edge_id;\n \
    \   edge_id.reserve(max(0, n - 1));\n    for (auto &&e : edges) {\n        if\
    \ (!uf.unite(e.from, e.to)) continue;\n        cost += e.cost;\n        edge_id.push_back(e.idx);\n\
    \    }\n    if ((int)edge_id.size() != max(0, n - 1)) return {false, T(0), {}};\n\
    \    return {true, cost, edge_id};\n}\n\n/**\n * @brief Kruskal\u6CD5\n * @docs\
    \ _md/kruskal.md\n */\n#line 11 \"test/yosupo_minimum_spanning_tree.test.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n\n    int n, m;\n    in.read(n,\
    \ m);\n    vector<edge<ll>> edges;\n    edges.reserve(m);\n    for (int i = 0;\
    \ i < m; ++i) {\n        int u, v;\n        ll w;\n        in.read(u, v, w);\n\
    \        edges.emplace_back(u, v, w, i);\n    }\n    auto res = kruskal(edges,\
    \ n);\n    if (!res.exists) return 0;\n    out.writeln(res.cost);\n    for (int\
    \ i = 0; i < (int)res.edge_id.size(); ++i) {\n        if (i) out.write(' ');\n\
    \        out.write(res.edge_id[i]);\n    }\n    out.writeln();\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/minimum_spanning_tree\"\
    \n\n#include <algorithm>\n#include <vector>\nusing namespace std;\n\nusing ll\
    \ = long long;\n\n#include \"../util/fastio.cpp\"\n#include \"../graph/kruskal.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n\n    int n, m;\n    in.read(n,\
    \ m);\n    vector<edge<ll>> edges;\n    edges.reserve(m);\n    for (int i = 0;\
    \ i < m; ++i) {\n        int u, v;\n        ll w;\n        in.read(u, v, w);\n\
    \        edges.emplace_back(u, v, w, i);\n    }\n    auto res = kruskal(edges,\
    \ n);\n    if (!res.exists) return 0;\n    out.writeln(res.cost);\n    for (int\
    \ i = 0; i < (int)res.edge_id.size(); ++i) {\n        if (i) out.write(' ');\n\
    \        out.write(res.edge_id[i]);\n    }\n    out.writeln();\n    return 0;\n\
    }\n"
  dependsOn:
  - util/fastio.cpp
  - graph/kruskal.cpp
  isVerificationFile: true
  path: test/yosupo_minimum_spanning_tree.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_minimum_spanning_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_minimum_spanning_tree.test.cpp
- /verify/test/yosupo_minimum_spanning_tree.test.cpp.html
title: test/yosupo_minimum_spanning_tree.test.cpp
---
