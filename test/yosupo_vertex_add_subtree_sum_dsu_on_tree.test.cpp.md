---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: tree/dsu_on_tree.cpp
    title: DSU on Tree
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 1 \"test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\nusing ll = long long;\n\n\
    #line 11 \"test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp\"\n#include\
    \ <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
    \ \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class T,\
    \ class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class T>\n\
    struct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
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
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k))\
    \ ret += bit[k - 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n\
    \        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T\
    \ x) {\n        if (x <= 0) return 0;\n        int i = 0;\n        for (int j\
    \ = m; j; j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i\
    \ + j - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n\
    \ * @brief Binary Indexed Tree(BIT)\n */\n#line 1 \"tree/dsu_on_tree.cpp\"\ntemplate<class\
    \ G>\nstruct DSUonTree {\n    G &g;\n    int n, root, ord;\n    vector<int> sub_size,\
    \ euler, down, up;\n\n    explicit DSUonTree(G &g, int root = 0)\n        : g(g),\
    \ n(g.size()), root(root), ord(0),\n          sub_size(n), euler(n), down(n),\
    \ up(n) {\n        dfs_sz(root, -1);\n        dfs_euler(root, -1);\n    }\n\n\
    \    int idx(int v) const {\n        return down[v];\n    }\n\n    int begin(int\
    \ v) const {\n        return down[v];\n    }\n\n    int end(int v) const {\n \
    \       return up[v];\n    }\n\n    template<class UPDATE, class QUERY, class\
    \ CLEAR, class RESET>\n    void run(UPDATE update, QUERY query, CLEAR clear, RESET\
    \ reset) {\n        auto dfs = [&](auto &&self, int v, int p, bool keep) -> void\
    \ {\n            int heavy = (g[v].empty() || g[v][0] == p ? -1 : g[v][0]);\n\
    \            for (auto &&u : g[v]) {\n                if (u == p || u == heavy)\
    \ continue;\n                self(self, u, v, false);\n            }\n       \
    \     if (heavy != -1) self(self, heavy, v, true);\n            for (auto &&u\
    \ : g[v]) {\n                if (u == p || u == heavy) continue;\n           \
    \     for (int i = down[u]; i < up[u]; ++i) update(euler[i]);\n            }\n\
    \            update(v);\n            query(v);\n            if (!keep) {\n   \
    \             for (int i = down[v]; i < up[v]; ++i) clear(euler[i]);\n       \
    \         reset();\n            }\n        };\n        dfs(dfs, root, -1, false);\n\
    \    }\n\nprivate:\n    void dfs_sz(int v, int p) {\n        sub_size[v] = 1;\n\
    \        int heavy_idx = -1;\n        for (int i = 0; i < (int)g[v].size(); ++i)\
    \ {\n            int u = g[v][i];\n            if (u == p) continue;\n       \
    \     dfs_sz(u, v);\n            sub_size[v] += sub_size[u];\n            if (heavy_idx\
    \ == -1 || sub_size[u] > sub_size[g[v][heavy_idx]]) {\n                heavy_idx\
    \ = i;\n            }\n        }\n        if (heavy_idx > 0) swap(g[v][0], g[v][heavy_idx]);\n\
    \    }\n\n    void dfs_euler(int v, int p) {\n        down[v] = ord;\n       \
    \ euler[ord++] = v;\n        for (auto &&u : g[v]) {\n            if (u == p)\
    \ continue;\n            dfs_euler(u, v);\n        }\n        up[v] = ord;\n \
    \   }\n};\n\n/**\n * @brief DSU on Tree\n */\n#line 16 \"test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp\"\
    \n\nstruct Query {\n    int time, type;\n    ll x;\n};\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<ll> a(n);\n\
    \    for (auto &&x : a) sc.read(x);\n\n    vector<vector<int>> g(n);\n    for\
    \ (int v = 1; v < n; ++v) {\n        int p;\n        sc.read(p);\n        g[p].push_back(v);\n\
    \        g[v].push_back(p);\n    }\n\n    vector<vector<Query>> qs(n);\n    vector<ll>\
    \ ans(q, -1);\n    for (int i = 0; i < q; ++i) {\n        int t, v;\n        sc.read(t,\
    \ v);\n        if (t == 0) {\n            ll x;\n            sc.read(x);\n   \
    \         qs[v].push_back({i, 0, x});\n        } else {\n            qs[v].push_back({i,\
    \ 1, 0});\n        }\n    }\n\n    BIT<ll> bit(q + 1);\n    vector<pair<int, ll>>\
    \ history;\n    ll base = 0;\n\n    auto update = [&](int v) {\n        base +=\
    \ a[v];\n        for (auto &&qu : qs[v]) {\n            if (qu.type == 0) {\n\
    \                bit.add(qu.time, qu.x);\n                history.push_back({qu.time,\
    \ qu.x});\n            }\n        }\n    };\n    auto query = [&](int v) {\n \
    \       for (auto &&qu : qs[v]) {\n            if (qu.type == 1) ans[qu.time]\
    \ = base + bit.sum(qu.time);\n        }\n    };\n    auto clear = [&](int) {};\n\
    \    auto reset = [&]() {\n        base = 0;\n        for (auto &&[t, x] : history)\
    \ bit.add(t, -x);\n        history.clear();\n    };\n\n    DSUonTree dsu(g);\n\
    \    dsu.run(update, query, clear, reset);\n\n    for (auto &&x : ans) {\n   \
    \     if (x != -1) pr.writeln(x);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n\n#include <bits/stdc++.h>\n\nusing namespace std;\nusing ll = long long;\n\n\
    #include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../datastructure/binaryindexedtree.cpp\"\
    \n#include \"../tree/dsu_on_tree.cpp\"\n\nstruct Query {\n    int time, type;\n\
    \    ll x;\n};\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n,\
    \ q;\n    sc.read(n, q);\n    vector<ll> a(n);\n    for (auto &&x : a) sc.read(x);\n\
    \n    vector<vector<int>> g(n);\n    for (int v = 1; v < n; ++v) {\n        int\
    \ p;\n        sc.read(p);\n        g[p].push_back(v);\n        g[v].push_back(p);\n\
    \    }\n\n    vector<vector<Query>> qs(n);\n    vector<ll> ans(q, -1);\n    for\
    \ (int i = 0; i < q; ++i) {\n        int t, v;\n        sc.read(t, v);\n     \
    \   if (t == 0) {\n            ll x;\n            sc.read(x);\n            qs[v].push_back({i,\
    \ 0, x});\n        } else {\n            qs[v].push_back({i, 1, 0});\n       \
    \ }\n    }\n\n    BIT<ll> bit(q + 1);\n    vector<pair<int, ll>> history;\n  \
    \  ll base = 0;\n\n    auto update = [&](int v) {\n        base += a[v];\n   \
    \     for (auto &&qu : qs[v]) {\n            if (qu.type == 0) {\n           \
    \     bit.add(qu.time, qu.x);\n                history.push_back({qu.time, qu.x});\n\
    \            }\n        }\n    };\n    auto query = [&](int v) {\n        for\
    \ (auto &&qu : qs[v]) {\n            if (qu.type == 1) ans[qu.time] = base + bit.sum(qu.time);\n\
    \        }\n    };\n    auto clear = [&](int) {};\n    auto reset = [&]() {\n\
    \        base = 0;\n        for (auto &&[t, x] : history) bit.add(t, -x);\n  \
    \      history.clear();\n    };\n\n    DSUonTree dsu(g);\n    dsu.run(update,\
    \ query, clear, reset);\n\n    for (auto &&x : ans) {\n        if (x != -1) pr.writeln(x);\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/binaryindexedtree.cpp
  - tree/dsu_on_tree.cpp
  isVerificationFile: true
  path: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
- /verify/test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp.html
title: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
---
