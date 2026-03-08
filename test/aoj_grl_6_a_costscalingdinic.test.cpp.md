---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/costscalingdinic.cpp
    title: flow/costscalingdinic.cpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A
  bundledCode: "#line 1 \"test/aoj_grl_6_a_costscalingdinic.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A\"\n\n#include <algorithm>\n\
    #include <limits>\n#include <queue>\n#include <vector>\nusing namespace std;\n\
    \nusing ll = long long;\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n#line 1 \"\
    flow/costscalingdinic.cpp\"\ntemplate<class T, bool directed>\nclass CostScalingDinic\
    \ {\n    void bfs(int s, T x){\n        fill(level.begin(),level.end(), -1);\n\
    \        queue<int> Q;\n        level[s] = 0;\n        Q.emplace(s);\n       \
    \ while(!Q.empty()){\n            int v = Q.front(); Q.pop();\n            for\
    \ (auto &&e : G[v]){\n                if(e.cap >= x && level[e.to] < 0){\n   \
    \                 level[e.to] = level[v] + 1;\n                    Q.emplace(e.to);\n\
    \                }\n            }\n        }\n    }\n\n    T dfs(int v, int t,\
    \ T x, T f){\n        if(v == t) return f;\n        T res = 0;\n        for(int\
    \ &i = iter[v]; i < G[v].size(); i++){\n            edge &e = G[v][i];\n     \
    \       if(e.cap >= x && level[v] < level[e.to]){\n                T d = dfs(e.to,\
    \ t, x, min(f-res,  e.cap));\n                if(d == 0) continue;\n         \
    \       e.cap -= d;\n                G[e.to][e.rev].cap += d;\n              \
    \  res += d;\n                if(f - res < x) break;\n            }\n        }\n\
    \        return res;\n    }\npublic:\n    struct edge {\n        int to{}; T cap;\
    \ int rev{};\n        edge() = default;\n        edge(int to, T cap, int rev)\
    \ : to(to), cap(cap), rev(rev) {}\n    };\n\n    vector<vector<edge>> G;\n   \
    \ vector<int> level, iter;\n    CostScalingDinic() = default;\n    explicit CostScalingDinic(int\
    \ n) : G(n), level(n), iter(n) {}\n\n    void add_edge(int from, int to, int cap){\n\
    \        if(!cap) return;\n        G[from].emplace_back(to, cap, G[to].size());\n\
    \        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);\n  \
    \  }\n\n    T flow(int s, int t, T lim = INF<T>){\n        T ret = 0;\n      \
    \  T cap = 1; while(cap<<1 <= lim) cap <<= 1;\n        while(cap) {\n        \
    \    bfs(s, cap);\n            if(level[t] < 0){\n                cap >>= 1;\n\
    \                continue;\n            }\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            ret += dfs(s, t, cap, INF<T>);\n        }\n        return ret;\n\
    \    }\n};\n#line 14 \"test/aoj_grl_6_a_costscalingdinic.test.cpp\"\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n\n    int n, m;\n    sc.read(n, m);\n \
    \   CostScalingDinic<int, true> mf(n);\n    for (int i = 0; i < m; ++i) {\n  \
    \      int u, v, c;\n        sc.read(u, v, c);\n        mf.add_edge(u, v, c);\n\
    \    }\n    pr.writeln(mf.flow(0, n - 1));\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A\"\n\n\
    #include <algorithm>\n#include <limits>\n#include <queue>\n#include <vector>\n\
    using namespace std;\n\nusing ll = long long;\ntemplate<class T> constexpr T INF\
    \ = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../flow/costscalingdinic.cpp\"\n\nint main() {\n    Scanner sc;\n\
    \    Printer pr;\n\n    int n, m;\n    sc.read(n, m);\n    CostScalingDinic<int,\
    \ true> mf(n);\n    for (int i = 0; i < m; ++i) {\n        int u, v, c;\n    \
    \    sc.read(u, v, c);\n        mf.add_edge(u, v, c);\n    }\n    pr.writeln(mf.flow(0,\
    \ n - 1));\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - flow/costscalingdinic.cpp
  isVerificationFile: true
  path: test/aoj_grl_6_a_costscalingdinic.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 15:06:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_grl_6_a_costscalingdinic.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_grl_6_a_costscalingdinic.test.cpp
- /verify/test/aoj_grl_6_a_costscalingdinic.test.cpp.html
title: test/aoj_grl_6_a_costscalingdinic.test.cpp
---
