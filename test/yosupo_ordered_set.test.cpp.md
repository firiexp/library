---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/order_statistic_tree.cpp
    title: "\u9806\u5E8F\u6728(Order Statistic Tree)"
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
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"test/yosupo_ordered_set.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <vector>\nusing namespace\
    \ std;\n\nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace\
    \ std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\n\
    template<class T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
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
    \ */\n#line 1 \"datastructure/order_statistic_tree.cpp\"\ntemplate<class T, class\
    \ Compare = less<T>>\nclass OrderStatisticTree {\nprivate:\n    struct Node {\n\
    \        T key;\n        int cnt;\n        int sz;\n        uint32_t pri;\n  \
    \      int l;\n        int r;\n\n        Node(const T& key_, uint32_t pri_)\n\
    \            : key(key_), cnt(1), sz(1), pri(pri_), l(-1), r(-1) {}\n    };\n\n\
    \    int root_ = -1;\n    uint32_t rng_ = 2463534242u;\n    vector<Node> nodes_;\n\
    \    vector<int> free_nodes_;\n    Compare comp_;\n\n    int size(int t) const\
    \ {\n        return t == -1 ? 0 : nodes_[t].sz;\n    }\n\n    bool equal_key(const\
    \ T& a, const T& b) const {\n        return !comp_(a, b) && !comp_(b, a);\n  \
    \  }\n\n    void pull(int t) {\n        if (t == -1) return;\n        Node& node\
    \ = nodes_[t];\n        node.sz = node.cnt + size(node.l) + size(node.r);\n  \
    \  }\n\n    uint32_t next_rand() {\n        uint32_t x = rng_;\n        x ^= x\
    \ << 13;\n        x ^= x >> 17;\n        x ^= x << 5;\n        rng_ = x;\n   \
    \     return x;\n    }\n\n    int make_node(const T& x) {\n        uint32_t pri\
    \ = next_rand();\n        if (!free_nodes_.empty()) {\n            int idx = free_nodes_.back();\n\
    \            free_nodes_.pop_back();\n            nodes_[idx] = Node(x, pri);\n\
    \            return idx;\n        }\n        nodes_.emplace_back(x, pri);\n  \
    \      return (int)nodes_.size() - 1;\n    }\n\n    void recycle_node(int t) {\n\
    \        if (t != -1) free_nodes_.push_back(t);\n    }\n\n    void rotate_left(int&\
    \ t) {\n        int r = nodes_[t].r;\n        nodes_[t].r = nodes_[r].l;\n   \
    \     nodes_[r].l = t;\n        pull(t);\n        pull(r);\n        t = r;\n \
    \   }\n\n    void rotate_right(int& t) {\n        int l = nodes_[t].l;\n     \
    \   nodes_[t].l = nodes_[l].r;\n        nodes_[l].r = t;\n        pull(t);\n \
    \       pull(l);\n        t = l;\n    }\n\n    void insert(int& t, const T& x)\
    \ {\n        if (t == -1) {\n            t = make_node(x);\n            return;\n\
    \        }\n\n        if (equal_key(x, nodes_[t].key)) {\n            ++nodes_[t].cnt;\n\
    \            pull(t);\n            return;\n        }\n\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            insert(child,\
    \ x);\n            nodes_[t].l = child;\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[t].pri) rotate_right(t);\n        } else {\n            int child =\
    \ nodes_[t].r;\n            insert(child, x);\n            nodes_[t].r = child;\n\
    \            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);\n  \
    \      }\n        pull(t);\n    }\n\n    bool erase_one(int& t, const T& x) {\n\
    \        if (t == -1) return false;\n\n        bool ok = false;\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].l = child;\n        } else if (comp_(nodes_[t].key,\
    \ x)) {\n            int child = nodes_[t].r;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].r = child;\n        } else {\n            ok = true;\n\
    \            if (nodes_[t].cnt > 1) {\n                --nodes_[t].cnt;\n    \
    \            pull(t);\n                return true;\n            }\n         \
    \   if (nodes_[t].l == -1 || nodes_[t].r == -1) {\n                int old = t;\n\
    \                t = nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r;\n  \
    \              recycle_node(old);\n                return true;\n            }\n\
    \            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {\n      \
    \          rotate_right(t);\n                int child = nodes_[t].r;\n      \
    \          ok = erase_one(child, x);\n                nodes_[t].r = child;\n \
    \           } else {\n                rotate_left(t);\n                int child\
    \ = nodes_[t].l;\n                ok = erase_one(child, x);\n                nodes_[t].l\
    \ = child;\n            }\n        }\n\n        if (t != -1) pull(t);\n      \
    \  return ok;\n    }\n\npublic:\n    explicit OrderStatisticTree(uint32_t seed\
    \ = 2463534242u, Compare comp = Compare())\n        : root_(-1), rng_(seed), comp_(comp)\
    \ {\n        if (rng_ == 0) rng_ = 2463534242u;\n    }\n\n    void reserve(int\
    \ capacity) {\n        assert(capacity >= 0);\n        nodes_.reserve(capacity);\n\
    \        free_nodes_.reserve(capacity);\n    }\n\n    int size() const {\n   \
    \     return size(root_);\n    }\n\n    bool empty() const {\n        return root_\
    \ == -1;\n    }\n\n    void insert(const T& x) {\n        insert(root_, x);\n\
    \    }\n\n    bool erase_one(const T& x) {\n        return erase_one(root_, x);\n\
    \    }\n\n    int count(const T& x) const {\n        int t = root_;\n        while\
    \ (t != -1) {\n            const Node& node = nodes_[t];\n            if (equal_key(x,\
    \ node.key)) return node.cnt;\n            t = comp_(x, node.key) ? node.l : node.r;\n\
    \        }\n        return 0;\n    }\n\n    bool contains(const T& x) const {\n\
    \        return count(x) > 0;\n    }\n\n    T find_by_order(int k) const {\n \
    \       assert(0 <= k && k < size());\n\n        int t = root_;\n        while\
    \ (true) {\n            const Node& node = nodes_[t];\n            int left_sz\
    \ = size(node.l);\n            if (k < left_sz) {\n                t = node.l;\n\
    \            } else if (k < left_sz + node.cnt) {\n                return node.key;\n\
    \            } else {\n                k -= left_sz + node.cnt;\n            \
    \    t = node.r;\n            }\n        }\n    }\n\n    int order_of_key(const\
    \ T& x) const {\n        int res = 0;\n        int t = root_;\n        while (t\
    \ != -1) {\n            const Node& node = nodes_[t];\n            if (comp_(node.key,\
    \ x)) {\n                res += size(node.l) + node.cnt;\n                t =\
    \ node.r;\n            } else {\n                t = node.l;\n            }\n\
    \        }\n        return res;\n    }\n};\n\n/**\n * @brief \u9806\u5E8F\u7D71\
    \u8A08\u6728(Order Statistic Tree)\n */\n#line 17 \"test/yosupo_ordered_set.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    OrderStatisticTree<int> st;\n    st.reserve(n + q);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int a;\n        sc.read(a);\n        st.insert(a);\n\
    \    }\n\n    for (int i = 0; i < q; ++i) {\n        int t, x;\n        sc.read(t,\
    \ x);\n        if (t == 0) {\n            if (!st.contains(x)) st.insert(x);\n\
    \        } else if (t == 1) {\n            st.erase_one(x);\n        } else if\
    \ (t == 2) {\n            if (st.size() < x) pr.println(-1);\n            else\
    \ pr.println(st.find_by_order(x - 1));\n        } else if (t == 3) {\n       \
    \     pr.println(st.order_of_key(x + 1));\n        } else if (t == 4) {\n    \
    \        int k = st.order_of_key(x + 1);\n            if (k == 0) pr.println(-1);\n\
    \            else pr.println(st.find_by_order(k - 1));\n        } else {\n   \
    \         int k = st.order_of_key(x);\n            if (k == st.size()) pr.println(-1);\n\
    \            else pr.println(st.find_by_order(k));\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <vector>\nusing namespace std;\n\nusing\
    \ ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../datastructure/order_statistic_tree.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    OrderStatisticTree<int> st;\n    st.reserve(n + q);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int a;\n        sc.read(a);\n        st.insert(a);\n\
    \    }\n\n    for (int i = 0; i < q; ++i) {\n        int t, x;\n        sc.read(t,\
    \ x);\n        if (t == 0) {\n            if (!st.contains(x)) st.insert(x);\n\
    \        } else if (t == 1) {\n            st.erase_one(x);\n        } else if\
    \ (t == 2) {\n            if (st.size() < x) pr.println(-1);\n            else\
    \ pr.println(st.find_by_order(x - 1));\n        } else if (t == 3) {\n       \
    \     pr.println(st.order_of_key(x + 1));\n        } else if (t == 4) {\n    \
    \        int k = st.order_of_key(x + 1);\n            if (k == 0) pr.println(-1);\n\
    \            else pr.println(st.find_by_order(k - 1));\n        } else {\n   \
    \         int k = st.order_of_key(x);\n            if (k == st.size()) pr.println(-1);\n\
    \            else pr.println(st.find_by_order(k));\n        }\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/order_statistic_tree.cpp
  isVerificationFile: true
  path: test/yosupo_ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-05-25 00:35:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_ordered_set.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_ordered_set.test.cpp
- /verify/test/yosupo_ordered_set.test.cpp.html
title: test/yosupo_ordered_set.test.cpp
---
