---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: datastructure/top_k_sum.cpp
    title: "\u4E0A\u4F4DK\u500B\u306E\u548C\u3092\u7BA1\u7406\u3059\u308B\u30C7\u30FC\
      \u30BF\u69CB\u9020"
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_top_k_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <numeric>\n#include <random>\n#include <set>\n#include <vector>\n\
    using namespace std;\n\nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing\
    \ namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
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
    \ */\n#line 1 \"datastructure/top_k_sum.cpp\"\ntemplate<class T, class SumT =\
    \ long long, bool Largest = true>\nclass TopKSum {\nprivate:\n    multiset<T>\
    \ selected_;\n    multiset<T> other_;\n    int K_ = 0;\n    int total_size_ =\
    \ 0;\n    SumT total_sum_ = 0;\n    SumT selected_sum_ = 0;\n\n    static bool\
    \ selected_before(const T& a, const T& b) {\n        if constexpr (Largest) return\
    \ a > b;\n        else return a < b;\n    }\n\n    typename multiset<T>::iterator\
    \ selected_boundary() {\n        assert(!selected_.empty());\n        if constexpr\
    \ (Largest) return selected_.begin();\n        else return prev(selected_.end());\n\
    \    }\n\n    typename multiset<T>::const_iterator selected_boundary() const {\n\
    \        assert(!selected_.empty());\n        if constexpr (Largest) return selected_.begin();\n\
    \        else return prev(selected_.end());\n    }\n\n    typename multiset<T>::iterator\
    \ other_best() {\n        assert(!other_.empty());\n        if constexpr (Largest)\
    \ return prev(other_.end());\n        else return other_.begin();\n    }\n\n \
    \   void move_selected_to_other() {\n        auto it = selected_boundary();\n\
    \        T x = *it;\n        selected_.erase(it);\n        selected_sum_ -= (SumT)x;\n\
    \        other_.insert(x);\n    }\n\n    void move_other_to_selected() {\n   \
    \     auto it = other_best();\n        T x = *it;\n        other_.erase(it);\n\
    \        selected_.insert(x);\n        selected_sum_ += (SumT)x;\n    }\n\n  \
    \  void rebalance() {\n        int target = min(K_, total_size_);\n        while\
    \ ((int)selected_.size() > target) move_selected_to_other();\n        while ((int)selected_.size()\
    \ < target) move_other_to_selected();\n        while (!selected_.empty() && !other_.empty())\
    \ {\n            auto sit = selected_boundary();\n            auto oit = other_best();\n\
    \            T s = *sit;\n            T o = *oit;\n            if (!selected_before(o,\
    \ s)) break;\n            selected_.erase(sit);\n            other_.erase(oit);\n\
    \            selected_.insert(o);\n            other_.insert(s);\n           \
    \ selected_sum_ += (SumT)o - (SumT)s;\n        }\n    }\n\npublic:\n    explicit\
    \ TopKSum(int K = 0) : K_(K) {\n        assert(K >= 0);\n    }\n\n    TopKSum(const\
    \ TopKSum&) = delete;\n    TopKSum& operator=(const TopKSum&) = delete;\n\n  \
    \  int k() const {\n        return K_;\n    }\n\n    void set_k(int new_k) {\n\
    \        assert(new_k >= 0);\n        K_ = new_k;\n        rebalance();\n    }\n\
    \n    int size() const {\n        return total_size_;\n    }\n\n    bool empty()\
    \ const {\n        return total_size_ == 0;\n    }\n\n    SumT total_sum() const\
    \ {\n        return total_sum_;\n    }\n\n    void insert(const T& x) {\n    \
    \    ++total_size_;\n        total_sum_ += (SumT)x;\n        if ((int)selected_.size()\
    \ < K_) {\n            selected_.insert(x);\n            selected_sum_ += (SumT)x;\n\
    \        } else if (selected_.empty()) {\n            other_.insert(x);\n    \
    \    } else {\n            T s = *selected_boundary();\n            if (selected_before(x,\
    \ s)) {\n                selected_.insert(x);\n                selected_sum_ +=\
    \ (SumT)x;\n            } else {\n                other_.insert(x);\n        \
    \    }\n        }\n        rebalance();\n    }\n\n    bool erase_one(const T&\
    \ x) {\n        auto it = selected_.find(x);\n        if (it != selected_.end())\
    \ {\n            selected_sum_ -= (SumT)x;\n            selected_.erase(it);\n\
    \        } else {\n            it = other_.find(x);\n            if (it == other_.end())\
    \ return false;\n            other_.erase(it);\n        }\n        --total_size_;\n\
    \        total_sum_ -= (SumT)x;\n        rebalance();\n        return true;\n\
    \    }\n\n    bool has_kth() const {\n        return 1 <= K_ && K_ <= total_size_;\n\
    \    }\n\n    T kth() const {\n        assert(has_kth());\n        return *selected_boundary();\n\
    \    }\n\n    SumT sum_topk() const {\n        return selected_sum_;\n    }\n\
    };\n\n/**\n * @brief \u4E0A\u4F4DK\u548C\u7BA1\u7406\n */\n#line 20 \"test/yosupo_aplusb_top_k_sum.test.cpp\"\
    \n\ntemplate<bool Largest>\nll brute_sum_topk(const vector<ll>& a, int k) {\n\
    \    if (k <= 0) return 0;\n    vector<ll> b = a;\n    sort(b.begin(), b.end());\n\
    \    if constexpr (Largest) reverse(b.begin(), b.end());\n    k = min(k, (int)b.size());\n\
    \    return accumulate(b.begin(), b.begin() + k, 0LL);\n}\n\ntemplate<bool Largest>\n\
    ll brute_kth(const vector<ll>& a, int k) {\n    vector<ll> b = a;\n    sort(b.begin(),\
    \ b.end());\n    if constexpr (Largest) reverse(b.begin(), b.end());\n    return\
    \ b[k - 1];\n}\n\ntemplate<bool Largest>\nvoid verify_one(const vector<ll>& cur,\
    \ const TopKSum<ll, ll, Largest>& ds) {\n    assert(ds.size() == (int)cur.size());\n\
    \    assert(ds.empty() == cur.empty());\n    assert(ds.total_sum() == accumulate(cur.begin(),\
    \ cur.end(), 0LL));\n    assert(ds.sum_topk() == brute_sum_topk<Largest>(cur,\
    \ ds.k()));\n    if (ds.has_kth()) {\n        assert(ds.kth() == brute_kth<Largest>(cur,\
    \ ds.k()));\n    } else {\n        assert(ds.k() <= 0 || ds.k() > (int)cur.size());\n\
    \    }\n}\n\nvoid random_check() {\n    mt19937 rng(0);\n    for (int tc = 0;\
    \ tc < 300; ++tc) {\n        TopKSum<ll, ll, true> largest(0);\n        TopKSum<ll,\
    \ ll, false> smallest(0);\n        vector<ll> cur;\n\n        for (int step =\
    \ 0; step < 200; ++step) {\n            int op = rng() % 4;\n            if (op\
    \ <= 1) {\n                ll x = (int)(rng() % 17) - 8;\n                largest.insert(x);\n\
    \                smallest.insert(x);\n                cur.push_back(x);\n    \
    \        } else if (op == 2) {\n                ll x = (int)(rng() % 17) - 8;\n\
    \                bool ok1 = largest.erase_one(x);\n                bool ok2 =\
    \ smallest.erase_one(x);\n                auto it = find(cur.begin(), cur.end(),\
    \ x);\n                bool ok3 = it != cur.end();\n                if (ok3) cur.erase(it);\n\
    \                assert(ok1 == ok2);\n                assert(ok2 == ok3);\n  \
    \          } else {\n                int new_k = rng() % 12;\n               \
    \ largest.set_k(new_k);\n                smallest.set_k(new_k);\n            }\n\
    \            verify_one<true>(cur, largest);\n            verify_one<false>(cur,\
    \ smallest);\n        }\n    }\n}\n\nvoid sliding_window_check() {\n    mt19937\
    \ rng(1);\n    for (int tc = 0; tc < 100; ++tc) {\n        int n = rng() % 80\
    \ + 1;\n        int m = rng() % n + 1;\n        int k = rng() % (m + 2);\n   \
    \     vector<ll> a(n);\n        for (ll& x : a) x = (int)(rng() % 31) - 15;\n\n\
    \        TopKSum<ll, ll, false> ds(k);\n        vector<ll> got;\n        for (int\
    \ i = 0; i < n; ++i) {\n            ds.insert(a[i]);\n            if (i >= m)\
    \ ds.erase_one(a[i - m]);\n            if (i >= m - 1) {\n                vector<ll>\
    \ cur(a.begin() + i - m + 1, a.begin() + i + 1);\n                got.push_back(ds.sum_topk());\n\
    \                assert(got.back() == brute_sum_topk<false>(cur, k));\n      \
    \      }\n        }\n    }\n}\n\nint main() {\n    random_check();\n    sliding_window_check();\n\
    \n    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.writeln(a\
    \ + b);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <random>\n#include <set>\n#include\
    \ <vector>\nusing namespace std;\n\nusing ll = long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../datastructure/top_k_sum.cpp\"\n\ntemplate<bool Largest>\nll brute_sum_topk(const\
    \ vector<ll>& a, int k) {\n    if (k <= 0) return 0;\n    vector<ll> b = a;\n\
    \    sort(b.begin(), b.end());\n    if constexpr (Largest) reverse(b.begin(),\
    \ b.end());\n    k = min(k, (int)b.size());\n    return accumulate(b.begin(),\
    \ b.begin() + k, 0LL);\n}\n\ntemplate<bool Largest>\nll brute_kth(const vector<ll>&\
    \ a, int k) {\n    vector<ll> b = a;\n    sort(b.begin(), b.end());\n    if constexpr\
    \ (Largest) reverse(b.begin(), b.end());\n    return b[k - 1];\n}\n\ntemplate<bool\
    \ Largest>\nvoid verify_one(const vector<ll>& cur, const TopKSum<ll, ll, Largest>&\
    \ ds) {\n    assert(ds.size() == (int)cur.size());\n    assert(ds.empty() == cur.empty());\n\
    \    assert(ds.total_sum() == accumulate(cur.begin(), cur.end(), 0LL));\n    assert(ds.sum_topk()\
    \ == brute_sum_topk<Largest>(cur, ds.k()));\n    if (ds.has_kth()) {\n       \
    \ assert(ds.kth() == brute_kth<Largest>(cur, ds.k()));\n    } else {\n       \
    \ assert(ds.k() <= 0 || ds.k() > (int)cur.size());\n    }\n}\n\nvoid random_check()\
    \ {\n    mt19937 rng(0);\n    for (int tc = 0; tc < 300; ++tc) {\n        TopKSum<ll,\
    \ ll, true> largest(0);\n        TopKSum<ll, ll, false> smallest(0);\n       \
    \ vector<ll> cur;\n\n        for (int step = 0; step < 200; ++step) {\n      \
    \      int op = rng() % 4;\n            if (op <= 1) {\n                ll x =\
    \ (int)(rng() % 17) - 8;\n                largest.insert(x);\n               \
    \ smallest.insert(x);\n                cur.push_back(x);\n            } else if\
    \ (op == 2) {\n                ll x = (int)(rng() % 17) - 8;\n               \
    \ bool ok1 = largest.erase_one(x);\n                bool ok2 = smallest.erase_one(x);\n\
    \                auto it = find(cur.begin(), cur.end(), x);\n                bool\
    \ ok3 = it != cur.end();\n                if (ok3) cur.erase(it);\n          \
    \      assert(ok1 == ok2);\n                assert(ok2 == ok3);\n            }\
    \ else {\n                int new_k = rng() % 12;\n                largest.set_k(new_k);\n\
    \                smallest.set_k(new_k);\n            }\n            verify_one<true>(cur,\
    \ largest);\n            verify_one<false>(cur, smallest);\n        }\n    }\n\
    }\n\nvoid sliding_window_check() {\n    mt19937 rng(1);\n    for (int tc = 0;\
    \ tc < 100; ++tc) {\n        int n = rng() % 80 + 1;\n        int m = rng() %\
    \ n + 1;\n        int k = rng() % (m + 2);\n        vector<ll> a(n);\n       \
    \ for (ll& x : a) x = (int)(rng() % 31) - 15;\n\n        TopKSum<ll, ll, false>\
    \ ds(k);\n        vector<ll> got;\n        for (int i = 0; i < n; ++i) {\n   \
    \         ds.insert(a[i]);\n            if (i >= m) ds.erase_one(a[i - m]);\n\
    \            if (i >= m - 1) {\n                vector<ll> cur(a.begin() + i -\
    \ m + 1, a.begin() + i + 1);\n                got.push_back(ds.sum_topk());\n\
    \                assert(got.back() == brute_sum_topk<false>(cur, k));\n      \
    \      }\n        }\n    }\n}\n\nint main() {\n    random_check();\n    sliding_window_check();\n\
    \n    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.writeln(a\
    \ + b);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/top_k_sum.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_top_k_sum.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 11:58:39+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_aplusb_top_k_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_top_k_sum.test.cpp
- /verify/test/yosupo_aplusb_top_k_sum.test.cpp.html
title: test/yosupo_aplusb_top_k_sum.test.cpp
---
