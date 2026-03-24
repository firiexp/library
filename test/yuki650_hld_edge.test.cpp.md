---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/segtree.cpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: "HL\u5206\u89E3(HL Decomposition)"
  - icon: ':heavy_check_mark:'
    path: tree/hld_edge.cpp
    title: "HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA)"
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
    PROBLEM: https://yukicoder.me/problems/no/650
    links:
    - https://yukicoder.me/problems/no/650
  bundledCode: "#line 1 \"test/yuki650_hld_edge.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/650\"\
    \n\n#include <array>\n#include <limits>\n#include <vector>\nusing namespace std;\n\
    \nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\ntemplate<class T> constexpr T INF = numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    extern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
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
    MOD)\n */\n\n\n#line 1 \"tree/hld.cpp\"\n\nclass HeavyLightDecomposition {\n \
    \   void dfs_sz(int v){\n        int heavy = -1;\n        for (auto &&u : G[v])\
    \ {\n            if(u == par[v]) continue;\n            par[u] = v; dep[u] = dep[v]\
    \ + 1;\n            dfs_sz(u);\n            sub_size[v] += sub_size[u];\n    \
    \        if(heavy == -1 || sub_size[u] > sub_size[heavy]) heavy = u;\n       \
    \ }\n        if (heavy != -1 && G[v][0] != heavy) {\n            for (auto &&u\
    \ : G[v]) {\n                if (u == heavy) {\n                    swap(u, G[v][0]);\n\
    \                    break;\n                }\n            }\n        }\n   \
    \ }\n    void dfs_hld(int v, int c, int &pos){\n        id[v] = pos++;\n     \
    \   id_inv[id[v]]= v;\n        tree_id[v] = c;\n        for (auto &&u : G[v])\
    \ {\n            if(u == par[v]) continue;\n            head[u] = (u == G[v][0]\
    \ ? head[v] : u);\n            dfs_hld(u, c, pos);\n        }\n    }\npublic:\n\
    \    int n;\n    vector<vector<int>> G;\n    vector<int> par, dep, sub_size, id,\
    \ id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int n) : n(n),\
    \ G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n){}\n\
    \    explicit HeavyLightDecomposition(vector<vector<int>> &G) : n(G.size()), G(G),\
    \ par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n) {}\n\n\
    \    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n        G[v].emplace_back(u);\n\
    \    }\n\n    void build(vector<int> roots = {0}){\n        fill(par.begin(),\
    \ par.end(), -1);\n        fill(dep.begin(), dep.end(), 0);\n        fill(sub_size.begin(),\
    \ sub_size.end(), 1);\n        int c = 0, pos = 0;\n        for (auto &&i : roots)\
    \ {\n            dfs_sz(i);\n            head[i] = i;\n            dfs_hld(i,\
    \ c++, pos);\n        }\n    }\n\n    int lca(int u, int v){\n        while(true){\n\
    \            if(id[u] > id[v]) swap(u, v);\n            if(head[u] == head[v])\
    \ return u;\n            v = par[head[v]];\n        }\n    }\n\n    int parent(int\
    \ v) const {\n        return par[v];\n    }\n\n    int ancestor(int v, int k)\
    \ {\n        if(dep[v] < k) return -1;\n        while(true) {\n            int\
    \ u = head[v];\n            if(id[v] - k >= id[u]) return id_inv[id[v] - k];\n\
    \            k -= id[v]-id[u]+1;\n            v = par[u];\n        }\n    }\n\n\
    \    int distance(int u, int v){ return dep[u] + dep[v] - 2*dep[lca(u, v)]; }\n\
    \n    pair<int, int> subtree(int v, bool edge = false) const {\n        return\
    \ {id[v] + edge, id[v] + sub_size[v]};\n    }\n\n    template<typename F>\n  \
    \  void add(int u, int v, const F &f, bool edge){\n        while (head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v);\n            f(id[head[v]], id[v]+1);\n\
    \            v = par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v);\n\
    \        f(id[u]+edge, id[v]+1);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f, bool edge = false){\n        add(u, v, f, edge);\n\
    \    }\n\n    template<typename F>\n    void apply_subtree(int v, const F &f,\
    \ bool edge = false){\n        auto [l, r] = subtree(v, edge);\n        f(l, r);\n\
    \    }\n\n    template<typename T, typename Q, typename F>\n    T query(int u,\
    \ int v, const T &e, const Q &q, const F &f, bool edge){\n        T l = e, r =\
    \ e;\n        while(head[u] != head[v]){\n            if(id[u] > id[v]) swap(u,\
    \ v), swap(l, r);\n            l = f(l, q(id[head[v]], id[v]+1));\n          \
    \  v = par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v), swap(l,\
    \ r);\n        return f(q(id[u]+edge, id[v]+1), f(l, r));\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T path_query(int u, int v, const T &e, const\
    \ Q &q, const F &f, bool edge = false){\n        return query(u, v, e, q, f, edge);\n\
    \    }\n\n    template<typename T, typename QL, typename QR, typename F>\n   \
    \ T query_order(int u, int v, const T &e, const QL &ql, const QR &qr, const F\
    \ &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) {\n                l = f(l, qr(id[head[u]], id[u]+1));\n\
    \                u = par[head[u]];\n            }else {\n                r = f(ql(id[head[v]],\
    \ id[v]+1), r);\n                v = par[head[v]];\n            }\n        }\n\
    \        T mid = (id[u] > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));\n\
    \        return f(f(l, mid), r);\n    }\n\n    template<typename T, typename QL,\
    \ typename QR, typename F>\n    T path_query_ordered(int u, int v, const T &e,\
    \ const QL &ql, const QR &qr, const F &f, bool edge = false){\n        return\
    \ query_order(u, v, e, ql, qr, f, edge);\n    }\n\n    template<typename T, typename\
    \ Q>\n    T subtree_query(int v, const Q &q, bool edge = false){\n        auto\
    \ [l, r] = subtree(v, edge);\n        return q(l, r);\n    }\n};\n\n/**\n * @brief\
    \ HL\u5206\u89E3(HL Decomposition)\n */\n#line 2 \"tree/hld_edge.cpp\"\n\nstruct\
    \ HeavyLightDecompositionEdge {\n    HeavyLightDecomposition hld;\n\n    explicit\
    \ HeavyLightDecompositionEdge(int n) : hld(n) {}\n    explicit HeavyLightDecompositionEdge(vector<vector<int>>\
    \ &g) : hld(g) {}\n\n    void add_edge(int u, int v) {\n        hld.add_edge(u,\
    \ v);\n    }\n\n    void build(vector<int> roots = {0}) {\n        hld.build(roots);\n\
    \    }\n\n    int lca(int u, int v) {\n        return hld.lca(u, v);\n    }\n\n\
    \    int parent(int v) const {\n        return hld.parent(v);\n    }\n\n    int\
    \ ancestor(int v, int k) {\n        return hld.ancestor(v, k);\n    }\n\n    int\
    \ distance(int u, int v) {\n        return hld.distance(u, v);\n    }\n\n    int\
    \ edge_index(int v) const {\n        if (hld.par[v] == -1) return -1;\n      \
    \  return hld.id[v];\n    }\n\n    pair<int, int> subtree(int v) const {\n   \
    \     return hld.subtree(v, true);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f) {\n        hld.path(u, v, f, true);\n    }\n\n\
    \    template<typename F>\n    void apply_subtree(int v, const F &f) {\n     \
    \   hld.apply_subtree(v, f, true);\n    }\n\n    template<typename T, typename\
    \ Q, typename F>\n    T path_query(int u, int v, const T &e, const Q &q, const\
    \ F &f) {\n        return hld.path_query(u, v, e, q, f, true);\n    }\n\n    template<typename\
    \ T, typename QL, typename QR, typename F>\n    T path_query_ordered(int u, int\
    \ v, const T &e, const QL &ql, const QR &qr, const F &f) {\n        return hld.path_query_ordered(u,\
    \ v, e, ql, qr, f, true);\n    }\n\n    template<typename T, typename Q>\n   \
    \ T subtree_query(int v, const Q &q) {\n        return hld.subtree_query<T>(v,\
    \ q, true);\n    }\n};\n\n/**\n * @brief HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA\
    )\n */\n#line 1 \"datastructure/segmenttree/segtree.cpp\"\ntemplate <class M>\n\
    struct SegmentTree{\n    using T = typename M::T;\n    int sz, n, height{};\n\
    \    vector<T> seg;\n    explicit SegmentTree(int n) : n(n) {\n        sz = 1;\
    \ while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n    }\n\
    \n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n    void build(){\n \
    \       for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);\n\
    \    }\n\n    void update(int k, const T &x){\n        k += sz;\n        seg[k]\
    \ = x;\n        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n    }\n\n\
    \    T query(int a, int b){\n        T l = M::e(), r = M::e();\n        for(a\
    \ += sz, b += sz; a < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l, seg[a++]);\n\
    \            if(b & 1) r = M::f(seg[--b], r);\n        }\n        return M::f(l,\
    \ r);\n    }\n\n    template<class F>\n    int search_right(int l, F cond){\n\
    \        if(l == n) return n;\n        T val = M::e();\n        l += sz;\n   \
    \     do {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val,\
    \ seg[l]))){\n                while(l < sz) {\n                    l <<= 1;\n\
    \                    if (cond(M::f(val, seg[l]))){\n                        val\
    \ = M::f(val, seg[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - sz;\n            }\n          \
    \  val = M::f(val, seg[l]);\n            l++;\n        } while((l & -l) != l);\n\
    \        return n;\n    }\n\n    template<class F>\n    int search_left(int r,\
    \ F cond){\n        if(r == 0) return 0;\n        T val = M::e();\n        r +=\
    \ sz;\n        do {\n            r--;\n            while(r&1) r >>= 1;\n     \
    \       if(!cond(M::f(seg[r], val))){\n                while(r < sz) {\n     \
    \               r = ((r << 1)|1);\n                    if (cond(M::f(seg[r], val))){\n\
    \                        val = M::f(seg[r], val);\n                        r--;\n\
    \                    }\n                }\n                return r + 1 - sz;\n\
    \            }\n            val = M::f(seg[r], val);\n        } while((r & -r)\
    \ != r);\n        return 0;\n    }\n    T operator[](const int &k) const { return\
    \ seg[k + sz]; }\n};\n\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n\
    \    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static\
    \ T e() { return {1, 0}; }\n};\n*/\n\n/**\n * @brief Segment Tree\n */\n#line\
    \ 23 \"test/yuki650_hld_edge.test.cpp\"\n\nstruct MatMonoidL {\n    using T =\
    \ array<mint, 4>;\n    static T f(T a, T b) {\n        return {\n            a[0]\
    \ * b[0] + a[1] * b[2],\n            a[0] * b[1] + a[1] * b[3],\n            a[2]\
    \ * b[0] + a[3] * b[2],\n            a[2] * b[1] + a[3] * b[3]\n        };\n \
    \   }\n    static T e() { return {1, 0, 0, 1}; }\n};\n\nstruct MatMonoidR {\n\
    \    using T = array<mint, 4>;\n    static T f(T b, T a) {\n        return {\n\
    \            a[0] * b[0] + a[1] * b[2],\n            a[0] * b[1] + a[1] * b[3],\n\
    \            a[2] * b[0] + a[3] * b[2],\n            a[2] * b[1] + a[3] * b[3]\n\
    \        };\n    }\n    static T e() { return {1, 0, 0, 1}; }\n};\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n\n    int n;\n    sc.read(n);\n    HeavyLightDecompositionEdge\
    \ hld(n);\n    vector<pair<int, int>> edges(n - 1);\n    for (int i = 0; i < n\
    \ - 1; ++i) {\n        int a, b;\n        sc.read(a, b);\n        edges[i] = {a,\
    \ b};\n        hld.add_edge(a, b);\n    }\n    hld.build();\n\n    SegmentTree<MatMonoidL>\
    \ segl(n);\n    SegmentTree<MatMonoidR> segr(n);\n\n    vector<int> child(n -\
    \ 1);\n    for (int i = 0; i < n - 1; ++i) {\n        auto [a, b] = edges[i];\n\
    \        child[i] = (hld.parent(a) == b ? a : b);\n        int p = hld.edge_index(child[i]);\n\
    \        segl.set(p, MatMonoidL::e());\n        segr.set(p, MatMonoidR::e());\n\
    \    }\n    segl.build();\n    segr.build();\n\n    auto ql = [&](int l, int r)\
    \ { return segl.query(l, r); };\n    auto qr = [&](int l, int r) { return segr.query(l,\
    \ r); };\n    auto merge = [&](MatMonoidL::T a, MatMonoidL::T b) -> MatMonoidL::T\
    \ {\n        return MatMonoidL::f(a, b);\n    };\n\n    int q;\n    sc.read(q);\n\
    \    for (int qi = 0; qi < q; ++qi) {\n        char type;\n        sc.read(type);\n\
    \        if (type == 'x') {\n            int i, x00, x01, x10, x11;\n        \
    \    sc.read(i, x00, x01, x10, x11);\n            int p = hld.edge_index(child[i]);\n\
    \            array<mint, 4> mat = {x00, x01, x10, x11};\n            segl.update(p,\
    \ mat);\n            segr.update(p, mat);\n        } else {\n            int i,\
    \ j;\n            sc.read(i, j);\n            auto ans = hld.path_query_ordered(i,\
    \ j, MatMonoidL::e(), ql, qr, merge);\n            pr.println(ans[0].val, ans[1].val,\
    \ ans[2].val, ans[3].val);\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/650\"\n\n#include <array>\n\
    #include <limits>\n#include <vector>\nusing namespace std;\n\nstatic const int\
    \ MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\ntemplate<class T> constexpr T INF = numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../util/modint.cpp\"\
    \n#include \"../tree/hld_edge.cpp\"\n#include \"../datastructure/segmenttree/segtree.cpp\"\
    \n\nstruct MatMonoidL {\n    using T = array<mint, 4>;\n    static T f(T a, T\
    \ b) {\n        return {\n            a[0] * b[0] + a[1] * b[2],\n           \
    \ a[0] * b[1] + a[1] * b[3],\n            a[2] * b[0] + a[3] * b[2],\n       \
    \     a[2] * b[1] + a[3] * b[3]\n        };\n    }\n    static T e() { return\
    \ {1, 0, 0, 1}; }\n};\n\nstruct MatMonoidR {\n    using T = array<mint, 4>;\n\
    \    static T f(T b, T a) {\n        return {\n            a[0] * b[0] + a[1]\
    \ * b[2],\n            a[0] * b[1] + a[1] * b[3],\n            a[2] * b[0] + a[3]\
    \ * b[2],\n            a[2] * b[1] + a[3] * b[3]\n        };\n    }\n    static\
    \ T e() { return {1, 0, 0, 1}; }\n};\n\nint main() {\n    Scanner sc;\n    Printer\
    \ pr;\n\n    int n;\n    sc.read(n);\n    HeavyLightDecompositionEdge hld(n);\n\
    \    vector<pair<int, int>> edges(n - 1);\n    for (int i = 0; i < n - 1; ++i)\
    \ {\n        int a, b;\n        sc.read(a, b);\n        edges[i] = {a, b};\n \
    \       hld.add_edge(a, b);\n    }\n    hld.build();\n\n    SegmentTree<MatMonoidL>\
    \ segl(n);\n    SegmentTree<MatMonoidR> segr(n);\n\n    vector<int> child(n -\
    \ 1);\n    for (int i = 0; i < n - 1; ++i) {\n        auto [a, b] = edges[i];\n\
    \        child[i] = (hld.parent(a) == b ? a : b);\n        int p = hld.edge_index(child[i]);\n\
    \        segl.set(p, MatMonoidL::e());\n        segr.set(p, MatMonoidR::e());\n\
    \    }\n    segl.build();\n    segr.build();\n\n    auto ql = [&](int l, int r)\
    \ { return segl.query(l, r); };\n    auto qr = [&](int l, int r) { return segr.query(l,\
    \ r); };\n    auto merge = [&](MatMonoidL::T a, MatMonoidL::T b) -> MatMonoidL::T\
    \ {\n        return MatMonoidL::f(a, b);\n    };\n\n    int q;\n    sc.read(q);\n\
    \    for (int qi = 0; qi < q; ++qi) {\n        char type;\n        sc.read(type);\n\
    \        if (type == 'x') {\n            int i, x00, x01, x10, x11;\n        \
    \    sc.read(i, x00, x01, x10, x11);\n            int p = hld.edge_index(child[i]);\n\
    \            array<mint, 4> mat = {x00, x01, x10, x11};\n            segl.update(p,\
    \ mat);\n            segr.update(p, mat);\n        } else {\n            int i,\
    \ j;\n            sc.read(i, j);\n            auto ans = hld.path_query_ordered(i,\
    \ j, MatMonoidL::e(), ql, qr, merge);\n            pr.println(ans[0].val, ans[1].val,\
    \ ans[2].val, ans[3].val);\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - tree/hld_edge.cpp
  - tree/hld.cpp
  - datastructure/segmenttree/segtree.cpp
  isVerificationFile: true
  path: test/yuki650_hld_edge.test.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yuki650_hld_edge.test.cpp
layout: document
redirect_from:
- /verify/test/yuki650_hld_edge.test.cpp
- /verify/test/yuki650_hld_edge.test.cpp.html
title: test/yuki650_hld_edge.test.cpp
---
