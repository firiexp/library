template <class T, class U>
struct DynamicWeightedWaveletMatrix {
    struct CountSum {
        int count;
        U sum;
    };

    int n, lg, blocks, slot_count;
    bool initialized, built;
    vector<int> mid;
    vector<int> row_offset;
    vector<unsigned long long> bit;
    vector<int> pref;
    vector<int> zero_count_fenwick;
    vector<U> zero_sum_fenwick;
    vector<int> leaf_count_fenwick;
    vector<U> leaf_sum_fenwick;
    vector<U> base_sum_fenwick;
    vector<int> offset;
    vector<int> current_slot;
    vector<int> slot_value_index;
    vector<U> weights;
    vector<T> vals;
    vector<T> slot_values;
    vector<pair<int, T>> value_candidates;

    DynamicWeightedWaveletMatrix()
        : n(0), lg(0), blocks(0), slot_count(0), initialized(false), built(false) {}

    explicit DynamicWeightedWaveletMatrix(int n) : DynamicWeightedWaveletMatrix() {
        init(n);
    }

    DynamicWeightedWaveletMatrix(const vector<T> &v, const vector<U> &w)
        : DynamicWeightedWaveletMatrix((int)v.size()) {
        build(v, w);
    }

    DynamicWeightedWaveletMatrix(const vector<T> &v, const vector<U> &w,
                                 const vector<pair<int, T>> &candidates)
        : DynamicWeightedWaveletMatrix((int)v.size()) {
        reserve_candidates((int)candidates.size());
        for (const auto &[k, x] : candidates) add_value_candidate(k, x);
        build(v, w);
    }

    void init(int size) {
        assert(size >= 0);
        n = size;
        lg = blocks = slot_count = 0;
        initialized = true;
        built = false;
        mid.clear();
        row_offset.clear();
        bit.clear();
        pref.clear();
        zero_count_fenwick.clear();
        zero_sum_fenwick.clear();
        leaf_count_fenwick.clear();
        leaf_sum_fenwick.clear();
        base_sum_fenwick.clear();
        offset.clear();
        current_slot.clear();
        slot_value_index.clear();
        weights.clear();
        vals.clear();
        slot_values.clear();
        value_candidates.clear();
    }

    void reserve_candidates(int capacity) {
        assert(initialized && !built && capacity >= 0);
        value_candidates.reserve(capacity);
    }

    void add_value_candidate(int k, const T &x) {
        assert(initialized && !built);
        assert(0 <= k && k < n);
        value_candidates.push_back({k, x});
    }

    static bool equivalent(const T &a, const T &b) {
        return !(a < b) && !(b < a);
    }

