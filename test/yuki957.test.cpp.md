---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: flow/dinic.cpp
    title: "Dinic\u6CD5(Dinic)"
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
    PROBLEM: https://yukicoder.me/problems/no/957
    links:
    - https://yukicoder.me/problems/no/957
  bundledCode: "#line 1 \"test/yuki957.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/957\"\
    \n\n#include <algorithm>\n#include <limits>\n#include <queue>\n#include <vector>\n\
    using namespace std;\n\nusing ll = long long;\ntemplate<class T>\nconstexpr T\
    \ INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#line 1 \"util/fastio.cpp\"\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 1 \"flow/dinic.cpp\"\ntemplate<class T, bool directed>\nclass Dinic {\n\
    \    void bfs(int s){\n        fill(level.begin(),level.end(), -1);\n        queue<int>\
    \ Q;\n        level[s] = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n\
    \            int v = Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n\
    \                if(e.cap > 0 && level[e.to] < 0){\n                    level[e.to]\
    \ = level[v] + 1;\n                    Q.emplace(e.to);\n                }\n \
    \           }\n        }\n    }\n \n    T dfs(int v, int t, T f){\n        if(v\
    \ == t) return f;\n        for(int &i = iter[v]; i < G[v].size(); i++){\n    \
    \        edge &e = G[v][i];\n            if(e.cap > 0 && level[v] < level[e.to]){\n\
    \                T d = dfs(e.to, t, min(f,  e.cap));\n                if(d ==\
    \ 0) continue;\n                e.cap -= d;\n                G[e.to][e.rev].cap\
    \ += d;\n                return d;\n            }\n        }\n        return 0;\n\
    \    }\npublic:\n    struct edge {\n        int to{}; T cap; int rev{};\n    \
    \    edge() = default;\n        edge(int to, T cap, int rev) : to(to), cap(cap),\
    \ rev(rev) {}\n    };\n \n    vector<vector<edge>> G;\n    vector<int> level,\
    \ iter;\n    Dinic() = default;\n    explicit Dinic(int n) : G(n), level(n), iter(n)\
    \ {}\n \n    void add_edge(int from, int to, T cap){\n        G[from].emplace_back(to,\
    \ cap, G[to].size());\n        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);\n\
    \    }\n \n \n    T flow(int s, int t, T lim = INF<T>){\n        T ret = 0;\n\
    \        while(true) {\n            bfs(s);\n            if(level[t] < 0 || lim\
    \ == 0) break;\n            fill(iter.begin(),iter.end(), 0);\n            while(true){\n\
    \                T f = dfs(s, t, lim);\n                if(f == 0) break;\n  \
    \              ret += f;\n                lim -= f;\n            }\n        }\n\
    \        return ret;\n    }\n};\n\n/**\n * @brief Dinic\u6CD5(Dinic)\n * @docs\
    \ _md/dinic.md\n */\n#line 15 \"test/yuki957.test.cpp\"\n\nint main() {\n    Scanner\
    \ in;\n    Printer out;\n    int h, w;\n    in.read(h, w);\n\n    vector<vector<ll>>\
    \ g(h, vector<ll>(w));\n    for (int i = 0; i < h; ++i) {\n        for (int j\
    \ = 0; j < w; ++j) {\n            in.read(g[i][j]);\n        }\n    }\n    vector<ll>\
    \ row(h), col(w);\n    for (int i = 0; i < h; ++i) in.read(row[i]);\n    for (int\
    \ j = 0; j < w; ++j) in.read(col[j]);\n\n    int s = h + w;\n    int t = s + 1;\n\
    \    Dinic<ll, true> mf(h + w + 2);\n    ll base = 0;\n    auto add_cost_if_true\
    \ = [&](int v, ll cost) {\n        if (cost >= 0) mf.add_edge(s, v, cost);\n \
    \       else {\n            base += cost;\n            mf.add_edge(v, t, -cost);\n\
    \        }\n    };\n\n    for (int i = 0; i < h; ++i) {\n        ll cost = -row[i];\n\
    \        for (int j = 0; j < w; ++j) cost += g[i][j];\n        add_cost_if_true(i,\
    \ cost);\n    }\n    for (int j = 0; j < w; ++j) {\n        add_cost_if_true(h\
    \ + j, -col[j]);\n    }\n    for (int i = 0; i < h; ++i) {\n        for (int j\
    \ = 0; j < w; ++j) {\n            mf.add_edge(i, h + j, g[i][j]);\n        }\n\
    \    }\n\n    ll min_cost = base + mf.flow(s, t);\n    out.writeln(-min_cost);\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/957\"\n\n#include <algorithm>\n\
    #include <limits>\n#include <queue>\n#include <vector>\nusing namespace std;\n\
    \nusing ll = long long;\ntemplate<class T>\nconstexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include \"../util/fastio.cpp\"\n#include \"../flow/dinic.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n    int h, w;\n    in.read(h,\
    \ w);\n\n    vector<vector<ll>> g(h, vector<ll>(w));\n    for (int i = 0; i <\
    \ h; ++i) {\n        for (int j = 0; j < w; ++j) {\n            in.read(g[i][j]);\n\
    \        }\n    }\n    vector<ll> row(h), col(w);\n    for (int i = 0; i < h;\
    \ ++i) in.read(row[i]);\n    for (int j = 0; j < w; ++j) in.read(col[j]);\n\n\
    \    int s = h + w;\n    int t = s + 1;\n    Dinic<ll, true> mf(h + w + 2);\n\
    \    ll base = 0;\n    auto add_cost_if_true = [&](int v, ll cost) {\n       \
    \ if (cost >= 0) mf.add_edge(s, v, cost);\n        else {\n            base +=\
    \ cost;\n            mf.add_edge(v, t, -cost);\n        }\n    };\n\n    for (int\
    \ i = 0; i < h; ++i) {\n        ll cost = -row[i];\n        for (int j = 0; j\
    \ < w; ++j) cost += g[i][j];\n        add_cost_if_true(i, cost);\n    }\n    for\
    \ (int j = 0; j < w; ++j) {\n        add_cost_if_true(h + j, -col[j]);\n    }\n\
    \    for (int i = 0; i < h; ++i) {\n        for (int j = 0; j < w; ++j) {\n  \
    \          mf.add_edge(i, h + j, g[i][j]);\n        }\n    }\n\n    ll min_cost\
    \ = base + mf.flow(s, t);\n    out.writeln(-min_cost);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - flow/dinic.cpp
  isVerificationFile: true
  path: test/yuki957.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yuki957.test.cpp
layout: document
redirect_from:
- /verify/test/yuki957.test.cpp
- /verify/test/yuki957.test.cpp.html
title: test/yuki957.test.cpp
---
