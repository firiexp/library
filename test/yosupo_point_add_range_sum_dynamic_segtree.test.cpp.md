---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/dynamic_segtree.cpp
    title: Dynamic Segment Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n\
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
    \ */\n#line 1 \"datastructure/segmenttree/dynamic_segtree.cpp\"\ntemplate <class\
    \ M>\nstruct DynamicSegmentTree{\n    using T = typename M::T;\n    struct Node{\n\
    \        T val;\n        int l, r;\n    };\n\n    long long n{};\n    vector<Node>\
    \ node;\n    int root;\n\n    explicit DynamicSegmentTree(long long n): n(n),\
    \ root(-1) {}\n\n    void reserve(size_t sz){\n        node.reserve(sz);\n   \
    \ }\n\n    void update(long long k, const T &x){\n        if(n == 0) return;\n\
    \        update_(root, k, x, 0, n);\n    }\n\n    void add(long long k, const\
    \ T &x){\n        if(n == 0) return;\n        add_(root, k, x, 0, n);\n    }\n\
    \n    T query(long long a, long long b) const {\n        if(n == 0 || b <= a)\
    \ return M::e();\n        return query_(root, a, b, 0, n);\n    }\n\n    T get(long\
    \ long k) const { return query(k, k+1); }\n    T operator[](const long long &k)\
    \ const { return get(k); }\n\nprivate:\n    int make_node(const T &v, int l, int\
    \ r){\n        node.push_back({v, l, r});\n        return (int)node.size()-1;\n\
    \    }\n\n    void update_(int &id, long long k, const T &x, long long l, long\
    \ long r){\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        if(l+1\
    \ == r){\n            node[id].val = x;\n            return;\n        }\n    \
    \    long long m = l + ((r-l)>>1);\n        if(k < m){\n            int child\
    \ = node[id].l;\n            update_(child, k, x, l, m);\n            node[id].l\
    \ = child;\n        }else{\n            int child = node[id].r;\n            update_(child,\
    \ k, x, m, r);\n            node[id].r = child;\n        }\n        node[id].val\
    \ = M::f(value(node[id].l), value(node[id].r));\n    }\n\n    void add_(int &id,\
    \ long long k, const T &x, long long l, long long r){\n        if(id == -1) id\
    \ = make_node(M::e(), -1, -1);\n        if(l+1 == r){\n            node[id].val\
    \ = M::f(node[id].val, x);\n            return;\n        }\n        long long\
    \ m = l + ((r-l)>>1);\n        if(k < m){\n            int child = node[id].l;\n\
    \            add_(child, k, x, l, m);\n            node[id].l = child;\n     \
    \   }else{\n            int child = node[id].r;\n            add_(child, k, x,\
    \ m, r);\n            node[id].r = child;\n        }\n        node[id].val = M::f(value(node[id].l),\
    \ value(node[id].r));\n    }\n\n    T query_(int id, long long a, long long b,\
    \ long long l, long long r) const {\n        if(id == -1 || r <= a || b <= l)\
    \ return M::e();\n        if(a <= l && r <= b) return node[id].val;\n        long\
    \ long m = l + ((r-l)>>1);\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n\n    T value(int id) const {\n   \
    \     return id == -1 ? M::e() : node[id].val;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = long long;\n    static T f(T a, T b) { return a + b; }\n    static\
    \ T e() { return 0; }\n};\n*/\n\n/**\n * @brief Dynamic Segment Tree\n */\n#line\
    \ 13 \"test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp\"\n\nstruct Monoid{\n\
    \    using T = long long;\n    static T f(T a, T b) { return a + b; }\n    static\
    \ T e() { return 0; }\n};\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n\
    \    int n, q;\n    sc.read(n, q);\n    DynamicSegmentTree<Monoid> seg(n);\n \
    \   if (n > 0) seg.reserve((size_t)4 * n);\n    for (int i = 0; i < n; ++i) {\n\
    \        long long a;\n        sc.read(a);\n        seg.add(i, a);\n    }\n\n\
    \    while (q--) {\n        int t;\n        sc.read(t);\n        if (t == 0) {\n\
    \            int p;\n            long long x;\n            sc.read(p, x);\n  \
    \          seg.add(p, x);\n        } else {\n            int l, r;\n         \
    \   sc.read(l, r);\n            pr.println(seg.query(l, r));\n        }\n    }\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <vector>\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/segmenttree/dynamic_segtree.cpp\"\n\nstruct Monoid{\n\
    \    using T = long long;\n    static T f(T a, T b) { return a + b; }\n    static\
    \ T e() { return 0; }\n};\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n\
    \    int n, q;\n    sc.read(n, q);\n    DynamicSegmentTree<Monoid> seg(n);\n \
    \   if (n > 0) seg.reserve((size_t)4 * n);\n    for (int i = 0; i < n; ++i) {\n\
    \        long long a;\n        sc.read(a);\n        seg.add(i, a);\n    }\n\n\
    \    while (q--) {\n        int t;\n        sc.read(t);\n        if (t == 0) {\n\
    \            int p;\n            long long x;\n            sc.read(p, x);\n  \
    \          seg.add(p, x);\n        } else {\n            int l, r;\n         \
    \   sc.read(l, r);\n            pr.println(seg.query(l, r));\n        }\n    }\n\
    \    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/segmenttree/dynamic_segtree.cpp
  isVerificationFile: true
  path: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
- /verify/test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp.html
title: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
---
