---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/trie.cpp
    title: "Trie \u6728"
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907
  bundledCode: "#line 1 \"test/aoj2907_prefix_suffix_search.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907\"\n\n#include\
    \ <array>\n#include <algorithm>\n#include <string>\n#include <utility>\n#include\
    \ <vector>\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n#include\
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
    \ */\n#line 1 \"datastructure/trie.cpp\"\ntemplate<int W, class F> // W -> word\
    \ size\nstruct Trie {\n    struct Node {\n        char c;\n        array<int,\
    \ W> nxt;\n        vector<int> idxs;\n        int id;\n        explicit Node(char\
    \ c): c(c), id(-1){\n            fill(nxt.begin(),nxt.end(), -1);\n        }\n\
    \    };\n    vector<Node> v;\n    F f;\n    explicit Trie(F f, char c = '$') :\
    \ f(f) {\n        v.emplace_back(c);\n    }\n    void add(const string &s, int\
    \ x){\n        int cur = 0;\n        for (auto &&i : s) {\n            int k =\
    \ f(i);\n            if(~v[cur].nxt[k]){\n                cur = v[cur].nxt[k];\n\
    \                continue;\n            }\n            int npos = v.size();\n\
    \            v[cur].nxt[k] = npos;\n            v.emplace_back(i);\n         \
    \   cur = npos;\n        }\n        v[cur].id = x;\n        v[cur].idxs.emplace_back(x);\n\
    \    }\n\n    int find(const string &s){\n        int cur = 0;\n        for (auto\
    \ &&i : s) {\n            int k = f(i);\n            if(v[cur].nxt[k] < 0) return\
    \ -1;\n            cur = v[cur].nxt[k];\n        }\n        return cur;\n    }\n\
    \    int find(int cur, char c) {return v[cur].nxt[f(c)]; }\n    int id(int cur)\
    \ { return cur < 0 ? -1 : v[cur].id;}\n\n    vector<int> idxs(int cur) { return\
    \ cur < 0 ? vector<int>() : v[cur].idxs; }\n};\n\n/**\n * @brief Trie \u6728\n\
    \ */\n#line 16 \"test/aoj2907_prefix_suffix_search.test.cpp\"\n\nstruct Fenwick\
    \ {\n    int n;\n    vector<int> bit;\n    explicit Fenwick(int n) : n(n), bit(n\
    \ + 1, 0) {}\n    void add(int i, int x) {\n        for (++i; i <= n; i += i &\
    \ -i) bit[i] += x;\n    }\n    int sum(int r) const {\n        int res = 0;\n\
    \        for (; r > 0; r -= r & -r) res += bit[r];\n        return res;\n    }\n\
    };\n\ntemplate<class T>\nvoid build_ranges(const T &trie, vector<int> &word_pos,\
    \ vector<int> &l, vector<int> &r) {\n    const int n = trie.v.size();\n    l.assign(n,\
    \ 0);\n    r.assign(n, 0);\n    vector<int> it(n, 0);\n    vector<char> entered(n,\
    \ 0);\n    int order = 0;\n\n    struct Frame {\n        int v;\n    };\n    vector<Frame>\
    \ st;\n    st.push_back({0});\n    while (!st.empty()) {\n        int v = st.back().v;\n\
    \        if (!entered[v]) {\n            entered[v] = 1;\n            l[v] = order;\n\
    \            for (int id : trie.v[v].idxs) word_pos[id] = order++;\n        }\n\
    \        while (it[v] < 26 && trie.v[v].nxt[it[v]] == -1) ++it[v];\n        if\
    \ (it[v] == 26) {\n            r[v] = order;\n            st.pop_back();\n   \
    \         continue;\n        }\n        st.push_back({trie.v[v].nxt[it[v]++]});\n\
    \    }\n}\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n\
    \    sc.read(n, q);\n    vector<string> words(n);\n    auto f = [](char c) { return\
    \ c - 'a'; };\n    Trie<26, decltype(f)> pref(f), suff(f);\n\n    for (int i =\
    \ 0; i < n; ++i) {\n        sc.read(words[i]);\n        pref.add(words[i], i);\n\
    \        reverse(words[i].begin(), words[i].end());\n        suff.add(words[i],\
    \ i);\n        reverse(words[i].begin(), words[i].end());\n    }\n\n    vector<int>\
    \ pref_pos(n), suff_pos(n), lp, rp, ls, rs;\n    build_ranges(pref, pref_pos,\
    \ lp, rp);\n    build_ranges(suff, suff_pos, ls, rs);\n\n    struct Point {\n\
    \        int x, y;\n    };\n    vector<Point> pts(n);\n    for (int i = 0; i <\
    \ n; ++i) pts[i] = {pref_pos[i], suff_pos[i]};\n    sort(pts.begin(), pts.end(),\
    \ [](const Point &a, const Point &b) {\n        if (a.x != b.x) return a.x < b.x;\n\
    \        return a.y < b.y;\n    });\n\n    struct Event {\n        int x, y, id,\
    \ sign;\n    };\n    vector<Event> ev;\n    ev.reserve(4 * q);\n    vector<long\
    \ long> ans(q);\n\n    for (int i = 0; i < q; ++i) {\n        string p, s;\n \
    \       sc.read(p, s);\n        int pv = pref.find(p);\n        int sv = -1;\n\
    \        reverse(s.begin(), s.end());\n        sv = suff.find(s);\n        if\
    \ (pv == -1 || sv == -1) {\n            continue;\n        }\n        ev.push_back({rp[pv],\
    \ rs[sv], i, +1});\n        ev.push_back({lp[pv], rs[sv], i, -1});\n        ev.push_back({rp[pv],\
    \ ls[sv], i, -1});\n        ev.push_back({lp[pv], ls[sv], i, +1});\n    }\n\n\
    \    sort(ev.begin(), ev.end(), [](const Event &a, const Event &b) {\n       \
    \ return a.x < b.x;\n    });\n\n    Fenwick bit(n);\n    int p = 0;\n    for (const\
    \ auto &e : ev) {\n        while (p < n && pts[p].x < e.x) {\n            bit.add(pts[p].y,\
    \ 1);\n            ++p;\n        }\n        ans[e.id] += 1LL * e.sign * bit.sum(e.y);\n\
    \    }\n\n    for (int i = 0; i < q; ++i) pr.println(ans[i]);\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907\"\
    \n\n#include <array>\n#include <algorithm>\n#include <string>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../datastructure/trie.cpp\"\
    \n\nstruct Fenwick {\n    int n;\n    vector<int> bit;\n    explicit Fenwick(int\
    \ n) : n(n), bit(n + 1, 0) {}\n    void add(int i, int x) {\n        for (++i;\
    \ i <= n; i += i & -i) bit[i] += x;\n    }\n    int sum(int r) const {\n     \
    \   int res = 0;\n        for (; r > 0; r -= r & -r) res += bit[r];\n        return\
    \ res;\n    }\n};\n\ntemplate<class T>\nvoid build_ranges(const T &trie, vector<int>\
    \ &word_pos, vector<int> &l, vector<int> &r) {\n    const int n = trie.v.size();\n\
    \    l.assign(n, 0);\n    r.assign(n, 0);\n    vector<int> it(n, 0);\n    vector<char>\
    \ entered(n, 0);\n    int order = 0;\n\n    struct Frame {\n        int v;\n \
    \   };\n    vector<Frame> st;\n    st.push_back({0});\n    while (!st.empty())\
    \ {\n        int v = st.back().v;\n        if (!entered[v]) {\n            entered[v]\
    \ = 1;\n            l[v] = order;\n            for (int id : trie.v[v].idxs) word_pos[id]\
    \ = order++;\n        }\n        while (it[v] < 26 && trie.v[v].nxt[it[v]] ==\
    \ -1) ++it[v];\n        if (it[v] == 26) {\n            r[v] = order;\n      \
    \      st.pop_back();\n            continue;\n        }\n        st.push_back({trie.v[v].nxt[it[v]++]});\n\
    \    }\n}\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n\
    \    sc.read(n, q);\n    vector<string> words(n);\n    auto f = [](char c) { return\
    \ c - 'a'; };\n    Trie<26, decltype(f)> pref(f), suff(f);\n\n    for (int i =\
    \ 0; i < n; ++i) {\n        sc.read(words[i]);\n        pref.add(words[i], i);\n\
    \        reverse(words[i].begin(), words[i].end());\n        suff.add(words[i],\
    \ i);\n        reverse(words[i].begin(), words[i].end());\n    }\n\n    vector<int>\
    \ pref_pos(n), suff_pos(n), lp, rp, ls, rs;\n    build_ranges(pref, pref_pos,\
    \ lp, rp);\n    build_ranges(suff, suff_pos, ls, rs);\n\n    struct Point {\n\
    \        int x, y;\n    };\n    vector<Point> pts(n);\n    for (int i = 0; i <\
    \ n; ++i) pts[i] = {pref_pos[i], suff_pos[i]};\n    sort(pts.begin(), pts.end(),\
    \ [](const Point &a, const Point &b) {\n        if (a.x != b.x) return a.x < b.x;\n\
    \        return a.y < b.y;\n    });\n\n    struct Event {\n        int x, y, id,\
    \ sign;\n    };\n    vector<Event> ev;\n    ev.reserve(4 * q);\n    vector<long\
    \ long> ans(q);\n\n    for (int i = 0; i < q; ++i) {\n        string p, s;\n \
    \       sc.read(p, s);\n        int pv = pref.find(p);\n        int sv = -1;\n\
    \        reverse(s.begin(), s.end());\n        sv = suff.find(s);\n        if\
    \ (pv == -1 || sv == -1) {\n            continue;\n        }\n        ev.push_back({rp[pv],\
    \ rs[sv], i, +1});\n        ev.push_back({lp[pv], rs[sv], i, -1});\n        ev.push_back({rp[pv],\
    \ ls[sv], i, -1});\n        ev.push_back({lp[pv], ls[sv], i, +1});\n    }\n\n\
    \    sort(ev.begin(), ev.end(), [](const Event &a, const Event &b) {\n       \
    \ return a.x < b.x;\n    });\n\n    Fenwick bit(n);\n    int p = 0;\n    for (const\
    \ auto &e : ev) {\n        while (p < n && pts[p].x < e.x) {\n            bit.add(pts[p].y,\
    \ 1);\n            ++p;\n        }\n        ans[e.id] += 1LL * e.sign * bit.sum(e.y);\n\
    \    }\n\n    for (int i = 0; i < q; ++i) pr.println(ans[i]);\n    return 0;\n\
    }\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/trie.cpp
  isVerificationFile: true
  path: test/aoj2907_prefix_suffix_search.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj2907_prefix_suffix_search.test.cpp
layout: document
redirect_from:
- /verify/test/aoj2907_prefix_suffix_search.test.cpp
- /verify/test/aoj2907_prefix_suffix_search.test.cpp.html
title: test/aoj2907_prefix_suffix_search.test.cpp
---
