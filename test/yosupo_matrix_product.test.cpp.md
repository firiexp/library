---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix.cpp
    title: "\u884C\u5217"
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
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product
    links:
    - https://judge.yosupo.jp/problem/matrix_product
  bundledCode: "#line 1 \"test/yosupo_matrix_product.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/matrix_product\"\n\n#include <vector>\nusing namespace\
    \ std;\n\nstatic const int MOD = 998244353;\nusing ll = long long;\nusing uint\
    \ = unsigned;\nusing ull = unsigned long long;\n\n#include <cstdio>\n#include\
    \ <cstring>\n#include <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin)))\
    \ {}\n\n    inline void load() {\n        int len = size - idx;\n        memmove(buf,\
    \ buf + idx, len);\n        if (interactive) {\n            if (fgets(buf + len,\
    \ BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n          \
    \  else size = len;\n        } else {\n            size = len + (int)fread(buf\
    \ + len, 1, BUFSIZE - len, stdin);\n        }\n        idx = 0;\n        buf[size]\
    \ = 0;\n    }\n\n    inline void ensure() {\n        if (idx + OFFSET > size)\
    \ load();\n    }\n\n    inline void ensure_interactive() {\n        if (idx ==\
    \ size) load();\n    }\n\n    inline char skip() {\n        if (interactive) {\n\
    \            ensure_interactive();\n            while (buf[idx] && buf[idx] <=\
    \ ' ') {\n                ++idx;\n                ensure_interactive();\n    \
    \        }\n            return buf[idx++];\n        }\n        ensure();\n   \
    \     while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n\
    \        }\n        return buf[idx++];\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T &x) {\n  \
    \      if (interactive) {\n            char c = skip();\n            bool neg\
    \ = false;\n            if constexpr (is_signed<T>::value) {\n               \
    \ if (c == '-') {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       x = 0;\n            while (c >= '0') {\n                x = x * 10 + (c\
    \ & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg) x = -x;\n            }\n            return;\n        }\n      \
    \  char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        x = 0;\n        while (c\
    \ >= '0') {\n            x = x * 10 + (c & 15);\n            c = buf[idx++];\n\
    \        }\n        if constexpr (is_signed<T>::value) {\n            if (neg)\
    \ x = -x;\n        }\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ Head, class Next, class... Tail>\n    void read(Head &head, Next &next, Tail\
    \ &...tail) {\n        read(head);\n        read(next, tail...);\n    }\n\n  \
    \  template<class T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first,\
    \ p.second);\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void print(T x) {\n      \
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
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value,\
    \ int>::type = 0>\n    void print(const T &x) {\n        print(x.value());\n \
    \   }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    MOD)\n */\n\n\n#line 1 \"math/matrix.cpp\"\ntemplate<class H>\nstruct matrix {\n\
    \    using T = typename H::T;\n    vector<vector<T>> A;\n    matrix() = default;\n\
    \    matrix(size_t n, size_t m) : A(n, vector<T>(m)) {}\n    explicit matrix(size_t\
    \ n) : A(n, vector<T> (n)) {};\n    size_t height() const { return (A.size());\
    \ }\n    size_t width() const { return (A.empty() ? 0 : A[0].size()); }\n\n  \
    \  const vector<T> &operator [] (int k) const { return A[k]; }\n    vector<T>\
    \ &operator[] (int k) { return A[k]; }\n\n    static matrix I(size_t n){\n   \
    \     matrix mat(n);\n        for (size_t i = 0; i < n; ++i) mat[i][i] = 1;\n\
    \        return mat;\n    }\n\n    matrix &operator+= (const matrix &B){\n   \
    \     size_t h = height(), w = width();\n        for (size_t i = 0; i < h; ++i)\
    \ {\n            for (size_t j = 0; j < w; ++j) {\n                H::add((*this)[i][j],\
    \ B[i][j]);\n            }\n        }\n        return (*this);\n    }\n\n    matrix\
    \ &operator-= (const matrix &B){\n        size_t h = height(), w = width();\n\
    \        for (size_t i = 0; i < h; ++i) {\n            for (size_t j = 0; j <\
    \ w; ++j) {\n                H::add((*this)[i][j], -B[i][j]);\n            }\n\
    \        }\n        return (*this);\n    }\n\n    matrix &operator*=(const matrix\
    \ &B) {\n        size_t n = height(), m = B.width(), p = width();\n        matrix\
    \ C(n, m);\n        for (size_t i = 0; i < n; ++i) {\n            for (size_t\
    \ k = 0; k < p; ++k) {\n                for (size_t j = 0; j < m; ++j) {\n   \
    \                 H::add(C[i][j], H::mul((*this)[i][k], B[k][j]));\n         \
    \       }\n            }\n        }\n        A.swap(C.A);\n        return (*this);\n\
    \    }\n\n    matrix pow(ll n) const {\n        matrix a = (*this), res = I(height());\n\
    \        while(n > 0){\n            if (n & 1) res *= a;\n            a *= a;\n\
    \            n >>= 1;\n        }\n        return res;\n    }\n    matrix operator+(const\
    \ matrix &B) const {return matrix(*this) += B;}\n    matrix operator-(const matrix\
    \ &B) const {return matrix(*this) -= B;}\n    matrix operator*(const matrix &B)\
    \ const {return matrix(*this) *= B;}\n\n    mint detarminant(){\n        mint\
    \ res = 1;\n        int rank = 0;\n        for (int c = 0; c < width(); ++c) {\n\
    \            int k = -1;\n            for (int i = rank; i < height(); ++i) {\n\
    \                if(A[i][c] != H::zero()){\n                    k = i;\n     \
    \               break;\n                }\n            }\n            if(!~k)\
    \ continue;\n            swap(A[k], A[rank]);\n            res *= A[rank][c];\n\
    \            T x = T(1)/A[rank][c];\n            for (int j = 0; j < width();\
    \ ++j) A[rank][j] *= x;\n            for (int i = 0; i < height(); ++i) {\n  \
    \              if(i != rank && A[i][c] != H::zero()){\n                    T coeff\
    \ = A[i][c];\n                    for (int j = 0; j < width(); ++j) {\n      \
    \                  A[i][j] -= A[rank][j]*coeff;\n                    }\n     \
    \           }\n            }\n            rank++;\n        }\n        for (int\
    \ i = 0; i < min(width(), height()); ++i) {\n            res *= A[i][i];\n   \
    \     }\n        return res;\n    }\n};\n\nstruct SemiRing {\n    using T = mint;\n\
    \    static inline T mul(T x, T y){ return x * y; }\n    static inline void add(T\
    \ &x, T y){ x += y; }\n    static inline T one(){ return 1; }\n    static inline\
    \ T zero(){ return 0; }\n};\n#line 19 \"test/yosupo_matrix_product.test.cpp\"\n\
    \nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, m, k;\n    sc.read(n,\
    \ m, k);\n    if (n == 0 || m == 0 || k == 0) {\n        for (int i = 0; i < n;\
    \ ++i) {\n            for (int j = 0; j < k; ++j) {\n                pr.print(0);\n\
    \                pr.print(j + 1 == k ? '\\n' : ' ');\n            }\n        \
    \    if (k == 0) pr.print('\\n');\n        }\n        return 0;\n    }\n    matrix<SemiRing>\
    \ A(n, m), B(m, k);\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0;\
    \ j < m; ++j) {\n            int x;\n            sc.read(x);\n            A[i][j]\
    \ = x;\n        }\n    }\n    for (int i = 0; i < m; ++i) {\n        for (int\
    \ j = 0; j < k; ++j) {\n            int x;\n            sc.read(x);\n        \
    \    B[i][j] = x;\n        }\n    }\n\n    auto C = A * B;\n    for (int i = 0;\
    \ i < n; ++i) {\n        for (int j = 0; j < k; ++j) {\n            pr.print(C[i][j].val);\n\
    \            pr.print(j + 1 == k ? '\\n' : ' ');\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\n\n#include\
    \ <vector>\nusing namespace std;\n\nstatic const int MOD = 998244353;\nusing ll\
    \ = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\n#include\
    \ <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\n\
    #include \"../util/fastio.cpp\"\n#include \"../util/modint.cpp\"\n#include \"\
    ../math/matrix.cpp\"\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n   \
    \ int n, m, k;\n    sc.read(n, m, k);\n    if (n == 0 || m == 0 || k == 0) {\n\
    \        for (int i = 0; i < n; ++i) {\n            for (int j = 0; j < k; ++j)\
    \ {\n                pr.print(0);\n                pr.print(j + 1 == k ? '\\n'\
    \ : ' ');\n            }\n            if (k == 0) pr.print('\\n');\n        }\n\
    \        return 0;\n    }\n    matrix<SemiRing> A(n, m), B(m, k);\n    for (int\
    \ i = 0; i < n; ++i) {\n        for (int j = 0; j < m; ++j) {\n            int\
    \ x;\n            sc.read(x);\n            A[i][j] = x;\n        }\n    }\n  \
    \  for (int i = 0; i < m; ++i) {\n        for (int j = 0; j < k; ++j) {\n    \
    \        int x;\n            sc.read(x);\n            B[i][j] = x;\n        }\n\
    \    }\n\n    auto C = A * B;\n    for (int i = 0; i < n; ++i) {\n        for\
    \ (int j = 0; j < k; ++j) {\n            pr.print(C[i][j].val);\n            pr.print(j\
    \ + 1 == k ? '\\n' : ' ');\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - math/matrix.cpp
  isVerificationFile: true
  path: test/yosupo_matrix_product.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_matrix_product.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_matrix_product.test.cpp
- /verify/test/yosupo_matrix_product.test.cpp.html
title: test/yosupo_matrix_product.test.cpp
---
