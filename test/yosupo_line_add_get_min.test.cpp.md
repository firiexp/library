---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/li_chao_tree.cpp
    title: Li Chao Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 1 \"test/yosupo_line_add_get_min.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n#include <algorithm>\n\
    #include <deque>\n#include <limits>\n#include <utility>\n#include <vector>\n\n\
    using ll = long long;\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing\
    \ namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\nstruct FastIoDigitTable\
    \ {\n    char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n    \
    \    for (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for\
    \ (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x %\
    \ 10);\n                x /= 10;\n            }\n        }\n    }\n};\n\nstruct\
    \ Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n    bool interactive;\n\
    \n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin))) {}\n\n \
    \   inline void load() {\n        int len = size - idx;\n        memmove(buf,\
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
    \ x = -x;\n        }\n    }\n\n    template<class Head, class Next, class... Tail>\n\
    \    void read(Head &head, Next &next, Tail &...tail) {\n        read(head);\n\
    \        read(next, tail...);\n    }\n\n    template<class T, class U>\n    void\
    \ read(pair<T, U> &p) {\n        read(p.first, p.second);\n    }\n\n    template<class\
    \ T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type,\
    \ string>::value, int>::type = 0>\n    void read(T &a) {\n        for (auto &x\
    \ : a) read(x);\n    }\n\n    void read(char &c) {\n        c = skip();\n    }\n\
    \n    void read(string &s) {\n        s.clear();\n        if (interactive) {\n\
    \            ensure_interactive();\n            while (buf[idx] && buf[idx] <=\
    \ ' ') {\n                ++idx;\n                ensure_interactive();\n    \
    \        }\n            while (true) {\n                int start = idx;\n   \
    \             while (idx < size && buf[idx] > ' ') ++idx;\n                s.append(buf\
    \ + start, idx - start);\n                if (idx < size) break;\n           \
    \     load();\n                if (size == 0) break;\n            }\n        \
    \    if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
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
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/li_chao_tree.cpp\"\
    \ntemplate<class T, bool get_max = false>\nstruct LiChaoTree {\n    struct Line\
    \ {\n        T a, b;\n        Line(T a = 0, T b = inf()) : a(a), b(b) {}\n   \
    \     T get(T x) const { return a * x + b; }\n    };\n\n    vector<T> xs;\n  \
    \  vector<Line> seg;\n    int n;\n\n    explicit LiChaoTree(vector<T> xs) : xs(xs)\
    \ {\n        sort(this->xs.begin(), this->xs.end());\n        this->xs.erase(unique(this->xs.begin(),\
    \ this->xs.end()), this->xs.end());\n        n = (int)this->xs.size();\n     \
    \   seg.assign(max(1, 4 * n), Line());\n    }\n\n    void add_line(T a, T b) {\n\
    \        if (n == 0) return;\n        if (get_max) a = -a, b = -b;\n        add_line_node(1,\
    \ 0, n, Line(a, b));\n    }\n\n    void add_segment(T a, T b, T l, T r) {\n  \
    \      if (n == 0 || l >= r) return;\n        if (get_max) a = -a, b = -b;\n \
    \       int L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();\n        int\
    \ R = lower_bound(xs.begin(), xs.end(), r) - xs.begin();\n        if (L >= R)\
    \ return;\n        add_segment_node(1, 0, n, L, R, Line(a, b));\n    }\n\n   \
    \ T query(T x) const {\n        if (n == 0) return get_max ? -inf() : inf();\n\
    \        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();\n        if\
    \ (i == n || xs[i] != x) return get_max ? -inf() : inf();\n        T ret = query_node(1,\
    \ 0, n, i, x);\n        return get_max ? -ret : ret;\n    }\n\nprivate:\n    static\
    \ constexpr T inf() {\n        return numeric_limits<T>::max() / 4;\n    }\n\n\
    \    void add_line_node(int k, int l, int r, Line x) {\n        int m = (l + r)\
    \ / 2;\n        bool lef = x.get(xs[l]) < seg[k].get(xs[l]);\n        bool mid\
    \ = x.get(xs[m]) < seg[k].get(xs[m]);\n        if (mid) swap(seg[k], x);\n   \
    \     if (r - l == 1) return;\n        if (lef != mid) add_line_node(k * 2, l,\
    \ m, x);\n        else add_line_node(k * 2 + 1, m, r, x);\n    }\n\n    void add_segment_node(int\
    \ k, int l, int r, int a, int b, Line x) {\n        if (r <= a || b <= l) return;\n\
    \        if (a <= l && r <= b) {\n            add_line_node(k, l, r, x);\n   \
    \         return;\n        }\n        int m = (l + r) / 2;\n        add_segment_node(k\
    \ * 2, l, m, a, b, x);\n        add_segment_node(k * 2 + 1, m, r, a, b, x);\n\
    \    }\n\n    T query_node(int k, int l, int r, int i, T x) const {\n        T\
    \ ret = seg[k].get(x);\n        if (r - l == 1) return ret;\n        int m = (l\
    \ + r) / 2;\n        if (i < m) return min(ret, query_node(k * 2, l, m, i, x));\n\
    \        return min(ret, query_node(k * 2 + 1, m, r, i, x));\n    }\n};\n\ntemplate<class\
    \ T, bool get_max = false>\nstruct OnlineLiChaoTree {\n    struct Line {\n   \
    \     T a, b;\n        Line(T a = 0, T b = inf()) : a(a), b(b) {}\n        T get(T\
    \ x) const { return a * x + b; }\n    };\n\n    struct Node {\n        Line line;\n\
    \        int l, r;\n        explicit Node(const Line &line) : line(line), l(-1),\
    \ r(-1) {}\n    };\n\n    T low, high;\n    int root;\n    deque<Node> nodes;\n\
    \n    explicit OnlineLiChaoTree(T low, T high) : low(low), high(high), root(-1)\
    \ {}\n\n    void add_line(T a, T b) {\n        if (get_max) a = -a, b = -b;\n\
    \        add_line(root, low, high, Line(a, b));\n    }\n\n    void add_segment(T\
    \ a, T b, T l, T r) {\n        if (l >= r) return;\n        if (get_max) a = -a,\
    \ b = -b;\n        add_segment(root, low, high, l, r, Line(a, b));\n    }\n\n\
    \    T query(T x) const {\n        T ret = query(root, low, high, x);\n      \
    \  return get_max ? -ret : ret;\n    }\n\nprivate:\n    static constexpr T inf()\
    \ {\n        return numeric_limits<T>::max() / 4;\n    }\n\n    int new_node(const\
    \ Line &line) {\n        nodes.emplace_back(line);\n        return (int)nodes.size()\
    \ - 1;\n    }\n\n    void add_line(int &t, T l, T r, Line x) {\n        if (t\
    \ == -1) {\n            t = new_node(x);\n            return;\n        }\n   \
    \     Node &node = nodes[t];\n        T m = l + (r - l) / 2;\n        bool lef\
    \ = x.get(l) < node.line.get(l);\n        bool mid = x.get(m) < node.line.get(m);\n\
    \        if (mid) swap(node.line, x);\n        if (r - l == 1) return;\n     \
    \   if (lef != mid) add_line(node.l, l, m, x);\n        else add_line(node.r,\
    \ m, r, x);\n    }\n\n    void add_segment(int &t, T l, T r, T a, T b, Line x)\
    \ {\n        if (r <= a || b <= l) return;\n        if (a <= l && r <= b) {\n\
    \            add_line(t, l, r, x);\n            return;\n        }\n        if\
    \ (t == -1) t = new_node(Line());\n        Node &node = nodes[t];\n        T m\
    \ = l + (r - l) / 2;\n        if (a < m) add_segment(node.l, l, m, a, b, x);\n\
    \        if (m < b) add_segment(node.r, m, r, a, b, x);\n    }\n\n    T query(int\
    \ t, T l, T r, T x) const {\n        T ret = inf();\n        while (t != -1) {\n\
    \            const Node &node = nodes[t];\n            ret = min(ret, node.line.get(x));\n\
    \            if (r - l == 1) break;\n            T m = l + (r - l) / 2;\n    \
    \        if (x < m) {\n                t = node.l;\n                r = m;\n \
    \           } else {\n                t = node.r;\n                l = m;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief Li Chao\
    \ Tree\n */\n#line 19 \"test/yosupo_line_add_get_min.test.cpp\"\n\nint main()\
    \ {\n    Scanner in;\n    Printer out;\n\n    int n, q;\n    in.read(n, q);\n\
    \    vector<pair<ll, ll>> init(n);\n    for (int i = 0; i < n; ++i) {\n      \
    \  in.read(init[i].first, init[i].second);\n    }\n\n    struct Query {\n    \
    \    int t;\n        ll a, b, p;\n    };\n    vector<Query> qs;\n    qs.reserve(q);\n\
    \    vector<ll> xs;\n    xs.reserve(q);\n\n    for (int i = 0; i < q; ++i) {\n\
    \        int t;\n        in.read(t);\n        if (!t) {\n            ll a, b;\n\
    \            in.read(a, b);\n            qs.push_back({0, a, b, 0});\n       \
    \ } else {\n            ll p;\n            in.read(p);\n            qs.push_back({1,\
    \ 0, 0, p});\n            xs.push_back(p);\n        }\n    }\n\n    LiChaoTree<ll>\
    \ li(xs);\n    for (auto [a, b] : init) li.add_line(a, b);\n\n    for (auto qu\
    \ : qs) {\n        if (qu.t == 0) li.add_line(qu.a, qu.b);\n        else out.writeln(li.query(qu.p));\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n\
    #include <algorithm>\n#include <deque>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nusing ll = long long;\nusing namespace std;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../datastructure/li_chao_tree.cpp\"\n\nint main() {\n    Scanner\
    \ in;\n    Printer out;\n\n    int n, q;\n    in.read(n, q);\n    vector<pair<ll,\
    \ ll>> init(n);\n    for (int i = 0; i < n; ++i) {\n        in.read(init[i].first,\
    \ init[i].second);\n    }\n\n    struct Query {\n        int t;\n        ll a,\
    \ b, p;\n    };\n    vector<Query> qs;\n    qs.reserve(q);\n    vector<ll> xs;\n\
    \    xs.reserve(q);\n\n    for (int i = 0; i < q; ++i) {\n        int t;\n   \
    \     in.read(t);\n        if (!t) {\n            ll a, b;\n            in.read(a,\
    \ b);\n            qs.push_back({0, a, b, 0});\n        } else {\n           \
    \ ll p;\n            in.read(p);\n            qs.push_back({1, 0, 0, p});\n  \
    \          xs.push_back(p);\n        }\n    }\n\n    LiChaoTree<ll> li(xs);\n\
    \    for (auto [a, b] : init) li.add_line(a, b);\n\n    for (auto qu : qs) {\n\
    \        if (qu.t == 0) li.add_line(qu.a, qu.b);\n        else out.writeln(li.query(qu.p));\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/li_chao_tree.cpp
  isVerificationFile: true
  path: test/yosupo_line_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_line_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_line_add_get_min.test.cpp
- /verify/test/yosupo_line_add_get_min.test.cpp.html
title: test/yosupo_line_add_get_min.test.cpp
---
