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
    char buf[BUFSIZE + 1];
    int idx, size;
    bool interactive;

    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin))) {}

    inline void load() {
        int len = size - idx;
        memmove(buf, buf + idx, len);
        if (interactive) {
            if (fgets(buf + len, BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);
            else size = len;
        } else {
            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);
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
            x = 0;
            while (c >= '0') {
                x = x * 10 + (c & 15);
                ensure_interactive();
                c = buf[idx++];
            }
            if constexpr (is_signed<T>::value) {
                if (neg) x = -x;
            }
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
        x = 0;
        while (c >= '0') {
            x = x * 10 + (c & 15);
            c = buf[idx++];
        }
        if constexpr (is_signed<T>::value) {
            if (neg) x = -x;
        }
    }

    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>
    void read(T &x) {
        long long v;
        read(v);
        x = T(v);
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
    char buf[BUFSIZE];
    int idx;
    bool interactive;
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
        static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;
        char tmp[TMP_SIZE];
        int pos = TMP_SIZE;
        while (y >= 10000) {
            pos -= 4;
            memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);
            y /= 10000;
        }
        if (y >= 1000) {
            memcpy(buf + idx, table.num + (y << 2), 4);
            idx += 4;
        } else if (y >= 100) {
            memcpy(buf + idx, table.num + (y << 2) + 1, 3);
            idx += 3;
        } else if (y >= 10) {
            unsigned q = (unsigned(y) * 205) >> 11;
            buf[idx] = char('0' + q);
            buf[idx + 1] = char('0' + (unsigned(y) - q * 10));
            idx += 2;
        } else {
            buf[idx++] = char('0' + y);
        }
        memcpy(buf + idx, tmp + pos, TMP_SIZE - pos);
        idx += TMP_SIZE - pos;
    }

    template<class T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>
    void print(const T &x) {
        print(x.value());
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
