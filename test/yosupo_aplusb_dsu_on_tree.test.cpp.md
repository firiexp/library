---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/dsu_on_tree.cpp
    title: DSU on Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_dsu_on_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <random>\n\
    #include <vector>\nusing namespace std;\n\nusing ll = long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
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
    \ */\n#line 1 \"tree/dsu_on_tree.cpp\"\nstruct DSUonTree {\n    int n, root;\n\
    \    vector<pair<int, int>> edges;\n    vector<int> start, to;\n    vector<int>\
    \ sub_size, heavy;\n    vector<int> order, dfn;\n\n    explicit DSUonTree(int\
    \ n = 0) : n(n), root(0) {\n        edges.reserve(max(0, n - 1));\n    }\n\n \
    \   template<class G>\n    explicit DSUonTree(const vector<vector<G>> &g, int\
    \ root = 0) : DSUonTree((int)g.size()) {\n        vector<int> parent(n, -2);\n\
    \        vector<int> st(1, root);\n        parent[root] = -1;\n        while (!st.empty())\
    \ {\n            int v = st.back();\n            st.pop_back();\n            for\
    \ (auto &&u : g[v]) {\n                if (u == parent[v] || parent[u] != -2)\
    \ continue;\n                parent[u] = v;\n                edges.emplace_back(v,\
    \ u);\n                st.push_back(u);\n            }\n        }\n        build(root);\n\
    \    }\n\n    void add_edge(int u, int v) {\n        edges.emplace_back(u, v);\n\
    \    }\n\n    void build(int root = 0) {\n        this->root = root;\n       \
    \ start.assign(n + 1, 0);\n        to.assign(edges.size() * 2, 0);\n        for\
    \ (auto &&[u, v] : edges) {\n            ++start[u + 1];\n            ++start[v\
    \ + 1];\n        }\n        for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n\
    \        auto counter = start;\n        for (auto &&[u, v] : edges) {\n      \
    \      to[counter[u]++] = v;\n            to[counter[v]++] = u;\n        }\n \
    \       build_dfs();\n    }\n\n    int idx(int v) const {\n        return dfn[v];\n\
    \    }\n\n    int begin(int v) const {\n        return dfn[v];\n    }\n\n    int\
    \ end(int v) const {\n        return dfn[v] + sub_size[v];\n    }\n\n    template<class\
    \ ADD, class QUERY, class REMOVE>\n    void run_add_remove(ADD add, QUERY query,\
    \ REMOVE remove) const {\n        auto dfs = [&](auto &&self, int v, int p, bool\
    \ keep) -> void {\n            for (int ei = start[v]; ei < start[v + 1]; ++ei)\
    \ {\n                int u = to[ei];\n                if (u == p || u == heavy[v])\
    \ continue;\n                self(self, u, v, false);\n            }\n       \
    \     if (heavy[v] != -1) self(self, heavy[v], v, true);\n            for (int\
    \ ei = start[v]; ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n\
    \                if (u == p || u == heavy[v]) continue;\n                for (int\
    \ i = dfn[u]; i < dfn[u] + sub_size[u]; ++i) add(order[i]);\n            }\n \
    \           add(v);\n            query(v);\n            if (!keep) {\n       \
    \         for (int i = dfn[v]; i < dfn[v] + sub_size[v]; ++i) remove(order[i]);\n\
    \            }\n        };\n        dfs(dfs, root, -1, false);\n    }\n\n    template<class\
    \ ADD, class QUERY, class RESET>\n    void run_add_reset(ADD add, QUERY query,\
    \ RESET reset) const {\n        int L = 0, R = 0;\n        for (int i = n - 1;\
    \ i >= 0; --i) {\n            int v = order[i];\n            if (sub_size[v] ==\
    \ 1) {\n                reset();\n                L = R = dfn[v];\n          \
    \  }\n            while (L > dfn[v]) add(order[--L]);\n            while (R <\
    \ dfn[v] + sub_size[v]) add(order[R++]);\n            query(v);\n        }\n \
    \       reset();\n    }\n\nprivate:\n    void build_dfs() {\n        sub_size.assign(n,\
    \ 0);\n        heavy.assign(n, -1);\n        auto dfs_size = [&](auto &&self,\
    \ int v, int p) -> void {\n            sub_size[v] = 1;\n            for (int\
    \ ei = start[v]; ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n\
    \                if (u == p) continue;\n                self(self, u, v);\n  \
    \              sub_size[v] += sub_size[u];\n                if (heavy[v] == -1\
    \ || sub_size[u] > sub_size[heavy[v]]) {\n                    heavy[v] = u;\n\
    \                }\n            }\n        };\n        dfs_size(dfs_size, root,\
    \ -1);\n        dfn.assign(n, 0);\n        order.clear();\n        order.reserve(n);\n\
    \        auto dfs_order = [&](auto &&self, int v, int p) -> void {\n         \
    \   dfn[v] = (int)order.size();\n            order.push_back(v);\n           \
    \ if (heavy[v] != -1) self(self, heavy[v], v);\n            for (int ei = start[v];\
    \ ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n              \
    \  if (u == p || u == heavy[v]) continue;\n                self(self, u, v);\n\
    \            }\n        };\n        dfs_order(dfs_order, root, -1);\n    }\n};\n\
    \n/**\n * @brief DSU on Tree\n */\n#line 17 \"test/yosupo_aplusb_dsu_on_tree.test.cpp\"\
    \n\nbool is_ancestor(const vector<int> &parent, int a, int v) {\n    while (v\
    \ != -1) {\n        if (v == a) return true;\n        v = parent[v];\n    }\n\
    \    return false;\n}\n\nvector<ll> run_with_clear(const DSUonTree &dsu, const\
    \ vector<ll> &w) {\n    int n = w.size();\n    vector<ll> ans(n, -1);\n    ll\
    \ cur = 0;\n    auto add = [&](int v) {\n        cur += w[v];\n    };\n    auto\
    \ query = [&](int v) {\n        ans[v] = cur;\n    };\n    auto remove = [&](int\
    \ v) {\n        cur -= w[v];\n    };\n    dsu.run_add_remove(add, query, remove);\n\
    \    return ans;\n}\n\nvector<ll> run_with_reset(const DSUonTree &dsu, const vector<ll>\
    \ &w) {\n    vector<ll> ans(w.size(), -1);\n    ll cur = 0;\n    auto add = [&](int\
    \ v) {\n        cur += w[v];\n    };\n    auto query = [&](int v) {\n        ans[v]\
    \ = cur;\n    };\n    auto reset = [&]() {\n        cur = 0;\n    };\n    dsu.run_add_reset(add,\
    \ query, reset);\n    assert(cur == 0);\n    return ans;\n}\n\nvoid self_check()\
    \ {\n    mt19937 rng(0);\n    for (int tc = 0; tc < 300; ++tc) {\n        int\
    \ n = rng() % 40 + 1;\n        vector<int> parent(n, -1);\n        vector<vector<int>>\
    \ g(n);\n        for (int v = 1; v < n; ++v) {\n            parent[v] = rng()\
    \ % v;\n            g[parent[v]].push_back(v);\n            g[v].push_back(parent[v]);\n\
    \        }\n\n        vector<ll> w(n);\n        for (auto &&x : w) x = (int)(rng()\
    \ % 2001) - 1000;\n\n        vector<ll> want = w;\n        vector<int> sub_size(n,\
    \ 1);\n        for (int v = n - 1; v >= 1; --v) {\n            want[parent[v]]\
    \ += want[v];\n            sub_size[parent[v]] += sub_size[v];\n        }\n\n\
    \        DSUonTree dsu1(g, 0);\n        DSUonTree dsu2(n);\n        for (int v\
    \ = 1; v < n; ++v) dsu2.add_edge(parent[v], v);\n        dsu2.build(0);\n\n  \
    \      for (auto &&dsu : {dsu1, dsu2}) {\n            assert(run_with_clear(dsu,\
    \ w) == want);\n            assert(run_with_reset(dsu, w) == want);\n        \
    \    for (int v = 0; v < n; ++v) {\n                assert(dsu.end(v) - dsu.begin(v)\
    \ == sub_size[v]);\n                for (int u = 0; u < n; ++u) {\n          \
    \          bool in = dsu.begin(v) <= dsu.idx(u) && dsu.idx(u) < dsu.end(v);\n\
    \                    assert(in == is_ancestor(parent, v, u));\n              \
    \  }\n            }\n        }\n    }\n}\n\nint main() {\n    self_check();\n\n\
    \    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <random>\n#include <vector>\nusing namespace std;\n\nusing ll = long\
    \ long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include\
    \ <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../tree/dsu_on_tree.cpp\"\
    \n\nbool is_ancestor(const vector<int> &parent, int a, int v) {\n    while (v\
    \ != -1) {\n        if (v == a) return true;\n        v = parent[v];\n    }\n\
    \    return false;\n}\n\nvector<ll> run_with_clear(const DSUonTree &dsu, const\
    \ vector<ll> &w) {\n    int n = w.size();\n    vector<ll> ans(n, -1);\n    ll\
    \ cur = 0;\n    auto add = [&](int v) {\n        cur += w[v];\n    };\n    auto\
    \ query = [&](int v) {\n        ans[v] = cur;\n    };\n    auto remove = [&](int\
    \ v) {\n        cur -= w[v];\n    };\n    dsu.run_add_remove(add, query, remove);\n\
    \    return ans;\n}\n\nvector<ll> run_with_reset(const DSUonTree &dsu, const vector<ll>\
    \ &w) {\n    vector<ll> ans(w.size(), -1);\n    ll cur = 0;\n    auto add = [&](int\
    \ v) {\n        cur += w[v];\n    };\n    auto query = [&](int v) {\n        ans[v]\
    \ = cur;\n    };\n    auto reset = [&]() {\n        cur = 0;\n    };\n    dsu.run_add_reset(add,\
    \ query, reset);\n    assert(cur == 0);\n    return ans;\n}\n\nvoid self_check()\
    \ {\n    mt19937 rng(0);\n    for (int tc = 0; tc < 300; ++tc) {\n        int\
    \ n = rng() % 40 + 1;\n        vector<int> parent(n, -1);\n        vector<vector<int>>\
    \ g(n);\n        for (int v = 1; v < n; ++v) {\n            parent[v] = rng()\
    \ % v;\n            g[parent[v]].push_back(v);\n            g[v].push_back(parent[v]);\n\
    \        }\n\n        vector<ll> w(n);\n        for (auto &&x : w) x = (int)(rng()\
    \ % 2001) - 1000;\n\n        vector<ll> want = w;\n        vector<int> sub_size(n,\
    \ 1);\n        for (int v = n - 1; v >= 1; --v) {\n            want[parent[v]]\
    \ += want[v];\n            sub_size[parent[v]] += sub_size[v];\n        }\n\n\
    \        DSUonTree dsu1(g, 0);\n        DSUonTree dsu2(n);\n        for (int v\
    \ = 1; v < n; ++v) dsu2.add_edge(parent[v], v);\n        dsu2.build(0);\n\n  \
    \      for (auto &&dsu : {dsu1, dsu2}) {\n            assert(run_with_clear(dsu,\
    \ w) == want);\n            assert(run_with_reset(dsu, w) == want);\n        \
    \    for (int v = 0; v < n; ++v) {\n                assert(dsu.end(v) - dsu.begin(v)\
    \ == sub_size[v]);\n                for (int u = 0; u < n; ++u) {\n          \
    \          bool in = dsu.begin(v) <= dsu.idx(u) && dsu.idx(u) < dsu.end(v);\n\
    \                    assert(in == is_ancestor(parent, v, u));\n              \
    \  }\n            }\n        }\n    }\n}\n\nint main() {\n    self_check();\n\n\
    \    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/dsu_on_tree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_dsu_on_tree.test.cpp
  requiredBy: []
  timestamp: '2026-04-19 01:08:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_dsu_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_dsu_on_tree.test.cpp
- /verify/test/yosupo_aplusb_dsu_on_tree.test.cpp.html
title: test/yosupo_aplusb_dsu_on_tree.test.cpp
---
