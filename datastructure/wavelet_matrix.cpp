#if defined(__GNUC__) && defined(__x86_64__)
#include <immintrin.h>
#endif

template <class T>
struct WaveletMatrix {
    int n, lg, blocks;
    vector<int> mid;
    vector<unsigned long long> bit;
    vector<int> pref;
    vector<T> vals;

    WaveletMatrix() : n(0), lg(0), blocks(0) {}
    explicit WaveletMatrix(const vector<T> &v) { build(v); }

    static inline void rank1_pair(const unsigned long long *row, const int *row_pref, int l, int r, int &l1, int &r1) {
        int l_block = l >> 6;
        l1 = row_pref[l_block];
        int l_rem = l & 63;
        if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) - 1));

        int r_block = r >> 6;
        r1 = row_pref[r_block];
        int r_rem = r & 63;
        if (r_rem) r1 += __builtin_popcountll(row[r_block] & ((1ULL << r_rem) - 1));
    }

#if defined(__GNUC__) && defined(__x86_64__)
    __attribute__((target("popcnt,bmi2")))
    static inline void rank1_pair_bmi2(const unsigned long long *row, const int *row_pref, int l, int r,
                                       int &l1, int &r1) {
        int l_block = l >> 6;
        l1 = row_pref[l_block] + __builtin_popcountll(__builtin_ia32_bzhi_di(row[l_block], l & 63));

        int r_block = r >> 6;
        r1 = row_pref[r_block] + __builtin_popcountll(__builtin_ia32_bzhi_di(row[r_block], r & 63));
    }
#endif

    static int build_bit_row(const int *cur, int n, int blocks, int shift,
                             unsigned long long *row, int *row_pref) {
        int one_cnt = 0;
        for (int block = 0; block < blocks; ++block) {
            int begin = block << 6;
            int end = min(begin + 64, n);
            unsigned long long word = 0;
            for (int i = begin; i < end; ++i) {
                word |= (unsigned long long)((cur[i] >> shift) & 1) << (i - begin);
            }
            row[block] = word;
            one_cnt += __builtin_popcountll(word);
            row_pref[block + 1] = one_cnt;
        }
        return one_cnt;
    }

