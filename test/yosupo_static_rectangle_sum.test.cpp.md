---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: datastructure/static_rectangle_sum.cpp
    title: Static Rectangle Sum
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
  bundledCode: "#line 1 \"test/yosupo_static_rectangle_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include <algorithm>\n\
    #include <vector>\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    extern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
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
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class Next, class... Tail>\n    void read(Head &head, Next &next, Tail &...tail)\
    \ {\n        read(head);\n        read(next, tail...);\n    }\n\n    template<class\
    \ T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \  }\n\n    inline void write_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n \
    \       write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
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
    \ T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type,\
    \ string>::value, int>::type = 0>\n    void write(const T &a) {\n        bool\
    \ first = true;\n        for (auto &&x : a) {\n            if (!first) pc(' ');\n\
    \            first = false;\n            write(x);\n        }\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner &in, T &x) {\n  \
    \  in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter &operator<<(Printer\
    \ &out, const T &x) {\n    out.write(x);\n    return out;\n}\n\n/**\n * @brief\
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/static_rectangle_sum.cpp\"\
    \nusing namespace std;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\ntemplate<class\
    \ T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n):\
    \ bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    T sum(int\
    \ k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k -\
    \ 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n        for (k++;\
    \ k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T x) {\n\
    \        if (x <= 0) return 0;\n        int i = 0;\n        for (int j = m; j;\
    \ j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j\
    \ - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n\
    \ * @brief Binary Indexed Tree(BIT)\n */\n#line 4 \"datastructure/static_rectangle_sum.cpp\"\
    \n\ntemplate<class T>\nstruct StaticRectangleSum {\n    struct Point {\n     \
    \   int x, y;\n        T w;\n    };\n\n    struct Event {\n        int x, d, u,\
    \ id, sign;\n\n        bool operator<(const Event& other) const {\n          \
    \  return x < other.x;\n        }\n    };\n\n    vector<Point> points;\n    vector<Event>\
    \ events;\n    vector<int> ys;\n\n    void add_point(int x, int y, T w) {\n  \
    \      points.push_back({x, y, w});\n        ys.push_back(y);\n    }\n\n    void\
    \ add_query(int l, int d, int r, int u) {\n        int id = (int)events.size()\
    \ / 2;\n        events.push_back({r, d, u, id, 1});\n        events.push_back({l,\
    \ d, u, id, -1});\n        ys.push_back(d);\n        ys.push_back(u);\n    }\n\
    \n    vector<T> solve() {\n        vector<int> ord_y = ys;\n        sort(ord_y.begin(),\
    \ ord_y.end());\n        ord_y.erase(unique(ord_y.begin(), ord_y.end()), ord_y.end());\n\
    \n        auto get_y = [&](int y) {\n            return (int)(lower_bound(ord_y.begin(),\
    \ ord_y.end(), y) - ord_y.begin());\n        };\n\n        vector<Point> ps =\
    \ points;\n        for (auto& p : ps) p.y = get_y(p.y);\n        for (auto& e\
    \ : events) {\n            e.d = get_y(e.d);\n            e.u = get_y(e.u);\n\
    \        }\n\n        sort(ps.begin(), ps.end(), [](const Point& a, const Point&\
    \ b) {\n            return a.x < b.x;\n        });\n        sort(events.begin(),\
    \ events.end());\n\n        int q = (int)events.size() / 2;\n        vector<T>\
    \ ans(q, 0);\n        BIT<T> bit((int)ord_y.size());\n        int i = 0;\n   \
    \     for (auto e : events) {\n            while (i < (int)ps.size() && ps[i].x\
    \ < e.x) {\n                bit.add(ps[i].y, ps[i].w);\n                ++i;\n\
    \            }\n            ans[e.id] += (bit.sum(e.u) - bit.sum(e.d)) * e.sign;\n\
    \        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u9759\u7684\u9577\
    \u65B9\u5F62\u548C(Static Rectangle Sum)\n */\n#line 13 \"test/yosupo_static_rectangle_sum.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    StaticRectangleSum<long long> solver;\n    for (int i = 0; i < n;\
    \ ++i) {\n        int x, y;\n        long long w;\n        sc.read(x, y, w);\n\
    \        solver.add_point(x, y, w);\n    }\n    for (int i = 0; i < q; ++i) {\n\
    \        int l, d, r, u;\n        sc.read(l, d, r, u);\n        solver.add_query(l,\
    \ d, r, u);\n    }\n\n    auto ans = solver.solve();\n    for (auto x : ans) pr.writeln(x);\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../datastructure/static_rectangle_sum.cpp\"\n\nint main() {\n    Scanner sc;\n\
    \    Printer pr;\n    int n, q;\n    sc.read(n, q);\n\n    StaticRectangleSum<long\
    \ long> solver;\n    for (int i = 0; i < n; ++i) {\n        int x, y;\n      \
    \  long long w;\n        sc.read(x, y, w);\n        solver.add_point(x, y, w);\n\
    \    }\n    for (int i = 0; i < q; ++i) {\n        int l, d, r, u;\n        sc.read(l,\
    \ d, r, u);\n        solver.add_query(l, d, r, u);\n    }\n\n    auto ans = solver.solve();\n\
    \    for (auto x : ans) pr.writeln(x);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/static_rectangle_sum.cpp
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: true
  path: test/yosupo_static_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_static_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_static_rectangle_sum.test.cpp
- /verify/test/yosupo_static_rectangle_sum.test.cpp.html
title: test/yosupo_static_rectangle_sum.test.cpp
---
