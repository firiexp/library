using namespace std;

class DynamicBitset {
    static constexpr int B = 64;
    using Word = unsigned long long;

    int n;
    vector<Word> a;

    static int popcount(Word x) {
        return __builtin_popcountll(x);
    }
    static int ctz(Word x) {
        return __builtin_ctzll(x);
    }
    static int clz(Word x) {
        return __builtin_clzll(x);
    }

    Word tail_mask() const {
        int rem = n & (B - 1);
        return rem ? ((1ULL << rem) - 1) : ~0ULL;
    }

    void normalize() {
        if (!a.empty()) a.back() &= tail_mask();
    }

public:
    DynamicBitset() : n(0) {}
    explicit DynamicBitset(int n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL : 0ULL) {
        normalize();
    }

    int size() const { return n; }
    bool empty() const { return n == 0; }

    void reset() {
        fill(a.begin(), a.end(), 0);
    }
    void set() {
        fill(a.begin(), a.end(), ~0ULL);
        normalize();
    }
    void flip() {
        for (auto &x : a) x = ~x;
        normalize();
    }

    bool test(int k) const {
        return (a[k >> 6] >> (k & 63)) & 1ULL;
    }
    void set(int k) {
        a[k >> 6] |= 1ULL << (k & 63);
    }
    void reset(int k) {
        a[k >> 6] &= ~(1ULL << (k & 63));
    }
    void flip(int k) {
        a[k >> 6] ^= 1ULL << (k & 63);
    }
    void assign(int k, bool x) {
        if (x) set(k);
        else reset(k);
    }

    bool any() const {
        for (auto x : a) if (x) return true;
        return false;
    }
    bool none() const { return !any(); }
    bool all() const {
        if (a.empty()) return true;
        for (int i = 0; i + 1 < (int)a.size(); ++i) {
            if (a[i] != ~0ULL) return false;
        }
        return a.back() == tail_mask();
    }
    int count() const {
        int res = 0;
        for (auto x : a) res += popcount(x);
        return res;
    }

    int find_first() const {
        for (int i = 0; i < (int)a.size(); ++i) {
            if (a[i]) return (i << 6) + ctz(a[i]);
        }
        return -1;
    }
    int find_last() const {
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            if (a[i]) return (i << 6) + (B - 1 - clz(a[i]));
        }
        return -1;
    }
    int find_next(int k) const {
        ++k;
        if (k >= n) return -1;
        int i = k >> 6;
        Word x = a[i] & (~0ULL << (k & 63));
        if (x) return (i << 6) + ctz(x);
        for (++i; i < (int)a.size(); ++i) {
            if (a[i]) return (i << 6) + ctz(a[i]);
        }
        return -1;
    }
    int find_prev(int k) const {
        --k;
        if (k < 0) return -1;
        int i = k >> 6;
        int rem = k & 63;
        Word mask = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);
        Word x = a[i] & mask;
        if (x) return (i << 6) + (B - 1 - clz(x));
        for (--i; i >= 0; --i) {
            if (a[i]) return (i << 6) + (B - 1 - clz(a[i]));
        }
        return -1;
    }

    DynamicBitset& operator&=(const DynamicBitset &r) {
        for (int i = 0; i < (int)a.size(); ++i) a[i] &= r.a[i];
        return *this;
    }
    DynamicBitset& operator|=(const DynamicBitset &r) {
        for (int i = 0; i < (int)a.size(); ++i) a[i] |= r.a[i];
        return *this;
    }
    DynamicBitset& operator^=(const DynamicBitset &r) {
        for (int i = 0; i < (int)a.size(); ++i) a[i] ^= r.a[i];
        normalize();
        return *this;
    }

    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset &r) { return l &= r; }
    friend DynamicBitset operator|(DynamicBitset l, const DynamicBitset &r) { return l |= r; }
    friend DynamicBitset operator^(DynamicBitset l, const DynamicBitset &r) { return l ^= r; }

    DynamicBitset& operator<<=(int s) {
        if (s <= 0) return *this;
        if (s >= n) {
            reset();
            return *this;
        }
        int block = s >> 6, rem = s & 63;
        if (rem == 0) {
            for (int i = (int)a.size() - 1; i >= 0; --i) {
                a[i] = i >= block ? a[i - block] : 0;
            }
        } else {
            for (int i = (int)a.size() - 1; i >= 0; --i) {
                Word x = 0;
                if (i >= block) {
                    x = a[i - block] << rem;
                    if (i - block - 1 >= 0) x |= a[i - block - 1] >> (B - rem);
                }
                a[i] = x;
            }
        }
        normalize();
        return *this;
    }
    DynamicBitset& operator>>=(int s) {
        if (s <= 0) return *this;
        if (s >= n) {
            reset();
            return *this;
        }
        int block = s >> 6, rem = s & 63;
        if (rem == 0) {
            for (int i = 0; i < (int)a.size(); ++i) {
                a[i] = i + block < (int)a.size() ? a[i + block] : 0;
            }
        } else {
            for (int i = 0; i < (int)a.size(); ++i) {
                Word x = 0;
                if (i + block < (int)a.size()) {
                    x = a[i + block] >> rem;
                    if (i + block + 1 < (int)a.size()) x |= a[i + block + 1] << (B - rem);
                }
                a[i] = x;
            }
        }
        normalize();
        return *this;
    }

    friend DynamicBitset operator<<(DynamicBitset l, int s) { return l <<= s; }
    friend DynamicBitset operator>>(DynamicBitset l, int s) { return l >>= s; }
};

/**
 * @brief 動的bitset(Dynamic Bitset)
 */
