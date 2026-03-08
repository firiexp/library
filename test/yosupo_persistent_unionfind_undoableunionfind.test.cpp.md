---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/undoableunionfind.cpp
    title: Undoable Union Find
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
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"test/yosupo_persistent_unionfind_undoableunionfind.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n\
    #include <bits/stdc++.h>\n\nusing namespace std;\n\n#line 4 \"util/fastio.cpp\"\
    \n#include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable {\n\
    \    char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for\
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
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/undoableunionfind.cpp\"\
    \nclass UndoableUnionFind {\n    stack<pair<int, int>> hist;\n    int forest_size;\n\
    \    int snap;\n\npublic:\n    vector<int> uni;\n\n    explicit UndoableUnionFind(int\
    \ sz) : forest_size(sz), snap(0), uni(sz, -1) {}\n\n    int root(int a) {\n  \
    \      if (uni[a] < 0) return a;\n        return root(uni[a]);\n    }\n\n    bool\
    \ same(int a, int b) {\n        return root(a) == root(b);\n    }\n\n    bool\
    \ unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n        hist.emplace(a,\
    \ uni[a]);\n        hist.emplace(b, uni[b]);\n        if (a == b) return false;\n\
    \        if (uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n       \
    \ uni[b] = a;\n        forest_size--;\n        return true;\n    }\n\n    int\
    \ size() { return forest_size; }\n    int size(int i) { return -uni[root(i)];\
    \ }\n\n    int get_state() const {\n        return int(hist.size() >> 1);\n  \
    \  }\n\n    void undo() {\n        int a = hist.top().first;\n        int ua =\
    \ hist.top().second;\n        hist.pop();\n        int b = hist.top().first;\n\
    \        int ub = hist.top().second;\n        hist.pop();\n        if (a != b)\
    \ forest_size++;\n        uni[a] = ua;\n        uni[b] = ub;\n    }\n\n    void\
    \ snapshot() {\n        snap = get_state();\n    }\n\n    void rollback(int state\
    \ = -1) {\n        if (state == -1) state = snap;\n        while (get_state()\
    \ > state) undo();\n    }\n};\n\n/**\n * @brief Undoable Union Find\n */\n#line\
    \ 9 \"test/yosupo_persistent_unionfind_undoableunionfind.test.cpp\"\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n \
    \   using A = array<int, 4>;\n    vector<vector<A>> g(q + 1);\n    vector<int>\
    \ ans(q + 1, -1);\n    for (int i = 1; i <= q; ++i) {\n        int t, k, u, v;\n\
    \        sc.read(t, k, u, v);\n        ++k;\n        g[k].push_back({t, i, u,\
    \ v});\n    }\n\n    UndoableUnionFind uf(n);\n    auto dfs = [&](auto &&f, A\
    \ cur) -> void {\n        int t = cur[0], idx = cur[1], u = cur[2], v = cur[3];\n\
    \        if (t == 1) {\n            ans[idx] = uf.same(u, v);\n            return;\n\
    \        }\n        if (t == 0) uf.unite(u, v);\n        for (auto &&nxt : g[idx])\
    \ f(f, nxt);\n        if (t == 0) uf.undo();\n    };\n    dfs(dfs, A{-1, 0, -1,\
    \ -1});\n\n    for (int i = 1; i <= q; ++i) {\n        if (ans[i] != -1) pr.writeln(ans[i]);\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../datastructure/undoableunionfind.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    using A = array<int,\
    \ 4>;\n    vector<vector<A>> g(q + 1);\n    vector<int> ans(q + 1, -1);\n    for\
    \ (int i = 1; i <= q; ++i) {\n        int t, k, u, v;\n        sc.read(t, k, u,\
    \ v);\n        ++k;\n        g[k].push_back({t, i, u, v});\n    }\n\n    UndoableUnionFind\
    \ uf(n);\n    auto dfs = [&](auto &&f, A cur) -> void {\n        int t = cur[0],\
    \ idx = cur[1], u = cur[2], v = cur[3];\n        if (t == 1) {\n            ans[idx]\
    \ = uf.same(u, v);\n            return;\n        }\n        if (t == 0) uf.unite(u,\
    \ v);\n        for (auto &&nxt : g[idx]) f(f, nxt);\n        if (t == 0) uf.undo();\n\
    \    };\n    dfs(dfs, A{-1, 0, -1, -1});\n\n    for (int i = 1; i <= q; ++i) {\n\
    \        if (ans[i] != -1) pr.writeln(ans[i]);\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/undoableunionfind.cpp
  isVerificationFile: true
  path: test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
- /verify/test/yosupo_persistent_unionfind_undoableunionfind.test.cpp.html
title: test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
---
