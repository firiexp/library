struct Prime {
    static constexpr int wheel[8]  = {4, 2, 4, 2, 4, 6, 2, 6};
    static constexpr int wheel2[8] = {7, 11, 13, 17, 19, 23, 29, 31};
    static constexpr int wheel_sum[30] = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        2, 2, 3, 3, 3, 3, 4, 4, 5, 5,
        5, 5, 6, 6, 6, 6, 6, 6, 7, 7
    };
    static constexpr int off64[64] = {
          0,  4,  6, 10, 12, 16, 22, 24,
         30, 34, 36, 40, 42, 46, 52, 54,
         60, 64, 66, 70, 72, 76, 82, 84,
         90, 94, 96,100,102,106,112,114,
        120,124,126,130,132,136,142,144,
        150,154,156,160,162,166,172,174,
        180,184,186,190,192,196,202,204,
        210,214,216,220,222,226,232,234
    };

    // old 1-based
    static inline int f(int n) { return (n - 1) / 30 * 8 + wheel_sum[(n - 1) % 30]; }
    static inline int g(int n) { return ((n - 1) >> 3) * 30 + wheel2[(n - 1) & 7]; }

    // internal 0-based
    static inline int f0(int n) { return f(n) - 1; }
    static inline int g0(int n) { return (n >> 3) * 30 + wheel2[n & 7]; }

    int count = 0;
    vector<int> primes;
    vector<int> picked;

private:
    static void build_sieve(int M, vector<ull>& sieve, int& n0) {
        if (M < 7) {
            n0 = -1;
            sieve.clear();
            return;
        }

        n0 = f0(M);
        int sq = (int)std::sqrt((double)M);
        int k0 = (sq >= 7 ? f0(sq) : -1);

        int num = n0 + 1;
        sieve.assign((num + 63) >> 6, ~0ULL);
        if (num & 63) sieve.back() &= (1ULL << (num & 63)) - 1;

        auto* sv = sieve.data();
        array<int, 8> delta{};

        for (int i = 0; i <= k0; ++i) {
            if (((sv[i >> 6] >> (i & 63)) & 1ULL) == 0) continue;

            int p = g0(i);
            int phase0 = i & 7;

            long long cur = 1LL * p * p;
            int idx = f0((int)cur);

            for (int t = 0; t < 8; ++t) {
                long long nxt = cur + 1LL * wheel[(phase0 + t) & 7] * p;
                delta[t] = f((int)nxt) - f((int)cur);
                cur = nxt;
            }

            const int d0 = delta[0];
            const int d1 = delta[1];
            const int d2 = delta[2];
            const int d3 = delta[3];
            const int d4 = delta[4];
            const int d5 = delta[5];
            const int d6 = delta[6];
            const int d7 = delta[7];

            while (idx <= n0) {
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d0;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d1;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d2;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d3;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d4;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d5;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d6;
                if (idx > n0) break;
                sv[idx >> 6] &= ~(1ULL << (idx & 63));
                idx += d7;
            }
        }
    }

public:
    Prime(int M) {
        if (M >= 17) {
            primes.reserve(max(0, (int)(M / (log((double)M) - 1.12))));
        }

        if (M >= 2) primes.push_back(2), ++count;
        if (M >= 3) primes.push_back(3), ++count;
        if (M >= 5) primes.push_back(5), ++count;
        if (M < 7) return;

        vector<ull> sieve;
        int n0;
        build_sieve(M, sieve, n0);

        int words = (n0 + 64) >> 6;
        for (int w = 0; w < words; ++w) {
            ull bits = sieve[w];
            int base = 240 * w + 7; // 64 candidates = 8 cycles = 240 numbers
            while (bits) {
                int t = __builtin_ctzll(bits);
                primes.push_back(base + off64[t]);
                ++count;
                bits &= bits - 1;
            }
        }
    }

    Prime(int M, int a, int b) {
        int next_pick = b;

        auto add_small = [&](int p) {
            if (count == next_pick) {
                picked.push_back(p);
                next_pick += a;
            }
            ++count;
        };

        if (M >= 2) add_small(2);
        if (M >= 3) add_small(3);
        if (M >= 5) add_small(5);
        if (M < 7) return;

        vector<ull> sieve;
        int n0;
        build_sieve(M, sieve, n0);

        int words = (n0 + 64) >> 6;
        for (int w = 0; w < words; ++w) {
            ull bits = sieve[w];
            int pc = __builtin_popcountll(bits);

            if (next_pick >= count + pc) {
                count += pc;
                continue;
            }

            int base = 240 * w + 7;
            while (bits) {
                int t = __builtin_ctzll(bits);
                if (count == next_pick) {
                    picked.push_back(base + off64[t]);
                    next_pick += a;
                }
                ++count;
                bits &= bits - 1;
            }
        }
    }
};

constexpr int Prime::wheel[8];
constexpr int Prime::wheel2[8];
constexpr int Prime::wheel_sum[30];
constexpr int Prime::off64[64];
