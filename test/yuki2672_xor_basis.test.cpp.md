---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/xor_basis.cpp
    title: "XOR\u57FA\u5E95(Linear Basis)"
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
    PROBLEM: https://yukicoder.me/problems/no/2672
    links:
    - https://yukicoder.me/problems/no/2672
  bundledCode: "#line 1 \"test/yuki2672_xor_basis.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/2672\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <random>\n#include <vector>\n\
    using namespace std;\nusing ull = unsigned long long;\n\n#include <cstdio>\n#include\
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
    \ */\n#line 1 \"math/xor_basis.cpp\"\ntemplate<class T>\nstruct XorBasis {\n \
    \   static_assert(is_integral_v<T>, \"XorBasis requires integral T\");\n\n   \
    \ using U = make_unsigned_t<T>;\n    static constexpr int B = numeric_limits<U>::digits;\n\
    \n    vector<U> basis;\n    int rank = 0;\n\n    XorBasis() : basis(B, 0) {}\n\
    \n    int size() const {\n        return rank;\n    }\n\n    bool empty() const\
    \ {\n        return rank == 0;\n    }\n\n    bool add(T x) {\n        U y = reduce_unsigned(static_cast<U>(x));\n\
    \        if (y == 0) return false;\n\n        int p = B - 1;\n        while (((y\
    \ >> p) & 1) == 0) --p;\n        for (int i = 0; i < p; ++i) {\n            if\
    \ ((y >> i) & 1) y ^= basis[i];\n        }\n        basis[p] = y;\n        ++rank;\n\
    \        for (int i = p + 1; i < B; ++i) {\n            if ((basis[i] >> p) &\
    \ 1) basis[i] ^= y;\n        }\n        return true;\n    }\n\n    bool contains(T\
    \ x) const {\n        return reduce_unsigned(static_cast<U>(x)) == 0;\n    }\n\
    \n    T get_min(T x = 0) const {\n        return static_cast<T>(reduce_unsigned(static_cast<U>(x)));\n\
    \    }\n\n    T get_max(T x = 0) const {\n        U y = static_cast<U>(x);\n \
    \       for (int i = B - 1; i >= 0; --i) {\n            if (basis[i] == 0) continue;\n\
    \            U z = y ^ basis[i];\n            if (z > y) y = z;\n        }\n \
    \       return static_cast<T>(y);\n    }\n\n    void merge(const XorBasis &other)\
    \ {\n        for (int i = 0; i < B; ++i) {\n            if (other.basis[i] !=\
    \ 0) add(static_cast<T>(other.basis[i]));\n        }\n    }\n\nprivate:\n    U\
    \ reduce_unsigned(U x) const {\n        for (int i = B - 1; i >= 0; --i) {\n \
    \           if (((x >> i) & 1) == 0 || basis[i] == 0) continue;\n            x\
    \ ^= basis[i];\n        }\n        return x;\n    }\n};\n\n/**\n * @brief XOR\u57FA\
    \u5E95(Linear Basis)\n */\n#line 17 \"test/yuki2672_xor_basis.test.cpp\"\n\nbool\
    \ brute(const vector<int> &a) {\n    int n = a.size();\n    for (int mask = 1;\
    \ mask < (1 << n) - 1; ++mask) {\n        int xb = 0;\n        int xc = 0;\n \
    \       for (int i = 0; i < n; ++i) {\n            if ((mask >> i) & 1) xb ^=\
    \ a[i];\n            else xc ^= a[i];\n        }\n        if (xb == 0 && xc ==\
    \ 0) return true;\n    }\n    return false;\n}\n\nvoid self_check() {\n    {\n\
    \        for (int n = 2; n <= 12; ++n) {\n            for (int mask = 0; mask\
    \ < (1 << n); ++mask) {\n                vector<int> a(n);\n                for\
    \ (int i = 0; i < n; ++i) a[i] = (mask >> i) & 1;\n                XorBasis<int>\
    \ xb;\n                int total = 0;\n                for (int x : a) {\n   \
    \                 xb.add(x);\n                    total ^= x;\n              \
    \  }\n                bool ok = total == 0 && xb.size() < n - 1;\n           \
    \     assert(ok == brute(a));\n            }\n        }\n    }\n    {\n      \
    \  mt19937 rng(0);\n        for (int tc = 0; tc < 1000; ++tc) {\n            int\
    \ n = rng() % 14 + 2;\n            vector<int> a(n);\n            for (int i =\
    \ 0; i < n; ++i) a[i] = rng() % 16;\n            XorBasis<int> xb;\n         \
    \   int total = 0;\n            for (int x : a) {\n                xb.add(x);\n\
    \                total ^= x;\n            }\n            bool ok = total == 0\
    \ && xb.size() < n - 1;\n            assert(ok == brute(a));\n        }\n    }\n\
    }\n\nint main() {\n    self_check();\n\n    Scanner sc;\n    Printer pr;\n   \
    \ int n;\n    sc.read(n);\n    XorBasis<int> xb;\n    int total = 0;\n    for\
    \ (int i = 0; i < n; ++i) {\n        int a;\n        sc.read(a);\n        xb.add(a);\n\
    \        total ^= a;\n    }\n    pr.writeln(total == 0 && xb.size() < n - 1 ?\
    \ \"Yes\" : \"No\");\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2672\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <random>\n#include <vector>\nusing namespace std;\n\
    using ull = unsigned long long;\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../math/xor_basis.cpp\"\n\nbool brute(const vector<int> &a) {\n    int n =\
    \ a.size();\n    for (int mask = 1; mask < (1 << n) - 1; ++mask) {\n        int\
    \ xb = 0;\n        int xc = 0;\n        for (int i = 0; i < n; ++i) {\n      \
    \      if ((mask >> i) & 1) xb ^= a[i];\n            else xc ^= a[i];\n      \
    \  }\n        if (xb == 0 && xc == 0) return true;\n    }\n    return false;\n\
    }\n\nvoid self_check() {\n    {\n        for (int n = 2; n <= 12; ++n) {\n   \
    \         for (int mask = 0; mask < (1 << n); ++mask) {\n                vector<int>\
    \ a(n);\n                for (int i = 0; i < n; ++i) a[i] = (mask >> i) & 1;\n\
    \                XorBasis<int> xb;\n                int total = 0;\n         \
    \       for (int x : a) {\n                    xb.add(x);\n                  \
    \  total ^= x;\n                }\n                bool ok = total == 0 && xb.size()\
    \ < n - 1;\n                assert(ok == brute(a));\n            }\n        }\n\
    \    }\n    {\n        mt19937 rng(0);\n        for (int tc = 0; tc < 1000; ++tc)\
    \ {\n            int n = rng() % 14 + 2;\n            vector<int> a(n);\n    \
    \        for (int i = 0; i < n; ++i) a[i] = rng() % 16;\n            XorBasis<int>\
    \ xb;\n            int total = 0;\n            for (int x : a) {\n           \
    \     xb.add(x);\n                total ^= x;\n            }\n            bool\
    \ ok = total == 0 && xb.size() < n - 1;\n            assert(ok == brute(a));\n\
    \        }\n    }\n}\n\nint main() {\n    self_check();\n\n    Scanner sc;\n \
    \   Printer pr;\n    int n;\n    sc.read(n);\n    XorBasis<int> xb;\n    int total\
    \ = 0;\n    for (int i = 0; i < n; ++i) {\n        int a;\n        sc.read(a);\n\
    \        xb.add(a);\n        total ^= a;\n    }\n    pr.writeln(total == 0 &&\
    \ xb.size() < n - 1 ? \"Yes\" : \"No\");\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/xor_basis.cpp
  isVerificationFile: true
  path: test/yuki2672_xor_basis.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 11:58:39+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yuki2672_xor_basis.test.cpp
layout: document
redirect_from:
- /verify/test/yuki2672_xor_basis.test.cpp
- /verify/test/yuki2672_xor_basis.test.cpp.html
title: test/yuki2672_xor_basis.test.cpp
---
