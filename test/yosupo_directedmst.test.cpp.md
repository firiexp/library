---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/chu_liu_edmonds.cpp
    title: "\u6700\u5C0F\u5168\u57DF\u6709\u5411\u6728(Chu-Liu/Edmonds)"
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
    PROBLEM: https://judge.yosupo.jp/problem/directedmst
    links:
    - https://judge.yosupo.jp/problem/directedmst
  bundledCode: "#line 1 \"test/yosupo_directedmst.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/directedmst\"\
    \n\n#include <vector>\nusing ll = long long;\nusing namespace std;\n\n#line 1\
    \ \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable {\n  \
    \  char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for\
    \ (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int\
    \ j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n\
    \                x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner\
    \ {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner() : idx(0),\
    \ size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n    \
    \    memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf + len,\
    \ 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n    }\n\
    \n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\
    \n    inline char skip() {\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        return\
    \ buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
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
    #line 1 \"graph/chu_liu_edmonds.cpp\"\ntemplate<class T>\nstruct ChuLiuEdmonds\
    \ {\n    struct Edge {\n        int from, to;\n        T cost;\n    };\n\n   \
    \ struct Result {\n        bool exists;\n        T cost;\n        vector<int>\
    \ parent;\n        vector<int> edge_id;\n    };\n\n    struct UnionFind {\n  \
    \      vector<int> p;\n\n        explicit UnionFind(int n) : p(n, -1) {}\n\n \
    \       int root(int x) {\n            if (p[x] < 0) return x;\n            return\
    \ p[x] = root(p[x]);\n        }\n\n        bool unite(int a, int b) {\n      \
    \      a = root(a);\n            b = root(b);\n            if (a == b) return\
    \ false;\n            if (p[a] > p[b]) swap(a, b);\n            p[a] += p[b];\n\
    \            p[b] = a;\n            return true;\n        }\n    };\n\n    struct\
    \ SkewHeapNode {\n        T key, lazy;\n        int idx;\n        SkewHeapNode\
    \ *l, *r;\n\n        SkewHeapNode(T key, int idx) : key(key), lazy(0), idx(idx),\
    \ l(nullptr), r(nullptr) {}\n    };\n\n    int n, root;\n    vector<Edge> edges;\n\
    \n    explicit ChuLiuEdmonds(int n, int root) : n(n), root(root) {}\n\n    int\
    \ add_edge(int from, int to, T cost) {\n        edges.push_back({from, to, cost});\n\
    \        return (int)edges.size() - 1;\n    }\n\n    static void push(SkewHeapNode\
    \ *node) {\n        if (node == nullptr || node->lazy == T(0)) return;\n     \
    \   if (node->l != nullptr) {\n            node->l->key += node->lazy;\n     \
    \       node->l->lazy += node->lazy;\n        }\n        if (node->r != nullptr)\
    \ {\n            node->r->key += node->lazy;\n            node->r->lazy += node->lazy;\n\
    \        }\n        node->lazy = T(0);\n    }\n\n    static SkewHeapNode* meld(SkewHeapNode\
    \ *a, SkewHeapNode *b) {\n        if (a == nullptr) return b;\n        if (b ==\
    \ nullptr) return a;\n        if (b->key < a->key) swap(a, b);\n        push(a);\n\
    \        a->r = meld(a->r, b);\n        swap(a->l, a->r);\n        return a;\n\
    \    }\n\n    static SkewHeapNode* pop(SkewHeapNode *a) {\n        push(a);\n\
    \        return meld(a->l, a->r);\n    }\n\n    Result solve() const {\n     \
    \   vector<SkewHeapNode> nodes;\n        nodes.reserve(edges.size());\n      \
    \  vector<SkewHeapNode*> come(n, nullptr);\n        for (int i = 0; i < (int)edges.size();\
    \ ++i) {\n            nodes.emplace_back(edges[i].cost, i);\n            come[edges[i].to]\
    \ = meld(come[edges[i].to], &nodes.back());\n        }\n\n        UnionFind uf(n);\n\
    \        vector<int> used(n, -1), from(n, -1), stem(n, -1);\n        vector<T>\
    \ from_cost(n, T(0));\n        vector<int> parent_edge(edges.size(), -1), order;\n\
    \        used[root] = root;\n        T total = T(0);\n\n        for (int start\
    \ = 0; start < n; ++start) {\n            if (used[start] != -1) continue;\n \
    \           int cur = start;\n            vector<int> child_edges;\n         \
    \   int cycle = 0;\n            while (used[cur] == -1 || used[cur] == start)\
    \ {\n                used[cur] = start;\n                while (come[cur] != nullptr\
    \ && uf.root(edges[come[cur]->idx].from) == cur) {\n                    come[cur]\
    \ = pop(come[cur]);\n                }\n                if (come[cur] == nullptr)\
    \ return {false, T(0), {}, {}};\n                int idx = come[cur]->idx;\n \
    \               int src = uf.root(edges[idx].from);\n                T cost =\
    \ come[cur]->key;\n                come[cur] = pop(come[cur]);\n\n           \
    \     from[cur] = src;\n                from_cost[cur] = cost;\n             \
    \   if (stem[cur] == -1) stem[cur] = idx;\n                total += cost;\n  \
    \              order.push_back(idx);\n                while (cycle) {\n      \
    \              parent_edge[child_edges.back()] = idx;\n                    child_edges.pop_back();\n\
    \                    --cycle;\n                }\n                child_edges.push_back(idx);\n\
    \n                if (used[src] == start) {\n                    int p = cur;\n\
    \                    do {\n                        if (come[p] != nullptr) {\n\
    \                            come[p]->key -= from_cost[p];\n                 \
    \           come[p]->lazy -= from_cost[p];\n                        }\n      \
    \                  if (p != cur) {\n                            int pv = p;\n\
    \                            int cv = cur;\n                            uf.unite(pv,\
    \ cv);\n                            cur = uf.root(cv);\n                     \
    \       come[cur] = meld(come[pv], come[cv]);\n                        }\n   \
    \                     p = uf.root(from[p]);\n                        ++cycle;\n\
    \                    } while (p != cur);\n                } else {\n         \
    \           cur = src;\n                }\n            }\n        }\n\n      \
    \  vector<int> used_edge(edges.size(), 0), edge_id(n, -1), parent(n, -1);\n  \
    \      parent[root] = root;\n        for (int i = (int)order.size() - 1; i >=\
    \ 0; --i) {\n            int idx = order[i];\n            if (used_edge[idx])\
    \ continue;\n            int v = edges[idx].to;\n            edge_id[v] = idx;\n\
    \            parent[v] = edges[idx].from;\n            int x = stem[v];\n    \
    \        while (x != idx) {\n                used_edge[x] = 1;\n             \
    \   x = parent_edge[x];\n            }\n        }\n        return {true, total,\
    \ parent, edge_id};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u5168\u57DF\u6709\
    \u5411\u6728(Chu-Liu/Edmonds)\n * @docs _md/chu_liu_edmonds.md\n */\n#line 9 \"\
    test/yosupo_directedmst.test.cpp\"\n\nint main() {\n    Scanner in;\n    Printer\
    \ out;\n    int n, m, r;\n    in.read(n, m, r);\n    ChuLiuEdmonds<ll> dmst(n,\
    \ r);\n    for (int i = 0; i < m; ++i) {\n        int a, b;\n        ll c;\n \
    \       in.read(a, b, c);\n        dmst.add_edge(a, b, c);\n    }\n    auto res\
    \ = dmst.solve();\n    if (!res.exists) return 0;\n    out.writeln(res.cost);\n\
    \    for (int i = 0; i < n; ++i) {\n        if (i) out.write(' ');\n        out.write(res.parent[i]);\n\
    \    }\n    out.writeln();\n    return 0;\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/directedmst\"\n\n#include\
    \ <vector>\nusing ll = long long;\nusing namespace std;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../graph/chu_liu_edmonds.cpp\"\n\nint main() {\n    Scanner in;\n\
    \    Printer out;\n    int n, m, r;\n    in.read(n, m, r);\n    ChuLiuEdmonds<ll>\
    \ dmst(n, r);\n    for (int i = 0; i < m; ++i) {\n        int a, b;\n        ll\
    \ c;\n        in.read(a, b, c);\n        dmst.add_edge(a, b, c);\n    }\n    auto\
    \ res = dmst.solve();\n    if (!res.exists) return 0;\n    out.writeln(res.cost);\n\
    \    for (int i = 0; i < n; ++i) {\n        if (i) out.write(' ');\n        out.write(res.parent[i]);\n\
    \    }\n    out.writeln();\n    return 0;\n}\n\n"
  dependsOn:
  - util/fastio.cpp
  - graph/chu_liu_edmonds.cpp
  isVerificationFile: true
  path: test/yosupo_directedmst.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_directedmst.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_directedmst.test.cpp
- /verify/test/yosupo_directedmst.test.cpp.html
title: test/yosupo_directedmst.test.cpp
---
