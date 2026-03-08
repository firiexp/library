---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/unionfind.cpp
    title: "UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/yosupo_unionfind.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#include <algorithm>\n#include <iomanip>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n#include <cstdint>\n\nstatic const int MOD = 1000000007;\nusing ll\
    \ = long long;\nusing uint = uint32_t;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"datastructure/unionfind.cpp\"\
    \nclass UnionFind {\n    int n;\n    vector<int> uni;\n    int forest_size;\n\
    public:\n    explicit UnionFind(int n) : n(n), uni(static_cast<uint>(n), -1),\
    \ forest_size(n) {};\n\n    int root(int a){\n        if (uni[a] < 0) return a;\n\
    \        else return (uni[a] = root(uni[a]));\n    }\n\n    bool unite(int a,\
    \ int b) {\n        a = root(a);\n        b = root(b);\n        if(a == b) return\
    \ false;\n        if(uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n\
    \        uni[b] = a;\n        forest_size--;\n        return true;\n    }\n  \
    \  int size(){ return forest_size; }\n    int size(int i){ return -uni[root(i)];\
    \ }\n    bool same(int a, int b) { return root(a) == root(b); }\n};\n\n/**\n *\
    \ @brief UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)\n * @docs\
    \ _md/unionfind.md\n */\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include\
    \ <cstring>\n#include <string>\n#include <type_traits>\nusing namespace std;\n\
    \nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n#line 23 \"\
    test/yosupo_unionfind.test.cpp\"\n\nint main() {\n    Scanner in;\n    Printer\
    \ out;\n    int n, q;\n    in.read(n);\n    in.read(q);\n    UnionFind uf(n);\n\
    \    for (int i = 0; i < q; ++i) {\n        int t, u, v;\n        in.read(t);\n\
    \        in.read(u);\n        in.read(v);\n        if(t) out.writeln(uf.same(u,\
    \ v));\n        else uf.unite(u, v);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <algorithm>\n#include <iomanip>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n#include\
    \ <cstdint>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = uint32_t;\nusing namespace std;\n\ntemplate<class T> constexpr T INF\
    \ = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../datastructure/unionfind.cpp\"\
    \n#include \"../util/fastio.cpp\"\n\nint main() {\n    Scanner in;\n    Printer\
    \ out;\n    int n, q;\n    in.read(n);\n    in.read(q);\n    UnionFind uf(n);\n\
    \    for (int i = 0; i < q; ++i) {\n        int t, u, v;\n        in.read(t);\n\
    \        in.read(u);\n        in.read(v);\n        if(t) out.writeln(uf.same(u,\
    \ v));\n        else uf.unite(u, v);\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/unionfind.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_unionfind.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 12:02:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_unionfind.test.cpp
- /verify/test/yosupo_unionfind.test.cpp.html
title: test/yosupo_unionfind.test.cpp
---