#if defined(__GNUC__) && defined(__x86_64__)
    __attribute__((target("avx2,popcnt")))
    static int build_bit_row_avx2(const int *cur, int n, int blocks, int shift,
                                  unsigned long long *row, int *row_pref) {
        int one_cnt = 0;
        __m128i shift_count = _mm_cvtsi32_si128(31 - shift);
        for (int block = 0; block < blocks; ++block) {
            int begin = block << 6;
            int end = min(begin + 64, n);
            unsigned long long word = 0;
            int i = begin;
            for (; i + 8 <= end; i += 8) {
                __m256i x = _mm256_loadu_si256((const __m256i *)(cur + i));
                __m256i shifted = _mm256_sll_epi32(x, shift_count);
                unsigned int mask = _mm256_movemask_ps(_mm256_castsi256_ps(shifted));
                word |= (unsigned long long)mask << (i - begin);
            }
            for (; i < end; ++i) {
                word |= (unsigned long long)((cur[i] >> shift) & 1) << (i - begin);
            }
            row[block] = word;
            one_cnt += __builtin_popcountll(word);
            row_pref[block + 1] = one_cnt;
        }
        return one_cnt;
    }

    struct PartitionTable8 {
        alignas(32) int perm[256][8];
        alignas(32) int rotate[9][8];
        alignas(32) int store[9][8];

        PartitionTable8() {
            for (int mask = 0; mask < 256; ++mask) {
                int pos = 0;
                for (int i = 0; i < 8; ++i) {
                    if (!((mask >> i) & 1)) perm[mask][pos++] = i;
                }
                for (int i = 0; i < 8; ++i) {
                    if ((mask >> i) & 1) perm[mask][pos++] = i;
                }
            }
            for (int zero_count = 0; zero_count <= 8; ++zero_count) {
                for (int i = 0; i < 8; ++i) {
                    rotate[zero_count][i] = zero_count + i < 8 ? zero_count + i : 0;
                    store[zero_count][i] = i < zero_count ? -1 : 0;
                }
            }
        }
    };

    __attribute__((target("avx2,popcnt")))
    static void stable_partition_avx2(const int *cur, int n, int shift, int zero_cnt,
                                      const unsigned long long *row, int *nxt) {
        static const PartitionTable8 table;
        int zi = 0, oi = zero_cnt;
        int i = 0;
        for (; i + 8 <= n; i += 8) {
            __m256i x = _mm256_loadu_si256((const __m256i *)(cur + i));
            unsigned int ones = (row[i >> 6] >> (i & 63)) & 0xffU;
            int one_count = __builtin_popcount(ones);
            int zero_count = 8 - one_count;
            __m256i perm = _mm256_load_si256((const __m256i *)table.perm[ones]);
            __m256i packed = _mm256_permutevar8x32_epi32(x, perm);
            __m256i one_perm = _mm256_load_si256((const __m256i *)table.rotate[zero_count]);
            __m256i one_values = _mm256_permutevar8x32_epi32(packed, one_perm);
            __m256i zero_store = _mm256_load_si256((const __m256i *)table.store[zero_count]);
            __m256i one_store = _mm256_load_si256((const __m256i *)table.store[one_count]);
            _mm256_maskstore_epi32(nxt + zi, zero_store, packed);
            _mm256_maskstore_epi32(nxt + oi, one_store, one_values);
            zi += zero_count;
            oi += one_count;
        }
        for (; i < n; ++i) {
            int x = cur[i];
            int b = (x >> shift) & 1;
            int dst = b ? oi : zi;
            nxt[dst] = x;
            zi += b ^ 1;
            oi += b;
        }
    }

    __attribute__((target("avx512f,popcnt")))
    static void stable_partition_avx512(const int *cur, int n, int shift, int zero_cnt,
                                        const unsigned long long *row, int *nxt) {
        int zi = 0, oi = zero_cnt;
        int i = 0;
        for (; i + 16 <= n; i += 16) {
            __m512i x = _mm512_loadu_si512((const void *)(cur + i));
            unsigned int ones = (row[i >> 6] >> (i & 63)) & 0xffffU;
            __mmask16 one_mask = (__mmask16)ones;
            __mmask16 zero_mask = (__mmask16)~one_mask;
            _mm512_mask_compressstoreu_epi32(nxt + zi, zero_mask, x);
            _mm512_mask_compressstoreu_epi32(nxt + oi, one_mask, x);
            int one_count = __builtin_popcount(ones);
            zi += 16 - one_count;
            oi += one_count;
        }
        for (; i < n; ++i) {
            int x = cur[i];
            int b = (x >> shift) & 1;
            int dst = b ? oi : zi;
            nxt[dst] = x;
            zi += b ^ 1;
            oi += b;
        }
    }

