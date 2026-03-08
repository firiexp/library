---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/hungarian.cpp
    title: Hungarian algorithm
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/assignment
    links:
    - https://judge.yosupo.jp/problem/assignment
  bundledCode: "#line 1 \"test/yosupo_assignment_hungarian.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/assignment\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <limits>\n#include <tuple>\n#include <vector>\nusing namespace\
    \ std;\n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable\
    \ {\n    char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n    \
    \    for (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for\
    \ (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x %\
    \ 10);\n                x /= 10;\n            }\n        }\n    }\n};\n\nstruct\
    \ Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner()\
    \ : idx(0), size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n\
    \        memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf +\
    \ len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n \
    \   }\n\n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n\
    \    }\n\n    inline char skip() {\n        ensure();\n        while (buf[idx]\
    \ && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n        }\n\
    \        return buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
    \ int>::type = 0>\n    void read(T &x) {\n        char c = skip();\n        bool\
    \ neg = false;\n        if constexpr (is_signed<T>::value) {\n            if (c\
    \ == '-') {\n                neg = true;\n                c = buf[idx++];\n  \
    \          }\n        }\n        x = 0;\n        while (c >= '0') {\n        \
    \    x = x * 10 + (c & 15);\n            c = buf[idx++];\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg) x = -x;\n        }\n\
    \    }\n\n    template<class Head, class... Tail>\n    void read(Head &head, Tail\
    \ &...tail) {\n        read(head);\n        (read(tail), ...);\n    }\n\n    void\
    \ read(char &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n\
    \        s.clear();\n        ensure();\n        while (buf[idx] && buf[idx] <=\
    \ ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (buf[idx] > ' ') ++idx;\n\
    \            s.append(buf + start, idx - start);\n            if (buf[idx] <=\
    \ ' ') break;\n            load();\n        }\n        ++idx;\n    }\n};\n\nstruct\
    \ Printer {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr\
    \ FastIoDigitTable table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush();\
    \ }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n    }\n\n    inline void write_range(const char *s, size_t n) {\n    \
    \    size_t pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE)\
    \ flush();\n            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n\
    \            memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n\
    \            pos += chunk;\n        }\n    }\n\n    void write(const char *s)\
    \ {\n        write_range(s, strlen(s));\n    }\n\n    void write(const string\
    \ &s) {\n        write_range(s.data(), s.size());\n    }\n\n    void write(char\
    \ c) {\n        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0'\
    \ + (b ? 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
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
    \    }\n};\n#line 1 \"flow/hungarian.cpp\"\ntemplate<class T, bool Minimize =\
    \ true>\ntuple<T, vector<int>, vector<T>, vector<T>> hungarian(const vector<vector<T>>\
    \ &cost) {\n    int n = cost.size();\n    if (n == 0) return {T(0), {}, {}, {}};\n\
    \    int m = cost[0].size();\n    assert(n <= m);\n    for (int i = 0; i < n;\
    \ ++i) assert((int)cost[i].size() == m);\n\n    vector<vector<T>> a(n + 1, vector<T>(m\
    \ + 1));\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0; j < m; ++j)\
    \ {\n            a[i + 1][j + 1] = Minimize ? cost[i][j] : -cost[i][j];\n    \
    \    }\n    }\n\n    vector<int> p(m + 1), way(m + 1);\n    vector<T> u(n + 1),\
    \ v(m + 1), minv(m + 1);\n    vector<char> used(m + 1);\n\n    for (int i = 1;\
    \ i <= n; ++i) {\n        p[0] = i;\n        fill(minv.begin(), minv.end(), numeric_limits<T>::max());\n\
    \        fill(used.begin(), used.end(), 0);\n        int j0 = 0;\n        while\
    \ (p[j0] != 0) {\n            used[j0] = 1;\n            int i0 = p[j0], j1 =\
    \ 0;\n            T delta = numeric_limits<T>::max();\n            for (int j\
    \ = 1; j <= m; ++j) {\n                if (used[j]) continue;\n              \
    \  T cur = a[i0][j] - u[i0] - v[j];\n                if (cur < minv[j]) {\n  \
    \                  minv[j] = cur;\n                    way[j] = j0;\n        \
    \        }\n                if (minv[j] < delta) {\n                    delta\
    \ = minv[j];\n                    j1 = j;\n                }\n            }\n\
    \            for (int j = 0; j <= m; ++j) {\n                if (used[j]) {\n\
    \                    u[p[j]] += delta;\n                    v[j] -= delta;\n \
    \               } else {\n                    minv[j] -= delta;\n            \
    \    }\n            }\n            j0 = j1;\n        }\n        while (j0 != 0)\
    \ {\n            int j1 = way[j0];\n            p[j0] = p[j1];\n            j0\
    \ = j1;\n        }\n    }\n\n    vector<int> match(n, -1);\n    for (int j = 1;\
    \ j <= m; ++j) {\n        if (p[j] != 0) match[p[j] - 1] = j - 1;\n    }\n\n \
    \   vector<T> row(n), col(m);\n    for (int i = 0; i < n; ++i) row[i] = u[i +\
    \ 1];\n    for (int j = 0; j < m; ++j) col[j] = v[j + 1];\n    T ans = -v[0];\n\
    \    if (!Minimize) {\n        ans = -ans;\n        for (int i = 0; i < n; ++i)\
    \ row[i] = -row[i];\n        for (int j = 0; j < m; ++j) col[j] = -col[j];\n \
    \   }\n    return {ans, match, row, col};\n}\n\n/**\n * @brief Hungarian algorithm\n\
    \ * @docs _md/hungarian.md\n */\n#line 12 \"test/yosupo_assignment_hungarian.test.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n    int n;\n    in.read(n);\n\
    \    vector<vector<long long>> a(n, vector<long long>(n));\n    for (int i = 0;\
    \ i < n; ++i) {\n        for (int j = 0; j < n; ++j) {\n            in.read(a[i][j]);\n\
    \        }\n    }\n    auto [ans, match, row, col] = hungarian<long long>(a);\n\
    \    out.writeln(ans);\n    for (int i = 0; i < n; ++i) {\n        if (i) out.write('\
    \ ');\n        out.write(match[i]);\n    }\n    out.writeln();\n\n    long long\
    \ dual_sum = 0;\n    for (int i = 0; i < n; ++i) dual_sum += row[i];\n    for\
    \ (int j = 0; j < n; ++j) dual_sum += col[j];\n    assert(dual_sum == ans);\n\
    \    for (int i = 0; i < n; ++i) {\n        for (int j = 0; j < n; ++j) {\n  \
    \          assert(row[i] + col[j] <= a[i][j]);\n        }\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <tuple>\n#include\
    \ <vector>\nusing namespace std;\n\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../flow/hungarian.cpp\"\n\nint main() {\n    Scanner in;\n    Printer out;\n\
    \    int n;\n    in.read(n);\n    vector<vector<long long>> a(n, vector<long long>(n));\n\
    \    for (int i = 0; i < n; ++i) {\n        for (int j = 0; j < n; ++j) {\n  \
    \          in.read(a[i][j]);\n        }\n    }\n    auto [ans, match, row, col]\
    \ = hungarian<long long>(a);\n    out.writeln(ans);\n    for (int i = 0; i < n;\
    \ ++i) {\n        if (i) out.write(' ');\n        out.write(match[i]);\n    }\n\
    \    out.writeln();\n\n    long long dual_sum = 0;\n    for (int i = 0; i < n;\
    \ ++i) dual_sum += row[i];\n    for (int j = 0; j < n; ++j) dual_sum += col[j];\n\
    \    assert(dual_sum == ans);\n    for (int i = 0; i < n; ++i) {\n        for\
    \ (int j = 0; j < n; ++j) {\n            assert(row[i] + col[j] <= a[i][j]);\n\
    \        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - flow/hungarian.cpp
  isVerificationFile: true
  path: test/yosupo_assignment_hungarian.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 15:57:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_assignment_hungarian.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_assignment_hungarian.test.cpp
- /verify/test/yosupo_assignment_hungarian.test.cpp.html
title: test/yosupo_assignment_hungarian.test.cpp
---
