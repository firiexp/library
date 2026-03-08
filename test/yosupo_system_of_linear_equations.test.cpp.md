---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/gauss_jordan_mint.cpp
    title: Gauss Jordan Mint
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  - icon: ':question:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/system_of_linear_equations
    links:
    - https://judge.yosupo.jp/problem/system_of_linear_equations
  bundledCode: "#line 1 \"test/yosupo_system_of_linear_equations.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/system_of_linear_equations\"\n\n#include\
    \ <vector>\nusing namespace std;\n\nstatic const int MOD = 998244353;\nusing ll\
    \ = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\n#line\
    \ 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable {\n  \
    \  char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for\
    \ (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int\
    \ j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n\
    \                x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner\
    \ {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner() : idx(0),\
    \ size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n    \
    \    memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf + len,\
    \ 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n    }\n\
    \n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\
    \n    inline char skip() {\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        return\
    \ buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
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
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n    \
    \    if (idx) {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n\
    \        }\n    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE -\
    \ OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n    inline void write_range(const\
    \ char *s, size_t n) {\n        size_t pos = 0;\n        while (pos < n) {\n \
    \           if (idx == BUFSIZE) flush();\n            size_t chunk = min(n - pos,\
    \ (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s + pos, chunk);\n\
    \            idx += (int)chunk;\n            pos += chunk;\n        }\n    }\n\
    \n    void write(const char *s) {\n        write_range(s, strlen(s));\n    }\n\
    \n    void write(const string &s) {\n        write_range(s.data(), s.size());\n\
    \    }\n\n    void write(char c) {\n        pc(c);\n    }\n\n    void write(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void write(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
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
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T>\n    void writeln(const T\
    \ &x) {\n        write(x);\n        pc('\\n');\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void writeln(const Head &head, const Tail &...tail) {\n\
    \        write(head);\n        ((pc(' '), write(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"util/modint.cpp\"\
    \ntemplate <uint M>\nstruct modint {\n    uint val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M);\
    \ }\n    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n\
    \    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n  \
    \  modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -=\
    \ M; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % M); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(M-2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n */\n#line 2 \"math/gauss_jordan_mint.cpp\"\
    \n\nint gauss_jordan(vector<vector<mint>> &A, bool is_extended = false) {\n  \
    \  int m = A.size(), n = A[0].size();\n    int rank = 0;\n    for (int col = 0;\
    \ col < n; ++col) {\n        if (is_extended && col == n-1) break;\n        int\
    \ pivot = -1;\n        for (int row = rank; row < m; ++row) {\n            if\
    \ (A[row][col].val) {\n                pivot = row;\n                break;\n\
    \            }\n        }\n        if (pivot == -1) continue;\n        swap(A[pivot],\
    \ A[rank]);\n        auto d = A[rank][col].inv();\n        for (int col2 = 0;\
    \ col2 < n; ++col2) A[rank][col2] *= d;\n        for (int row = 0; row < m; ++row)\
    \ {\n            if (row != rank && A[row][col].val) {\n                auto fac\
    \ = A[row][col];\n                for (int col2 = 0; col2 < n; ++col2) {\n   \
    \                 A[row][col2] -= A[rank][col2] * fac;\n                }\n  \
    \          }\n        }\n        ++rank;\n    }\n    return rank;\n}\n\n/**\n\
    \ * @brief Gauss-Jordan\u6D88\u53BB(modint)\n */\n#line 13 \"test/yosupo_system_of_linear_equations.test.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n\n    int n, m;\n    in.read(n,\
    \ m);\n    vector<vector<mint>> a(n, vector<mint>(m + 1));\n    for (int i = 0;\
    \ i < n; ++i) {\n        for (int j = 0; j < m; ++j) {\n            int x;\n \
    \           in.read(x);\n            a[i][j] = x;\n        }\n    }\n    for (int\
    \ i = 0; i < n; ++i) {\n        int x;\n        in.read(x);\n        a[i][m] =\
    \ x;\n    }\n\n    int rank = gauss_jordan(a, true);\n    for (int row = rank;\
    \ row < n; ++row) {\n        if (a[row][m].val) {\n            out.writeln(-1);\n\
    \            return 0;\n        }\n    }\n\n    vector<int> pivot(rank, -1);\n\
    \    vector<int> is_pivot(m);\n    for (int row = 0; row < rank; ++row) {\n  \
    \      for (int col = 0; col < m; ++col) {\n            if (a[row][col].val) {\n\
    \                pivot[row] = col;\n                is_pivot[col] = 1;\n     \
    \           break;\n            }\n        }\n    }\n\n    vector<mint> particular(m);\n\
    \    for (int row = 0; row < rank; ++row) {\n        particular[pivot[row]] =\
    \ a[row][m];\n    }\n\n    vector<vector<mint>> basis;\n    for (int free_col\
    \ = 0; free_col < m; ++free_col) {\n        if (is_pivot[free_col]) continue;\n\
    \        vector<mint> vec(m);\n        vec[free_col] = 1;\n        for (int row\
    \ = 0; row < rank; ++row) {\n            vec[pivot[row]] = -a[row][free_col];\n\
    \        }\n        basis.push_back(vec);\n    }\n\n    out.writeln((int)basis.size());\n\
    \    for (int i = 0; i < m; ++i) {\n        out.write(particular[i].val);\n  \
    \      out.write(i + 1 == m ? '\\n' : ' ');\n    }\n    for (auto &&vec : basis)\
    \ {\n        for (int i = 0; i < m; ++i) {\n            out.write(vec[i].val);\n\
    \            out.write(i + 1 == m ? '\\n' : ' ');\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/system_of_linear_equations\"\
    \n\n#include <vector>\nusing namespace std;\n\nstatic const int MOD = 998244353;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../math/gauss_jordan_mint.cpp\"\n\
    \nint main() {\n    Scanner in;\n    Printer out;\n\n    int n, m;\n    in.read(n,\
    \ m);\n    vector<vector<mint>> a(n, vector<mint>(m + 1));\n    for (int i = 0;\
    \ i < n; ++i) {\n        for (int j = 0; j < m; ++j) {\n            int x;\n \
    \           in.read(x);\n            a[i][j] = x;\n        }\n    }\n    for (int\
    \ i = 0; i < n; ++i) {\n        int x;\n        in.read(x);\n        a[i][m] =\
    \ x;\n    }\n\n    int rank = gauss_jordan(a, true);\n    for (int row = rank;\
    \ row < n; ++row) {\n        if (a[row][m].val) {\n            out.writeln(-1);\n\
    \            return 0;\n        }\n    }\n\n    vector<int> pivot(rank, -1);\n\
    \    vector<int> is_pivot(m);\n    for (int row = 0; row < rank; ++row) {\n  \
    \      for (int col = 0; col < m; ++col) {\n            if (a[row][col].val) {\n\
    \                pivot[row] = col;\n                is_pivot[col] = 1;\n     \
    \           break;\n            }\n        }\n    }\n\n    vector<mint> particular(m);\n\
    \    for (int row = 0; row < rank; ++row) {\n        particular[pivot[row]] =\
    \ a[row][m];\n    }\n\n    vector<vector<mint>> basis;\n    for (int free_col\
    \ = 0; free_col < m; ++free_col) {\n        if (is_pivot[free_col]) continue;\n\
    \        vector<mint> vec(m);\n        vec[free_col] = 1;\n        for (int row\
    \ = 0; row < rank; ++row) {\n            vec[pivot[row]] = -a[row][free_col];\n\
    \        }\n        basis.push_back(vec);\n    }\n\n    out.writeln((int)basis.size());\n\
    \    for (int i = 0; i < m; ++i) {\n        out.write(particular[i].val);\n  \
    \      out.write(i + 1 == m ? '\\n' : ' ');\n    }\n    for (auto &&vec : basis)\
    \ {\n        for (int i = 0; i < m; ++i) {\n            out.write(vec[i].val);\n\
    \            out.write(i + 1 == m ? '\\n' : ' ');\n        }\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/gauss_jordan_mint.cpp
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_system_of_linear_equations.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_system_of_linear_equations.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_system_of_linear_equations.test.cpp
- /verify/test/yosupo_system_of_linear_equations.test.cpp.html
title: test/yosupo_system_of_linear_equations.test.cpp
---
