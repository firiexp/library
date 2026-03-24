---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/functional_graph.cpp
    title: Functional Graph
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_functional_graph.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include\
    \ <random>\n#include <tuple>\n#include <vector>\nusing namespace std;\n\nusing\
    \ ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
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
    \ */\n#line 1 \"graph/functional_graph.cpp\"\nstruct FunctionalGraph {\n    static\
    \ constexpr int LOG = 63;\n\n    int n;\n    vector<int> to;\n    vector<vector<int>>\
    \ up;\n    vector<int> comp_id;\n    vector<int> cycle_pos;\n    vector<int> cycle_len;\n\
    \    vector<int> dist_to_cycle;\n    vector<int> cycle_entry;\n    vector<vector<int>>\
    \ cycles;\n\n    explicit FunctionalGraph(int n)\n        : n(n),\n          to(n,\
    \ -1),\n          up(LOG, vector<int>(n, -1)),\n          comp_id(n, -1),\n  \
    \        cycle_pos(n, -1),\n          cycle_len(n, 0),\n          dist_to_cycle(n,\
    \ -1),\n          cycle_entry(n, -1) {}\n\n    explicit FunctionalGraph(const\
    \ vector<int> &to)\n        : FunctionalGraph((int)to.size()) {\n        this->to\
    \ = to;\n        build();\n    }\n\n    void set_edge(int v, int nxt) {\n    \
    \    to[v] = nxt;\n    }\n\n    void build() {\n        up.assign(LOG, vector<int>(n,\
    \ -1));\n        for (int v = 0; v < n; ++v) up[0][v] = to[v];\n        for (int\
    \ k = 0; k + 1 < LOG; ++k) {\n            for (int v = 0; v < n; ++v) {\n    \
    \            up[k + 1][v] = up[k][up[k][v]];\n            }\n        }\n\n   \
    \     vector<int> indeg(n);\n        for (int v = 0; v < n; ++v) ++indeg[to[v]];\n\
    \n        vector<int> que, order;\n        que.reserve(n);\n        order.reserve(n);\n\
    \        for (int v = 0; v < n; ++v) {\n            if (indeg[v] == 0) que.push_back(v);\n\
    \        }\n        for (int head = 0; head < (int)que.size(); ++head) {\n   \
    \         int v = que[head];\n            order.push_back(v);\n            int\
    \ nxt = to[v];\n            if (--indeg[nxt] == 0) que.push_back(nxt);\n     \
    \   }\n\n        comp_id.assign(n, -1);\n        cycle_pos.assign(n, -1);\n  \
    \      cycle_len.assign(n, 0);\n        dist_to_cycle.assign(n, -1);\n       \
    \ cycle_entry.assign(n, -1);\n        cycles.clear();\n\n        vector<int> seen(n);\n\
    \        for (int v = 0; v < n; ++v) {\n            if (indeg[v] == 0 || seen[v])\
    \ continue;\n            int cid = cycles.size();\n            vector<int> cyc;\n\
    \            int cur = v;\n            do {\n                seen[cur] = 1;\n\
    \                comp_id[cur] = cid;\n                cycle_pos[cur] = cyc.size();\n\
    \                dist_to_cycle[cur] = 0;\n                cycle_entry[cur] = cur;\n\
    \                cyc.push_back(cur);\n                cur = to[cur];\n       \
    \     } while (cur != v);\n            for (int x : cyc) cycle_len[x] = cyc.size();\n\
    \            cycles.push_back(cyc);\n        }\n\n        for (int i = (int)order.size()\
    \ - 1; i >= 0; --i) {\n            int v = order[i];\n            int nxt = to[v];\n\
    \            comp_id[v] = comp_id[nxt];\n            cycle_pos[v] = cycle_pos[nxt];\n\
    \            cycle_len[v] = cycle_len[nxt];\n            dist_to_cycle[v] = dist_to_cycle[nxt]\
    \ + 1;\n            cycle_entry[v] = cycle_entry[nxt];\n        }\n    }\n\n \
    \   int jump(int v, long long k) const {\n        for (int i = 0; i < LOG; ++i)\
    \ {\n            if ((k >> i) & 1) v = up[i][v];\n        }\n        return v;\n\
    \    }\n\n    bool in_cycle(int v) const {\n        return dist_to_cycle[v] ==\
    \ 0;\n    }\n\n    int cycle_id(int v) const {\n        return comp_id[v];\n \
    \   }\n\n    int cycle_size(int v) const {\n        return cycle_len[v];\n   \
    \ }\n\n    int steps_to_cycle(int v) const {\n        return dist_to_cycle[v];\n\
    \    }\n\n    int cycle_vertex(int v) const {\n        return cycle_entry[v];\n\
    \    }\n\n    int cycle_index(int v) const {\n        return cycle_pos[v];\n \
    \   }\n\n    const vector<int> &cycle(int id) const {\n        return cycles[id];\n\
    \    }\n};\n\n/**\n * @brief Functional Graph\n */\n#line 18 \"test/yosupo_aplusb_functional_graph.test.cpp\"\
    \n\ntuple<vector<int>, int, int> walk_info(const vector<int> &to, int start) {\n\
    \    int n = to.size();\n    vector<int> pos(n, -1), ord;\n    int cur = start;\n\
    \    while (pos[cur] == -1) {\n        pos[cur] = ord.size();\n        ord.push_back(cur);\n\
    \        cur = to[cur];\n    }\n    return {ord, pos[cur], (int)ord.size() - pos[cur]};\n\
    }\n\nint brute_jump(const vector<int> &to, int start, long long k) {\n    auto\
    \ [ord, offset, len] = walk_info(to, start);\n    if (k < (int)ord.size()) return\
    \ ord[k];\n    return ord[offset + (k - offset) % len];\n}\n\nvoid self_check()\
    \ {\n    mt19937 rng(0);\n    for (int tc = 0; tc < 500; ++tc) {\n        int\
    \ n = rng() % 30 + 1;\n        vector<int> to(n);\n        for (int v = 0; v <\
    \ n; ++v) to[v] = rng() % n;\n\n        FunctionalGraph fg(n);\n        for (int\
    \ v = 0; v < n; ++v) fg.set_edge(v, to[v]);\n        fg.build();\n\n        FunctionalGraph\
    \ fg2(to);\n        for (int v = 0; v < n; ++v) {\n            assert(fg.jump(v,\
    \ 0) == v);\n            assert(fg.jump(v, 1) == to[v]);\n            assert(fg.jump(v,\
    \ 37) == fg2.jump(v, 37));\n\n            auto [ord, offset, len] = walk_info(to,\
    \ v);\n            int entry = ord[offset];\n            assert(fg.steps_to_cycle(v)\
    \ == offset);\n            assert(fg.cycle_vertex(v) == entry);\n            assert(fg.cycle_size(v)\
    \ == len);\n            assert(fg.in_cycle(v) == (offset == 0));\n           \
    \ assert(fg.cycle_id(v) == fg.cycle_id(entry));\n\n            const auto &cyc\
    \ = fg.cycle(fg.cycle_id(v));\n            assert((int)cyc.size() == len);\n \
    \           assert(cyc[fg.cycle_index(v)] == entry);\n\n            for (long\
    \ long k = 0; k <= 100; ++k) {\n                assert(fg.jump(v, k) == brute_jump(to,\
    \ v, k));\n            }\n            for (int rep = 0; rep < 20; ++rep) {\n \
    \               long long k = (long long)(rng() % 1000000) * (rng() % 1000000);\n\
    \                assert(fg.jump(v, k) == brute_jump(to, v, k));\n            }\n\
    \        }\n\n        vector<int> seen_cycle(fg.cycles.size());\n        for (int\
    \ cid = 0; cid < (int)fg.cycles.size(); ++cid) {\n            const auto &cyc\
    \ = fg.cycle(cid);\n            for (int i = 0; i < (int)cyc.size(); ++i) {\n\
    \                int v = cyc[i];\n                assert(fg.in_cycle(v));\n  \
    \              assert(to[v] == cyc[(i + 1) % cyc.size()]);\n                ++seen_cycle[cid];\n\
    \            }\n        }\n        for (int cid = 0; cid < (int)fg.cycles.size();\
    \ ++cid) {\n            assert(seen_cycle[cid] == (int)fg.cycle(cid).size());\n\
    \        }\n    }\n}\n\nint main() {\n    self_check();\n\n    Scanner sc;\n \
    \   Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n  \
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <random>\n#include <tuple>\n#include <vector>\nusing namespace std;\n\
    \nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../graph/functional_graph.cpp\"\
    \n\ntuple<vector<int>, int, int> walk_info(const vector<int> &to, int start) {\n\
    \    int n = to.size();\n    vector<int> pos(n, -1), ord;\n    int cur = start;\n\
    \    while (pos[cur] == -1) {\n        pos[cur] = ord.size();\n        ord.push_back(cur);\n\
    \        cur = to[cur];\n    }\n    return {ord, pos[cur], (int)ord.size() - pos[cur]};\n\
    }\n\nint brute_jump(const vector<int> &to, int start, long long k) {\n    auto\
    \ [ord, offset, len] = walk_info(to, start);\n    if (k < (int)ord.size()) return\
    \ ord[k];\n    return ord[offset + (k - offset) % len];\n}\n\nvoid self_check()\
    \ {\n    mt19937 rng(0);\n    for (int tc = 0; tc < 500; ++tc) {\n        int\
    \ n = rng() % 30 + 1;\n        vector<int> to(n);\n        for (int v = 0; v <\
    \ n; ++v) to[v] = rng() % n;\n\n        FunctionalGraph fg(n);\n        for (int\
    \ v = 0; v < n; ++v) fg.set_edge(v, to[v]);\n        fg.build();\n\n        FunctionalGraph\
    \ fg2(to);\n        for (int v = 0; v < n; ++v) {\n            assert(fg.jump(v,\
    \ 0) == v);\n            assert(fg.jump(v, 1) == to[v]);\n            assert(fg.jump(v,\
    \ 37) == fg2.jump(v, 37));\n\n            auto [ord, offset, len] = walk_info(to,\
    \ v);\n            int entry = ord[offset];\n            assert(fg.steps_to_cycle(v)\
    \ == offset);\n            assert(fg.cycle_vertex(v) == entry);\n            assert(fg.cycle_size(v)\
    \ == len);\n            assert(fg.in_cycle(v) == (offset == 0));\n           \
    \ assert(fg.cycle_id(v) == fg.cycle_id(entry));\n\n            const auto &cyc\
    \ = fg.cycle(fg.cycle_id(v));\n            assert((int)cyc.size() == len);\n \
    \           assert(cyc[fg.cycle_index(v)] == entry);\n\n            for (long\
    \ long k = 0; k <= 100; ++k) {\n                assert(fg.jump(v, k) == brute_jump(to,\
    \ v, k));\n            }\n            for (int rep = 0; rep < 20; ++rep) {\n \
    \               long long k = (long long)(rng() % 1000000) * (rng() % 1000000);\n\
    \                assert(fg.jump(v, k) == brute_jump(to, v, k));\n            }\n\
    \        }\n\n        vector<int> seen_cycle(fg.cycles.size());\n        for (int\
    \ cid = 0; cid < (int)fg.cycles.size(); ++cid) {\n            const auto &cyc\
    \ = fg.cycle(cid);\n            for (int i = 0; i < (int)cyc.size(); ++i) {\n\
    \                int v = cyc[i];\n                assert(fg.in_cycle(v));\n  \
    \              assert(to[v] == cyc[(i + 1) % cyc.size()]);\n                ++seen_cycle[cid];\n\
    \            }\n        }\n        for (int cid = 0; cid < (int)fg.cycles.size();\
    \ ++cid) {\n            assert(seen_cycle[cid] == (int)fg.cycle(cid).size());\n\
    \        }\n    }\n}\n\nint main() {\n    self_check();\n\n    Scanner sc;\n \
    \   Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n  \
    \  return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/functional_graph.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_functional_graph.test.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_functional_graph.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_functional_graph.test.cpp
- /verify/test/yosupo_aplusb_functional_graph.test.cpp.html
title: test/yosupo_aplusb_functional_graph.test.cpp
---
