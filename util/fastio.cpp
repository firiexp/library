using namespace std;

extern "C" int fileno(FILE *);
extern "C" int isatty(int);

template<class T, class = void>
struct is_fastio_range : false_type {};

template<class T>
struct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> : true_type {};

template<class T, class = void>
struct has_fastio_value : false_type {};

template<class T>
struct has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type {};

template<class T, class = void>
struct has_fastio_assign_string : false_type {};

template<class T>
struct has_fastio_assign_string<T, void_t<decltype(declval<T &>().assign(declval<const string &>()))>> : true_type {};

template<class T, class = void>
struct has_fastio_to_string : false_type {};

template<class T>
struct has_fastio_to_string<T, void_t<decltype(declval<const T &>().to_string())>> : true_type {};

struct FastIoDigitTable {
    char num[40000];

    constexpr FastIoDigitTable() : num() {
        for (int i = 0; i < 10000; ++i) {
            int x = i;
            for (int j = 3; j >= 0; --j) {
                num[i * 4 + j] = char('0' + x % 10);
                x /= 10;
            }
        }
    }
};

struct Scanner {
    static constexpr int BUFSIZE = 1 << 17;
    static constexpr int OFFSET = 64;
    static constexpr int LONG_TOKEN_SAMPLE_SIZE = 1024;
    static constexpr int LONG_TOKEN_MIN_DIGITS = 16;
    char buf[BUFSIZE + 1];
    int idx, size;
    bool interactive, long_tokens;
    string number_token;

    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin))), long_tokens(false) {}

    __attribute__((always_inline))
    static inline unsigned parse_eight_digits(const char *p) {
        unsigned long long value;
        memcpy(&value, p, 8);
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        value = __builtin_bswap64(value);
#endif
        value -= 0x3030303030303030ULL;
        value = (value * 10 + (value >> 8)) & 0x00ff00ff00ff00ffULL;
        value = (value * 100 + (value >> 16)) & 0x0000ffff0000ffffULL;
        value = (value * 10000 + (value >> 32)) & 0x00000000ffffffffULL;
        return (unsigned)value;
    }

    __attribute__((always_inline))
    static inline bool are_eight_digits(const char *p) {
        unsigned long long value;
        memcpy(&value, p, 8);
        return (((value + 0x4646464646464646ULL) | (value - 0x3030303030303030ULL)) & 0x8080808080808080ULL) == 0;
    }

    template<class U>
    __attribute__((noinline))
    U read_long_digits(char c) {
        const char *p = buf + idx - 1;
        const char *end = buf + size;
        U value = 0;
        if (c >= '0' && end - p >= 16 && p[15] >= '0' && are_eight_digits(p) && are_eight_digits(p + 8)) {
            value = (U)parse_eight_digits(p) * 100000000 + parse_eight_digits(p + 8);
            p += 16;
            while (*p >= '0') {
                value = value * 10 + (*p & 15);
                ++p;
            }
            idx = (int)(p - buf) + 1;
            return value;
        }
        while (c >= '0') {
            value = value * 10 + (c & 15);
            c = buf[idx++];
        }
        return value;
    }

    inline void load() {
        int len = size - idx;
        memmove(buf, buf + idx, len);
        if (interactive) {
            if (fgets(buf + len, BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);
            else size = len;
        } else {
            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);
            int sample_size = min(size, LONG_TOKEN_SAMPLE_SIZE);
            int separators = 0;
            int minus_signs = 0;
            for (int i = 0; i < sample_size; ++i) {
                separators += buf[i] <= ' ';
                minus_signs += buf[i] == '-';
            }
            // Select once per buffer so ordinary short integers avoid the
            // checks and call overhead of the 16-digit SWAR path.
            long_tokens = separators * LONG_TOKEN_MIN_DIGITS < sample_size - minus_signs;
        }
        idx = 0;
        buf[size] = 0;
    }

    inline void ensure() {
        if (idx + OFFSET > size) load();
    }

    inline void ensure_interactive() {
        if (idx == size) load();
    }

    inline char skip() {
        if (interactive) {
            ensure_interactive();
            while (buf[idx] && buf[idx] <= ' ') {
                ++idx;
                ensure_interactive();
            }
            return buf[idx++];
        }
        ensure();
        while (buf[idx] && buf[idx] <= ' ') {
            ++idx;
            ensure();
        }
        return buf[idx++];
    }

    template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
    void read(T &x) {
        using Base = typename conditional<is_same<T, bool>::value, unsigned, T>::type;
        using U = typename make_unsigned<Base>::type;
        // The unsigned magnitude and -(y - 1) - 1 below also cover min(T).
        if (interactive) {
            char c = skip();
            bool neg = false;
            if constexpr (is_signed<T>::value) {
                if (c == '-') {
                    neg = true;
                    ensure_interactive();
                    c = buf[idx++];
                }
            }
            U y = 0;
            while (c >= '0') {
                y = y * 10 + (c & 15);
                ensure_interactive();
                c = buf[idx++];
            }
            if constexpr (is_signed<T>::value) {
                if (neg && y) {
                    x = -static_cast<T>(y - 1);
                    --x;
                    return;
                }
            }
            x = static_cast<T>(y);
            return;
        }
        char c = skip();
        bool neg = false;
        if constexpr (is_signed<T>::value) {
            if (c == '-') {
                neg = true;
                c = buf[idx++];
            }
        }
        U y;
        if (__builtin_expect(long_tokens, false)) {
            y = read_long_digits<U>(c);
        } else {
            y = 0;
            while (c >= '0') {
                y = y * 10 + (c & 15);
                c = buf[idx++];
            }
        }
        if constexpr (is_signed<T>::value) {
            if (neg && y) {
                x = -static_cast<T>(y - 1);
                --x;
                return;
            }
        }
        x = static_cast<T>(y);
    }

    void read(double &x) {
        read(number_token);
        const char *first = number_token.data();
        const char *last = first + number_token.size();
        auto result = from_chars(first, last, x);
        if (result.ec != errc{} || result.ptr != last) __builtin_trap();
    }

    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>
    void read(T &x) {
        long long v;
        read(v);
        x = T(v);
    }

    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value && has_fastio_assign_string<T>::value, int>::type = 0>
    void read(T &x) {
        string s;
        read(s);
        bool ok = x.assign(s);
        if (!ok) __builtin_trap();
    }

    template<class Head, class Next, class... Tail>
    void read(Head &head, Next &next, Tail &...tail) {
        read(head);
        read(next, tail...);
    }

    template<class T, class U>
    void read(pair<T, U> &p) {
        read(p.first, p.second);
    }

    template<class T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value, int>::type = 0>
    void read(T &a) {
        for (auto &x : a) read(x);
    }

    void read(char &c) {
        c = skip();
    }

    void read(string &s) {
        s.clear();
        if (interactive) {
            ensure_interactive();
            while (buf[idx] && buf[idx] <= ' ') {
                ++idx;
                ensure_interactive();
            }
            while (true) {
                int start = idx;
                while (idx < size && buf[idx] > ' ') ++idx;
                s.append(buf + start, idx - start);
                if (idx < size) break;
                load();
                if (size == 0) break;
            }
            if (idx < size) ++idx;
            return;
        }
        ensure();
        while (buf[idx] && buf[idx] <= ' ') {
            ++idx;
            ensure();
        }
        while (true) {
            int start = idx;
            while (idx < size && buf[idx] > ' ') ++idx;
            s.append(buf + start, idx - start);
            if (idx < size) break;
            load();
        }
        if (idx < size) ++idx;
    }
};

