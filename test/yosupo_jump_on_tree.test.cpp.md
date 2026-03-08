---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/jump_on_tree.cpp
    title: Jump on Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/jump_on_tree
    links:
    - https://judge.yosupo.jp/problem/jump_on_tree
  bundledCode: "#line 1 \"test/yosupo_jump_on_tree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/jump_on_tree\"\n\n#include <algorithm>\n#include\
    \ <queue>\n#include <random>\n#include <vector>\nusing namespace std;\n\n#line\
    \ 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
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
    \ (true) {\n            int start = idx;\n            while (buf[idx] > ' ') ++idx;\n\
    \            s.append(buf + start, idx - start);\n            if (buf[idx] <=\
    \ ' ') break;\n            load();\n        }\n        ++idx;\n    }\n};\n\nstruct\
    \ Printer {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr\
    \ FastIoDigitTable table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush();\
    \ }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n    }\n\n    inline void write_range(const char *s, size_t n) {\n    \
    \    size_t pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE)\
    \ flush();\n            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n\
    \            memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n\
    \            pos += chunk;\n        }\n    }\n\n    void write(const char *s)\
    \ {\n        write_range(s, strlen(s));\n    }\n\n    void write(const string\
    \ &s) {\n        write_range(s.data(), s.size());\n    }\n\n    void write(char\
    \ c) {\n        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0'\
    \ + (b ? 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
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
    \    }\n};\n#line 1 \"tree/jump_on_tree.cpp\"\nclass JumpOnTree {\n    int logn;\n\
    \    vector<vector<int>> up;\n\npublic:\n    int n;\n    vector<vector<int>> G;\n\
    \    vector<int> depth;\n\n    explicit JumpOnTree(int n) : logn(0), n(n), G(n),\
    \ depth(n, -1) {}\n\n    void add_edge(int u, int v) {\n        G[u].emplace_back(v);\n\
    \        G[v].emplace_back(u);\n    }\n\n    void build(int root = 0) {\n    \
    \    logn = 1;\n        while ((1 << logn) <= n) ++logn;\n        up.assign(logn,\
    \ vector<int>(n, -1));\n        vector<int> st = {root};\n        depth[root]\
    \ = 0;\n        while (!st.empty()) {\n            int v = st.back();\n      \
    \      st.pop_back();\n            for (int to : G[v]) {\n                if (to\
    \ == up[0][v]) continue;\n                up[0][to] = v;\n                depth[to]\
    \ = depth[v] + 1;\n                st.push_back(to);\n            }\n        }\n\
    \        for (int k = 0; k + 1 < logn; ++k) {\n            for (int v = 0; v <\
    \ n; ++v) {\n                int p = up[k][v];\n                up[k + 1][v] =\
    \ (p == -1 ? -1 : up[k][p]);\n            }\n        }\n    }\n\n    int ancestor(int\
    \ v, int k) const {\n        if (k > depth[v]) return -1;\n        for (int i\
    \ = 0; i < logn; ++i) {\n            if (k >> i & 1) v = up[i][v];\n        }\n\
    \        return v;\n    }\n\n    int lca(int u, int v) const {\n        if (depth[u]\
    \ < depth[v]) swap(u, v);\n        u = ancestor(u, depth[u] - depth[v]);\n   \
    \     if (u == v) return u;\n        for (int k = logn - 1; k >= 0; --k) {\n \
    \           if (up[k][u] == up[k][v]) continue;\n            u = up[k][u];\n \
    \           v = up[k][v];\n        }\n        return up[0][u];\n    }\n\n    int\
    \ dist(int u, int v) const {\n        int w = lca(u, v);\n        return depth[u]\
    \ + depth[v] - 2 * depth[w];\n    }\n\n    int jump(int s, int t, int k) const\
    \ {\n        int w = lca(s, t);\n        int a = depth[s] - depth[w];\n      \
    \  int b = depth[t] - depth[w];\n        if (k > a + b) return -1;\n        if\
    \ (k <= a) return ancestor(s, k);\n        return ancestor(t, a + b - k);\n  \
    \  }\n};\n\n/**\n * @brief Jump on Tree\n * @docs _md/jump_on_tree.md\n */\n#line\
    \ 11 \"test/yosupo_jump_on_tree.test.cpp\"\n\nint main() {\n    Scanner sc;\n\
    \    Printer pr;\n    int n, q;\n    sc.read(n, q);\n    JumpOnTree jt(n);\n \
    \   for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        sc.read(u, v);\n\
    \        jt.add_edge(u, v);\n    }\n    jt.build(0);\n    while (q--) {\n    \
    \    int s, t, k;\n        sc.read(s, t, k);\n        pr.writeln(jt.jump(s, t,\
    \ k));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n\n#include\
    \ <algorithm>\n#include <queue>\n#include <random>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../util/fastio.cpp\"\n#include \"../tree/jump_on_tree.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n    JumpOnTree jt(n);\n    for (int i = 0; i < n - 1; ++i) {\n        int\
    \ u, v;\n        sc.read(u, v);\n        jt.add_edge(u, v);\n    }\n    jt.build(0);\n\
    \    while (q--) {\n        int s, t, k;\n        sc.read(s, t, k);\n        pr.writeln(jt.jump(s,\
    \ t, k));\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/jump_on_tree.cpp
  isVerificationFile: true
  path: test/yosupo_jump_on_tree.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 19:26:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_jump_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_jump_on_tree.test.cpp
- /verify/test/yosupo_jump_on_tree.test.cpp.html
title: test/yosupo_jump_on_tree.test.cpp
---
