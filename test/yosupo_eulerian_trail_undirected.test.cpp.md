---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/eulerian_trail.cpp
    title: "\u30AA\u30A4\u30E9\u30FC\u8DEF(Eulerian Trail)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/eulerian_trail_undirected
    links:
    - https://judge.yosupo.jp/problem/eulerian_trail_undirected
  bundledCode: "#line 1 \"test/yosupo_eulerian_trail_undirected.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\n\n#include\
    \ <algorithm>\n#include <vector>\nusing namespace std;\n\n#line 1 \"util/fastio.cpp\"\
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
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
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
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs\
    \ _md/fastio.md\n */\n#line 1 \"graph/eulerian_trail.cpp\"\ntemplate<bool directed>\n\
    struct EulerianTrail {\n    struct Edge {\n        int from, to;\n    };\n\n \
    \   struct Result {\n        bool exists;\n        vector<int> vertices;\n   \
    \     vector<int> edge_ids;\n    };\n\n    int n;\n    vector<Edge> edges;\n \
    \   vector<vector<pair<int, int>>> g;\n\n    explicit EulerianTrail(int n) : n(n),\
    \ g(n) {}\n\n    int add_edge(int from, int to) {\n        int id = (int)edges.size();\n\
    \        edges.push_back({from, to});\n        g[from].push_back({to, id});\n\
    \        if constexpr (!directed) g[to].push_back({from, id});\n        return\
    \ id;\n    }\n\n    Result solve() const {\n        int m = edges.size();\n  \
    \      if (m == 0) {\n            return {true, {0}, {}};\n        }\n\n     \
    \   vector<int> indeg(n), outdeg(n), deg(n);\n        for (auto&& e : edges) {\n\
    \            ++outdeg[e.from];\n            ++indeg[e.to];\n            ++deg[e.from];\n\
    \            ++deg[e.to];\n        }\n\n        int start = -1, plus = 0, minus\
    \ = 0;\n        if constexpr (directed) {\n            for (int v = 0; v < n;\
    \ ++v) {\n                int diff = outdeg[v] - indeg[v];\n                if\
    \ (diff == 1) {\n                    start = v;\n                    ++plus;\n\
    \                } else if (diff == -1) {\n                    ++minus;\n    \
    \            } else if (diff != 0) {\n                    return {false, {}, {}};\n\
    \                }\n            }\n            if (!((plus == 1 && minus == 1)\
    \ || (plus == 0 && minus == 0))) {\n                return {false, {}, {}};\n\
    \            }\n            if (start == -1) {\n                for (int v = 0;\
    \ v < n; ++v) {\n                    if (outdeg[v] > 0) {\n                  \
    \      start = v;\n                        break;\n                    }\n   \
    \             }\n            }\n        } else {\n            int odd = 0;\n \
    \           for (int v = 0; v < n; ++v) {\n                if (deg[v] & 1) {\n\
    \                    start = v;\n                    ++odd;\n                }\n\
    \            }\n            if (!(odd == 0 || odd == 2)) return {false, {}, {}};\n\
    \            if (start == -1) {\n                for (int v = 0; v < n; ++v) {\n\
    \                    if (deg[v] > 0) {\n                        start = v;\n \
    \                       break;\n                    }\n                }\n   \
    \         }\n        }\n\n        vector<int> ptr(n), used(m);\n        vector<int>\
    \ st_v{start}, st_e{-1};\n        vector<int> vs, es;\n        while (!st_v.empty())\
    \ {\n            int v = st_v.back();\n            while (ptr[v] < (int)g[v].size()\
    \ && used[g[v][ptr[v]].second]) ++ptr[v];\n            if (ptr[v] == (int)g[v].size())\
    \ {\n                vs.push_back(v);\n                st_v.pop_back();\n    \
    \            int id = st_e.back();\n                st_e.pop_back();\n       \
    \         if (id != -1) es.push_back(id);\n                continue;\n       \
    \     }\n            auto [to, id] = g[v][ptr[v]++];\n            if (used[id])\
    \ continue;\n            used[id] = 1;\n            st_v.push_back(to);\n    \
    \        st_e.push_back(id);\n        }\n\n        if ((int)es.size() != m) return\
    \ {false, {}, {}};\n        reverse(vs.begin(), vs.end());\n        reverse(es.begin(),\
    \ es.end());\n        return {true, vs, es};\n    }\n};\n\n/**\n * @brief \u30AA\
    \u30A4\u30E9\u30FC\u8DEF(Eulerian Trail)\n * @docs _md/eulerian_trail.md\n */\n\
    #line 9 \"test/yosupo_eulerian_trail_undirected.test.cpp\"\n\nint main() {\n \
    \   Scanner in;\n    Printer out;\n    int t;\n    in.read(t);\n    while (t--)\
    \ {\n        int n, m;\n        in.read(n, m);\n        EulerianTrail<false> g(n);\n\
    \        for (int i = 0; i < m; ++i) {\n            int a, b;\n            in.read(a,\
    \ b);\n            g.add_edge(a, b);\n        }\n        auto res = g.solve();\n\
    \        if (!res.exists) {\n            out.writeln(\"No\");\n            continue;\n\
    \        }\n        out.writeln(\"Yes\");\n        for (int i = 0; i < (int)res.vertices.size();\
    \ ++i) {\n            if (i) out.write(' ');\n            out.write(res.vertices[i]);\n\
    \        }\n        out.writeln();\n        for (int i = 0; i < (int)res.edge_ids.size();\
    \ ++i) {\n            if (i) out.write(' ');\n            out.write(res.edge_ids[i]);\n\
    \        }\n        out.writeln();\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\
    \n\n#include <algorithm>\n#include <vector>\nusing namespace std;\n\n#include\
    \ \"../util/fastio.cpp\"\n#include \"../graph/eulerian_trail.cpp\"\n\nint main()\
    \ {\n    Scanner in;\n    Printer out;\n    int t;\n    in.read(t);\n    while\
    \ (t--) {\n        int n, m;\n        in.read(n, m);\n        EulerianTrail<false>\
    \ g(n);\n        for (int i = 0; i < m; ++i) {\n            int a, b;\n      \
    \      in.read(a, b);\n            g.add_edge(a, b);\n        }\n        auto\
    \ res = g.solve();\n        if (!res.exists) {\n            out.writeln(\"No\"\
    );\n            continue;\n        }\n        out.writeln(\"Yes\");\n        for\
    \ (int i = 0; i < (int)res.vertices.size(); ++i) {\n            if (i) out.write('\
    \ ');\n            out.write(res.vertices[i]);\n        }\n        out.writeln();\n\
    \        for (int i = 0; i < (int)res.edge_ids.size(); ++i) {\n            if\
    \ (i) out.write(' ');\n            out.write(res.edge_ids[i]);\n        }\n  \
    \      out.writeln();\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/eulerian_trail.cpp
  isVerificationFile: true
  path: test/yosupo_eulerian_trail_undirected.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_eulerian_trail_undirected.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_eulerian_trail_undirected.test.cpp
- /verify/test/yosupo_eulerian_trail_undirected.test.cpp.html
title: test/yosupo_eulerian_trail_undirected.test.cpp
---
