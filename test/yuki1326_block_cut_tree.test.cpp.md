---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/biconnected_components.cpp
    title: "\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':x:'
    path: graph/block_cut_tree.cpp
    title: "\u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut Tree)"
  - icon: ':x:'
    path: tree/hld.cpp
    title: "\u91CD\u8EFD\u5206\u89E3"
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1326
    links:
    - https://yukicoder.me/problems/no/1326
  bundledCode: "#line 1 \"test/yuki1326_block_cut_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/1326\"\n\n#include <algorithm>\n#include\
    \ <vector>\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include\
    \ <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
    \ \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class T,\
    \ class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class T>\n\
    struct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
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
    \ */\n#line 1 \"graph/block_cut_tree.cpp\"\nusing namespace std;\n\n#line 1 \"\
    graph/biconnected_components.cpp\"\nclass BiconnectedComponents {\n    vector<int>\
    \ st;\n    void dfs(int i, int pe, int &pos){\n        ord[i] = low[i] = pos++;\n\
    \        for (auto &&e : G[i]) {\n            int j = e.first, id = e.second;\n\
    \            if(id == pe) continue;\n            if(ord[j] < ord[i]) st.emplace_back(id);\n\
    \            if(~ord[j]){\n                low[i] = min(low[i], ord[j]);\n   \
    \             continue;\n            }\n            par[j] = i;\n            dfs(j,\
    \ id, pos);\n            low[i] = min(low[i], low[j]);\n            if(ord[i]\
    \ <= low[j]){\n                bcc_edges.emplace_back();\n                while(true){\n\
    \                    int k = st.back();\n                    st.pop_back();\n\
    \                    bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second),\
    \ max(edges[k].first, edges[k].second));\n                    if(k == id) break;\n\
    \                }\n            }\n        }\n    }\npublic:\n    vector<int>\
    \ ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> G;\n    vector<vector<pair<int, int>>> bcc_edges;\n    vector<vector<int>>\
    \ bcc_vertices;\n    explicit BiconnectedComponents(int n): ord(n, -1), low(n),\
    \ par(n, -1), G(n){}\n\n    void add_edge(int u, int v){\n        if(u != v){\n\
    \            int id = edges.size();\n            edges.emplace_back(u, v);\n \
    \           G[u].emplace_back(v, id);\n            G[v].emplace_back(u, id);\n\
    \        }\n    }\n\n    int build(){\n        int n = G.size(), pos = 0;\n  \
    \      fill(ord.begin(), ord.end(), -1);\n        fill(par.begin(), par.end(),\
    \ -1);\n        bcc_edges.clear();\n        bcc_vertices.clear();\n        st.clear();\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, -1,\
    \ pos);\n        }\n        vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(now);\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G[i].empty()){\n\
    \                bcc_edges.emplace_back();\n                bcc_vertices.push_back({i});\n\
    \            }\n        }\n        return bcc_vertices.size();\n    }\n};\n\n\
    /**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)\n\
    \ */\n#line 4 \"graph/block_cut_tree.cpp\"\n\nstruct BlockCutTree {\n    int n,\
    \ block_count;\n    BiconnectedComponents bcc;\n    vector<vector<int>> tree,\
    \ nodes;\n    vector<int> id, rev;\n    vector<char> is_articulation;\n\n    explicit\
    \ BlockCutTree(int n) : n(n), block_count(0), bcc(n), id(n, -1), is_articulation(n,\
    \ 0) {}\n\n    void add_edge(int u, int v) {\n        bcc.add_edge(u, v);\n  \
    \  }\n\n    int build() {\n        block_count = bcc.build();\n        vector<int>\
    \ cnt(n);\n        for (auto &&vs : bcc.bcc_vertices) {\n            for (auto\
    \ &&v : vs) ++cnt[v];\n        }\n\n        int m = block_count;\n        id.assign(n,\
    \ -1);\n        is_articulation.assign(n, 0);\n        for (int v = 0; v < n;\
    \ ++v) {\n            if (cnt[v] > 1) {\n                is_articulation[v] =\
    \ 1;\n                id[v] = m++;\n            }\n        }\n\n        tree.assign(m,\
    \ {});\n        nodes.assign(m, {});\n        rev.assign(m, -1);\n        for\
    \ (int i = 0; i < block_count; ++i) {\n            nodes[i] = bcc.bcc_vertices[i];\n\
    \            for (auto &&v : bcc.bcc_vertices[i]) {\n                if (cnt[v]\
    \ > 1) {\n                    tree[i].push_back(id[v]);\n                    tree[id[v]].push_back(i);\n\
    \                } else {\n                    id[v] = i;\n                }\n\
    \            }\n        }\n        for (int v = 0; v < n; ++v) {\n           \
    \ if (is_articulation[v]) {\n                nodes[id[v]].push_back(v);\n    \
    \            rev[id[v]] = v;\n            }\n        }\n        return m;\n  \
    \  }\n};\n\n/**\n * @brief \u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut\
    \ Tree)\n */\n#line 1 \"tree/hld.cpp\"\n\nclass HeavyLightDecomposition {\n  \
    \  void dfs_sz(int v){\n        int heavy = -1;\n        for (auto &&u : G[v])\
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
    \ HL\u5206\u89E3(HL Decomposition)\n */\n#line 14 \"test/yuki1326_block_cut_tree.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, m;\n    sc.read(n,\
    \ m);\n\n    BlockCutTree g(n);\n    for (int i = 0; i < m; ++i) {\n        int\
    \ u, v;\n        sc.read(u, v);\n        --u, --v;\n        g.add_edge(u, v);\n\
    \    }\n\n    g.build();\n    HeavyLightDecomposition hld(g.tree);\n    hld.build();\n\
    \n    vector<int> pref((int)g.tree.size());\n    for (int i = 0; i < (int)g.tree.size();\
    \ ++i) {\n        int v = hld.id_inv[i];\n        pref[v] = (g.rev[v] != -1);\n\
    \        if (hld.par[v] != -1) pref[v] += pref[hld.par[v]];\n    }\n\n    int\
    \ q;\n    sc.read(q);\n    while (q--) {\n        int x, y;\n        sc.read(x,\
    \ y);\n        --x, --y;\n        if (x == y) {\n            pr.writeln(0);\n\
    \            continue;\n        }\n        int u = g.id[x], v = g.id[y];\n   \
    \     int a = hld.lca(u, v);\n        int ans = pref[u] + pref[v] - 2 * pref[a]\
    \ + (g.rev[a] != -1);\n        if (g.is_articulation[x]) --ans;\n        if (g.is_articulation[y])\
    \ --ans;\n        pr.writeln(ans);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1326\"\n\n#include <algorithm>\n\
    #include <vector>\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../graph/block_cut_tree.cpp\"\
    \n#include \"../tree/hld.cpp\"\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\
    \    int n, m;\n    sc.read(n, m);\n\n    BlockCutTree g(n);\n    for (int i =\
    \ 0; i < m; ++i) {\n        int u, v;\n        sc.read(u, v);\n        --u, --v;\n\
    \        g.add_edge(u, v);\n    }\n\n    g.build();\n    HeavyLightDecomposition\
    \ hld(g.tree);\n    hld.build();\n\n    vector<int> pref((int)g.tree.size());\n\
    \    for (int i = 0; i < (int)g.tree.size(); ++i) {\n        int v = hld.id_inv[i];\n\
    \        pref[v] = (g.rev[v] != -1);\n        if (hld.par[v] != -1) pref[v] +=\
    \ pref[hld.par[v]];\n    }\n\n    int q;\n    sc.read(q);\n    while (q--) {\n\
    \        int x, y;\n        sc.read(x, y);\n        --x, --y;\n        if (x ==\
    \ y) {\n            pr.writeln(0);\n            continue;\n        }\n       \
    \ int u = g.id[x], v = g.id[y];\n        int a = hld.lca(u, v);\n        int ans\
    \ = pref[u] + pref[v] - 2 * pref[a] + (g.rev[a] != -1);\n        if (g.is_articulation[x])\
    \ --ans;\n        if (g.is_articulation[y]) --ans;\n        pr.writeln(ans);\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/block_cut_tree.cpp
  - graph/biconnected_components.cpp
  - tree/hld.cpp
  isVerificationFile: true
  path: test/yuki1326_block_cut_tree.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 11:58:39+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yuki1326_block_cut_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yuki1326_block_cut_tree.test.cpp
- /verify/test/yuki1326_block_cut_tree.test.cpp.html
title: test/yuki1326_block_cut_tree.test.cpp
---
