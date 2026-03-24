---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/dinic.cpp
    title: "Dinic\u6CD5(Dinic)"
  - icon: ':heavy_check_mark:'
    path: flow/project_selection_problem.cpp
    title: Project Selection Problem
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
    PROBLEM: https://yukicoder.me/problems/no/957
    links:
    - https://yukicoder.me/problems/no/957
  bundledCode: "#line 1 \"test/yuki957_project_selection_problem.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/957\"\n\n#include <algorithm>\n#include\
    \ <limits>\n#include <queue>\n#include <tuple>\n#include <vector>\nusing namespace\
    \ std;\n\nusing ll = long long;\ntemplate<class T>\nconstexpr T INF = numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    extern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value\
    \ : false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
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
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class T, typename\
    \ enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>\n\
    \    void read(T &x) {\n        long long v;\n        read(v);\n        x = T(v);\n\
    \    }\n\n    template<class Head, class Next, class... Tail>\n    void read(Head\
    \ &head, Next &next, Tail &...tail) {\n        read(head);\n        read(next,\
    \ tail...);\n    }\n\n    template<class T, class U>\n    void read(pair<T, U>\
    \ &p) {\n        read(p.first, p.second);\n    }\n\n    template<class T, typename\
    \ enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value,\
    \ int>::type = 0>\n    void read(T &a) {\n        for (auto &x : a) read(x);\n\
    \    }\n\n    void read(char &c) {\n        c = skip();\n    }\n\n    void read(string\
    \ &s) {\n        s.clear();\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            while (true)\
    \ {\n                int start = idx;\n                while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n                s.append(buf + start, idx - start);\n       \
    \         if (idx < size) break;\n                load();\n                if\
    \ (size == 0) break;\n            }\n            if (idx < size) ++idx;\n    \
    \        return;\n        }\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    bool interactive;\n    inline static constexpr FastIoDigitTable table{};\n\
    \n    Printer() : idx(0), interactive(isatty(fileno(stdout))) {}\n    ~Printer()\
    \ { flush(); }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n        if (interactive && c == '\\n') flush();\n    }\n\n    inline void\
    \ print_range(const char *s, size_t n) {\n        size_t pos = 0;\n        while\
    \ (pos < n) {\n            if (idx == BUFSIZE) flush();\n            size_t chunk\
    \ = min(n - pos, (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s +\
    \ pos, chunk);\n            idx += (int)chunk;\n            pos += chunk;\n  \
    \      }\n    }\n\n    void print(const char *s) {\n        print_range(s, strlen(s));\n\
    \    }\n\n    void print(const string &s) {\n        print_range(s.data(), s.size());\n\
    \    }\n\n    void print(char c) {\n        pc(c);\n    }\n\n    void print(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void print(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
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
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \ */\n#line 1 \"flow/dinic.cpp\"\ntemplate<class T, bool directed>\nclass Dinic\
    \ {\n    void bfs(int s){\n        fill(level.begin(),level.end(), -1);\n    \
    \    queue<int> Q;\n        level[s] = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n\
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
    \        return ret;\n    }\n};\n\n/**\n * @brief Dinic\u6CD5(Dinic)\n */\n#line\
    \ 2 \"flow/project_selection_problem.cpp\"\n\ntemplate<class T>\nclass ProjectSelectionProblem\
    \ {\n    int n;\n    T base_score{};\n    vector<T> weight;\n    vector<tuple<int,\
    \ int, T>> penalty;\n    vector<int> selected;\n\npublic:\n    ProjectSelectionProblem()\
    \ : n(0) {}\n    explicit ProjectSelectionProblem(int n) : n(n), base_score(0),\
    \ weight(n, 0), selected(n, 0) {}\n\n    int add_vertex() {\n        weight.emplace_back(0);\n\
    \        selected.emplace_back(0);\n        return n++;\n    }\n\n    int size()\
    \ const {\n        return n;\n    }\n\n    void add_true_profit(int v, T x) {\n\
    \        weight[v] += x;\n    }\n\n    void add_false_profit(int v, T x) {\n \
    \       base_score += x;\n        weight[v] -= x;\n    }\n\n    void add_penalty(int\
    \ x, int y, T cost) {\n        penalty.emplace_back(x, y, cost);\n    }\n\n  \
    \  void add_if_then(int x, int y) {\n        add_penalty(x, y, INF<T>);\n    }\n\
    \n    void force_true(int v) {\n        add_true_profit(v, INF<T>);\n    }\n\n\
    \    void force_false(int v) {\n        add_false_profit(v, INF<T>);\n    }\n\n\
    \    T solve() {\n        int s = n, t = n + 1;\n        Dinic<T, true> mf(n +\
    \ 2);\n        T offset = base_score;\n        for (int v = 0; v < n; ++v) {\n\
    \            if (weight[v] >= 0) {\n                offset += weight[v];\n   \
    \             mf.add_edge(s, v, weight[v]);\n            } else {\n          \
    \      mf.add_edge(v, t, -weight[v]);\n            }\n        }\n        for (auto&&\
    \ [x, y, cost] : penalty) {\n            mf.add_edge(x, y, cost);\n        }\n\
    \        T cut = mf.flow(s, t);\n\n        fill(selected.begin(), selected.end(),\
    \ 0);\n        queue<int> q;\n        q.emplace(s);\n        vector<int> vis(n\
    \ + 2, 0);\n        vis[s] = 1;\n        while (!q.empty()) {\n            int\
    \ v = q.front();\n            q.pop();\n            for (auto&& e : mf.G[v]) {\n\
    \                if (e.cap <= 0 || vis[e.to]) continue;\n                vis[e.to]\
    \ = 1;\n                q.emplace(e.to);\n            }\n        }\n        for\
    \ (int v = 0; v < n; ++v) {\n            selected[v] = vis[v];\n        }\n  \
    \      return offset - cut;\n    }\n\n    const vector<int>& get_selected() const\
    \ {\n        return selected;\n    }\n};\n\n/**\n * @brief Project Selection Problem\n\
    \ */\n#line 21 \"test/yuki957_project_selection_problem.test.cpp\"\n\nint main()\
    \ {\n    Scanner in;\n    Printer out;\n\n    int h, w;\n    in.read(h, w);\n\n\
    \    vector<vector<ll>> g(h, vector<ll>(w));\n    for (int i = 0; i < h; ++i)\
    \ {\n        for (int j = 0; j < w; ++j) {\n            in.read(g[i][j]);\n  \
    \      }\n    }\n    vector<ll> row(h), col(w);\n    for (int i = 0; i < h; ++i)\
    \ in.read(row[i]);\n    for (int j = 0; j < w; ++j) in.read(col[j]);\n\n    ProjectSelectionProblem<ll>\
    \ psp(h + w);\n    for (int i = 0; i < h; ++i) {\n        ll sum = 0;\n      \
    \  for (int j = 0; j < w; ++j) {\n            sum += g[i][j];\n            psp.add_penalty(h\
    \ + j, i, g[i][j]);\n        }\n        psp.add_true_profit(i, row[i] - sum);\n\
    \    }\n    for (int j = 0; j < w; ++j) {\n        psp.add_true_profit(h + j,\
    \ col[j]);\n    }\n\n    out.println(psp.solve());\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/957\"\n\n#include <algorithm>\n\
    #include <limits>\n#include <queue>\n#include <tuple>\n#include <vector>\nusing\
    \ namespace std;\n\nusing ll = long long;\ntemplate<class T>\nconstexpr T INF\
    \ = numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../flow/project_selection_problem.cpp\"\n\nint main() {\n    Scanner\
    \ in;\n    Printer out;\n\n    int h, w;\n    in.read(h, w);\n\n    vector<vector<ll>>\
    \ g(h, vector<ll>(w));\n    for (int i = 0; i < h; ++i) {\n        for (int j\
    \ = 0; j < w; ++j) {\n            in.read(g[i][j]);\n        }\n    }\n    vector<ll>\
    \ row(h), col(w);\n    for (int i = 0; i < h; ++i) in.read(row[i]);\n    for (int\
    \ j = 0; j < w; ++j) in.read(col[j]);\n\n    ProjectSelectionProblem<ll> psp(h\
    \ + w);\n    for (int i = 0; i < h; ++i) {\n        ll sum = 0;\n        for (int\
    \ j = 0; j < w; ++j) {\n            sum += g[i][j];\n            psp.add_penalty(h\
    \ + j, i, g[i][j]);\n        }\n        psp.add_true_profit(i, row[i] - sum);\n\
    \    }\n    for (int j = 0; j < w; ++j) {\n        psp.add_true_profit(h + j,\
    \ col[j]);\n    }\n\n    out.println(psp.solve());\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - flow/project_selection_problem.cpp
  - flow/dinic.cpp
  isVerificationFile: true
  path: test/yuki957_project_selection_problem.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yuki957_project_selection_problem.test.cpp
layout: document
redirect_from:
- /verify/test/yuki957_project_selection_problem.test.cpp
- /verify/test/yuki957_project_selection_problem.test.cpp.html
title: test/yuki957_project_selection_problem.test.cpp
---
