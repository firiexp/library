---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: tree/LCA.cpp
    title: "\u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)"
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
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/yosupo_lca.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \n\n#include <bits/stdc++.h>\n\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#line 12 \"test/yosupo_lca.test.cpp\"\
    \n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\
    \nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
    \n    constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0),\
    \ size(0), interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n\
    \        int len = size - idx;\n        memmove(buf, buf + idx, len);\n      \
    \  if (interactive) {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin))\
    \ size = len + (int)strlen(buf + len);\n            else size = len;\n       \
    \ } else {\n            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void\
    \ ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void\
    \ ensure_interactive() {\n        if (idx == size) load();\n    }\n\n    inline\
    \ char skip() {\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            return buf[idx++];\n\
    \        }\n        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n\
    \            ++idx;\n            ensure();\n        }\n        return buf[idx++];\n\
    \    }\n\n    template<class T, typename enable_if<is_integral<T>::value, int>::type\
    \ = 0>\n    void read(T &x) {\n        if (interactive) {\n            char c\
    \ = skip();\n            bool neg = false;\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    neg = true;\n      \
    \              ensure_interactive();\n                    c = buf[idx++];\n  \
    \              }\n            }\n            x = 0;\n            while (c >= '0')\
    \ {\n                x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class Next, class... Tail>\n    void read(Head &head, Next &next, Tail &...tail)\
    \ {\n        read(head);\n        read(next, tail...);\n    }\n\n    template<class\
    \ T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void write_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n \
    \       write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
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
    \ T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type,\
    \ string>::value, int>::type = 0>\n    void write(const T &a) {\n        bool\
    \ first = true;\n        for (auto &&x : a) {\n            if (!first) pc(' ');\n\
    \            first = false;\n            write(x);\n        }\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner &in, T &x) {\n  \
    \  in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter &operator<<(Printer\
    \ &out, const T &x) {\n    out.write(x);\n    return out;\n}\n\n/**\n * @brief\
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/sparsetable.cpp\"\
    \ntemplate <class F>\nstruct SparseTable {\n    using T = typename F::T;\n   \
    \ vector<vector<T>> table;\n    vector<int> u;\n    SparseTable() = default;\n\
    \    explicit SparseTable(const vector<T> &v){ build(v); }\n \n    void build(const\
    \ vector<T> &v){\n        int n = v.size(), m = 1;\n        while((1<<m) <= n)\
    \ m++;\n        table.assign(m, vector<T>(n));\n        u.assign(n+1, 0);\n  \
    \      for (int i = 2; i <= n; ++i) {\n            u[i] = u[i>>1] + 1;\n     \
    \   }\n        for (int i = 0; i < n; ++i) {\n            table[0][i] = v[i];\n\
    \        }\n        for (int i = 1; i < m; ++i) {\n            int x = (1<<(i-1));\n\
    \            for (int j = 0; j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j],\
    \ table[i-1][min(j+x, n-1)]);\n            }\n        }\n    }\n \n    T query(int\
    \ a, int b){\n        int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n#line 2 \"tree/LCA.cpp\"\n\nstruct\
    \ LCA_MinDepth {\n    using T = pair<int, int>;\n    static T f(T a, T b) { return\
    \ min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\nclass LCA\
    \ {\n    SparseTable<LCA_MinDepth> table;\n\n    void dfs_euler(int v, int p,\
    \ int d, int &k) {\n        id[v] = k;\n        vs[k] = v;\n        depth[k++]\
    \ = d;\n        for (auto &&u : G[v]) {\n            if (u == p) continue;\n \
    \           dfs_euler(u, v, d + 1, k);\n            vs[k] = v;\n            depth[k++]\
    \ = d;\n        }\n    }\n\npublic:\n    int n;\n    vector<vector<int>> G;\n\
    \    vector<int> vs, depth, id;\n\n    explicit LCA(int n) : table(), n(n), G(n),\
    \ vs(2 * n - 1), depth(2 * n - 1), id(n) {}\n\n    void add_edge(int a, int b)\
    \ {\n        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n    }\n\n \
    \   void eulertour(int root = 0) {\n        int k = 0;\n        dfs_euler(root,\
    \ -1, 0, k);\n    }\n\n    void build(int root = 0) {\n        eulertour(root);\n\
    \        vector<pair<int, int>> v(2 * n - 1);\n        for (int i = 0; i < 2 *\
    \ n - 1; ++i) {\n            v[i] = make_pair(depth[i], i);\n        }\n     \
    \   table.build(v);\n    }\n\n    void buildLCA(int root = 0) {\n        build(root);\n\
    \    }\n\n    int lca(int u, int v) {\n        if (id[u] > id[v]) swap(u, v);\n\
    \        return vs[table.query(id[u], id[v] + 1).second];\n    }\n};\n\n/**\n\
    \ * @brief \u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)\n */\n#line 16 \"test/yosupo_lca.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n,\
    \ q);\n    LCA lca(n);\n    for (int v = 1; v < n; ++v) {\n        int p;\n  \
    \      sc.read(p);\n        lca.add_edge(p, v);\n    }\n    lca.build(0);\n\n\
    \    while (q--) {\n        int u, v;\n        sc.read(u, v);\n        pr.writeln(lca.lca(u,\
    \ v));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <bits/stdc++.h>\n\
    \nusing namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../tree/LCA.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n,\
    \ q);\n    LCA lca(n);\n    for (int v = 1; v < n; ++v) {\n        int p;\n  \
    \      sc.read(p);\n        lca.add_edge(p, v);\n    }\n    lca.build(0);\n\n\
    \    while (q--) {\n        int u, v;\n        sc.read(u, v);\n        pr.writeln(lca.lca(u,\
    \ v));\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/LCA.cpp
  - datastructure/sparsetable.cpp
  isVerificationFile: true
  path: test/yosupo_lca.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_lca.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_lca.test.cpp
- /verify/test/yosupo_lca.test.cpp.html
title: test/yosupo_lca.test.cpp
---
