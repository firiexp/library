---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/bipartite_matching.cpp
    title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0\
      (Bipartite Matching)"
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
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_bipartite_matching.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <algorithm>\n\
    #include <random>\n#include <utility>\n#include <vector>\nusing namespace std;\n\
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
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 1 \"graph/bipartite_matching.cpp\"\nclass Bipartite_Matching {\nprotected:\n\
    \    vector<vector<int>> G;\n    vector<int> used, alive;\n    int t;\n    int\
    \ l, r;\n\npublic:\n    vector<int> match;\n\n    explicit Bipartite_Matching(int\
    \ l, int r)\n        : G(l), used(l, 0), alive(l + r, -1), t(0), l(l), r(r), match(l\
    \ + r, -1) {}\n\n    void add_edge(int a, int b) {\n        G[a].push_back(b);\n\
    \    }\n\n    bool dfs(int x) {\n        used[x] = t;\n        for (int y : G[x])\
    \ {\n            int ry = y + l;\n            if (alive[ry] == 0) continue;\n\
    \            int w = match[ry];\n            if (w != -1 && (alive[w] == 0 ||\
    \ used[w] == t || !dfs(w))) continue;\n            match[x] = ry;\n          \
    \  match[ry] = x;\n            return true;\n        }\n        return false;\n\
    \    }\n\n    int matching() {\n        int ans = 0;\n        for (int i = 0;\
    \ i < l; ++i) {\n            if (alive[i] == 0 || match[i] != -1) continue;\n\
    \            ++t;\n            ans += dfs(i);\n        }\n        return ans;\n\
    \    }\n\n    vector<pair<int, int>> get_pairs() const {\n        vector<pair<int,\
    \ int>> res;\n        for (int i = 0; i < l; ++i) {\n            if (match[i]\
    \ == -1) continue;\n            res.emplace_back(i, match[i] - l);\n        }\n\
    \        return res;\n    }\n};\n\n/**\n * @brief \u4E8C\u90E8\u30B0\u30E9\u30D5\
    \u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(Bipartite Matching)\n * @docs _md/bipartite_matching.md\n\
    \ */\n#line 11 \"test/yosupo_many_aplusb_bipartite_matching.test.cpp\"\n\nint\
    \ main() {\n    {\n        mt19937 rng(123456789);\n        for (int l = 0; l\
    \ <= 8; ++l) {\n            for (int r = 0; r <= 8; ++r) {\n                for\
    \ (int trial = 0; trial < 200; ++trial) {\n                    vector<vector<int>>\
    \ g(l);\n                    for (int i = 0; i < l; ++i) {\n                 \
    \       for (int j = 0; j < r; ++j) {\n                            if (uniform_int_distribution<int>(0,\
    \ 1)(rng)) g[i].push_back(j);\n                        }\n                   \
    \ }\n\n                    Bipartite_Matching bm(l, r);\n                    for\
    \ (int i = 0; i < l; ++i) {\n                        for (int j : g[i]) bm.add_edge(i,\
    \ j);\n                    }\n                    int got = bm.matching();\n\n\
    \                    vector<int> dp(1 << r, -1);\n                    dp[0] =\
    \ 0;\n                    for (int i = 0; i < l; ++i) {\n                    \
    \    auto ndp = dp;\n                        for (int mask = 0; mask < (1 << r);\
    \ ++mask) {\n                            if (dp[mask] < 0) continue;\n       \
    \                     for (int j : g[i]) {\n                                if\
    \ (mask >> j & 1) continue;\n                                ndp[mask | (1 <<\
    \ j)] = max(ndp[mask | (1 << j)], dp[mask] + 1);\n                           \
    \ }\n                        }\n                        dp.swap(ndp);\n      \
    \              }\n                    int want = 0;\n                    for (int\
    \ x : dp) want = max(want, x);\n                    if (got != want) return 1;\n\
    \n                    auto pairs = bm.get_pairs();\n                    if ((int)pairs.size()\
    \ != got) return 1;\n                    vector<int> used_l(l, 0), used_r(r, 0);\n\
    \                    for (auto &&[a, b] : pairs) {\n                        if\
    \ (!(0 <= a && a < l && 0 <= b && b < r)) return 1;\n                        if\
    \ (used_l[a] || used_r[b]) return 1;\n                        used_l[a] = used_r[b]\
    \ = 1;\n                        if (bm.match[a] != b + l) return 1;\n        \
    \                if (bm.match[b + l] != a) return 1;\n                       \
    \ if (find(g[a].begin(), g[a].end(), b) == g[a].end()) return 1;\n           \
    \         }\n                }\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <algorithm>\n#include <random>\n#include <utility>\n#include <vector>\nusing\
    \ namespace std;\n\n#include \"../util/fastio.cpp\"\n#include \"../graph/bipartite_matching.cpp\"\
    \n\nint main() {\n    {\n        mt19937 rng(123456789);\n        for (int l =\
    \ 0; l <= 8; ++l) {\n            for (int r = 0; r <= 8; ++r) {\n            \
    \    for (int trial = 0; trial < 200; ++trial) {\n                    vector<vector<int>>\
    \ g(l);\n                    for (int i = 0; i < l; ++i) {\n                 \
    \       for (int j = 0; j < r; ++j) {\n                            if (uniform_int_distribution<int>(0,\
    \ 1)(rng)) g[i].push_back(j);\n                        }\n                   \
    \ }\n\n                    Bipartite_Matching bm(l, r);\n                    for\
    \ (int i = 0; i < l; ++i) {\n                        for (int j : g[i]) bm.add_edge(i,\
    \ j);\n                    }\n                    int got = bm.matching();\n\n\
    \                    vector<int> dp(1 << r, -1);\n                    dp[0] =\
    \ 0;\n                    for (int i = 0; i < l; ++i) {\n                    \
    \    auto ndp = dp;\n                        for (int mask = 0; mask < (1 << r);\
    \ ++mask) {\n                            if (dp[mask] < 0) continue;\n       \
    \                     for (int j : g[i]) {\n                                if\
    \ (mask >> j & 1) continue;\n                                ndp[mask | (1 <<\
    \ j)] = max(ndp[mask | (1 << j)], dp[mask] + 1);\n                           \
    \ }\n                        }\n                        dp.swap(ndp);\n      \
    \              }\n                    int want = 0;\n                    for (int\
    \ x : dp) want = max(want, x);\n                    if (got != want) return 1;\n\
    \n                    auto pairs = bm.get_pairs();\n                    if ((int)pairs.size()\
    \ != got) return 1;\n                    vector<int> used_l(l, 0), used_r(r, 0);\n\
    \                    for (auto &&[a, b] : pairs) {\n                        if\
    \ (!(0 <= a && a < l && 0 <= b && b < r)) return 1;\n                        if\
    \ (used_l[a] || used_r[b]) return 1;\n                        used_l[a] = used_r[b]\
    \ = 1;\n                        if (bm.match[a] != b + l) return 1;\n        \
    \                if (bm.match[b + l] != a) return 1;\n                       \
    \ if (find(g[a].begin(), g[a].end(), b) == g[a].end()) return 1;\n           \
    \         }\n                }\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n\
    \    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/bipartite_matching.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_bipartite_matching.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_bipartite_matching.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_bipartite_matching.test.cpp
- /verify/test/yosupo_many_aplusb_bipartite_matching.test.cpp.html
title: test/yosupo_many_aplusb_bipartite_matching.test.cpp
---
