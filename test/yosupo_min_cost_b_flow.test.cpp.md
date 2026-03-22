---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/minimum_cost_b_flow.cpp
    title: Minimum Cost B-Flow
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
    PROBLEM: https://judge.yosupo.jp/problem/min_cost_b_flow
    links:
    - https://judge.yosupo.jp/problem/min_cost_b_flow
  bundledCode: "#line 1 \"test/yosupo_min_cost_b_flow.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n#include <bits/stdc++.h>\n\
    \nusing ll = long long;\nusing namespace std;\n\n#line 10 \"test/yosupo_min_cost_b_flow.test.cpp\"\
    \n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\
    \nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
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
    \ */\n#line 1 \"graph/minimum_cost_b_flow.cpp\"\ntemplate<class Flow, class Cost>\n\
    struct MinimumCostBFlow {\n    using Sum = __int128_t;\n    struct Edge {\n  \
    \      int from, to, rev;\n        Flow flow, cap;\n        Cost cost;\n\n   \
    \     Flow residual_cap() const {\n            return cap - flow;\n        }\n\
    \    };\n\n    struct EdgeRef {\n        int from, idx;\n    };\n\n    int n;\n\
    \    vector<vector<Edge>> g;\n    vector<Flow> b;\n    vector<EdgeRef> edges;\n\
    \    vector<Cost> potential;\n\n    explicit MinimumCostBFlow(int n) : n(n), g(n),\
    \ b(n, 0), potential(n, 0) {}\n\n    void add_supply(int v, Flow x) {\n      \
    \  b[v] += x;\n    }\n\n    void add_demand(int v, Flow x) {\n        b[v] -=\
    \ x;\n    }\n\n    int add_edge(int from, int to, Flow lower, Flow upper, Cost\
    \ cost) {\n        assert(lower <= upper);\n        int idx = (int)g[from].size();\n\
    \        int rev = from == to ? idx + 1 : (int)g[to].size();\n        g[from].push_back({from,\
    \ to, rev, 0, upper, cost});\n        g[to].push_back({to, from, idx, 0, -lower,\
    \ -cost});\n        edges.push_back({from, idx});\n        return (int)edges.size()\
    \ - 1;\n    }\n\n    Edge& rev_edge(const Edge& e) {\n        return g[e.to][e.rev];\n\
    \    }\n\n    const Edge& get_edge(int i) const {\n        return g[edges[i].from][edges[i].idx];\n\
    \    }\n\n    vector<Flow> get_flows() const {\n        vector<Flow> ret(edges.size());\n\
    \        for (int i = 0; i < (int)edges.size(); ++i) ret[i] = get_edge(i).flow;\n\
    \        return ret;\n    }\n\n    vector<Cost> get_potential() const {\n    \
    \    vector<Cost> ret(n, 0);\n        for (int iter = 0; iter < n; ++iter) {\n\
    \            bool updated = false;\n            for (int v = 0; v < n; ++v) {\n\
    \                for (auto&& e : g[v]) {\n                    if(e.residual_cap()\
    \ <= 0) continue;\n                    if(ret[e.to] > ret[e.from] + e.cost) {\n\
    \                        ret[e.to] = ret[e.from] + e.cost;\n                 \
    \       updated = true;\n                    }\n                }\n          \
    \  }\n            if(!updated) break;\n        }\n        return ret;\n    }\n\
    \n    pair<bool, Sum> solve() {\n        const Cost unreachable = numeric_limits<Cost>::max();\n\
    \        vector<Cost> dist(n);\n        vector<Edge*> parent(n);\n        vector<int>\
    \ excess, deficit;\n        priority_queue<pair<Cost, int>, vector<pair<Cost,\
    \ int>>, greater<pair<Cost, int>>> pq;\n        Cost farthest = 0;\n\n       \
    \ auto push = [&](Edge& e, Flow amount) {\n            e.flow += amount;\n   \
    \         rev_edge(e).flow -= amount;\n        };\n        auto residual_cost\
    \ = [&](const Edge& e) {\n            return e.cost + potential[e.from] - potential[e.to];\n\
    \        };\n\n        auto saturate_negative = [&](Flow delta) {\n          \
    \  excess.clear();\n            deficit.clear();\n            for (auto&& es :\
    \ g) {\n                for (auto&& e : es) {\n                    Flow rcap =\
    \ e.residual_cap();\n                    if(rcap < delta) continue;\n        \
    \            if(residual_cost(e) < 0) {\n                        push(e, rcap);\n\
    \                        b[e.from] -= rcap;\n                        b[e.to] +=\
    \ rcap;\n                    }\n                }\n            }\n           \
    \ for (int v = 0; v < n; ++v) {\n                if(b[v] > 0) excess.push_back(v);\n\
    \                if(b[v] < 0) deficit.push_back(v);\n            }\n        };\n\
    \n        auto dual = [&](Flow delta) {\n            fill(dist.begin(), dist.end(),\
    \ unreachable);\n            fill(parent.begin(), parent.end(), nullptr);\n\n\
    \            excess.erase(remove_if(excess.begin(), excess.end(), [&](int v) {\n\
    \                return b[v] < delta;\n            }), excess.end());\n      \
    \      deficit.erase(remove_if(deficit.begin(), deficit.end(), [&](int v) {\n\
    \                return b[v] > -delta;\n            }), deficit.end());\n\n  \
    \          while(!pq.empty()) pq.pop();\n            for (int v : excess) {\n\
    \                dist[v] = 0;\n                pq.emplace(0, v);\n           \
    \ }\n\n            farthest = 0;\n            int reached = 0;\n            while(!pq.empty())\
    \ {\n                auto [d, v] = pq.top();\n                pq.pop();\n    \
    \            if(dist[v] != d) continue;\n                farthest = d;\n     \
    \           if(b[v] <= -delta) ++reached;\n                if(reached >= (int)deficit.size())\
    \ break;\n                for (auto&& e : g[v]) {\n                    if(e.residual_cap()\
    \ < delta) continue;\n                    Cost nd = d + residual_cost(e);\n  \
    \                  if(nd >= dist[e.to]) continue;\n                    dist[e.to]\
    \ = nd;\n                    parent[e.to] = &e;\n                    pq.emplace(nd,\
    \ e.to);\n                }\n            }\n\n            for (int v = 0; v <\
    \ n; ++v) {\n                potential[v] += min(dist[v], farthest);\n       \
    \     }\n            return reached > 0;\n        };\n\n        auto primal =\
    \ [&](Flow delta) {\n            for (int t : deficit) {\n                if(dist[t]\
    \ > farthest) continue;\n                Flow f = -b[t];\n                int\
    \ v = t;\n                while(parent[v] != nullptr && f >= delta) {\n      \
    \              f = min(f, parent[v]->residual_cap());\n                    v =\
    \ parent[v]->from;\n                }\n                f = min(f, b[v]);\n   \
    \             if(f < delta) continue;\n                v = t;\n              \
    \  while(parent[v] != nullptr) {\n                    Edge& e = *parent[v];\n\
    \                    push(e, f);\n                    int u = e.from;\n      \
    \              parent[v] = nullptr;\n                    v = u;\n            \
    \    }\n                b[t] += f;\n                b[v] -= f;\n            }\n\
    \        };\n\n        for (auto&& es : g) {\n            for (auto&& e : es)\
    \ {\n                Flow rcap = e.residual_cap();\n                if(rcap <\
    \ 0) {\n                    push(e, rcap);\n                    b[e.from] -= rcap;\n\
    \                    b[e.to] += rcap;\n                }\n            }\n    \
    \    }\n\n        Flow max_cap = 1;\n        for (auto&& es : g) {\n         \
    \   for (auto&& e : es) {\n                max_cap = max(max_cap, e.residual_cap());\n\
    \            }\n        }\n        Flow delta = 1;\n        while(delta <= max_cap\
    \ / 2) delta <<= 1;\n        for (delta >>= 1; delta > 0; delta >>= 1) {\n   \
    \         saturate_negative(delta);\n            while(dual(delta)) primal(delta);\n\
    \        }\n\n        Sum value = 0;\n        bool ok = true;\n        for (int\
    \ v = 0; v < n; ++v) {\n            if(b[v] != 0) ok = false;\n        }\n   \
    \     for (int i = 0; i < (int)edges.size(); ++i) {\n            auto&& e = get_edge(i);\n\
    \            value += (Sum)e.flow * (Sum)e.cost;\n        }\n        return {ok,\
    \ value};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528b-flow(Min-Cost\
    \ b-Flow)\n */\n#line 14 \"test/yosupo_min_cost_b_flow.test.cpp\"\n\nvoid write_i128(Printer&\
    \ pr, __int128_t x) {\n    if(x == 0) {\n        pr.write('0');\n        return;\n\
    \    }\n    if(x < 0) {\n        pr.write('-');\n        x = -x;\n    }\n    string\
    \ s;\n    while(x > 0) {\n        s.push_back(char('0' + x % 10));\n        x\
    \ /= 10;\n    }\n    reverse(s.begin(), s.end());\n    pr.write(s);\n}\n\nint\
    \ main() {\n    Scanner sc;\n    Printer pr;\n    int n, m;\n    sc.read(n, m);\n\
    \    MinimumCostBFlow<ll, ll> mcf(n);\n    for (int i = 0; i < n; ++i) {\n   \
    \     ll b;\n        sc.read(b);\n        mcf.add_supply(i, b);\n    }\n    for\
    \ (int i = 0; i < m; ++i) {\n        int s, t;\n        ll lower, upper, cost;\n\
    \        sc.read(s, t, lower, upper, cost);\n        mcf.add_edge(s, t, lower,\
    \ upper, cost);\n    }\n\n    auto [ok, cost] = mcf.solve();\n    if(!ok) {\n\
    \        pr.writeln(\"infeasible\");\n        return 0;\n    }\n\n    write_i128(pr,\
    \ cost);\n    pr.writeln();\n    auto potential = mcf.get_potential();\n    for\
    \ (int i = 0; i < n; ++i) {\n        pr.write(potential[i]);\n        pr.write(i\
    \ + 1 == n ? '\\n' : ' ');\n    }\n    auto flow = mcf.get_flows();\n    for (int\
    \ i = 0; i < m; ++i) {\n        pr.writeln(flow[i]);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n#include\
    \ <bits/stdc++.h>\n\nusing ll = long long;\nusing namespace std;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../graph/minimum_cost_b_flow.cpp\"\n\nvoid write_i128(Printer& pr,\
    \ __int128_t x) {\n    if(x == 0) {\n        pr.write('0');\n        return;\n\
    \    }\n    if(x < 0) {\n        pr.write('-');\n        x = -x;\n    }\n    string\
    \ s;\n    while(x > 0) {\n        s.push_back(char('0' + x % 10));\n        x\
    \ /= 10;\n    }\n    reverse(s.begin(), s.end());\n    pr.write(s);\n}\n\nint\
    \ main() {\n    Scanner sc;\n    Printer pr;\n    int n, m;\n    sc.read(n, m);\n\
    \    MinimumCostBFlow<ll, ll> mcf(n);\n    for (int i = 0; i < n; ++i) {\n   \
    \     ll b;\n        sc.read(b);\n        mcf.add_supply(i, b);\n    }\n    for\
    \ (int i = 0; i < m; ++i) {\n        int s, t;\n        ll lower, upper, cost;\n\
    \        sc.read(s, t, lower, upper, cost);\n        mcf.add_edge(s, t, lower,\
    \ upper, cost);\n    }\n\n    auto [ok, cost] = mcf.solve();\n    if(!ok) {\n\
    \        pr.writeln(\"infeasible\");\n        return 0;\n    }\n\n    write_i128(pr,\
    \ cost);\n    pr.writeln();\n    auto potential = mcf.get_potential();\n    for\
    \ (int i = 0; i < n; ++i) {\n        pr.write(potential[i]);\n        pr.write(i\
    \ + 1 == n ? '\\n' : ' ');\n    }\n    auto flow = mcf.get_flows();\n    for (int\
    \ i = 0; i < m; ++i) {\n        pr.writeln(flow[i]);\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/minimum_cost_b_flow.cpp
  isVerificationFile: true
  path: test/yosupo_min_cost_b_flow.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 11:58:39+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_min_cost_b_flow.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_min_cost_b_flow.test.cpp
- /verify/test/yosupo_min_cost_b_flow.test.cpp.html
title: test/yosupo_min_cost_b_flow.test.cpp
---