#endif

    template <class U>
    static auto encode_key(U x) -> typename make_unsigned<U>::type {
        using Key = typename make_unsigned<U>::type;
        Key key = static_cast<Key>(x);
        if constexpr (is_signed<U>::value) key ^= (Key(1) << (sizeof(U) * 8 - 1));
        return key;
    }

    void compress_generic(const vector<T> &v, vector<int> &cur) {
        vector<pair<T, int>> ord(n);
        for (int i = 0; i < n; ++i) ord[i] = {v[i], i};
        sort(ord.begin(), ord.end(), [](const pair<T, int> &a, const pair<T, int> &b) {
            return a.first < b.first;
        });
        vals.clear();
        vals.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (vals.empty() || vals.back() < ord[i].first || ord[i].first < vals.back()) {
                vals.push_back(ord[i].first);
            }
            cur[ord[i].second] = (int)vals.size() - 1;
        }
    }

    void compress_integral(const vector<T> &v, vector<int> &cur) {
        using Key = typename make_unsigned<T>::type;
        vector<Key> keys(n);
        vector<int> ord(n), buf(n);
        Key min_key = encode_key(v[0]);
        Key max_key = min_key;
        for (int i = 0; i < n; ++i) {
            keys[i] = encode_key(v[i]);
            ord[i] = i;
            min_key = min(min_key, keys[i]);
            max_key = max(max_key, keys[i]);
        }

        const int B = 16;
        const int MASK = (1 << B) - 1;
        const int bucket_count = 1 << B;
        auto pass_count = [&](Key x) {
            int passes = 0;
            while (x) {
                ++passes;
                x >>= B;
            }
            return passes;
        };
        int passes = pass_count(min_key ^ max_key);
        int normalized_passes = pass_count(max_key - min_key);
        if (normalized_passes < passes) {
            for (int i = 0; i < n; ++i) keys[i] -= min_key;
            passes = normalized_passes;
        }

        vector<int> cnt(bucket_count);
        for (int pass = 0; pass < passes; ++pass) {
            fill(cnt.begin(), cnt.end(), 0);
            int shift = pass * B;
            for (int i = 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];
            int sum = 0;
            for (int i = 0; i < bucket_count; ++i) {
                int count = cnt[i];
                cnt[i] = sum;
                sum += count;
            }
            for (int i = 0; i < n; ++i) {
                int id = ord[i];
                buf[cnt[(keys[id] >> shift) & MASK]++] = id;
            }
            ord.swap(buf);
        }

        vals.clear();
        vals.reserve(n);
        bool has_prev = false;
        Key prev = 0;
        for (int i = 0; i < n; ++i) {
            int id = ord[i];
            if (!has_prev || keys[id] != prev) {
                vals.push_back(v[id]);
                prev = keys[id];
                has_prev = true;
            }
            cur[id] = (int)vals.size() - 1;
        }
    }

    void compress_values(const vector<T> &v, vector<int> &cur) {
        if constexpr (is_integral<T>::value && sizeof(T) <= 8) compress_integral(v, cur);
        else compress_generic(v, cur);
    }

    void build_from_index_internal(vector<int> cur) {
        n = (int)cur.size();
        if (n == 0) {
            lg = 0;
            blocks = 0;
            mid.clear();
            bit.clear();
            pref.clear();
            return;
        }

        int m = (int)vals.size();
        lg = 0;
        while ((1LL << lg) < m) ++lg;
        if (lg == 0) lg = 1;
        blocks = (n + 63) >> 6;

        mid.assign(lg, 0);
        bit.assign(lg * blocks + 1, 0);
        pref.assign(lg * (blocks + 1), 0);
        vector<int> nxt(n);

#if defined(__GNUC__) && defined(__x86_64__)
        bool use_avx2 = __builtin_cpu_supports("avx2") && __builtin_cpu_supports("popcnt");
        bool use_avx512 = __builtin_cpu_supports("avx512f") && __builtin_cpu_supports("popcnt");
#endif

        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            auto *row = bit.data() + d * blocks;
            auto *row_pref = pref.data() + d * (blocks + 1);
            int one_cnt;
#if defined(__GNUC__) && defined(__x86_64__)
            if (use_avx2) one_cnt = build_bit_row_avx2(cur.data(), n, blocks, shift, row, row_pref);
            else one_cnt = build_bit_row(cur.data(), n, blocks, shift, row, row_pref);
#else
            one_cnt = build_bit_row(cur.data(), n, blocks, shift, row, row_pref);
#endif
            int zero_cnt = n - one_cnt;
            mid[d] = zero_cnt;

#if defined(__GNUC__) && defined(__x86_64__)
            if (use_avx512) stable_partition_avx512(cur.data(), n, shift, zero_cnt, row, nxt.data());
            else if (use_avx2) stable_partition_avx2(cur.data(), n, shift, zero_cnt, row, nxt.data());
            else
#endif
            {
                int zi = 0, oi = zero_cnt;
                for (int i = 0; i < n; ++i) {
                    int x = cur[i];
                    int b = (x >> shift) & 1;
                    int dst = b ? oi : zi;
                    nxt[dst] = x;
                    zi += b ^ 1;
                    oi += b;
                }
            }
            cur.swap(nxt);
        }
    }

    void build(const vector<T> &v) {
        n = (int)v.size();
        if (n == 0) {
            lg = 0;
            blocks = 0;
            vals.clear();
            mid.clear();
            bit.clear();
            pref.clear();
            return;
        }

        vector<int> cur(n);
        compress_values(v, cur);
        build_from_index_internal(move(cur));
    }

    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals) {
        vals = sorted_vals;
        build_from_index_internal(idx);
    }

