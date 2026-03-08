---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/slope_trick.cpp
    title: Slope Trick
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
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_slope_trick.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <queue>\n#include <random>\n#include\
    \ <vector>\nusing namespace std;\n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\nusing namespace\
    \ std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load() {\n  \
    \      int len = size - idx;\n        memmove(buf, buf + idx, len);\n        size\
    \ = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n\
    \        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if (idx\
    \ + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
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
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs\
    \ _md/fastio.md\n */\n#line 1 \"datastructure/slope_trick.cpp\"\ntemplate<class\
    \ T>\nstruct SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max()\
    \ / 4;\n\n    T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>,\
    \ greater<T>> R;\n    T add_l = 0, add_r = 0;\n\n    struct Query {\n        T\
    \ lx, rx, min_f;\n    };\n\nprivate:\n    void push_L(T a) { L.push(a - add_l);\
    \ }\n    void push_R(T a) { R.push(a - add_r); }\n    T top_L() const { return\
    \ L.empty() ? -INF : L.top() + add_l; }\n    T top_R() const { return R.empty()\
    \ ? INF : R.top() + add_r; }\n    T pop_L() {\n        T x = top_L();\n      \
    \  if (!L.empty()) L.pop();\n        return x;\n    }\n    T pop_R() {\n     \
    \   T x = top_R();\n        if (!R.empty()) R.pop();\n        return x;\n    }\n\
    \    size_t size() const { return L.size() + R.size(); }\n\npublic:\n    Query\
    \ query() const {\n        return {top_L(), top_R(), min_f};\n    }\n\n    void\
    \ add_all(T a) {\n        min_f += a;\n    }\n\n    void add_a_minus_x(T a) {\n\
    \        min_f += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n\
    \    }\n\n    void add_x_minus_a(T a) {\n        min_f += max<T>(0, top_L() -\
    \ a);\n        push_L(a);\n        push_R(pop_L());\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_right() {\n        decltype(R){}.swap(R);\n    }\n\n    void clear_left()\
    \ {\n        decltype(L){}.swap(L);\n    }\n\n    void shift(T a, T b) {\n   \
    \     assert(a <= b);\n        add_l += a;\n        add_r += b;\n    }\n\n   \
    \ void shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x) const {\n\
    \        T res = min_f;\n        auto lq = L;\n        auto rq = R;\n        while\
    \ (!lq.empty()) {\n            res += max<T>(0, lq.top() + add_l - x);\n     \
    \       lq.pop();\n        }\n        while (!rq.empty()) {\n            res +=\
    \ max<T>(0, x - (rq.top() + add_r));\n            rq.pop();\n        }\n     \
    \   return res;\n    }\n\n    void merge(SlopeTrick &st) {\n        if (st.size()\
    \ > size()) swap(*this, st);\n        while (!st.L.empty()) add_a_minus_x(st.pop_L());\n\
    \        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n        min_f += st.min_f;\n\
    \    }\n};\n\n/**\n * @brief Slope Trick\n * @docs _md/slope_trick.md\n */\n#line\
    \ 13 \"test/yosupo_many_aplusb_slope_trick.test.cpp\"\n\nint main() {\n    {\n\
    \        mt19937 rng(123456789);\n        constexpr long long INF = (1LL << 60);\n\
    \        constexpr int LIM = 200;\n        auto idx = [&](int x) { return x +\
    \ LIM; };\n\n        auto make_zero = [&]() {\n            return vector<long\
    \ long>(2 * LIM + 1, 0);\n        };\n\n        auto apply_add_all = [&](vector<long\
    \ long> &f, int a) {\n            for (auto &x : f) x += a;\n        };\n    \
    \    auto apply_add_a_minus_x = [&](vector<long long> &f, int a) {\n         \
    \   for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += max(0, a - x);\n        };\n\
    \        auto apply_add_x_minus_a = [&](vector<long long> &f, int a) {\n     \
    \       for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += max(0, x - a);\n      \
    \  };\n        auto apply_add_abs = [&](vector<long long> &f, int a) {\n     \
    \       for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += abs(x - a);\n        };\n\
    \        auto apply_merge = [&](vector<long long> &f, const vector<long long>\
    \ &g) {\n            for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += g[idx(x)];\n\
    \        };\n\n        for (int trial = 0; trial < 200; ++trial) {\n         \
    \   SlopeTrick<long long> st;\n            auto brute = make_zero();\n       \
    \     for (int step = 0; step < 40; ++step) {\n                int op = uniform_int_distribution<int>(0,\
    \ 4)(rng);\n                int a = uniform_int_distribution<int>(-20, 20)(rng);\n\
    \                if (op == 0) {\n                    st.add_all(a);\n        \
    \            apply_add_all(brute, a);\n                } else if (op == 1) {\n\
    \                    st.add_a_minus_x(a);\n                    apply_add_a_minus_x(brute,\
    \ a);\n                } else if (op == 2) {\n                    st.add_x_minus_a(a);\n\
    \                    apply_add_x_minus_a(brute, a);\n                } else if\
    \ (op == 3) {\n                    st.add_abs(a);\n                    apply_add_abs(brute,\
    \ a);\n                } else {\n                    SlopeTrick<long long> other;\n\
    \                    auto brute_other = make_zero();\n                    int\
    \ kind = uniform_int_distribution<int>(0, 3)(rng);\n                    int c\
    \ = uniform_int_distribution<int>(-20, 20)(rng);\n                    if (kind\
    \ == 0) {\n                        other.add_a_minus_x(c);\n                 \
    \       apply_add_a_minus_x(brute_other, c);\n                    } else if (kind\
    \ == 1) {\n                        other.add_x_minus_a(c);\n                 \
    \       apply_add_x_minus_a(brute_other, c);\n                    } else if (kind\
    \ == 2) {\n                        other.add_abs(c);\n                       \
    \ apply_add_abs(brute_other, c);\n                    } else {\n             \
    \           other.add_all(c);\n                        apply_add_all(brute_other,\
    \ c);\n                    }\n                    st.merge(other);\n         \
    \           apply_merge(brute, brute_other);\n                }\n\n          \
    \      long long brute_min = INF;\n                for (int x = -LIM; x <= LIM;\
    \ ++x) {\n                    long long got = st.eval(x);\n                  \
    \  long long want = brute[idx(x)];\n                    if (got != want) return\
    \ 1;\n                    brute_min = min(brute_min, want);\n                }\n\
    \                if (st.query().min_f != brute_min) return 1;\n            }\n\
    \        }\n\n        {\n            SlopeTrick<long long> st;\n            st.add_abs(3);\n\
    \            st.clear_right();\n            for (int x = -LIM; x <= LIM; ++x)\
    \ {\n                if (st.eval(x) != max(0, 3 - x)) return 1;\n            }\n\
    \            if (st.query().min_f != 0) return 1;\n        }\n        {\n    \
    \        SlopeTrick<long long> st;\n            st.add_abs(3);\n            st.clear_left();\n\
    \            for (int x = -LIM; x <= LIM; ++x) {\n                if (st.eval(x)\
    \ != max(0, x - 3)) return 1;\n            }\n            if (st.query().min_f\
    \ != 0) return 1;\n        }\n        {\n            SlopeTrick<long long> st;\n\
    \            st.add_abs(3);\n            st.shift(2);\n            for (int x\
    \ = -LIM; x <= LIM; ++x) {\n                if (st.eval(x) != abs(x - 5)) return\
    \ 1;\n            }\n            if (st.query().min_f != 0) return 1;\n      \
    \  }\n        {\n            SlopeTrick<long long> st;\n            st.add_abs(0);\n\
    \            st.shift(1, 3);\n            for (int x = -LIM; x <= LIM; ++x) {\n\
    \                long long want = 0;\n                if (x < 1) want = 1 - x;\n\
    \                if (x > 3) want = x - 3;\n                if (st.eval(x) != want)\
    \ return 1;\n            }\n            if (st.query().min_f != 0) return 1;\n\
    \        }\n    }\n\n    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n\
    \    while (t--) {\n        long long a, b;\n        sc.read(a, b);\n        pr.writeln(a\
    \ + b);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <queue>\n#include\
    \ <random>\n#include <vector>\nusing namespace std;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../datastructure/slope_trick.cpp\"\n\nint main() {\n    {\n     \
    \   mt19937 rng(123456789);\n        constexpr long long INF = (1LL << 60);\n\
    \        constexpr int LIM = 200;\n        auto idx = [&](int x) { return x +\
    \ LIM; };\n\n        auto make_zero = [&]() {\n            return vector<long\
    \ long>(2 * LIM + 1, 0);\n        };\n\n        auto apply_add_all = [&](vector<long\
    \ long> &f, int a) {\n            for (auto &x : f) x += a;\n        };\n    \
    \    auto apply_add_a_minus_x = [&](vector<long long> &f, int a) {\n         \
    \   for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += max(0, a - x);\n        };\n\
    \        auto apply_add_x_minus_a = [&](vector<long long> &f, int a) {\n     \
    \       for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += max(0, x - a);\n      \
    \  };\n        auto apply_add_abs = [&](vector<long long> &f, int a) {\n     \
    \       for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += abs(x - a);\n        };\n\
    \        auto apply_merge = [&](vector<long long> &f, const vector<long long>\
    \ &g) {\n            for (int x = -LIM; x <= LIM; ++x) f[idx(x)] += g[idx(x)];\n\
    \        };\n\n        for (int trial = 0; trial < 200; ++trial) {\n         \
    \   SlopeTrick<long long> st;\n            auto brute = make_zero();\n       \
    \     for (int step = 0; step < 40; ++step) {\n                int op = uniform_int_distribution<int>(0,\
    \ 4)(rng);\n                int a = uniform_int_distribution<int>(-20, 20)(rng);\n\
    \                if (op == 0) {\n                    st.add_all(a);\n        \
    \            apply_add_all(brute, a);\n                } else if (op == 1) {\n\
    \                    st.add_a_minus_x(a);\n                    apply_add_a_minus_x(brute,\
    \ a);\n                } else if (op == 2) {\n                    st.add_x_minus_a(a);\n\
    \                    apply_add_x_minus_a(brute, a);\n                } else if\
    \ (op == 3) {\n                    st.add_abs(a);\n                    apply_add_abs(brute,\
    \ a);\n                } else {\n                    SlopeTrick<long long> other;\n\
    \                    auto brute_other = make_zero();\n                    int\
    \ kind = uniform_int_distribution<int>(0, 3)(rng);\n                    int c\
    \ = uniform_int_distribution<int>(-20, 20)(rng);\n                    if (kind\
    \ == 0) {\n                        other.add_a_minus_x(c);\n                 \
    \       apply_add_a_minus_x(brute_other, c);\n                    } else if (kind\
    \ == 1) {\n                        other.add_x_minus_a(c);\n                 \
    \       apply_add_x_minus_a(brute_other, c);\n                    } else if (kind\
    \ == 2) {\n                        other.add_abs(c);\n                       \
    \ apply_add_abs(brute_other, c);\n                    } else {\n             \
    \           other.add_all(c);\n                        apply_add_all(brute_other,\
    \ c);\n                    }\n                    st.merge(other);\n         \
    \           apply_merge(brute, brute_other);\n                }\n\n          \
    \      long long brute_min = INF;\n                for (int x = -LIM; x <= LIM;\
    \ ++x) {\n                    long long got = st.eval(x);\n                  \
    \  long long want = brute[idx(x)];\n                    if (got != want) return\
    \ 1;\n                    brute_min = min(brute_min, want);\n                }\n\
    \                if (st.query().min_f != brute_min) return 1;\n            }\n\
    \        }\n\n        {\n            SlopeTrick<long long> st;\n            st.add_abs(3);\n\
    \            st.clear_right();\n            for (int x = -LIM; x <= LIM; ++x)\
    \ {\n                if (st.eval(x) != max(0, 3 - x)) return 1;\n            }\n\
    \            if (st.query().min_f != 0) return 1;\n        }\n        {\n    \
    \        SlopeTrick<long long> st;\n            st.add_abs(3);\n            st.clear_left();\n\
    \            for (int x = -LIM; x <= LIM; ++x) {\n                if (st.eval(x)\
    \ != max(0, x - 3)) return 1;\n            }\n            if (st.query().min_f\
    \ != 0) return 1;\n        }\n        {\n            SlopeTrick<long long> st;\n\
    \            st.add_abs(3);\n            st.shift(2);\n            for (int x\
    \ = -LIM; x <= LIM; ++x) {\n                if (st.eval(x) != abs(x - 5)) return\
    \ 1;\n            }\n            if (st.query().min_f != 0) return 1;\n      \
    \  }\n        {\n            SlopeTrick<long long> st;\n            st.add_abs(0);\n\
    \            st.shift(1, 3);\n            for (int x = -LIM; x <= LIM; ++x) {\n\
    \                long long want = 0;\n                if (x < 1) want = 1 - x;\n\
    \                if (x > 3) want = x - 3;\n                if (st.eval(x) != want)\
    \ return 1;\n            }\n            if (st.query().min_f != 0) return 1;\n\
    \        }\n    }\n\n    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n\
    \    while (t--) {\n        long long a, b;\n        sc.read(a, b);\n        pr.writeln(a\
    \ + b);\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/slope_trick.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_slope_trick.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_slope_trick.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_slope_trick.test.cpp
- /verify/test/yosupo_many_aplusb_slope_trick.test.cpp.html
title: test/yosupo_many_aplusb_slope_trick.test.cpp
---
