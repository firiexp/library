---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/segbeats.cpp
    title: Segment Tree Beats!
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
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"test/yosupo_range_chmin_chmax_add_range_sum.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n#include <limits>\n#include <vector>\n\nusing ll = long long;\nusing namespace\
    \ std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value :\
    \ false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
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
    \ */\n#line 1 \"datastructure/segmenttree/segbeats.cpp\"\ntemplate<class T>\n\
    class SegmentTreeBeats {\n    void add_(int x, T val){\n        if(!val) return;\n\
    \        auto& now = seg[x];\n        now.sum += val*now.len;\n        now.mn\
    \ += val; now.mx += val; now.add += val;\n        if(now.mn2 != INF<T>) now.mn2\
    \ += val;\n        if(now.mx2 != -INF<T>) now.mx2 += val;\n    }\n    void chmin_(int\
    \ x, T val){\n        if(val >= seg[x].mx) return;\n        auto& now = seg[x];\n\
    \        now.sum += now.mxc*(val-now.mx);\n        if(now.mn == now.mx) now.mn\
    \ = val;\n        else if(now.mn2 == now.mx) now.mn2 = val;\n        now.mx =\
    \ val;\n    }\n    void chmax_(int x, T val){\n        if(val <= seg[x].mn) return;\n\
    \        auto& now = seg[x];\n        now.sum += now.mnc*(val-now.mn);\n     \
    \   if(now.mx == now.mn) now.mx = val;\n        else if(now.mx2 == now.mn) now.mx2\
    \ = val;\n        now.mn = val;\n    }\n    void get(int x){\n        M& now =\
    \ seg[x], &l = seg[(x<<1)|0], &r = seg[(x<<1)|1];\n        now.sum = l.sum + r.sum;\n\
    \        now.mn = min(l.mn, r.mn);\n        now.mx = max(l.mx, r.mx);\n      \
    \  now.len = l.len + r.len;\n        if(l.mn < r.mn) now.mnc = l.mnc, now.mn2\
    \ = min(l.mn2, r.mn);\n        else if(r.mn < l.mn) now.mnc = r.mnc, now.mn2 =\
    \ min(r.mn2, l.mn);\n        else now.mnc = l.mnc + r.mnc, now.mn2 = min(l.mn2,\
    \ r.mn2);\n        if(l.mx > r.mx) now.mxc = l.mxc, now.mx2 = max(l.mx2, r.mx);\n\
    \        else if(r.mx > l.mx) now.mxc = r.mxc, now.mx2 = max(r.mx2, l.mx);\n \
    \       else now.mxc = l.mxc + r.mxc, now.mx2 = max(l.mx2, r.mx2);\n    }\n  \
    \  void eval(int x){\n        auto &now = seg[x];\n        for (int i = 0; x <\
    \ n && i < 2; ++i) {\n            add_((x<<1)|i, now.add);\n            chmin_((x<<1)|i,\
    \ now.mx);\n            chmax_((x<<1)|i, now.mn);\n        }\n        now.add\
    \ = 0;\n    }\n    void thrust(int k){ for (int i = height-1; i >= 1; --i) eval(k>>i);\
    \ }\n    void recalc(int k) { k = k >> __builtin_ctz(k); while(k >>= 1) get(k);}\n\
    \n    void in_chmin(int x, T val) {\n        if(seg[x].mx2 < val) chmin_(x, val);\n\
    \        else {\n            eval(x);\n            in_chmin((x<<1)|0, val);\n\
    \            in_chmin((x<<1)|1, val);\n            get(x);\n        }\n    }\n\
    \    void in_chmax(int x, T val) {\n        if(seg[x].mn2 > val) chmax_(x, val);\n\
    \        else {\n            eval(x);\n            in_chmax((x<<1)|0, val);\n\
    \            in_chmax((x<<1)|1, val);\n            get(x);\n        }\n    }\n\
    public:\n#define RANGEX(NAME, INFUNC) \\\nvoid NAME(int a, int b, T val) { \\\n\
    \    thrust(a += n); \\\n    thrust(b += n); \\\n    for(int l = a, r = b; l <\
    \ r; l >>=1, r>>=1) { \\\n        if (l & 1) INFUNC(l++, val); \\\n        if\
    \ (r & 1) INFUNC(--r, val); \\\n    } \\\n    recalc(a); \\\n    recalc(b); \\\
    \n}\n    RANGEX(chmin, in_chmin)\n    RANGEX(chmax, in_chmax)\n    RANGEX(add,\
    \ add_)\n#undef RANGEX\n    T sum(int a, int b) {\n        thrust(a += n);\n \
    \       thrust(b += n);\n        T res = 0;\n        for(int l = a, r = b; l <\
    \ r; l >>=1, r>>=1) {\n            if (l & 1) res += seg[l++].sum;\n         \
    \   if (r & 1) res += seg[--r].sum;\n        }\n        return res;\n    }\n \
    \   struct M {\n        T sum, mx, mx2, mxc, mn, mn2, mnc, len, add;\n       \
    \ M() : mx2(-INF<T>), mxc(1), mn2(INF<T>), mnc(1), add(0) {};\n    };\n    vector<M>\
    \ seg;\n    int n, height;\n    SegmentTreeBeats() = default;\n    SegmentTreeBeats(const\
    \ vector<T>& v){\n        n = 1, height = 1;\n        while(n < v.size()) n <<=\
    \ 1, height++;\n        seg.resize(2*n);\n        for (int i = 0; i < v.size();\
    \ ++i) {\n            seg[i+n].sum = seg[i+n].mx = seg[i+n].mn = v[i];\n     \
    \       seg[i+n].len = 1;\n        }\n        for (int i = n-1; i >= 1; --i) get(i);\n\
    \    }\n};\n\n/**\n * @brief Segment Tree Beats!\n */\n#line 17 \"test/yosupo_range_chmin_chmax_add_range_sum.test.cpp\"\
    \nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n    vector<ll> v(n);\n    for (auto &&i : v) sc.read(i);\n    SegmentTreeBeats<ll>\
    \ seg(v);\n    while(q--){\n        int t;\n        sc.read(t);\n        if(t\
    \ == 0){\n            int l, r;\n            ll b;\n            sc.read(l, r,\
    \ b);\n            seg.chmin(l, r, b);\n        }else if(t == 1){\n          \
    \  int l, r;\n            ll b;\n            sc.read(l, r, b);\n            seg.chmax(l,\
    \ r, b);\n        }else if(t == 2){\n            int l, r;\n            ll b;\n\
    \            sc.read(l, r, b);\n            seg.add(l, r, b);\n        }else {\n\
    \            int l, r;\n            sc.read(l, r);\n            pr.println(seg.sum(l,\
    \ r));\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n#include <limits>\n#include <vector>\n\nusing ll = long long;\nusing namespace\
    \ std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../datastructure/segmenttree/segbeats.cpp\"\
    \nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n    vector<ll> v(n);\n    for (auto &&i : v) sc.read(i);\n    SegmentTreeBeats<ll>\
    \ seg(v);\n    while(q--){\n        int t;\n        sc.read(t);\n        if(t\
    \ == 0){\n            int l, r;\n            ll b;\n            sc.read(l, r,\
    \ b);\n            seg.chmin(l, r, b);\n        }else if(t == 1){\n          \
    \  int l, r;\n            ll b;\n            sc.read(l, r, b);\n            seg.chmax(l,\
    \ r, b);\n        }else if(t == 2){\n            int l, r;\n            ll b;\n\
    \            sc.read(l, r, b);\n            seg.add(l, r, b);\n        }else {\n\
    \            int l, r;\n            sc.read(l, r);\n            pr.println(seg.sum(l,\
    \ r));\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/segmenttree/segbeats.cpp
  isVerificationFile: true
  path: test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
- /verify/test/yosupo_range_chmin_chmax_add_range_sum.test.cpp.html
title: test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
---