private:
    int count_less_index_fallback(int l, int r, int xi) const {
        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        int res = 0;
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            if ((xi >> shift) & 1) {
                res += r0 - l0;
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            else {
                l = l0;
                r = r0;
            }
            if (l == r) break;
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return res;
    }

#if defined(__GNUC__) && defined(__x86_64__)
    __attribute__((target("popcnt,bmi2")))
    int count_less_index_bmi2(int l, int r, int xi) const {
        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        int res = 0;
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair_bmi2(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            if ((xi >> shift) & 1) {
                res += r0 - l0;
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            else {
                l = l0;
                r = r0;
            }
            if (l == r) break;
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return res;
    }
#endif

    int count_equal_index_fallback(int l, int r, int xi) const {
        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            if ((xi >> shift) & 1) {
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            else {
                l = l0;
                r = r0;
            }
            if (l == r) return 0;
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return r - l;
    }

#if defined(__GNUC__) && defined(__x86_64__)
    __attribute__((target("popcnt,bmi2")))
    int count_equal_index_bmi2(int l, int r, int xi) const {
        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair_bmi2(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            if ((xi >> shift) & 1) {
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            else {
                l = l0;
                r = r0;
            }
            if (l == r) return 0;
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return r - l;
    }
#endif

    int kth_smallest_index_fallback(int l, int r, int k) const {
        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        int idx = 0;
        for (int d = 0; d < lg; ++d) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            int z = r0 - l0;
            idx <<= 1;
            if (k < z) {
                l = l0;
                r = r0;
            }
            else {
                k -= z;
                idx |= 1;
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return idx;
    }

#if defined(__GNUC__) && defined(__x86_64__)
    __attribute__((target("popcnt,bmi2")))
    int kth_smallest_index_bmi2(int l, int r, int k) const {
        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        int idx = 0;
        for (int d = 0; d < lg; ++d) {
            int l1, r1;
            rank1_pair_bmi2(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            int z = r0 - l0;
            idx <<= 1;
            if (k < z) {
                l = l0;
                r = r0;
            }
            else {
                k -= z;
                idx |= 1;
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return idx;
    }
#endif

    template <bool Prev, bool UseBmi2>
    __attribute__((always_inline))
    bool neighbor_index_impl(int l, int r, int xi, int &res) const {
        int prefix = 0;
        int candidate_l = 0, candidate_r = 0, candidate_d = -1, candidate_idx = 0;
        int d = 0;
        for (; d < lg && l < r; ++d) {
            const auto *row = bit.data() + d * blocks;
            const int *row_pref = pref.data() + d * (blocks + 1);
            int l1, r1;
#if defined(__GNUC__) && defined(__x86_64__)
            if constexpr (UseBmi2) rank1_pair_bmi2(row, row_pref, l, r, l1, r1);
            else rank1_pair(row, row_pref, l, r, l1, r1);
#else
            rank1_pair(row, row_pref, l, r, l1, r1);
#endif
            int l0 = l - l1, r0 = r - r1;
            int bit_value = (xi >> (lg - d - 1)) & 1;
            if constexpr (Prev) {
                if (bit_value) {
                    if (l0 < r0) {
                        candidate_l = l0;
                        candidate_r = r0;
                        candidate_d = d + 1;
                        candidate_idx = prefix << 1;
                    }
                    l = mid[d] + l1;
                    r = mid[d] + r1;
                    prefix = prefix << 1 | 1;
                }
                else {
                    l = l0;
                    r = r0;
                    prefix <<= 1;
                }
            }
            else {
                if (bit_value) {
                    l = mid[d] + l1;
                    r = mid[d] + r1;
                    prefix = prefix << 1 | 1;
                }
                else {
                    if (l1 < r1) {
                        candidate_l = mid[d] + l1;
                        candidate_r = mid[d] + r1;
                        candidate_d = d + 1;
                        candidate_idx = prefix << 1 | 1;
                    }
                    l = l0;
                    r = r0;
                    prefix <<= 1;
                }
            }
        }

        if constexpr (!Prev) {
            if (d == lg && l < r) {
                res = prefix;
                return true;
            }
        }
        if (candidate_d < 0) return false;

        l = candidate_l;
        r = candidate_r;
        prefix = candidate_idx;
        for (d = candidate_d; d < lg; ++d) {
            const auto *row = bit.data() + d * blocks;
            const int *row_pref = pref.data() + d * (blocks + 1);
            int l1, r1;
#if defined(__GNUC__) && defined(__x86_64__)
            if constexpr (UseBmi2) rank1_pair_bmi2(row, row_pref, l, r, l1, r1);
            else rank1_pair(row, row_pref, l, r, l1, r1);
#else
            rank1_pair(row, row_pref, l, r, l1, r1);
#endif
            int l0 = l - l1, r0 = r - r1;
            prefix <<= 1;
            if constexpr (Prev) {
                if (l1 < r1) {
                    prefix |= 1;
                    l = mid[d] + l1;
                    r = mid[d] + r1;
                }
                else {
                    l = l0;
                    r = r0;
                }
            }
            else {
                if (l0 < r0) {
                    l = l0;
                    r = r0;
                }
                else {
                    prefix |= 1;
                    l = mid[d] + l1;
                    r = mid[d] + r1;
                }
            }
        }
        res = prefix;
        return true;
    }

    template <bool Prev>
    bool neighbor_index_fallback(int l, int r, int xi, int &res) const {
        return neighbor_index_impl<Prev, false>(l, r, xi, res);
    }

#if defined(__GNUC__) && defined(__x86_64__)
    template <bool Prev>
    __attribute__((target("popcnt,bmi2")))
    bool neighbor_index_bmi2(int l, int r, int xi, int &res) const {
        return neighbor_index_impl<Prev, true>(l, r, xi, res);
    }
#endif

public:
    int count_less_index(int l, int r, int xi) const {
        if (xi <= 0 || l >= r || n == 0) return 0;
        if (xi >= (int)vals.size()) return r - l;
#if defined(__GNUC__) && defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt") && __builtin_cpu_supports("bmi2")) {
            return count_less_index_bmi2(l, r, xi);
        }
#endif
        return count_less_index_fallback(l, r, xi);
    }

    int count_less(int l, int r, const T &x) const {
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_less_index(l, r, xi);
    }

    int count_equal_index(int l, int r, int xi) const {
        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size()) return 0;
#if defined(__GNUC__) && defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt") && __builtin_cpu_supports("bmi2")) {
            return count_equal_index_bmi2(l, r, xi);
        }
#endif
        return count_equal_index_fallback(l, r, xi);
    }

    vector<pair<int, int>> top_k_freq_index(int l, int r, int k) const {
        if (k <= 0 || l >= r || n == 0) return {};

#if defined(__GNUC__) && defined(__x86_64__)
        bool use_bmi2 = __builtin_cpu_supports("popcnt") && __builtin_cpu_supports("bmi2");
#endif

        struct Node {
            int l, r, d, idx;
            long long lower;
        };
        struct Item {
            int freq, idx;
        };

        auto item_better = [](const Item &a, const Item &b) {
            if (a.freq != b.freq) return a.freq > b.freq;
            return a.idx < b.idx;
        };
        auto node_worse = [](const Node &a, const Node &b) {
            int ca = a.r - a.l;
            int cb = b.r - b.l;
            if (ca != cb) return ca < cb;
            if (a.lower != b.lower) return a.lower > b.lower;
            return a.d < b.d;
        };

        vector<Node> heap;
        heap.push_back({l, r, 0, 0, 0});
        vector<Item> best;
        best.reserve(min(k, r - l));

        while (!heap.empty()) {
            if ((int)best.size() == k) {
                const Node &cur = heap.front();
                const Item &cut = best.front();
                int freq = cur.r - cur.l;
                if (freq < cut.freq) break;
                if (freq == cut.freq && cur.lower >= cut.idx) break;
            }

            pop_heap(heap.begin(), heap.end(), node_worse);
            Node cur = heap.back();
            heap.pop_back();

            if (cur.d == lg) {
                Item item{cur.r - cur.l, cur.idx};
                if ((int)best.size() < k) {
                    best.push_back(item);
                    push_heap(best.begin(), best.end(), item_better);
                }
                else if (item_better(item, best.front())) {
                    pop_heap(best.begin(), best.end(), item_better);
                    best.back() = item;
                    push_heap(best.begin(), best.end(), item_better);
                }
                continue;
            }

            const auto *row = bit.data() + cur.d * blocks;
            const int *row_pref = pref.data() + cur.d * (blocks + 1);
            int l1, r1;
#if defined(__GNUC__) && defined(__x86_64__)
            if (use_bmi2) rank1_pair_bmi2(row, row_pref, cur.l, cur.r, l1, r1);
            else rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);
#else
            rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);
#endif
            int l0 = cur.l - l1, r0 = cur.r - r1;
            int shift = lg - cur.d - 1;
            if (l0 < r0) {
                heap.push_back({l0, r0, cur.d + 1, cur.idx << 1, cur.lower});
                push_heap(heap.begin(), heap.end(), node_worse);
            }
            if (l1 < r1) {
                heap.push_back({
                    mid[cur.d] + l1,
                    mid[cur.d] + r1,
                    cur.d + 1,
                    cur.idx << 1 | 1,
                    cur.lower + (1LL << shift)
                });
                push_heap(heap.begin(), heap.end(), node_worse);
            }
        }

        sort(best.begin(), best.end(), item_better);
        vector<pair<int, int>> res;
        res.reserve(best.size());
        for (const auto &item : best) res.push_back({item.freq, item.idx});
        return res;
    }

    vector<pair<int, T>> top_k_freq(int l, int r, int k) const {
        auto idx_res = top_k_freq_index(l, r, k);
        vector<pair<int, T>> res;
        res.reserve(idx_res.size());
        for (const auto &p : idx_res) res.push_back({p.first, vals[p.second]});
        return res;
    }

    int range_freq(int l, int r, const T &lower, const T &upper) const {
        if (lower >= upper || l >= r) return 0;
        return count_less(l, r, upper) - count_less(l, r, lower);
    }

    int freq(int l, int r, const T &x) const {
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        if (xi == (int)vals.size() || vals[xi] != x) return 0;
        return count_equal_index(l, r, xi);
    }

    T kth_smallest(int l, int r, int k) const {
#if defined(__GNUC__) && defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt") && __builtin_cpu_supports("bmi2")) {
            return vals[kth_smallest_index_bmi2(l, r, k)];
        }
#endif
        return vals[kth_smallest_index_fallback(l, r, k)];
    }

    T kth_largest(int l, int r, int k) const {
        return kth_smallest(l, r, r - l - 1 - k);
    }

    bool prev_value(int l, int r, const T &upper, T &res) const {
        if (l >= r || n == 0) return false;
        int xi = (int)(lower_bound(vals.begin(), vals.end(), upper) - vals.begin());
        if (xi <= 0) return false;
        if (xi >= (int)vals.size()) {
            res = kth_largest(l, r, 0);
            return true;
        }
#if defined(__GNUC__) && defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt") && __builtin_cpu_supports("bmi2")) {
            int idx;
            if (!neighbor_index_bmi2<true>(l, r, xi, idx)) return false;
            res = vals[idx];
            return true;
        }
#endif
        int idx;
        if (!neighbor_index_fallback<true>(l, r, xi, idx)) return false;
        res = vals[idx];
        return true;
    }

    bool next_value(int l, int r, const T &lower, T &res) const {
        if (l >= r || n == 0) return false;
        int xi = (int)(lower_bound(vals.begin(), vals.end(), lower) - vals.begin());
        if (xi >= (int)vals.size()) return false;
#if defined(__GNUC__) && defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt") && __builtin_cpu_supports("bmi2")) {
            int idx;
            if (!neighbor_index_bmi2<false>(l, r, xi, idx)) return false;
            res = vals[idx];
            return true;
        }
#endif
        int idx;
        if (!neighbor_index_fallback<false>(l, r, xi, idx)) return false;
        res = vals[idx];
        return true;
    }
};

/**
 * @brief Wavelet Matrix
 */
