---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/link_cut_tree.cpp
    title: Link-Cut Tree
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
  bundledCode: "#line 1 \"test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n#include <bits/stdc++.h>\n\nstatic const int MOD = 998244353;\nusing ll = long\
    \ long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int\
    \ fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class =\
    \ void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct\
    \ is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
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
    \ */\n#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint {\n\
    \    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    static constexpr uint get_mod() { return Mod; }\n    static constexpr\
    \ uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class T>\n\
    \    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val = uint(x);\
    \ }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint &value()\
    \ noexcept { return val; }\n    const uint &value() const noexcept { return val;\
    \ }\n    modint& operator++() { val++; if (val == Mod) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = Mod; val--; return *this;\
    \ }\n    modint operator++(int) { modint result = *this; ++*this; return result;\
    \ }\n    modint operator--(int) { modint result = *this; --*this; return result;\
    \ }\n    modint& operator+=(const modint& b) { val += b.val; if (val >= Mod) val\
    \ -= Mod; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(Mod - 2); }\n    friend modint operator+(const modint& a, const\
    \ modint& b) { return modint(a) += b; }\n    friend modint operator-(const modint&\
    \ a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 1 \"tree/link_cut_tree.cpp\"\ntemplate <class M>\nstruct\
    \ LinkCutTree {\n    using T = typename M::T;\n\n    struct Node {\n        int\
    \ l, r, p, sz;\n        bool rev;\n        T val, sum, rsum;\n        Node() :\
    \ l(-1), r(-1), p(-1), sz(1), rev(false), val(M::e()), sum(M::e()), rsum(M::e())\
    \ {}\n    };\n\n    int n;\n    vector<Node> nodes;\n    vector<int> push_stack;\n\
    \n    explicit LinkCutTree(int n) : n(n), nodes(n), push_stack() {\n        push_stack.reserve(64);\n\
    \    }\n\n    bool is_root(int x) const {\n        int p = nodes[x].p;\n     \
    \   return p == -1 || (nodes[p].l != x && nodes[p].r != x);\n    }\n\n    void\
    \ reverse(int x) {\n        if (x == -1) return;\n        Node &nx = nodes[x];\n\
    \        swap(nx.l, nx.r);\n        swap(nx.sum, nx.rsum);\n        nx.rev ^=\
    \ 1;\n    }\n\n    void push(int x) {\n        if (x == -1 || !nodes[x].rev) return;\n\
    \        reverse(nodes[x].l);\n        reverse(nodes[x].r);\n        nodes[x].rev\
    \ = false;\n    }\n\n    void pull(int x) {\n        Node &nx = nodes[x];\n  \
    \      nx.sz = 1;\n        nx.sum = nx.val;\n        nx.rsum = nx.val;\n     \
    \   if (nx.l != -1) {\n            int y = nx.l;\n            nx.sz += nodes[y].sz;\n\
    \            nx.sum = M::f(nodes[y].sum, nx.sum);\n            nx.rsum = M::f(nx.rsum,\
    \ nodes[y].rsum);\n        }\n        if (nx.r != -1) {\n            int y = nx.r;\n\
    \            nx.sz += nodes[y].sz;\n            nx.sum = M::f(nx.sum, nodes[y].sum);\n\
    \            nx.rsum = M::f(nodes[y].rsum, nx.rsum);\n        }\n    }\n\n   \
    \ void rotate(int x) {\n        Node &nx = nodes[x];\n        int p = nx.p;\n\
    \        Node &np = nodes[p];\n        int g = np.p;\n        if (np.l == x) {\n\
    \            int b = nx.r;\n            nx.r = p;\n            np.l = b;\n   \
    \         if (b != -1) nodes[b].p = p;\n        } else {\n            int b =\
    \ nx.l;\n            nx.l = p;\n            np.r = b;\n            if (b != -1)\
    \ nodes[b].p = p;\n        }\n        np.p = x;\n        nx.p = g;\n        if\
    \ (g != -1) {\n            Node &ng = nodes[g];\n            if (ng.l == p) {\n\
    \                ng.l = x;\n            } else if (ng.r == p) {\n            \
    \    ng.r = x;\n            }\n        }\n        pull(p);\n        pull(x);\n\
    \    }\n\n    void splay(int x) {\n        push_stack.clear();\n        push_stack.emplace_back(x);\n\
    \        for (int y = x; !is_root(y); y = nodes[y].p) push_stack.emplace_back(nodes[y].p);\n\
    \        for (int i = (int)push_stack.size() - 1; i >= 0; --i) {\n           \
    \ push(push_stack[i]);\n        }\n        while (!is_root(x)) {\n           \
    \ int p = nodes[x].p;\n            int g = nodes[p].p;\n            if (!is_root(p))\
    \ {\n                bool zigzig = (nodes[p].l == x) == (nodes[g].l == p);\n \
    \               rotate(zigzig ? p : x);\n            }\n            rotate(x);\n\
    \        }\n    }\n\n    int expose(int x) {\n        int rp = -1;\n        for\
    \ (int cur = x; cur != -1; cur = nodes[cur].p) {\n            splay(cur);\n  \
    \          nodes[cur].r = rp;\n            pull(cur);\n            rp = cur;\n\
    \        }\n        splay(x);\n        return rp;\n    }\n\n    void evert(int\
    \ x) {\n        expose(x);\n        reverse(x);\n    }\n\n    int get_root(int\
    \ x) {\n        expose(x);\n        while (nodes[x].l != -1) {\n            push(x);\n\
    \            x = nodes[x].l;\n        }\n        splay(x);\n        return x;\n\
    \    }\n\n    bool connected(int u, int v) {\n        return get_root(u) == get_root(v);\n\
    \    }\n\n    bool link(int u, int v) {\n        evert(u);\n        if (get_root(v)\
    \ == u) return false;\n        expose(v);\n        nodes[u].p = v;\n        nodes[v].r\
    \ = u;\n        pull(v);\n        return true;\n    }\n\n    bool cut(int u, int\
    \ v) {\n        evert(u);\n        expose(v);\n        if (nodes[v].l != u ||\
    \ nodes[u].r != -1) return false;\n        nodes[v].l = -1;\n        nodes[u].p\
    \ = -1;\n        pull(v);\n        return true;\n    }\n\n    int lca(int u, int\
    \ v) {\n        if (!connected(u, v)) return -1;\n        expose(u);\n       \
    \ return expose(v);\n    }\n\n    int parent(int x) {\n        expose(x);\n  \
    \      if (nodes[x].l == -1) return -1;\n        x = nodes[x].l;\n        push(x);\n\
    \        while (nodes[x].r != -1) {\n            x = nodes[x].r;\n           \
    \ push(x);\n        }\n        splay(x);\n        return x;\n    }\n\n    void\
    \ set(int x, const T &val) {\n        expose(x);\n        nodes[x].val = val;\n\
    \        pull(x);\n    }\n\n    T get(int x) {\n        expose(x);\n        return\
    \ nodes[x].val;\n    }\n\n    T fold(int u, int v) {\n        evert(u);\n    \
    \    expose(v);\n        return nodes[v].sum;\n    }\n\n    int dist(int u, int\
    \ v) {\n        evert(u);\n        expose(v);\n        return nodes[v].sz - 1;\n\
    \    }\n};\n\n/**\n * @brief Link-Cut Tree\n */\n#line 13 \"test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n\nstruct Monoid {\n    using T = array<mint, 2>;\n    static T f(T a, T b) {\
    \ return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return {1, 0};\
    \ }\n};\n\nint main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n  \
    \  in.read(n, q);\n    LinkCutTree<Monoid> lct(n);\n    for (int i = 0; i < n;\
    \ ++i) {\n        int a, b;\n        in.read(a, b);\n        lct.set(i, {a, b});\n\
    \    }\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        in.read(u,\
    \ v);\n        lct.link(u, v);\n    }\n    for (int i = 0; i < q; ++i) {\n   \
    \     int t;\n        in.read(t);\n        if (t == 0) {\n            int u, v,\
    \ w, x;\n            in.read(u, v, w, x);\n            lct.cut(u, v);\n      \
    \      lct.link(w, x);\n        } else if (t == 1) {\n            int p, c, d;\n\
    \            in.read(p, c, d);\n            lct.set(p, {c, d});\n        } else\
    \ {\n            int u, v, x;\n            in.read(u, v, x);\n            auto\
    \ f = lct.fold(u, v);\n            out.println((f[0] * x + f[1]).val);\n     \
    \   }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n#include <bits/stdc++.h>\n\nstatic const int MOD = 998244353;\nusing ll = long\
    \ long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#include \"../util/fastio.cpp\"\n#include \"../util/modint.cpp\"\n#include\
    \ \"../tree/link_cut_tree.cpp\"\n\nstruct Monoid {\n    using T = array<mint,\
    \ 2>;\n    static T f(T a, T b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n\
    \    static T e() { return {1, 0}; }\n};\n\nint main() {\n    Scanner in;\n  \
    \  Printer out;\n    int n, q;\n    in.read(n, q);\n    LinkCutTree<Monoid> lct(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        int a, b;\n        in.read(a, b);\n\
    \        lct.set(i, {a, b});\n    }\n    for (int i = 0; i < n - 1; ++i) {\n \
    \       int u, v;\n        in.read(u, v);\n        lct.link(u, v);\n    }\n  \
    \  for (int i = 0; i < q; ++i) {\n        int t;\n        in.read(t);\n      \
    \  if (t == 0) {\n            int u, v, w, x;\n            in.read(u, v, w, x);\n\
    \            lct.cut(u, v);\n            lct.link(w, x);\n        } else if (t\
    \ == 1) {\n            int p, c, d;\n            in.read(p, c, d);\n         \
    \   lct.set(p, {c, d});\n        } else {\n            int u, v, x;\n        \
    \    in.read(u, v, x);\n            auto f = lct.fold(u, v);\n            out.println((f[0]\
    \ * x + f[1]).val);\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - tree/link_cut_tree.cpp
  isVerificationFile: true
  path: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
- /verify/test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp.html
title: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
---
