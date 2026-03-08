---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
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
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/yosupo_staticrmq_sparsetable.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include <bits/stdc++.h>\n\n\
    using namespace std;\n\n#line 4 \"util/fastio.cpp\"\n#include <type_traits>\n\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 1 \"datastructure/sparsetable.cpp\"\ntemplate <class F>\nstruct SparseTable\
    \ {\n    using T = typename F::T;\n    vector<vector<T>> table;\n    vector<int>\
    \ u;\n    SparseTable() = default;\n    explicit SparseTable(const vector<T> &v){\
    \ build(v); }\n \n    void build(const vector<T> &v){\n        int n = v.size(),\
    \ m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m, vector<T>(n));\n\
    \        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i) {\n         \
    \   u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n; ++i) {\n  \
    \          table[0][i] = v[i];\n        }\n        for (int i = 1; i < m; ++i)\
    \ {\n            int x = (1<<(i-1));\n            for (int j = 0; j < n; ++j)\
    \ {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x, n-1)]);\n\
    \            }\n        }\n    }\n \n    T query(int a, int b){\n        int l\
    \ = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n   \
    \ }\n};\n\n/**\n * @brief Sparse Table\n * @docs _md/sparsetable.md\n */\n#line\
    \ 9 \"test/yosupo_staticrmq_sparsetable.test.cpp\"\n\nstruct F {\n    using T\
    \ = int;\n    static T f(T a, T b) { return min(a, b); }\n};\n\nint main() {\n\
    \    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<int>\
    \ a(n);\n    for (auto &&x : a) sc.read(x);\n\n    SparseTable<F> st(a);\n   \
    \ while (q--) {\n        int l, r;\n        sc.read(l, r);\n        pr.writeln(st.query(l,\
    \ r));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ <bits/stdc++.h>\n\nusing namespace std;\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/sparsetable.cpp\"\n\nstruct F {\n    using T = int;\n\
    \    static T f(T a, T b) { return min(a, b); }\n};\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<int> a(n);\n\
    \    for (auto &&x : a) sc.read(x);\n\n    SparseTable<F> st(a);\n    while (q--)\
    \ {\n        int l, r;\n        sc.read(l, r);\n        pr.writeln(st.query(l,\
    \ r));\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/sparsetable.cpp
  isVerificationFile: true
  path: test/yosupo_staticrmq_sparsetable.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_staticrmq_sparsetable.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_staticrmq_sparsetable.test.cpp
- /verify/test/yosupo_staticrmq_sparsetable.test.cpp.html
title: test/yosupo_staticrmq_sparsetable.test.cpp
---
