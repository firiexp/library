---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/radixheap.cpp
    title: datastructure/radixheap.cpp
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_radix_heap.cpp
    title: "Dijkstra\u6CD5(Radix Heap)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "#line 1 \"test/yosupo_shortest_path_radix_heap.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include <algorithm>\n\
    #include <array>\n#include <limits>\n#include <tuple>\n#include <vector>\nusing\
    \ namespace std;\n\nusing ll = long long;\ntemplate<class T> constexpr T INF =\
    \ ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"util/fastio.cpp\"\n#include\
    \ <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\nusing\
    \ namespace std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr\
    \ FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000; ++i) {\n  \
    \          int x = i;\n            for (int j = 3; j >= 0; --j) {\n          \
    \      num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n      \
    \      }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE\
    \ = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n\
    \    int idx, size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load()\
    \ {\n        int len = size - idx;\n        memmove(buf, buf + idx, len);\n  \
    \      size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx\
    \ = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if\
    \ (idx + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
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
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line\
    \ 1 \"graph/dijkstra_radix_heap.cpp\"\ntemplate <typename T>\nstruct edge {\n\
    \    int from, to; T cost;\n    edge(int to, T cost) : from(-1), to(to), cost(cost)\
    \ {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}\n\
    };\n\n#line 1 \"datastructure/radixheap.cpp\"\ntemplate <class K, class V>\nclass\
    \ RadixHeap {\n    static constexpr int bit_length = sizeof(K)*8;\n    K last;\n\
    \    size_t sz, cnt;\n    \n    array<vector<pair<K, V>>, bit_length> v;\n   \
    \ static inline int bsr(int x){\n        return x ? bit_length-__builtin_clz(x)\
    \ : 0;\n    }\n    static inline int bsr(ll x){\n        return x ? bit_length-__builtin_clzll(x)\
    \ : 0;\n    }\n\n    void pull() {\n        if(cnt < v[0].size()) return;;\n \
    \       int i = 1;\n        while(v[i].empty()) i++;\n        last = min_element(v[i].begin(),v[i].end())->first;\n\
    \        for (auto &&x : v[i]) v[bsr(x.first ^ last)].push_back(x);\n        v[i].clear();\n\
    \    }\npublic:\n    RadixHeap() : last(0), sz(0), cnt(0) {}\n    void emplace(K\
    \ x, V val){\n        sz++;\n        v[bsr(x^last)].emplace_back(x, val);\n  \
    \  }\n\n    pair<K, V> top() {\n        pull();\n        return v[0][cnt];\n \
    \   }\n\n    void pop() {\n        pull();\n        sz--;\n        cnt++;\n  \
    \  }\n\n    size_t size() const { return sz; }\n    bool empty() const { return\
    \ !sz; }\n};\n#line 9 \"graph/dijkstra_radix_heap.cpp\"\n\ntemplate <typename\
    \ T>\nvector<T> dijkstra(int s,vector<vector<edge<T>>> &G){\n    auto n = G.size();\n\
    \    vector<T> d(n, INF<T>);\n    RadixHeap<ll, int> Q;\n    d[s] = 0;\n    Q.emplace(0,\
    \ s);\n    while(!Q.empty()){\n        T cost; int i;\n        tie(cost, i) =\
    \ Q.top(); Q.pop();\n        if(d[i] < cost) continue;\n        for (auto &&e\
    \ : G[i]) {\n            auto cost2 = cost + e.cost;\n            if(d[e.to] <=\
    \ cost2) continue;\n            d[e.to] = cost2;\n            Q.emplace(d[e.to],\
    \ e.to);\n        }\n    }\n    return d;\n}\n\n/**\n * @brief Dijkstra\u6CD5\
    (Radix Heap)\n */\n#line 15 \"test/yosupo_shortest_path_radix_heap.test.cpp\"\n\
    \nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, m, s, t;\n    sc.read(n,\
    \ m, s, t);\n    vector<vector<edge<ll>>> G(n), Ginv(n);\n    for (int i = 0;\
    \ i < m; ++i) {\n        int a, b, c;\n        sc.read(a, b, c);\n        G[a].emplace_back(b,\
    \ c);\n        Ginv[b].emplace_back(a, c);\n    }\n    auto d = dijkstra(s, G);\n\
    \    if (d[t] == INF<ll>) {\n        pr.writeln(-1);\n        return 0;\n    }\n\
    \    vector<int> ans{t};\n    vector<int> visited(n);\n    visited[t] = 1;\n \
    \   while (ans.back() != s) {\n        for (auto &&i : Ginv[ans.back()]) {\n \
    \           if (d[i.to] + i.cost == d[ans.back()] && !visited[i.to]) {\n     \
    \           ans.emplace_back(i.to);\n                visited[i.to] = 1;\n    \
    \            break;\n            }\n        }\n    }\n    pr.writeln(d[t], (int)ans.size()\
    \ - 1);\n    for (int i = (int)ans.size()-1; i > 0; --i) {\n        pr.writeln(ans[i],\
    \ ans[i - 1]);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include\
    \ <algorithm>\n#include <array>\n#include <limits>\n#include <tuple>\n#include\
    \ <vector>\nusing namespace std;\n\nusing ll = long long;\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../graph/dijkstra_radix_heap.cpp\"\n\nint main() {\n    Scanner sc;\n\
    \    Printer pr;\n\n    int n, m, s, t;\n    sc.read(n, m, s, t);\n    vector<vector<edge<ll>>>\
    \ G(n), Ginv(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b, c;\n  \
    \      sc.read(a, b, c);\n        G[a].emplace_back(b, c);\n        Ginv[b].emplace_back(a,\
    \ c);\n    }\n    auto d = dijkstra(s, G);\n    if (d[t] == INF<ll>) {\n     \
    \   pr.writeln(-1);\n        return 0;\n    }\n    vector<int> ans{t};\n    vector<int>\
    \ visited(n);\n    visited[t] = 1;\n    while (ans.back() != s) {\n        for\
    \ (auto &&i : Ginv[ans.back()]) {\n            if (d[i.to] + i.cost == d[ans.back()]\
    \ && !visited[i.to]) {\n                ans.emplace_back(i.to);\n            \
    \    visited[i.to] = 1;\n                break;\n            }\n        }\n  \
    \  }\n    pr.writeln(d[t], (int)ans.size() - 1);\n    for (int i = (int)ans.size()-1;\
    \ i > 0; --i) {\n        pr.writeln(ans[i], ans[i - 1]);\n    }\n    return 0;\n\
    }\n"
  dependsOn:
  - util/fastio.cpp
  - graph/dijkstra_radix_heap.cpp
  - datastructure/radixheap.cpp
  isVerificationFile: true
  path: test/yosupo_shortest_path_radix_heap.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_shortest_path_radix_heap.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_shortest_path_radix_heap.test.cpp
- /verify/test/yosupo_shortest_path_radix_heap.test.cpp.html
title: test/yosupo_shortest_path_radix_heap.test.cpp
---
