using namespace std;

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

    Scanner() : idx(0), size(0) {}

    inline void load() {
        int len = size - idx;
        memmove(buf, buf + idx, len);
        size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);
        idx = 0;
        buf[size] = 0;
    }

    inline void ensure() {
        if (idx + OFFSET > size) load();
    }

    inline char skip() {
        ensure();
        while (buf[idx] && buf[idx] <= ' ') {
            ++idx;
            ensure();
        }
        return buf[idx++];
    }

    template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
    void read(T &x) {
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

    template<class Head, class... Tail>
    void read(Head &head, Tail &...tail) {
        read(head);
        (read(tail), ...);
    }

    void read(char &c) {
        c = skip();
    }

    void read(string &s) {
        s.clear();
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
    inline static constexpr FastIoDigitTable table{};

    Printer() : idx(0) {}
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
    }

    inline void write_range(const char *s, size_t n) {
        size_t pos = 0;
        while (pos < n) {
            if (idx == BUFSIZE) flush();
            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));
            memcpy(buf + idx, s + pos, chunk);
            idx += (int)chunk;
            pos += chunk;
        }
    }

    void write(const char *s) {
        write_range(s, strlen(s));
    }

    void write(const string &s) {
        write_range(s.data(), s.size());
    }

    void write(char c) {
        pc(c);
    }

    void write(bool b) {
        pc(char('0' + (b ? 1 : 0)));
    }

    template<class T, typename enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>
    void write(T x) {
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

    template<class T>
    void writeln(const T &x) {
        write(x);
        pc('\n');
    }

    template<class Head, class... Tail>
    void writeln(const Head &head, const Tail &...tail) {
        write(head);
        ((pc(' '), write(tail)), ...);
        pc('\n');
    }

    void writeln() {
        pc('\n');
    }
};

/**
 * @brief 高速入出力(Fast IO)
 */
