---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: datastructure/binaryindexedtree.cpp
    title: datastructure/binaryindexedtree.cpp
  - icon: ':heavy_check_mark:'
    path: datastructure/point_add_rectangle_sum.cpp
    title: datastructure/point_add_rectangle_sum.cpp
  - icon: ':question:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"test/yosupo_point_add_rectangle_sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n#line\
    \ 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
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
    \ (true) {\n            int start = idx;\n            while (buf[idx] > ' ') ++idx;\n\
    \            s.append(buf + start, idx - start);\n            if (buf[idx] <=\
    \ ' ') break;\n            load();\n        }\n        ++idx;\n    }\n};\n\nstruct\
    \ Printer {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr\
    \ FastIoDigitTable table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush();\
    \ }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n    }\n\n    inline void write_range(const char *s, size_t n) {\n    \
    \    size_t pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE)\
    \ flush();\n            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n\
    \            memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n\
    \            pos += chunk;\n        }\n    }\n\n    void write(const char *s)\
    \ {\n        write_range(s, strlen(s));\n    }\n\n    void write(const string\
    \ &s) {\n        write_range(s.data(), s.size());\n    }\n\n    void write(char\
    \ c) {\n        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0'\
    \ + (b ? 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
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
    \    }\n};\n#line 1 \"datastructure/point_add_rectangle_sum.cpp\"\n#include <algorithm>\n\
    #include <vector>\nusing namespace std;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k))\
    \ ret += bit[k - 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n\
    \        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T\
    \ x) {\n        if (x <= 0) return 0;\n        int i = 0;\n        for (int j\
    \ = m; j; j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i\
    \ + j - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n#line\
    \ 6 \"datastructure/point_add_rectangle_sum.cpp\"\n\ntemplate<class T>\nstruct\
    \ PointAddRectangleSum {\n    struct Operation {\n        int type;\n        int\
    \ x, y, z;\n        T w;\n    };\n\n    vector<Operation> ops;\n    vector<int>\
    \ xs;\n\n    void add_point(int x, int y, T w) {\n        ops.push_back({0, x,\
    \ y, 0, w});\n        xs.push_back(x);\n    }\n\n    void add_query(int l, int\
    \ d, int r, int u) {\n        ops.push_back({1, l, d, r, u});\n    }\n\n    vector<T>\
    \ solve() const {\n        vector<int> ord_x = xs;\n        sort(ord_x.begin(),\
    \ ord_x.end());\n        ord_x.erase(unique(ord_x.begin(), ord_x.end()), ord_x.end());\n\
    \n        int m = (int)ord_x.size();\n        vector<vector<int>> ys(m + 1);\n\
    \        for (auto op : ops) {\n            if (op.type != 0) continue;\n    \
    \        int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), op.x) - ord_x.begin())\
    \ + 1;\n            for (int x = xi; x <= m; x += x & -x) ys[x].push_back(op.y);\n\
    \        }\n        for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(),\
    \ ys[i].end());\n            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n\
    \        }\n\n        vector<BIT<T>> bit;\n        bit.reserve(m + 1);\n     \
    \   bit.emplace_back(0);\n        for (int i = 1; i <= m; ++i) bit.emplace_back((int)ys[i].size());\n\
    \n        auto add = [&](int x, int y, T w) {\n            int xi = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), x) - ord_x.begin()) + 1;\n            for (int i = xi; i <= m;\
    \ i += i & -i) {\n                int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(),\
    \ y) - ys[i].begin());\n                bit[i].add(yi, w);\n            }\n  \
    \      };\n        auto sum = [&](int x, int y) {\n            T ret = 0;\n  \
    \          int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), x) - ord_x.begin());\n\
    \            for (int i = xi; i > 0; i -= i & -i) {\n                int yi =\
    \ (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n       \
    \         ret += bit[i].sum(yi);\n            }\n            return ret;\n   \
    \     };\n\n        vector<T> ans;\n        for (auto op : ops) {\n          \
    \  if (op.type == 0) {\n                add(op.x, op.y, (T)op.w);\n          \
    \  } else {\n                ans.push_back(sum(op.z, op.w) - sum(op.z, op.y) -\
    \ sum(op.x, op.w) + sum(op.x, op.y));\n            }\n        }\n        return\
    \ ans;\n    }\n};\n#line 5 \"test/yosupo_point_add_rectangle_sum.test.cpp\"\n\n\
    int main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    PointAddRectangleSum<long long> solver;\n    for (int i = 0; i <\
    \ n; ++i) {\n        int x, y;\n        long long w;\n        sc.read(x, y, w);\n\
    \        solver.add_point(x, y, w);\n    }\n    for (int i = 0; i < q; ++i) {\n\
    \        int t;\n        sc.read(t);\n        if (t == 0) {\n            int x,\
    \ y;\n            long long w;\n            sc.read(x, y, w);\n            solver.add_point(x,\
    \ y, w);\n        } else {\n            int l, d, r, u;\n            sc.read(l,\
    \ d, r, u);\n            solver.add_query(l, d, r, u);\n        }\n    }\n\n \
    \   auto ans = solver.solve();\n    for (auto x : ans) pr.writeln(x);\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../util/fastio.cpp\"\n#include \"../datastructure/point_add_rectangle_sum.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    PointAddRectangleSum<long long> solver;\n    for (int i = 0; i <\
    \ n; ++i) {\n        int x, y;\n        long long w;\n        sc.read(x, y, w);\n\
    \        solver.add_point(x, y, w);\n    }\n    for (int i = 0; i < q; ++i) {\n\
    \        int t;\n        sc.read(t);\n        if (t == 0) {\n            int x,\
    \ y;\n            long long w;\n            sc.read(x, y, w);\n            solver.add_point(x,\
    \ y, w);\n        } else {\n            int l, d, r, u;\n            sc.read(l,\
    \ d, r, u);\n            solver.add_query(l, d, r, u);\n        }\n    }\n\n \
    \   auto ans = solver.solve();\n    for (auto x : ans) pr.writeln(x);\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/point_add_rectangle_sum.cpp
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: true
  path: test/yosupo_point_add_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 18:50:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_point_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_add_rectangle_sum.test.cpp
- /verify/test/yosupo_point_add_rectangle_sum.test.cpp.html
title: test/yosupo_point_add_rectangle_sum.test.cpp
---
