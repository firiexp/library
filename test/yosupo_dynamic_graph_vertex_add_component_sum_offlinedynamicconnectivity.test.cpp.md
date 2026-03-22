---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/undoableunionfind.cpp
    title: Undoable Union Find
  - icon: ':heavy_check_mark:'
    path: graph/offlinedynamicconnectivity.cpp
    title: "Dynamic Connectivity (\u30AA\u30D5\u30E9\u30A4\u30F3)"
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
  bundledCode: "#line 1 \"test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n\n#include <algorithm>\n#include <map>\n#include <stack>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#line 15 \"test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp\"\
    \n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value :\
    \ false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
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
    \ */\n#line 1 \"graph/offlinedynamicconnectivity.cpp\"\nusing namespace std;\n\
    \n#line 1 \"datastructure/undoableunionfind.cpp\"\nclass UndoableUnionFind {\n\
    \    stack<pair<int, int>> hist;\n    int forest_size;\n    int snap;\n\npublic:\n\
    \    vector<int> uni;\n\n    explicit UndoableUnionFind(int sz) : forest_size(sz),\
    \ snap(0), uni(sz, -1) {}\n\n    int root(int a) {\n        if (uni[a] < 0) return\
    \ a;\n        return root(uni[a]);\n    }\n\n    bool same(int a, int b) {\n \
    \       return root(a) == root(b);\n    }\n\n    bool unite(int a, int b) {\n\
    \        a = root(a);\n        b = root(b);\n        hist.emplace(a, uni[a]);\n\
    \        hist.emplace(b, uni[b]);\n        if (a == b) return false;\n       \
    \ if (uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n        uni[b]\
    \ = a;\n        forest_size--;\n        return true;\n    }\n\n    int size()\
    \ { return forest_size; }\n    int size(int i) { return -uni[root(i)]; }\n\n \
    \   int get_state() const {\n        return int(hist.size() >> 1);\n    }\n\n\
    \    void undo() {\n        int a = hist.top().first;\n        int ua = hist.top().second;\n\
    \        hist.pop();\n        int b = hist.top().first;\n        int ub = hist.top().second;\n\
    \        hist.pop();\n        if (a != b) forest_size++;\n        uni[a] = ua;\n\
    \        uni[b] = ub;\n    }\n\n    void snapshot() {\n        snap = get_state();\n\
    \    }\n\n    void rollback(int state = -1) {\n        if (state == -1) state\
    \ = snap;\n        while (get_state() > state) undo();\n    }\n};\n\n/**\n * @brief\
    \ Undoable Union Find\n */\n#line 4 \"graph/offlinedynamicconnectivity.cpp\"\n\
    \nstruct OfflineDynamicConnectivity {\n    int n, q, sz;\n    UndoableUnionFind\
    \ uf;\n    vector<vector<pair<int, int>>> seg;\n    vector<pair<pair<int, int>,\
    \ pair<int, int>>> pend;\n    map<pair<int, int>, int> cnt, appear;\n\n    explicit\
    \ OfflineDynamicConnectivity(int n, int q) : n(n), q(q), uf(n) {\n        sz =\
    \ 1;\n        while (sz < q) sz <<= 1;\n        seg.resize(2 * sz);\n    }\n\n\
    \    void add_segment(int l, int r, const pair<int, int> &e) {\n        for (l\
    \ += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) seg[l++].push_back(e);\n\
    \            if (r & 1) seg[--r].push_back(e);\n        }\n    }\n\n    void insert(int\
    \ t, int a, int b) {\n        auto e = minmax(a, b);\n        if (cnt[e]++ ==\
    \ 0) appear[e] = t;\n    }\n\n    void erase(int t, int a, int b) {\n        auto\
    \ e = minmax(a, b);\n        if (--cnt[e] == 0) {\n            pend.emplace_back(make_pair(appear[e],\
    \ t), e);\n            appear.erase(e);\n        }\n    }\n\n    void build()\
    \ {\n        for (auto &&[e, c] : cnt) {\n            if (!c) continue;\n    \
    \        pend.emplace_back(make_pair(appear[e], q), e);\n        }\n        for\
    \ (auto &&[range, e] : pend) add_segment(range.first, range.second, e);\n    }\n\
    \n    template <class Enter, class Leave, class Leaf>\n    void dfs(const Enter\
    \ &enter, const Leave &leave, const Leaf &leaf, int k = 1) {\n        enter(k,\
    \ seg[k]);\n        if (k < sz) {\n            dfs(enter, leave, leaf, k << 1);\n\
    \            dfs(enter, leave, leaf, k << 1 | 1);\n        } else if (k - sz <\
    \ q) {\n            leaf(k - sz);\n        }\n        leave(k, seg[k]);\n    }\n\
    \n    template <class F>\n    void run(const F &f) {\n        dfs(\n         \
    \   [&](int, const vector<pair<int, int>> &edges) {\n                for (auto\
    \ &&[u, v] : edges) uf.unite(u, v);\n            },\n            [&](int, const\
    \ vector<pair<int, int>> &edges) {\n                for (int i = 0; i < (int)edges.size();\
    \ ++i) uf.undo();\n            },\n            [&](int t) {\n                if\
    \ constexpr (is_invocable_v<F, int, UndoableUnionFind &>) {\n                \
    \    f(t, uf);\n                } else {\n                    f(t);\n        \
    \        }\n            }\n        );\n    }\n};\n\n/**\n * @brief \u30AA\u30D5\
    \u30E9\u30A4\u30F3\u52D5\u7684\u9023\u7D50\u6027(Offline Dynamic Connectivity)\n\
    \ */\n#line 18 \"test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp\"\
    \n\nstruct RollbackUnionFindComponentSum {\n    struct History {\n        int\
    \ child, parent;\n        int parent_size, child_size;\n        long long parent_sum,\
    \ child_sum;\n    };\n\n    vector<int> parent_or_size;\n    vector<long long>\
    \ comp_sum;\n    vector<History> history;\n\n    explicit RollbackUnionFindComponentSum(int\
    \ n, const vector<long long> &a)\n        : parent_or_size(n, -1), comp_sum(a)\
    \ {}\n\n    int root(int v) const {\n        while (parent_or_size[v] >= 0) v\
    \ = parent_or_size[v];\n        return v;\n    }\n\n    int snapshot() const {\n\
    \        return (int)history.size();\n    }\n\n    void rollback(int snap) {\n\
    \        while ((int)history.size() > snap) {\n            auto h = history.back();\n\
    \            history.pop_back();\n            if (h.parent == -1) continue;\n\
    \            parent_or_size[h.parent] = h.parent_size;\n            parent_or_size[h.child]\
    \ = h.child_size;\n            comp_sum[h.parent] = h.parent_sum;\n          \
    \  comp_sum[h.child] = h.child_sum;\n        }\n    }\n\n    void unite(int a,\
    \ int b) {\n        a = root(a), b = root(b);\n        if (a == b) {\n       \
    \     history.push_back({-1, -1, 0, 0, 0, 0});\n            return;\n        }\n\
    \        if (parent_or_size[a] > parent_or_size[b]) swap(a, b);\n        history.push_back({b,\
    \ a, parent_or_size[a], parent_or_size[b], comp_sum[a], comp_sum[b]});\n     \
    \   parent_or_size[a] += parent_or_size[b];\n        parent_or_size[b] = a;\n\
    \        comp_sum[a] += comp_sum[b];\n    }\n\n    void add_value(int v, long\
    \ long x) {\n        int r = root(v);\n        history.push_back({r, r, parent_or_size[r],\
    \ parent_or_size[r], comp_sum[r], comp_sum[r]});\n        comp_sum[r] += x;\n\
    \    }\n\n    long long get_sum(int v) const {\n        return comp_sum[root(v)];\n\
    \    }\n};\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n\
    \    sc.read(n, q);\n    vector<long long> a(n);\n    for (auto &x : a) sc.read(x);\n\
    \n    OfflineDynamicConnectivity dc(n, q);\n    struct AddEvent {\n        int\
    \ v;\n        long long x;\n    };\n    vector<vector<AddEvent>> seg_adds(2 *\
    \ dc.sz);\n    vector<int> type(q), query_vertex(q, -1);\n\n    auto add_segment\
    \ = [&](int l, int r, const AddEvent &event) {\n        for (l += dc.sz, r +=\
    \ dc.sz; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) seg_adds[l++].push_back(event);\n\
    \            if (r & 1) seg_adds[--r].push_back(event);\n        }\n    };\n\n\
    \    for (int t = 0; t < q; ++t) {\n        sc.read(type[t]);\n        if (type[t]\
    \ == 0) {\n            int u, v;\n            sc.read(u, v);\n            dc.insert(t,\
    \ u, v);\n        } else if (type[t] == 1) {\n            int u, v;\n        \
    \    sc.read(u, v);\n            dc.erase(t, u, v);\n        } else if (type[t]\
    \ == 2) {\n            int v;\n            long long x;\n            sc.read(v,\
    \ x);\n            add_segment(t, q, {v, x});\n        } else {\n            sc.read(query_vertex[t]);\n\
    \        }\n    }\n    dc.build();\n\n    RollbackUnionFindComponentSum uf(n,\
    \ a);\n    vector<int> snaps;\n    vector<long long> ans;\n    ans.reserve(q);\n\
    \n    dc.dfs(\n        [&](int k, const vector<pair<int, int>> &edges) {\n   \
    \         snaps.push_back(uf.snapshot());\n            for (auto &&[u, v] : edges)\
    \ uf.unite(u, v);\n            for (auto &&event : seg_adds[k]) uf.add_value(event.v,\
    \ event.x);\n        },\n        [&](int, const vector<pair<int, int>> &) {\n\
    \            uf.rollback(snaps.back());\n            snaps.pop_back();\n     \
    \   },\n        [&](int t) {\n            if (type[t] == 3) ans.push_back(uf.get_sum(query_vertex[t]));\n\
    \        }\n    );\n\n    for (auto &&x : ans) pr.println(x);\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n\n#include <algorithm>\n#include <map>\n#include <stack>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../graph/offlinedynamicconnectivity.cpp\"\n\nstruct RollbackUnionFindComponentSum\
    \ {\n    struct History {\n        int child, parent;\n        int parent_size,\
    \ child_size;\n        long long parent_sum, child_sum;\n    };\n\n    vector<int>\
    \ parent_or_size;\n    vector<long long> comp_sum;\n    vector<History> history;\n\
    \n    explicit RollbackUnionFindComponentSum(int n, const vector<long long> &a)\n\
    \        : parent_or_size(n, -1), comp_sum(a) {}\n\n    int root(int v) const\
    \ {\n        while (parent_or_size[v] >= 0) v = parent_or_size[v];\n        return\
    \ v;\n    }\n\n    int snapshot() const {\n        return (int)history.size();\n\
    \    }\n\n    void rollback(int snap) {\n        while ((int)history.size() >\
    \ snap) {\n            auto h = history.back();\n            history.pop_back();\n\
    \            if (h.parent == -1) continue;\n            parent_or_size[h.parent]\
    \ = h.parent_size;\n            parent_or_size[h.child] = h.child_size;\n    \
    \        comp_sum[h.parent] = h.parent_sum;\n            comp_sum[h.child] = h.child_sum;\n\
    \        }\n    }\n\n    void unite(int a, int b) {\n        a = root(a), b =\
    \ root(b);\n        if (a == b) {\n            history.push_back({-1, -1, 0, 0,\
    \ 0, 0});\n            return;\n        }\n        if (parent_or_size[a] > parent_or_size[b])\
    \ swap(a, b);\n        history.push_back({b, a, parent_or_size[a], parent_or_size[b],\
    \ comp_sum[a], comp_sum[b]});\n        parent_or_size[a] += parent_or_size[b];\n\
    \        parent_or_size[b] = a;\n        comp_sum[a] += comp_sum[b];\n    }\n\n\
    \    void add_value(int v, long long x) {\n        int r = root(v);\n        history.push_back({r,\
    \ r, parent_or_size[r], parent_or_size[r], comp_sum[r], comp_sum[r]});\n     \
    \   comp_sum[r] += x;\n    }\n\n    long long get_sum(int v) const {\n       \
    \ return comp_sum[root(v)];\n    }\n};\n\nint main() {\n    Scanner sc;\n    Printer\
    \ pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<long long> a(n);\n    for\
    \ (auto &x : a) sc.read(x);\n\n    OfflineDynamicConnectivity dc(n, q);\n    struct\
    \ AddEvent {\n        int v;\n        long long x;\n    };\n    vector<vector<AddEvent>>\
    \ seg_adds(2 * dc.sz);\n    vector<int> type(q), query_vertex(q, -1);\n\n    auto\
    \ add_segment = [&](int l, int r, const AddEvent &event) {\n        for (l +=\
    \ dc.sz, r += dc.sz; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) seg_adds[l++].push_back(event);\n\
    \            if (r & 1) seg_adds[--r].push_back(event);\n        }\n    };\n\n\
    \    for (int t = 0; t < q; ++t) {\n        sc.read(type[t]);\n        if (type[t]\
    \ == 0) {\n            int u, v;\n            sc.read(u, v);\n            dc.insert(t,\
    \ u, v);\n        } else if (type[t] == 1) {\n            int u, v;\n        \
    \    sc.read(u, v);\n            dc.erase(t, u, v);\n        } else if (type[t]\
    \ == 2) {\n            int v;\n            long long x;\n            sc.read(v,\
    \ x);\n            add_segment(t, q, {v, x});\n        } else {\n            sc.read(query_vertex[t]);\n\
    \        }\n    }\n    dc.build();\n\n    RollbackUnionFindComponentSum uf(n,\
    \ a);\n    vector<int> snaps;\n    vector<long long> ans;\n    ans.reserve(q);\n\
    \n    dc.dfs(\n        [&](int k, const vector<pair<int, int>> &edges) {\n   \
    \         snaps.push_back(uf.snapshot());\n            for (auto &&[u, v] : edges)\
    \ uf.unite(u, v);\n            for (auto &&event : seg_adds[k]) uf.add_value(event.v,\
    \ event.x);\n        },\n        [&](int, const vector<pair<int, int>> &) {\n\
    \            uf.rollback(snaps.back());\n            snaps.pop_back();\n     \
    \   },\n        [&](int t) {\n            if (type[t] == 3) ans.push_back(uf.get_sum(query_vertex[t]));\n\
    \        }\n    );\n\n    for (auto &&x : ans) pr.println(x);\n    return 0;\n\
    }\n"
  dependsOn:
  - util/fastio.cpp
  - graph/offlinedynamicconnectivity.cpp
  - datastructure/undoableunionfind.cpp
  isVerificationFile: true
  path: test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
- /verify/test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp.html
title: test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
---
