---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/tree_hash.cpp
    title: "\u6728\u30CF\u30C3\u30B7\u30E5(Tree Hash)"
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
    PROBLEM: https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
    links:
    - https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
  bundledCode: "#line 1 \"test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <map>\n#include <random>\n\
    #include <string>\n#include <vector>\nusing namespace std;\n\nusing ll = long\
    \ long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#line 18 \"test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp\"\
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
    \ */\n#line 1 \"tree/tree_hash.cpp\"\nstruct TreeHash {\n    int n;\n    vector<vector<int>>\
    \ g;\n    vector<int> parent, order, hash_id;\n    int kind_count;\n\n    explicit\
    \ TreeHash(int n)\n        : n(n), g(n), parent(n, -1), hash_id(n, -1), kind_count(0)\
    \ {}\n\n    void add_edge(int u, int v) {\n        g[u].push_back(v);\n      \
    \  g[v].push_back(u);\n    }\n\n    vector<int> build(int root = 0) {\n      \
    \  order.clear();\n        order.reserve(n);\n        parent.assign(n, -1);\n\
    \        vector<int> st(1, root);\n        parent[root] = root;\n        while\
    \ (!st.empty()) {\n            int v = st.back();\n            st.pop_back();\n\
    \            order.push_back(v);\n            for (int to : g[v]) {\n        \
    \        if (to == parent[v]) continue;\n                parent[to] = v;\n   \
    \             st.push_back(to);\n            }\n        }\n\n        map<vector<int>,\
    \ int> ids;\n        for (int i = n - 1; i >= 0; --i) {\n            int v = order[i];\n\
    \            vector<int> ch;\n            ch.reserve(g[v].size() - (v != root));\n\
    \            for (int to : g[v]) {\n                if (to == parent[v]) continue;\n\
    \                ch.push_back(hash_id[to]);\n            }\n            sort(ch.begin(),\
    \ ch.end());\n            auto [it, inserted] = ids.emplace(ch, (int)ids.size());\n\
    \            hash_id[v] = it->second;\n        }\n        kind_count = ids.size();\n\
    \        return hash_id;\n    }\n\n    int operator[](int v) const {\n       \
    \ return hash_id[v];\n    }\n\n    int kinds() const {\n        return kind_count;\n\
    \    }\n};\n\n/**\n * @brief \u6728\u30CF\u30C3\u30B7\u30E5(Tree Hash)\n */\n\
    #line 22 \"test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp\"\
    \n\nstring canonical_dfs(int v, const vector<vector<int>> &ch) {\n    vector<string>\
    \ subs;\n    subs.reserve(ch[v].size());\n    for (int to : ch[v]) subs.push_back(canonical_dfs(to,\
    \ ch));\n    sort(subs.begin(), subs.end());\n    string res = \"(\";\n    for\
    \ (const auto &s : subs) res += s;\n    res += \")\";\n    return res;\n}\n\n\
    void self_check() {\n    mt19937 rng(0);\n    for (int tc = 0; tc < 300; ++tc)\
    \ {\n        int n = rng() % 30 + 1;\n        int root = rng() % n;\n        vector<pair<int,\
    \ int>> edges;\n        vector<vector<int>> g(n);\n        for (int v = 1; v <\
    \ n; ++v) {\n            int p = rng() % v;\n            edges.push_back({p, v});\n\
    \            g[p].push_back(v);\n            g[v].push_back(p);\n        }\n\n\
    \        vector<int> parent(n, -1), order;\n        order.reserve(n);\n      \
    \  vector<int> st(1, root);\n        parent[root] = root;\n        while (!st.empty())\
    \ {\n            int v = st.back();\n            st.pop_back();\n            order.push_back(v);\n\
    \            for (int to : g[v]) {\n                if (to == parent[v]) continue;\n\
    \                parent[to] = v;\n                st.push_back(to);\n        \
    \    }\n        }\n\n        vector<vector<int>> ch(n);\n        for (int v =\
    \ 0; v < n; ++v) {\n            if (v == root) continue;\n            ch[parent[v]].push_back(v);\n\
    \        }\n\n        vector<string> canon(n);\n        for (int i = n - 1; i\
    \ >= 0; --i) canon[order[i]] = canonical_dfs(order[i], ch);\n\n        TreeHash\
    \ th(n);\n        for (auto [u, v] : edges) th.add_edge(u, v);\n        auto id\
    \ = th.build(root);\n\n        map<string, int> expect;\n        for (int v =\
    \ 0; v < n; ++v) {\n            if (!expect.count(canon[v])) expect[canon[v]]\
    \ = expect.size();\n        }\n        assert(th.kinds() == (int)expect.size());\n\
    \        for (int i = 0; i < n; ++i) {\n            for (int j = 0; j < n; ++j)\
    \ {\n                assert((id[i] == id[j]) == (canon[i] == canon[j]));\n   \
    \         }\n        }\n    }\n}\n\nint main() {\n    self_check();\n\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int n;\n    sc.read(n);\n    TreeHash th(n);\n \
    \   for (int v = 1; v < n; ++v) {\n        int p;\n        sc.read(p);\n     \
    \   th.add_edge(p, v);\n    }\n    auto id = th.build(0);\n    pr.println(th.kinds());\n\
    \    for (int i = 0; i < n; ++i) {\n        pr.print(id[i]);\n        pr.print(i\
    \ + 1 == n ? '\\n' : ' ');\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <map>\n#include <random>\n\
    #include <string>\n#include <vector>\nusing namespace std;\n\nusing ll = long\
    \ long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../tree/tree_hash.cpp\"\n\nstring canonical_dfs(int v, const vector<vector<int>>\
    \ &ch) {\n    vector<string> subs;\n    subs.reserve(ch[v].size());\n    for (int\
    \ to : ch[v]) subs.push_back(canonical_dfs(to, ch));\n    sort(subs.begin(), subs.end());\n\
    \    string res = \"(\";\n    for (const auto &s : subs) res += s;\n    res +=\
    \ \")\";\n    return res;\n}\n\nvoid self_check() {\n    mt19937 rng(0);\n   \
    \ for (int tc = 0; tc < 300; ++tc) {\n        int n = rng() % 30 + 1;\n      \
    \  int root = rng() % n;\n        vector<pair<int, int>> edges;\n        vector<vector<int>>\
    \ g(n);\n        for (int v = 1; v < n; ++v) {\n            int p = rng() % v;\n\
    \            edges.push_back({p, v});\n            g[p].push_back(v);\n      \
    \      g[v].push_back(p);\n        }\n\n        vector<int> parent(n, -1), order;\n\
    \        order.reserve(n);\n        vector<int> st(1, root);\n        parent[root]\
    \ = root;\n        while (!st.empty()) {\n            int v = st.back();\n   \
    \         st.pop_back();\n            order.push_back(v);\n            for (int\
    \ to : g[v]) {\n                if (to == parent[v]) continue;\n             \
    \   parent[to] = v;\n                st.push_back(to);\n            }\n      \
    \  }\n\n        vector<vector<int>> ch(n);\n        for (int v = 0; v < n; ++v)\
    \ {\n            if (v == root) continue;\n            ch[parent[v]].push_back(v);\n\
    \        }\n\n        vector<string> canon(n);\n        for (int i = n - 1; i\
    \ >= 0; --i) canon[order[i]] = canonical_dfs(order[i], ch);\n\n        TreeHash\
    \ th(n);\n        for (auto [u, v] : edges) th.add_edge(u, v);\n        auto id\
    \ = th.build(root);\n\n        map<string, int> expect;\n        for (int v =\
    \ 0; v < n; ++v) {\n            if (!expect.count(canon[v])) expect[canon[v]]\
    \ = expect.size();\n        }\n        assert(th.kinds() == (int)expect.size());\n\
    \        for (int i = 0; i < n; ++i) {\n            for (int j = 0; j < n; ++j)\
    \ {\n                assert((id[i] == id[j]) == (canon[i] == canon[j]));\n   \
    \         }\n        }\n    }\n}\n\nint main() {\n    self_check();\n\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int n;\n    sc.read(n);\n    TreeHash th(n);\n \
    \   for (int v = 1; v < n; ++v) {\n        int p;\n        sc.read(p);\n     \
    \   th.add_edge(p, v);\n    }\n    auto id = th.build(0);\n    pr.println(th.kinds());\n\
    \    for (int i = 0; i < n; ++i) {\n        pr.print(id[i]);\n        pr.print(i\
    \ + 1 == n ? '\\n' : ' ');\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/tree_hash.cpp
  isVerificationFile: true
  path: test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
- /verify/test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp.html
title: test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
---