struct Printer {
    static constexpr int BUFSIZE = 1 << 17;
    static constexpr int OFFSET = 64;
    static constexpr int DEFAULT_DOUBLE_PRECISION = 15;
    char buf[BUFSIZE];
    int idx;
    bool interactive;
    string number_buf;
    inline static constexpr FastIoDigitTable table{};

    Printer() : idx(0), interactive(isatty(fileno(stdout))) {}
    ~Printer() { flush(); }

    inline void flush() {
        if (idx) {
            fwrite(buf, 1, idx, stdout);
            idx = 0;
        }
    }

    inline void pc(char c) {
        if (idx > BUFSIZE - OFFSET) flush();
        buf[idx++] = c;
        if (interactive && c == '\n') flush();
    }

    inline void print_range(const char *s, size_t n) {
        size_t pos = 0;
        while (pos < n) {
            if (idx == BUFSIZE) flush();
            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));
            memcpy(buf + idx, s + pos, chunk);
            idx += (int)chunk;
            pos += chunk;
        }
    }

    void print(const char *s) {
        print_range(s, strlen(s));
    }

    void print(const string &s) {
        print_range(s.data(), s.size());
    }

    void print(char c) {
        pc(c);
    }

    void print(bool b) {
        pc(char('0' + (b ? 1 : 0)));
    }

    inline char *write_top(char *out, unsigned x) {
        if (x >= 1000) {
            memcpy(out, table.num + (x << 2), 4);
            return out + 4;
        }
        if (x >= 100) {
            memcpy(out, table.num + (x << 2) + 1, 3);
            return out + 3;
        }
        if (x >= 10) {
            unsigned q = (x * 205) >> 11;
            out[0] = char('0' + q);
            out[1] = char('0' + (x - q * 10));
            return out + 2;
        }
        *out = char('0' + x);
        return out + 1;
    }

    inline void write_four(char *out, unsigned x) {
        memcpy(out, table.num + (x << 2), 4);
    }

    inline void write_eight(char *out, unsigned x) {
        unsigned hi = x / 10000;
        unsigned lo = x - hi * 10000;
        write_four(out, hi);
        write_four(out + 4, lo);
    }

    inline char *write_u32(char *out, unsigned x) {
        if (x >= 100000000) {
            unsigned hi = x / 100000000;
            unsigned lo = x - hi * 100000000;
            out = write_top(out, hi);
            write_eight(out, lo);
            return out + 8;
        }
        if (x >= 10000) {
            unsigned hi = x / 10000;
            unsigned lo = x - hi * 10000;
            out = write_top(out, hi);
            write_four(out, lo);
            return out + 4;
        }
        return write_top(out, x);
    }

    __attribute__((noinline))
    inline char *write_u64(char *out, unsigned long long x) {
        if (x <= 0xffffffffULL) return write_u32(out, (unsigned)x);
        unsigned long long hi = x / 100000000;
        unsigned lo = (unsigned)(x - hi * 100000000);
        if (hi <= 0xffffffffULL) {
            out = write_u32(out, (unsigned)hi);
            write_eight(out, lo);
            return out + 8;
        }
        unsigned top = (unsigned)(hi / 100000000);
        unsigned mid = (unsigned)(hi - (unsigned long long)top * 100000000);
        out = write_u32(out, top);
        write_eight(out, mid);
        write_eight(out + 8, lo);
        return out + 16;
    }

    template<class T, typename enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>
    void print(T x) {
        if (idx > BUFSIZE - 100) flush();
        using U = typename make_unsigned<T>::type;
        U y;
        if constexpr (is_signed<T>::value) {
            if (x < 0) {
                buf[idx++] = '-';
                y = U(0) - static_cast<U>(x);
            } else {
                y = static_cast<U>(x);
            }
        } else {
            y = x;
        }
        if (y == 0) {
            buf[idx++] = '0';
            return;
        }
        char *out;
        if constexpr (sizeof(U) <= 4) {
            out = write_u32(buf + idx, (unsigned)y);
        } else if constexpr (sizeof(U) <= 8) {
            out = write_u64(buf + idx, (unsigned long long)y);
        } else {
            static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;
            char tmp[TMP_SIZE];
            int pos = TMP_SIZE;
            while (y >= 10000) {
                pos -= 4;
                memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);
                y /= 10000;
            }
            out = write_top(buf + idx, (unsigned)y);
            memcpy(out, tmp + pos, TMP_SIZE - pos);
            out += TMP_SIZE - pos;
        }
        idx = (int)(out - buf);
    }

    void print_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION) {
        if (precision < 0) __builtin_trap();
        size_t required = (size_t)precision + 512;
        if (number_buf.size() < required) number_buf.resize(required);
        while (true) {
            char *first = number_buf.data();
            char *last = first + number_buf.size();
            auto result = to_chars(first, last, x, chars_format::fixed, precision);
            if (result.ec == errc{}) {
                print_range(first, result.ptr - first);
                return;
            }
            if (result.ec != errc::value_too_large) __builtin_trap();
            size_t next_size = number_buf.size() * 2;
            if (next_size <= number_buf.size()) __builtin_trap();
            number_buf.resize(next_size);
        }
    }

    void print(double x) {
        print_fixed(x);
    }

    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>
    void print(const T &x) {
        print(x.value());
    }

    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value && has_fastio_to_string<T>::value, int>::type = 0>
    void print(const T &x) {
        print(x.to_string());
    }

    template<class T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value, int>::type = 0>
    void print(const T &a) {
        bool first = true;
        for (auto &&x : a) {
            if (!first) pc(' ');
            first = false;
            print(x);
        }
    }

    template<class T>
    void println(const T &x) {
        print(x);
        pc('\n');
    }

    template<class Head, class... Tail>
    void println(const Head &head, const Tail &...tail) {
        print(head);
        ((pc(' '), print(tail)), ...);
        pc('\n');
    }

    void println_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION) {
        print_fixed(x, precision);
        pc('\n');
    }

    void println() {
        pc('\n');
    }
};

template<class T>
Scanner &operator>>(Scanner &in, T &x) {
    in.read(x);
    return in;
}

template<class T>
Printer &operator<<(Printer &out, const T &x) {
    out.print(x);
    return out;
}

/**
 * @brief 高速入出力(Fast IO)
 */