    static inline void rank1_pair(const unsigned long long *row, const int *row_pref,
                                  int l, int r, int &l1, int &r1) {
        int l_block = l >> 6;
        l1 = row_pref[l_block];
        int l_rem = l & 63;
        if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) - 1));

        int r_block = r >> 6;
        r1 = row_pref[r_block];
        int r_rem = r & 63;
        if (r_rem) r1 += __builtin_popcountll(row[r_block] & ((1ULL << r_rem) - 1));
    }

    int rank1(int d, int k) const {
        const auto *row = bit.data() + d * blocks;
        const int *row_pref = pref.data() + d * (blocks + 1);
        int block = k >> 6;
        int res = row_pref[block];
        int rem = k & 63;
        if (rem) res += __builtin_popcountll(row[block] & ((1ULL << rem) - 1));
        return res;
    }

    template <class V>
    static void fenwick_build(vector<V> &fw, int start, int length) {
        for (int i = 1; i <= length; ++i) {
            int j = i + (i & -i);
            if (j <= length) fw[start + j] += fw[start + i];
        }
    }

    template <class V>
    static void fenwick_add(vector<V> &fw, int start, int length, int k, const V &x) {
        for (++k; k <= length; k += k & -k) fw[start + k] += x;
    }

    template <class V>
    static V fenwick_prefix(const vector<V> &fw, int start, int k) {
        V res = V();
        for (; k > 0; k -= k & -k) res += fw[start + k];
        return res;
    }

    template <class V>
    static V fenwick_range(const vector<V> &fw, int start, int l, int r) {
        return fenwick_prefix(fw, start, r) - fenwick_prefix(fw, start, l);
    }

    int find_slot(int k, const T &x) const {
        auto first = slot_values.begin() + offset[k];
        auto last = slot_values.begin() + offset[k + 1];
        auto it = lower_bound(first, last, x);
        if (it == last || !equivalent(*it, x)) return -1;
        return (int)(it - slot_values.begin());
    }

    void build(const vector<T> &v, const vector<U> &w) {
        if (!initialized) init((int)v.size());
        assert(!built);
        assert((int)v.size() == n && (int)w.size() == n);

        vector<pair<int, T>> candidates = value_candidates;
        candidates.reserve(candidates.size() + n);
        for (int i = 0; i < n; ++i) candidates.push_back({i, v[i]});
        sort(candidates.begin(), candidates.end(), [](const pair<int, T> &a, const pair<int, T> &b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });

        int unique_size = 0;
        for (int i = 0; i < (int)candidates.size(); ++i) {
            if (unique_size == 0 || candidates[unique_size - 1].first != candidates[i].first ||
                !equivalent(candidates[unique_size - 1].second, candidates[i].second)) {
                if (unique_size != i) candidates[unique_size] = move(candidates[i]);
                ++unique_size;
            }
        }
        candidates.resize(unique_size);

        offset.assign(n + 1, 0);
        for (const auto &[k, x] : candidates) {
            (void)x;
            ++offset[k + 1];
        }
        for (int i = 0; i < n; ++i) offset[i + 1] += offset[i];

        slot_count = (int)candidates.size();
        slot_values.resize(slot_count);
        for (int i = 0; i < slot_count; ++i) slot_values[i] = move(candidates[i].second);

        vals = slot_values;
        sort(vals.begin(), vals.end());
        int value_count = 0;
        for (int i = 0; i < (int)vals.size(); ++i) {
            if (value_count == 0 || !equivalent(vals[value_count - 1], vals[i])) {
                if (value_count != i) vals[value_count] = move(vals[i]);
                ++value_count;
            }
        }
        vals.resize(value_count);

        current_slot.resize(n);
        weights = w;
        for (int i = 0; i < n; ++i) {
            current_slot[i] = find_slot(i, v[i]);
            assert(current_slot[i] != -1);
        }

        if (slot_count == 0) {
            lg = blocks = 0;
            mid.clear();
            row_offset.clear();
            bit.clear();
            pref.clear();
            zero_count_fenwick.clear();
            zero_sum_fenwick.clear();
            leaf_count_fenwick.assign(1, 0);
            leaf_sum_fenwick.assign(1, U());
            base_sum_fenwick.assign(1, U());
            slot_value_index.clear();
            value_candidates.clear();
            value_candidates.shrink_to_fit();
            built = true;
            return;
        }

        lg = 0;
        while ((1LL << lg) < (int)vals.size()) ++lg;
        if (lg == 0) lg = 1;
        blocks = (slot_count + 63) >> 6;

        slot_value_index.resize(slot_count);
        for (int i = 0; i < slot_count; ++i) {
            slot_value_index[i] = (int)(lower_bound(vals.begin(), vals.end(), slot_values[i]) - vals.begin());
        }

        vector<unsigned char> active(slot_count, 0);
        vector<U> active_weight(slot_count, U());
        for (int i = 0; i < n; ++i) {
            active[current_slot[i]] = 1;
            active_weight[current_slot[i]] = w[i];
        }

        mid.assign(lg, 0);
        bit.assign(lg * blocks, 0);
        pref.assign(lg * (blocks + 1), 0);
        vector<int> cur(slot_count), nxt(slot_count);
        for (int i = 0; i < slot_count; ++i) cur[i] = i;

        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            auto *row = bit.data() + d * blocks;
            auto *row_pref = pref.data() + d * (blocks + 1);
            int zero_count = 0;
            for (int i = 0; i < slot_count; ++i) {
                int b = (slot_value_index[cur[i]] >> shift) & 1;
                if (b) row[i >> 6] |= 1ULL << (i & 63);
                else ++zero_count;
            }
            mid[d] = zero_count;
            for (int i = 0; i < blocks; ++i) {
                row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);
            }

            int zi = 0, oi = zero_count;
            for (int i = 0; i < slot_count; ++i) {
                int id = cur[i];
                if ((slot_value_index[id] >> shift) & 1) nxt[oi++] = id;
                else nxt[zi++] = id;
            }
            cur.swap(nxt);
        }

        row_offset.resize(lg);
        size_t fenwick_size = 0;
        for (int d = 0; d < lg; ++d) {
            row_offset[d] = (int)fenwick_size;
            fenwick_size += (size_t)mid[d] + 1;
        }
        zero_count_fenwick.assign(fenwick_size, 0);
        zero_sum_fenwick.assign(fenwick_size, U());

        for (int i = 0; i < slot_count; ++i) cur[i] = i;
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int start = row_offset[d];
            int zi = 0, oi = mid[d];
            for (int i = 0; i < slot_count; ++i) {
                int id = cur[i];
                if ((slot_value_index[id] >> shift) & 1) {
                    nxt[oi++] = id;
                }
                else {
                    nxt[zi] = id;
                    if (active[id]) {
                        zero_count_fenwick[start + zi + 1] = 1;
                        zero_sum_fenwick[start + zi + 1] = active_weight[id];
                    }
                    ++zi;
                }
            }
            fenwick_build(zero_count_fenwick, start, mid[d]);
            fenwick_build(zero_sum_fenwick, start, mid[d]);
            cur.swap(nxt);
        }

        leaf_count_fenwick.assign(slot_count + 1, 0);
        leaf_sum_fenwick.assign(slot_count + 1, U());
        for (int i = 0; i < slot_count; ++i) {
            int id = cur[i];
            if (active[id]) {
                leaf_count_fenwick[i + 1] = 1;
                leaf_sum_fenwick[i + 1] = active_weight[id];
            }
        }
        fenwick_build(leaf_count_fenwick, 0, slot_count);
        fenwick_build(leaf_sum_fenwick, 0, slot_count);

        base_sum_fenwick.assign(slot_count + 1, U());
        for (int i = 0; i < n; ++i) base_sum_fenwick[current_slot[i] + 1] = w[i];
        fenwick_build(base_sum_fenwick, 0, slot_count);

        value_candidates.clear();
        value_candidates.shrink_to_fit();
        built = true;
    }

    void add_slot(int slot, int count_delta, const U &sum_delta) {
        fenwick_add(base_sum_fenwick, 0, slot_count, slot, sum_delta);
        int p = slot;
        int xi = slot_value_index[slot];
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int p1 = rank1(d, p);
            if ((xi >> shift) & 1) {
                p = mid[d] + p1;
            }
            else {
                p -= p1;
                if (count_delta != 0) {
                    fenwick_add(zero_count_fenwick, row_offset[d], mid[d], p, count_delta);
                }
                fenwick_add(zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);
            }
        }
        if (count_delta != 0) {
            fenwick_add(leaf_count_fenwick, 0, slot_count, p, count_delta);
        }
        fenwick_add(leaf_sum_fenwick, 0, slot_count, p, sum_delta);
    }

    bool set_value(int k, const T &x) {
        assert(built && 0 <= k && k < n);
        int next_slot = find_slot(k, x);
        if (next_slot == -1) return false;
        int old_slot = current_slot[k];
        if (old_slot == next_slot) return true;
        add_slot(old_slot, -1, U() - weights[k]);
        add_slot(next_slot, 1, weights[k]);
        current_slot[k] = next_slot;
        return true;
    }

    void set_weight(int k, const U &w) {
        assert(built && 0 <= k && k < n);
        U delta = w - weights[k];
        add_slot(current_slot[k], 0, delta);
        weights[k] = w;
    }

    void add_weight(int k, const U &delta) {
        assert(built && 0 <= k && k < n);
        add_slot(current_slot[k], 0, delta);
        weights[k] += delta;
    }

    bool set(int k, const T &x, const U &w) {
        assert(built && 0 <= k && k < n);
        int next_slot = find_slot(k, x);
        if (next_slot == -1) return false;
        int old_slot = current_slot[k];
        if (old_slot == next_slot) {
            set_weight(k, w);
            return true;
        }
        add_slot(old_slot, -1, U() - weights[k]);
        add_slot(next_slot, 1, w);
        current_slot[k] = next_slot;
        weights[k] = w;
        return true;
    }

    const T &get_value(int k) const {
        assert(built && 0 <= k && k < n);
        return slot_values[current_slot[k]];
    }

    const U &get_weight(int k) const {
        assert(built && 0 <= k && k < n);
        return weights[k];
    }

    template <bool need_count, bool need_sum>
    CountSum count_sum_less_index_internal(int l, int r, int xi) const {
        assert(built && 0 <= l && l <= r && r <= n);
        if (xi <= 0 || l >= r || n == 0) return {0, U()};
        if (xi >= (int)vals.size()) {
            U sum = U();
            if constexpr (need_sum) {
                sum = fenwick_range(base_sum_fenwick, 0, offset[l], offset[r]);
            }
            return {need_count ? r - l : 0, sum};
        }

        l = offset[l];
        r = offset[r];
        CountSum res{0, U()};
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            if ((xi >> shift) & 1) {
                if constexpr (need_count) {
                    res.count += fenwick_range(zero_count_fenwick, row_offset[d], l0, r0);
                }
                if constexpr (need_sum) {
                    res.sum += fenwick_range(zero_sum_fenwick, row_offset[d], l0, r0);
                }
                l = mid[d] + l1;
                r = mid[d] + r1;
            }
            else {
                l = l0;
                r = r0;
            }
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return res;
    }

    CountSum count_sum_less_index(int l, int r, int xi) const {
        return count_sum_less_index_internal<true, true>(l, r, xi);
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
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_sum_less_index_internal<true, false>(l, r, xi).count;
    }

    int count_less_equal(int l, int r, const T &x) const {
        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_sum_less_index_internal<true, false>(l, r, xi).count;
    }

    U sum_less(int l, int r, const T &x) const {
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_sum_less_index_internal<false, true>(l, r, xi).sum;
    }

    U sum_less_equal(int l, int r, const T &x) const {
        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_sum_less_index_internal<false, true>(l, r, xi).sum;
    }

    template <bool need_count, bool need_sum>
    CountSum count_sum_equal_internal(int l, int r, int xi) const {
        assert(built && 0 <= l && l <= r && r <= n);
        if (l >= r || xi < 0 || xi >= (int)vals.size()) return {0, U()};
        l = offset[l];
        r = offset[r];
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            if ((xi >> shift) & 1) {
                l = mid[d] + l1;
                r = mid[d] + r1;
            }
            else {
                l -= l1;
                r -= r1;
            }
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        int count = 0;
        U sum = U();
        if constexpr (need_count) count = fenwick_range(leaf_count_fenwick, 0, l, r);
        if constexpr (need_sum) sum = fenwick_range(leaf_sum_fenwick, 0, l, r);
        return {count, sum};
    }

    CountSum count_sum_equal(int l, int r, const T &x) const {
        assert(built);
        auto it = lower_bound(vals.begin(), vals.end(), x);
        if (it == vals.end() || !equivalent(*it, x)) return {0, U()};
        return count_sum_equal_internal<true, true>(l, r, (int)(it - vals.begin()));
    }

    int freq(int l, int r, const T &x) const {
        assert(built);
        auto it = lower_bound(vals.begin(), vals.end(), x);
        if (it == vals.end() || !equivalent(*it, x)) return 0;
        return count_sum_equal_internal<true, false>(l, r, (int)(it - vals.begin())).count;
    }

    U sum_equal(int l, int r, const T &x) const {
        assert(built);
        auto it = lower_bound(vals.begin(), vals.end(), x);
        if (it == vals.end() || !equivalent(*it, x)) return U();
        return count_sum_equal_internal<false, true>(l, r, (int)(it - vals.begin())).sum;
    }

    CountSum range_count_sum(int l, int r, const T &lower, const T &upper) const {
        CountSum hi = count_sum_less(l, r, upper);
        CountSum lo = count_sum_less(l, r, lower);
        return {hi.count - lo.count, hi.sum - lo.sum};
    }

    int range_freq(int l, int r, const T &lower, const T &upper) const {
        return count_less(l, r, upper) - count_less(l, r, lower);
    }

    U range_sum(int l, int r, const T &lower, const T &upper) const {
        return sum_less(l, r, upper) - sum_less(l, r, lower);
    }
};

/**
 * @brief 動的重み付きWavelet Matrix(Dynamic Weighted Wavelet Matrix)
 */
