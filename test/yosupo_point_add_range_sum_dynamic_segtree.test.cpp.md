---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: datastructure/dynamic_segtree.cpp
    title: datastructure/dynamic_segtree.cpp
  - icon: ':question:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n\
    #include <vector>\nusing namespace std;\n\n#line 1 \"util/fastio.cpp\"\n#include\
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
    \            while (buf[idx] > ' ') ++idx;\n            s.append(buf + start,\
    \ idx - start);\n            if (buf[idx] <= ' ') break;\n            load();\n\
    \        }\n        ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n#line 1 \"\
    datastructure/dynamic_segtree.cpp\"\ntemplate <class M>\nstruct DynamicSegmentTree{\n\
    \    using T = typename M::T;\n    struct Node{\n        T val;\n        int l,\
    \ r;\n    };\n\n    long long n{};\n    vector<Node> node;\n    int root;\n\n\
    \    explicit DynamicSegmentTree(long long n): n(n), root(-1) {}\n\n    void update(long\
    \ long k, const T &x){\n        if(n == 0) return;\n        root = update_(root,\
    \ k, x, 0, n);\n    }\n\n    void add(long long k, const T &x){\n        if(n\
    \ == 0) return;\n        root = add_(root, k, x, 0, n);\n    }\n\n    T query(long\
    \ long a, long long b) const {\n        if(n == 0 || b <= a) return M::e();\n\
    \        return query_(root, a, b, 0, n);\n    }\n\n    T get(long long k) const\
    \ { return query(k, k+1); }\n    T operator[](const long long &k) const { return\
    \ get(k); }\n\nprivate:\n    int make_node(const T &v, int l, int r){\n      \
    \  node.push_back({v, l, r});\n        return node.size()-1;\n    }\n\n    int\
    \ update_(int id, long long k, const T &x, long long l, long long r){\n      \
    \  if(l+1 == r) return make_node(x, -1, -1);\n        if(id == -1) id = make_node(M::e(),\
    \ -1, -1);\n        long long m = l + ((r-l)>>1);\n        int ll = node[id].l,\
    \ rr = node[id].r;\n        if(k < m) ll = update_(ll, k, x, l, m);\n        else\
    \ rr = update_(rr, k, x, m, r);\n        return make_node(M::f(value(ll), value(rr)),\
    \ ll, rr);\n    }\n\n    int add_(int id, long long k, const T &x, long long l,\
    \ long long r){\n        if(l+1 == r) return make_node(M::f(value(id), x), -1,\
    \ -1);\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        long long\
    \ m = l + ((r-l)>>1);\n        int ll = node[id].l, rr = node[id].r;\n       \
    \ if(k < m) ll = add_(ll, k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n\
    \        return make_node(M::f(value(ll), value(rr)), ll, rr);\n    }\n\n    T\
    \ query_(int id, long long a, long long b, long long l, long long r) const {\n\
    \        if(id == -1 || r <= a || b <= l) return M::e();\n        if(a <= l &&\
    \ r <= b) return node[id].val;\n        long long m = l + ((r-l)>>1);\n      \
    \  return M::f(query_(node[id].l, a, b, l, m), query_(node[id].r, a, b, m, r));\n\
    \    }\n\n    T value(int id) const {\n        return id == -1 ? M::e() : node[id].val;\n\
    \    }\n};\n\n/*\nstruct Monoid{\n    using T = long long;\n    static T f(T a,\
    \ T b) { return a + b; }\n    static T e() { return 0; }\n};\n*/\n#line 8 \"test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp\"\
    \n\nstruct Monoid{\n    using T = long long;\n    static T f(T a, T b) { return\
    \ a + b; }\n    static T e() { return 0; }\n};\n\nint main() {\n    Scanner sc;\n\
    \    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    DynamicSegmentTree<Monoid>\
    \ seg(n);\n    for (int i = 0; i < n; ++i) {\n        long long a;\n        sc.read(a);\n\
    \        seg.add(i, a);\n    }\n\n    while (q--) {\n        int t;\n        sc.read(t);\n\
    \        if (t == 0) {\n            int p;\n            long long x;\n       \
    \     sc.read(p, x);\n            seg.add(p, x);\n        } else {\n         \
    \   int l, r;\n            sc.read(l, r);\n            pr.writeln(seg.query(l,\
    \ r));\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <vector>\nusing namespace std;\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/dynamic_segtree.cpp\"\n\nstruct Monoid{\n    using\
    \ T = long long;\n    static T f(T a, T b) { return a + b; }\n    static T e()\
    \ { return 0; }\n};\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int\
    \ n, q;\n    sc.read(n, q);\n    DynamicSegmentTree<Monoid> seg(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        long long a;\n        sc.read(a);\n        seg.add(i,\
    \ a);\n    }\n\n    while (q--) {\n        int t;\n        sc.read(t);\n     \
    \   if (t == 0) {\n            int p;\n            long long x;\n            sc.read(p,\
    \ x);\n            seg.add(p, x);\n        } else {\n            int l, r;\n \
    \           sc.read(l, r);\n            pr.writeln(seg.query(l, r));\n       \
    \ }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/dynamic_segtree.cpp
  isVerificationFile: true
  path: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:18:09+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
- /verify/test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp.html
title: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
---
