---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/interval_set.cpp
    title: "\u533A\u9593\u96C6\u5408(Interval Set)"
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
    PROBLEM: https://judge.yosupo.jp/problem/predecessor_problem
    links:
    - https://judge.yosupo.jp/problem/predecessor_problem
  bundledCode: "#line 1 \"test/yosupo_predecessor_problem_interval_set.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\n#include\
    \ <bits/stdc++.h>\n\nusing namespace std;\n\n#line 10 \"test/yosupo_predecessor_problem_interval_set.test.cpp\"\
    \n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\
    \nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
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
    \ */\n#line 1 \"datastructure/interval_set.cpp\"\ntemplate<class T, class SumT\
    \ = long long>\nclass IntervalSet {\npublic:\n    struct Interval {\n        T\
    \ l, r;\n    };\n\nprivate:\n    struct Compare {\n        using is_transparent\
    \ = void;\n\n        bool operator()(const Interval& a, const Interval& b) const\
    \ {\n            return a.l < b.l;\n        }\n        bool operator()(const Interval&\
    \ a, const T& x) const {\n            return a.l < x;\n        }\n        bool\
    \ operator()(const T& x, const Interval& a) const {\n            return x < a.l;\n\
    \        }\n    };\n\n    set<Interval, Compare> st_;\n    SumT total_ = 0;\n\n\
    \    static SumT seg_len(const Interval& seg) {\n        return static_cast<SumT>(seg.r)\
    \ - static_cast<SumT>(seg.l);\n    }\n\n    typename set<Interval, Compare>::const_iterator\
    \ find_interval_it(T x) const {\n        auto it = st_.upper_bound(x);\n     \
    \   if (it == st_.begin()) return st_.end();\n        --it;\n        if (it->l\
    \ <= x && x < it->r) return it;\n        return st_.end();\n    }\n\npublic:\n\
    \    using const_iterator = typename set<Interval, Compare>::const_iterator;\n\
    \n    IntervalSet() = default;\n\n    bool empty() const {\n        return st_.empty();\n\
    \    }\n\n    int size() const {\n        return (int)st_.size();\n    }\n\n \
    \   SumT total_length() const {\n        return total_;\n    }\n\n    const_iterator\
    \ begin() const {\n        return st_.begin();\n    }\n\n    const_iterator end()\
    \ const {\n        return st_.end();\n    }\n\n    vector<Interval> intervals()\
    \ const {\n        return vector<Interval>(st_.begin(), st_.end());\n    }\n\n\
    \    bool contains(T x) const {\n        return find_interval_it(x) != st_.end();\n\
    \    }\n\n    Interval find_interval(T x) const {\n        auto it = find_interval_it(x);\n\
    \        if (it == st_.end()) return {-1, -1};\n        return *it;\n    }\n\n\
    \    Interval insert(T l, T r) {\n        if (!(l < r)) return {l, l};\n\n   \
    \     auto it = st_.lower_bound(l);\n\n        if (it != st_.begin()) {\n    \
    \        auto pit = prev(it);\n            if (pit->r >= l) {\n              \
    \  l = min(l, pit->l);\n                r = max(r, pit->r);\n                total_\
    \ -= seg_len(*pit);\n                it = st_.erase(pit);\n            }\n   \
    \     }\n\n        while (it != st_.end() && it->l <= r) {\n            r = max(r,\
    \ it->r);\n            total_ -= seg_len(*it);\n            it = st_.erase(it);\n\
    \        }\n\n        auto new_it = st_.insert(it, {l, r});\n        total_ +=\
    \ static_cast<SumT>(r) - static_cast<SumT>(l);\n        return *new_it;\n    }\n\
    \n    SumT erase(T l, T r) {\n        if (!(l < r)) return 0;\n\n        SumT\
    \ removed = 0;\n        vector<Interval> add_back;\n\n        auto it = st_.lower_bound(l);\n\
    \        if (it != st_.begin()) --it;\n\n        while (it != st_.end() && it->l\
    \ < r) {\n            if (it->r <= l) {\n                ++it;\n             \
    \   continue;\n            }\n\n            Interval cur = *it;\n            it\
    \ = st_.erase(it);\n            total_ -= seg_len(cur);\n\n            T a = max(cur.l,\
    \ l);\n            T b = min(cur.r, r);\n            removed += static_cast<SumT>(b)\
    \ - static_cast<SumT>(a);\n\n            if (cur.l < l) add_back.push_back({cur.l,\
    \ l});\n            if (r < cur.r) add_back.push_back({r, cur.r});\n        }\n\
    \n        for (const auto& seg : add_back) {\n            st_.insert(seg);\n \
    \           total_ += seg_len(seg);\n        }\n\n        return removed;\n  \
    \  }\n\n    SumT covered_length(T l, T r) const {\n        if (!(l < r)) return\
    \ 0;\n\n        SumT res = 0;\n        auto it = st_.lower_bound(l);\n       \
    \ if (it != st_.begin()) --it;\n\n        while (it != st_.end() && it->l < r)\
    \ {\n            if (l < it->r) {\n                T a = max(l, it->l);\n    \
    \            T b = min(r, it->r);\n                if (a < b) {\n            \
    \        res += static_cast<SumT>(b) - static_cast<SumT>(a);\n               \
    \ }\n            }\n            ++it;\n        }\n        return res;\n    }\n\
    \n    T mex(T x) const {\n        auto it = find_interval_it(x);\n        if (it\
    \ == st_.end()) return x;\n        return it->r;\n    }\n\n    void clear() {\n\
    \        st_.clear();\n        total_ = 0;\n    }\n\n    Interval prev_interval(T\
    \ x) const {\n        auto it = st_.upper_bound(x);\n        if (it == st_.begin())\
    \ return {-1, -1};\n        --it;\n        return *it;\n    }\n\n    Interval\
    \ next_interval(T x) const {\n        auto fit = find_interval_it(x);\n      \
    \  if (fit != st_.end()) return *fit;\n\n        auto it = st_.lower_bound(x);\n\
    \        if (it == st_.end()) return {-1, -1};\n        return *it;\n    }\n};\n\
    \n/**\n * @brief \u533A\u9593\u96C6\u5408(Interval Set)\n */\n#line 14 \"test/yosupo_predecessor_problem_interval_set.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    string\
    \ t;\n    sc.read(n, q, t);\n\n    IntervalSet<int, int> st;\n    for (int i =\
    \ 0; i < n; ++i) {\n        if (t[i] == '1') st.insert(i, i + 1);\n    }\n\n \
    \   while (q--) {\n        int c, k;\n        sc.read(c, k);\n        if (c ==\
    \ 0) {\n            st.insert(k, k + 1);\n        } else if (c == 1) {\n     \
    \       st.erase(k, k + 1);\n        } else if (c == 2) {\n            pr.println(st.contains(k)\
    \ ? 1 : 0);\n        } else if (c == 3) {\n            auto seg = st.next_interval(k);\n\
    \            if (seg.l == -1) pr.println(-1);\n            else pr.println(max(k,\
    \ seg.l));\n        } else {\n            auto seg = st.prev_interval(k);\n  \
    \          if (seg.l == -1) pr.println(-1);\n            else pr.println(min(k,\
    \ seg.r - 1));\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\n#include <cstdio>\n#include\
    \ <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../datastructure/interval_set.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int n, q;\n    string t;\n    sc.read(n, q, t);\n\
    \n    IntervalSet<int, int> st;\n    for (int i = 0; i < n; ++i) {\n        if\
    \ (t[i] == '1') st.insert(i, i + 1);\n    }\n\n    while (q--) {\n        int\
    \ c, k;\n        sc.read(c, k);\n        if (c == 0) {\n            st.insert(k,\
    \ k + 1);\n        } else if (c == 1) {\n            st.erase(k, k + 1);\n   \
    \     } else if (c == 2) {\n            pr.println(st.contains(k) ? 1 : 0);\n\
    \        } else if (c == 3) {\n            auto seg = st.next_interval(k);\n \
    \           if (seg.l == -1) pr.println(-1);\n            else pr.println(max(k,\
    \ seg.l));\n        } else {\n            auto seg = st.prev_interval(k);\n  \
    \          if (seg.l == -1) pr.println(-1);\n            else pr.println(min(k,\
    \ seg.r - 1));\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/interval_set.cpp
  isVerificationFile: true
  path: test/yosupo_predecessor_problem_interval_set.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 12:10:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_predecessor_problem_interval_set.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_predecessor_problem_interval_set.test.cpp
- /verify/test/yosupo_predecessor_problem_interval_set.test.cpp.html
title: test/yosupo_predecessor_problem_interval_set.test.cpp
---
