---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/general_matching.cpp
    title: "\u4E00\u822C\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0\
      (General Matching)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/general_matching
    links:
    - https://judge.yosupo.jp/problem/general_matching
  bundledCode: "#line 1 \"test/yosupo_general_matching.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/general_matching\"\n\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing\
    \ namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin)))\
    \ {}\n\n    inline void load() {\n        int len = size - idx;\n        memmove(buf,\
    \ buf + idx, len);\n        if (interactive) {\n            if (fgets(buf + len,\
    \ BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n          \
    \  else size = len;\n        } else {\n            size = len + (int)fread(buf\
    \ + len, 1, BUFSIZE - len, stdin);\n        }\n        idx = 0;\n        buf[size]\
    \ = 0;\n    }\n\n    inline void ensure() {\n        if (idx + OFFSET > size)\
    \ load();\n    }\n\n    inline void ensure_interactive() {\n        if (idx ==\
    \ size) load();\n    }\n\n    inline char skip() {\n        if (interactive) {\n\
    \            ensure_interactive();\n            while (buf[idx] && buf[idx] <=\
    \ ' ') {\n                ++idx;\n                ensure_interactive();\n    \
    \        }\n            return buf[idx++];\n        }\n        ensure();\n   \
    \     while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n\
    \        }\n        return buf[idx++];\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T &x) {\n  \
    \      if (interactive) {\n            char c = skip();\n            bool neg\
    \ = false;\n            if constexpr (is_signed<T>::value) {\n               \
    \ if (c == '-') {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       x = 0;\n            while (c >= '0') {\n                x = x * 10 + (c\
    \ & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg) x = -x;\n            }\n            return;\n        }\n      \
    \  char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        x = 0;\n        while (c\
    \ >= '0') {\n            x = x * 10 + (c & 15);\n            c = buf[idx++];\n\
    \        }\n        if constexpr (is_signed<T>::value) {\n            if (neg)\
    \ x = -x;\n        }\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ Head, class Next, class... Tail>\n    void read(Head &head, Next &next, Tail\
    \ &...tail) {\n        read(head);\n        read(next, tail...);\n    }\n\n  \
    \  template<class T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first,\
    \ p.second);\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void print(T x) {\n      \
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
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value,\
    \ int>::type = 0>\n    void print(const T &x) {\n        print(x.value());\n \
    \   }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ print(const T &a) {\n        bool first = true;\n        for (auto &&x : a)\
    \ {\n            if (!first) pc(' ');\n            first = false;\n          \
    \  print(x);\n        }\n    }\n\n    template<class T>\n    void println(const\
    \ T &x) {\n        print(x);\n        pc('\\n');\n    }\n\n    template<class\
    \ Head, class... Tail>\n    void println(const Head &head, const Tail &...tail)\
    \ {\n        print(head);\n        ((pc(' '), print(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void println() {\n        pc('\\n');\n    }\n};\n\ntemplate<class\
    \ T>\nScanner &operator>>(Scanner &in, T &x) {\n    in.read(x);\n    return in;\n\
    }\n\ntemplate<class T>\nPrinter &operator<<(Printer &out, const T &x) {\n    out.print(x);\n\
    \    return out;\n}\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n\
    \ */\n#line 1 \"graph/general_matching.cpp\"\nclass GeneralMatching {\n    int\
    \ n;\n    vector<vector<int>> g;\n    vector<int> match, parent, base, q;\n  \
    \  vector<bool> used, blossom;\n\n    int lca(int a, int b) {\n        vector<bool>\
    \ seen(n, false);\n        while (true) {\n            a = base[a];\n        \
    \    seen[a] = true;\n            if (match[a] == -1) break;\n            a =\
    \ parent[match[a]];\n        }\n        while (true) {\n            b = base[b];\n\
    \            if (seen[b]) return b;\n            if (match[b] == -1) break;\n\
    \            b = parent[match[b]];\n        }\n        return -1;\n    }\n\n \
    \   void mark_path(int v, int b, int child) {\n        while (base[v] != b) {\n\
    \            blossom[base[v]] = blossom[base[match[v]]] = true;\n            parent[v]\
    \ = child;\n            child = match[v];\n            v = parent[match[v]];\n\
    \        }\n    }\n\n    int find_path(int root) {\n        fill(used.begin(),\
    \ used.end(), false);\n        fill(parent.begin(), parent.end(), -1);\n     \
    \   for (int i = 0; i < n; ++i) base[i] = i;\n        int head = 0, tail = 0;\n\
    \        q[tail++] = root;\n        used[root] = true;\n        while (head <\
    \ tail) {\n            int v = q[head++];\n            for (int to : g[v]) {\n\
    \                if (base[v] == base[to] || match[v] == to) continue;\n      \
    \          if (to == root || (match[to] != -1 && parent[match[to]] != -1)) {\n\
    \                    int cur = lca(v, to);\n                    fill(blossom.begin(),\
    \ blossom.end(), false);\n                    mark_path(v, cur, to);\n       \
    \             mark_path(to, cur, v);\n                    for (int i = 0; i <\
    \ n; ++i) {\n                        if (!blossom[base[i]]) continue;\n      \
    \                  base[i] = cur;\n                        if (used[i]) continue;\n\
    \                        used[i] = true;\n                        q[tail++] =\
    \ i;\n                    }\n                } else if (parent[to] == -1) {\n\
    \                    parent[to] = v;\n                    if (match[to] == -1)\
    \ return to;\n                    int u = match[to];\n                    used[u]\
    \ = true;\n                    q[tail++] = u;\n                }\n           \
    \ }\n        }\n        return -1;\n    }\n\npublic:\n    explicit GeneralMatching(int\
    \ n)\n        : n(n), g(n), match(n, -1), parent(n), base(n), q(n), used(n), blossom(n)\
    \ {}\n\n    void add_edge(int u, int v) {\n        g[u].push_back(v);\n      \
    \  g[v].push_back(u);\n    }\n\n    int max_matching() {\n        int res = 0;\n\
    \        for (int i = 0; i < n; ++i) {\n            if (match[i] != -1) continue;\n\
    \            int v = find_path(i);\n            if (v == -1) continue;\n     \
    \       ++res;\n            while (v != -1) {\n                int pv = parent[v];\n\
    \                int nv = pv == -1 ? -1 : match[pv];\n                match[v]\
    \ = pv;\n                if (pv != -1) match[pv] = v;\n                v = nv;\n\
    \            }\n        }\n        return res;\n    }\n\n    const vector<int>&\
    \ get_match() const {\n        return match;\n    }\n\n    vector<pair<int, int>>\
    \ get_pairs() const {\n        vector<pair<int, int>> res;\n        for (int i\
    \ = 0; i < n; ++i) {\n            if (match[i] == -1 || i > match[i]) continue;\n\
    \            res.emplace_back(i, match[i]);\n        }\n        return res;\n\
    \    }\n};\n\n/**\n * @brief \u4E00\u822C\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\
    \u30C1\u30F3\u30B0(General Matching)\n */\n#line 14 \"test/yosupo_general_matching.test.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n    int n, m;\n    in.read(n,\
    \ m);\n    GeneralMatching gm(n);\n    for (int i = 0; i < m; ++i) {\n       \
    \ int u, v;\n        in.read(u, v);\n        gm.add_edge(u, v);\n    }\n    int\
    \ ans = gm.max_matching();\n    out.println(ans);\n    for (auto&& [u, v] : gm.get_pairs())\
    \ {\n        out.println(u, v);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../graph/general_matching.cpp\"\n\nint main() {\n    Scanner in;\n\
    \    Printer out;\n    int n, m;\n    in.read(n, m);\n    GeneralMatching gm(n);\n\
    \    for (int i = 0; i < m; ++i) {\n        int u, v;\n        in.read(u, v);\n\
    \        gm.add_edge(u, v);\n    }\n    int ans = gm.max_matching();\n    out.println(ans);\n\
    \    for (auto&& [u, v] : gm.get_pairs()) {\n        out.println(u, v);\n    }\n\
    \    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/general_matching.cpp
  isVerificationFile: true
  path: test/yosupo_general_matching.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_general_matching.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_general_matching.test.cpp
- /verify/test/yosupo_general_matching.test.cpp.html
title: test/yosupo_general_matching.test.cpp
---
