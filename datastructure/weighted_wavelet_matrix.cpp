template <class T, class U>
struct WeightedWaveletMatrix {
    struct CountSum {
        int count;
        U sum;
    };

    int n, lg, blocks;
    vector<int> mid;
    vector<unsigned long long> bit;
    vector<int> pref;
    vector<U> zero_sum;
    vector<U> base_sum;
    vector<T> vals;

    WeightedWaveletMatrix() : n(0), lg(0), blocks(0) {}
    WeightedWaveletMatrix(const vector<T> &v, const vector<U> &w) { build(v, w); }

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

    template <class X>
    static auto encode_key(X x) -> typename make_unsigned<X>::type {
        using Key = typename make_unsigned<X>::type;
        Key key = static_cast<Key>(x);
        if constexpr (is_signed<X>::value) key ^= (Key(1) << (sizeof(X) * 8 - 1));
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
        for (int i = 0; i < n; ++i) {
            keys[i] = encode_key(v[i]);
            ord[i] = i;
        }

        const int B = 16;
        const int MASK = (1 << B) - 1;
        const int bucket_count = 1 << B;
        const int passes = (int)(sizeof(Key) * 8 + B - 1) / B;
        vector<int> cnt(bucket_count), pos(bucket_count);
        for (int pass = 0; pass < passes; ++pass) {
            fill(cnt.begin(), cnt.end(), 0);
            int shift = pass * B;
            for (int i = 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];
            pos[0] = 0;
            for (int i = 0; i + 1 < bucket_count; ++i) pos[i + 1] = pos[i] + cnt[i];
            for (int i = 0; i < n; ++i) {
                int id = ord[i];
                buf[pos[(keys[id] >> shift) & MASK]++] = id;
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

    void build_from_index_internal(vector<int> cur, const vector<U> &w) {
        n = (int)cur.size();
        base_sum.assign(n + 1, U());
        for (int i = 0; i < n; ++i) base_sum[i + 1] = base_sum[i] + w[i];

        if (n == 0) {
            lg = 0;
            blocks = 0;
            mid.clear();
            bit.clear();
            pref.clear();
            zero_sum.clear();
            return;
        }

        int m = (int)vals.size();
        lg = 0;
        while ((1LL << lg) < m) ++lg;
        if (lg == 0) lg = 1;
        blocks = (n + 63) >> 6;
        vector<U> cur_w = w;

        mid.assign(lg, 0);
        bit.assign(lg * blocks, 0);
        pref.assign(lg * (blocks + 1), 0);
        zero_sum.assign(lg * (n + 1), U());
        vector<int> nxt(n);
        vector<U> nxt_w(n);

        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            auto *row = bit.data() + d * blocks;
            auto *row_pref = pref.data() + d * (blocks + 1);
            auto *row_zero_sum = zero_sum.data() + d * (n + 1);
            int zero_cnt = 0;
            for (int i = 0; i < n; ++i) {
                int x = cur[i];
                int b = (x >> shift) & 1;
                if (b) row[i >> 6] |= 1ULL << (i & 63);
                else ++zero_cnt;
                row_zero_sum[i + 1] = row_zero_sum[i] + (b ? U() : cur_w[i]);
            }
            mid[d] = zero_cnt;
            for (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);

            int zi = 0, oi = zero_cnt;
            for (int i = 0; i < n; ++i) {
                int x = cur[i];
                if ((x >> shift) & 1) {
                    nxt[oi] = x;
                    nxt_w[oi++] = cur_w[i];
                }
                else {
                    nxt[zi] = x;
                    nxt_w[zi++] = cur_w[i];
                }
            }
            cur.swap(nxt);
            cur_w.swap(nxt_w);
        }
    }

    void build(const vector<T> &v, const vector<U> &w) {
        n = (int)v.size();
        if (n == 0) {
            lg = 0;
            blocks = 0;
            vals.clear();
            mid.clear();
            bit.clear();
            pref.clear();
            zero_sum.clear();
            base_sum.assign(1, U());
            return;
        }

        vector<int> cur(n);
        compress_values(v, cur);
        build_from_index_internal(move(cur), w);
    }

    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals, const vector<U> &w) {
        vals = sorted_vals;
        build_from_index_internal(idx, w);
    }

    CountSum count_sum_less_index(int l, int r, int xi) const {
        if (xi <= 0 || l >= r || n == 0) return {0, U()};
        if (xi >= (int)vals.size()) return {r - l, base_sum[r] - base_sum[l]};

        const int *mid_data = mid.data();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        const U *zero_sum_data = zero_sum.data();
        CountSum res{0, U()};
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            if ((xi >> shift) & 1) {
                res.count += r0 - l0;
                res.sum += zero_sum_data[r] - zero_sum_data[l];
                l = mid_data[d] + l1;
                r = mid_data[d] + r1;
            }
            else {
                l = l0;
                r = r0;
            }
            bit_data += blocks;
            pref_data += blocks + 1;
            zero_sum_data += n + 1;
        }
        return res;
    }

    CountSum count_sum_less(int l, int r, const T &x) const {
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_sum_less_index(l, r, xi);
    }

    CountSum count_sum_less_equal(int l, int r, const T &x) const {
        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_sum_less_index(l, r, xi);
    }

    int count_less(int l, int r, const T &x) const {
        return count_sum_less(l, r, x).count;
    }

    int count_less_equal(int l, int r, const T &x) const {
        return count_sum_less_equal(l, r, x).count;
    }

    U sum_less(int l, int r, const T &x) const {
        return count_sum_less(l, r, x).sum;
    }

    U sum_less_equal(int l, int r, const T &x) const {
        return count_sum_less_equal(l, r, x).sum;
    }
};

/**
 * @brief 重み付きWavelet Matrix(Weighted Wavelet Matrix)
 */
