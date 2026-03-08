---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: tree/tree_center.cpp
    title: Tree Center
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_tree_center.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <algorithm>\n\
    #include <queue>\n#include <random>\n#include <vector>\nusing namespace std;\n\
    \n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable\
    \ {\n    char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n    \
    \    for (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for\
    \ (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x %\
    \ 10);\n                x /= 10;\n            }\n        }\n    }\n};\n\nstruct\
    \ Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner()\
    \ : idx(0), size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n\
    \        memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf +\
    \ len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n \
    \   }\n\n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n\
    \    }\n\n    inline char skip() {\n        ensure();\n        while (buf[idx]\
    \ && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n        }\n\
    \        return buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
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
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"tree/tree_center.cpp\"\
    \npair<int, vector<int>> tree_center(const vector<vector<int>> &G) {\n    int\
    \ n = G.size();\n    if (n == 0) return {0, {}};\n\n    auto bfs = [&](int s,\
    \ vector<int> &par) {\n        vector<int> dist(n, -1);\n        queue<int> q;\n\
    \        dist[s] = 0;\n        par.assign(n, -1);\n        q.push(s);\n      \
    \  int far = s;\n        while (!q.empty()) {\n            int v = q.front();\n\
    \            q.pop();\n            if (dist[far] < dist[v]) far = v;\n       \
    \     for (auto &&to : G[v]) {\n                if (dist[to] != -1) continue;\n\
    \                dist[to] = dist[v] + 1;\n                par[to] = v;\n     \
    \           q.push(to);\n            }\n        }\n        return pair<int, vector<int>>(far,\
    \ dist);\n    };\n\n    vector<int> par;\n    int s = bfs(0, par).first;\n   \
    \ auto [t, dist] = bfs(s, par);\n\n    vector<int> path;\n    for (int v = t;\
    \ v != -1; v = par[v]) path.push_back(v);\n    reverse(path.begin(), path.end());\n\
    \n    int diam = dist[t];\n    vector<int> centers;\n    centers.push_back(path[diam\
    \ / 2]);\n    if (diam & 1) centers.push_back(path[diam / 2 + 1]);\n    return\
    \ {(diam + 1) / 2, centers};\n}\n\n/**\n * @brief \u6728\u306E\u4E2D\u5FC3(Tree\
    \ Center)\n */\n#line 11 \"test/yosupo_many_aplusb_tree_center.test.cpp\"\n\n\
    int main() {\n    {\n        mt19937 rng(123456789);\n        for (int n = 0;\
    \ n <= 40; ++n) {\n            for (int trial = 0; trial < 200; ++trial) {\n \
    \               vector<vector<int>> g(n);\n                for (int v = 1; v <\
    \ n; ++v) {\n                    int p = uniform_int_distribution<int>(0, v -\
    \ 1)(rng);\n                    g[v].push_back(p);\n                    g[p].push_back(v);\n\
    \                }\n\n                int brute_radius = 0;\n                vector<int>\
    \ brute_centers;\n                if (n > 0) {\n                    vector<int>\
    \ ecc(n);\n                    for (int s = 0; s < n; ++s) {\n               \
    \         vector<int> dist(n, -1);\n                        queue<int> q;\n  \
    \                      dist[s] = 0;\n                        q.push(s);\n    \
    \                    while (!q.empty()) {\n                            int v =\
    \ q.front();\n                            q.pop();\n                         \
    \   for (int to : g[v]) {\n                                if (dist[to] != -1)\
    \ continue;\n                                dist[to] = dist[v] + 1;\n       \
    \                         q.push(to);\n                            }\n       \
    \                 }\n                        for (int d : dist) ecc[s] = max(ecc[s],\
    \ d);\n                    }\n                    brute_radius = *min_element(ecc.begin(),\
    \ ecc.end());\n                    for (int v = 0; v < n; ++v) {\n           \
    \             if (ecc[v] == brute_radius) brute_centers.push_back(v);\n      \
    \              }\n                }\n\n                auto [radius, centers]\
    \ = tree_center(g);\n                sort(centers.begin(), centers.end());\n \
    \               if (radius != brute_radius) return 1;\n                if (centers\
    \ != brute_centers) return 1;\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <algorithm>\n#include <queue>\n#include <random>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../util/fastio.cpp\"\n#include \"../tree/tree_center.cpp\"\
    \n\nint main() {\n    {\n        mt19937 rng(123456789);\n        for (int n =\
    \ 0; n <= 40; ++n) {\n            for (int trial = 0; trial < 200; ++trial) {\n\
    \                vector<vector<int>> g(n);\n                for (int v = 1; v\
    \ < n; ++v) {\n                    int p = uniform_int_distribution<int>(0, v\
    \ - 1)(rng);\n                    g[v].push_back(p);\n                    g[p].push_back(v);\n\
    \                }\n\n                int brute_radius = 0;\n                vector<int>\
    \ brute_centers;\n                if (n > 0) {\n                    vector<int>\
    \ ecc(n);\n                    for (int s = 0; s < n; ++s) {\n               \
    \         vector<int> dist(n, -1);\n                        queue<int> q;\n  \
    \                      dist[s] = 0;\n                        q.push(s);\n    \
    \                    while (!q.empty()) {\n                            int v =\
    \ q.front();\n                            q.pop();\n                         \
    \   for (int to : g[v]) {\n                                if (dist[to] != -1)\
    \ continue;\n                                dist[to] = dist[v] + 1;\n       \
    \                         q.push(to);\n                            }\n       \
    \                 }\n                        for (int d : dist) ecc[s] = max(ecc[s],\
    \ d);\n                    }\n                    brute_radius = *min_element(ecc.begin(),\
    \ ecc.end());\n                    for (int v = 0; v < n; ++v) {\n           \
    \             if (ecc[v] == brute_radius) brute_centers.push_back(v);\n      \
    \              }\n                }\n\n                auto [radius, centers]\
    \ = tree_center(g);\n                sort(centers.begin(), centers.end());\n \
    \               if (radius != brute_radius) return 1;\n                if (centers\
    \ != brute_centers) return 1;\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n\
    \    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/tree_center.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_tree_center.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_tree_center.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_tree_center.test.cpp
- /verify/test/yosupo_many_aplusb_tree_center.test.cpp.html
title: test/yosupo_many_aplusb_tree_center.test.cpp
---
