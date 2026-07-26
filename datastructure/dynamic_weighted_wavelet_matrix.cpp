template <class T, class U>
struct DynamicWeightedWaveletMatrix {
    struct CountSum {
        int count;
        U sum;
    };

    static constexpr bool use_fast_value_search =
            is_integral<T>::value && !is_same<T, bool>::value &&
            sizeof(T) <= 8;

    class Cursor {
        friend struct DynamicWeightedWaveletMatrix;

        const DynamicWeightedWaveletMatrix *owner_;
        int depth_, l_, r_, value_index_;
        CountSum all_;

        Cursor(const DynamicWeightedWaveletMatrix *owner, int depth,
               int l, int r, int value_index, CountSum all)
            : owner_(owner), depth_(depth), l_(l), r_(r),
              value_index_(value_index), all_(all) {}

    public:
        bool is_leaf() const {
            return depth_ == owner_->lg;
        }

        bool empty() const {
            return all_.count == 0;
        }

        int count() const {
            return all_.count;
        }

        const U &sum() const {
            return all_.sum;
        }

        const CountSum &info() const {
            return all_;
        }

        const T &value() const {
            assert(is_leaf() && !empty());
            assert(0 <= value_index_ && value_index_ < (int)owner_->vals.size());
            return owner_->vals[value_index_];
        }
    };

    struct Children {
        Cursor low;
        Cursor high;
    };

    int n, lg, blocks, slot_count;
    bool initialized, built;
    bool fixed_values;
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
    vector<int> update_offset;
    vector<int> update_position;
    vector<int> leaf_position;
    vector<U> weights;
    vector<T> vals;
    vector<T> value_search_tree;
    vector<int> value_search_rank;
    vector<T> slot_values;
    vector<pair<int, T>> value_candidates;

    DynamicWeightedWaveletMatrix()
        : n(0), lg(0), blocks(0), slot_count(0), initialized(false), built(false),
          fixed_values(false) {}

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
        fixed_values = false;
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
        update_offset.clear();
        update_position.clear();
        leaf_position.clear();
        weights.clear();
        vals.clear();
        value_search_tree.clear();
        value_search_rank.clear();
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

    int lower_bound_value(const T &x) const {
        if constexpr (use_fast_value_search) {
            unsigned k = 1;
            unsigned size = (unsigned)vals.size();
            constexpr unsigned prefetch_scale = sizeof(T) <= 4 ? 16 : 8;
            while (k <= size) {
                if (k <= size / prefetch_scale) {
                    __builtin_prefetch(
                            value_search_tree.data() + k * prefetch_scale);
                }
                k = (k << 1) + (value_search_tree[k] < x);
            }
            unsigned inverted = ~k;
            if (inverted == 0) return (int)size;
            k >>= __builtin_ctz(inverted) + 1;
            return k == 0 ? (int)size : value_search_rank[k];
        }
        return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    }

    int upper_bound_value(const T &x) const {
        if constexpr (use_fast_value_search) {
            unsigned k = 1;
            unsigned size = (unsigned)vals.size();
            constexpr unsigned prefetch_scale = sizeof(T) <= 4 ? 16 : 8;
            while (k <= size) {
                if (k <= size / prefetch_scale) {
                    __builtin_prefetch(
                            value_search_tree.data() + k * prefetch_scale);
                }
                k = (k << 1) + !(x < value_search_tree[k]);
            }
            unsigned inverted = ~k;
            if (inverted == 0) return (int)size;
            k >>= __builtin_ctz(inverted) + 1;
            return k == 0 ? (int)size : value_search_rank[k];
        }
        return (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
    }

    void build_value_search_tree() {
        if constexpr (use_fast_value_search) {
            int size = (int)vals.size();
            value_search_tree.resize(size + 1);
            value_search_rank.resize(size + 1);
            int rank = 0;
            auto visit = [&](auto &&self, unsigned k) -> void {
                if (k > (unsigned)size) return;
                self(self, k << 1);
                value_search_tree[k] = vals[rank];
                value_search_rank[k] = rank++;
                self(self, k << 1 | 1);
            };
            visit(visit, 1);
        }
    }

    template <class X>
    static auto encode_key(X x) -> typename make_unsigned<X>::type {
        using Key = typename make_unsigned<X>::type;
        Key key = static_cast<Key>(x);
        if constexpr (is_signed<X>::value) {
            key ^= Key(1) << (sizeof(X) * 8 - 1);
        }
        return key;
    }

    static inline int popcount(unsigned long long x) {
#if defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt")) {
            unsigned long long result;
            __asm__("popcnt{q %1, %0| %0, %1}"
                    : "=r"(result) : "r"(x) : "cc");
            return (int)result;
        }
#endif
        return __builtin_popcountll(x);
    }

    static inline void popcount_pair(unsigned long long x,
                                     unsigned long long y,
                                     int &x_count, int &y_count) {
#if defined(__x86_64__)
        if (__builtin_cpu_supports("popcnt")) {
            unsigned long long x_result, y_result;
            __asm__("popcnt{q %1, %0| %0, %1}"
                    : "=r"(x_result) : "r"(x) : "cc");
            __asm__("popcnt{q %1, %0| %0, %1}"
                    : "=r"(y_result) : "r"(y) : "cc");
            x_count = (int)x_result;
            y_count = (int)y_result;
            return;
        }
#endif
        x_count = __builtin_popcountll(x);
        y_count = __builtin_popcountll(y);
    }

    static inline void rank1_pair(const unsigned long long *row,
                                  const int *row_pref,
                                  int l, int r, int &l1, int &r1) {
        int l_block = l >> 6;
        l1 = row_pref[l_block];
        int l_rem = l & 63;
        int r_block = r >> 6;
        r1 = row_pref[r_block];
        int r_rem = r & 63;
        if (l_rem && r_rem) {
            int l_count, r_count;
            popcount_pair(
                    row[l_block] & ((1ULL << l_rem) - 1),
                    row[r_block] & ((1ULL << r_rem) - 1),
                    l_count, r_count);
            l1 += l_count;
            r1 += r_count;
            return;
        }
        if (l_rem) l1 += popcount(row[l_block] & ((1ULL << l_rem) - 1));
        if (r_rem) r1 += popcount(row[r_block] & ((1ULL << r_rem) - 1));
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

    static CountSum fenwick_range_count_sum(
            const vector<int> &count_fw, const vector<U> &sum_fw,
            int start, int l, int r) {
        CountSum res{0, U()};
        for (; r > 0; r -= r & -r) {
            res.count += count_fw[start + r];
            res.sum += sum_fw[start + r];
        }
        for (; l > 0; l -= l & -l) {
            res.count -= count_fw[start + l];
            res.sum -= sum_fw[start + l];
        }
        return res;
    }

    static void fenwick_add_count_sum(
            vector<int> &count_fw, vector<U> &sum_fw,
            int start, int length, int k, int count_delta, const U &sum_delta) {
        for (++k; k <= length; k += k & -k) {
            count_fw[start + k] += count_delta;
            sum_fw[start + k] += sum_delta;
        }
    }

    static int fenwick_lower_bound(const vector<int> &fw, int start, int length, int target) {
        assert(target > 0);
        int k = 0;
        int step = 1;
        while ((step << 1) <= length) step <<= 1;
        for (; step > 0; step >>= 1) {
            int next = k + step;
            if (next <= length && fw[start + next] < target) {
                k = next;
                target -= fw[start + next];
            }
        }
        return k + 1;
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

        vector<int> raw_offset(n + 1, 0);
        for (const auto &[k, x] : value_candidates) {
            (void)x;
            ++raw_offset[k + 1];
        }
        for (int i = 0; i < n; ++i) ++raw_offset[i + 1];
        for (int i = 0; i < n; ++i) raw_offset[i + 1] += raw_offset[i];

        vector<T> raw_values(raw_offset[n]);
        vector<int> write_position = raw_offset;
        for (const auto &[k, x] : value_candidates) {
            raw_values[write_position[k]++] = x;
        }
        for (int i = 0; i < n; ++i) {
            raw_values[write_position[i]++] = v[i];
        }

        offset.assign(n + 1, 0);
        slot_values.clear();
        slot_values.reserve(raw_values.size());
        for (int k = 0; k < n; ++k) {
            auto first = raw_values.begin() + raw_offset[k];
            auto last = raw_values.begin() + raw_offset[k + 1];
            sort(first, last);
            for (auto it = first; it != last; ++it) {
                if ((int)slot_values.size() == offset[k] ||
                    !equivalent(slot_values.back(), *it)) {
                    slot_values.push_back(move(*it));
                }
            }
            offset[k + 1] = (int)slot_values.size();
        }
        slot_count = (int)slot_values.size();

        slot_value_index.resize(slot_count);
        if constexpr (is_integral<T>::value && !is_same<T, bool>::value &&
                      sizeof(T) <= 8) {
            using Key = typename make_unsigned<T>::type;
            vector<Key> keys(slot_count);
            vector<int> ord(slot_count), buf(slot_count);
            for (int i = 0; i < slot_count; ++i) {
                keys[i] = encode_key(slot_values[i]);
                ord[i] = i;
            }

            constexpr int radix_bits = 16;
            constexpr int bucket_count = 1 << radix_bits;
            constexpr int mask = bucket_count - 1;
            int passes = (int)(sizeof(Key) * 8 + radix_bits - 1) / radix_bits;
            vector<int> count(bucket_count), position(bucket_count);
            for (int pass = 0; pass < passes; ++pass) {
                fill(count.begin(), count.end(), 0);
                int shift = pass * radix_bits;
                for (int id : ord) ++count[(keys[id] >> shift) & mask];
                position[0] = 0;
                for (int i = 0; i + 1 < bucket_count; ++i) {
                    position[i + 1] = position[i] + count[i];
                }
                for (int id : ord) {
                    buf[position[(keys[id] >> shift) & mask]++] = id;
                }
                ord.swap(buf);
            }

            vals.clear();
            vals.reserve(slot_count);
            bool has_previous = false;
            Key previous = 0;
            for (int id : ord) {
                if (!has_previous || keys[id] != previous) {
                    vals.push_back(slot_values[id]);
                    previous = keys[id];
                    has_previous = true;
                }
                slot_value_index[id] = (int)vals.size() - 1;
            }
        }
        else {
            vals = slot_values;
            sort(vals.begin(), vals.end());
            int value_count = 0;
            for (int i = 0; i < (int)vals.size(); ++i) {
                if (value_count == 0 ||
                    !equivalent(vals[value_count - 1], vals[i])) {
                    if (value_count != i) vals[value_count] = move(vals[i]);
                    ++value_count;
                }
            }
            vals.resize(value_count);
            for (int i = 0; i < slot_count; ++i) {
                slot_value_index[i] = (int)(lower_bound(
                        vals.begin(), vals.end(), slot_values[i]) - vals.begin());
            }
        }
        build_value_search_tree();
        fixed_values = slot_count == n;
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
            update_offset.clear();
            update_position.clear();
            leaf_position.clear();
            value_candidates.clear();
            value_candidates.shrink_to_fit();
            built = true;
            return;
        }

        lg = 0;
        while ((1LL << lg) < (int)vals.size()) ++lg;
        if (lg == 0) lg = 1;
        blocks = (slot_count + 63) >> 6;

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
                row_pref[i + 1] = row_pref[i] + popcount(row[i]);
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
        if (fixed_values) zero_count_fenwick.clear();
        else zero_count_fenwick.assign(fenwick_size, 0);
        zero_sum_fenwick.assign(fenwick_size, U());
        update_offset.resize(slot_count + 1);
        for (int i = 0; i < slot_count; ++i) {
            update_offset[i + 1] = update_offset[i] +
                    lg - __builtin_popcount((unsigned)slot_value_index[i]);
        }
        update_position.resize(update_offset.back());
        vector<int> update_next = update_offset;
        leaf_position.resize(slot_count);

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
                    update_position[update_next[id]++] = zi;
                    if (active[id]) {
                        if (!fixed_values) zero_count_fenwick[start + zi + 1] = 1;
                        zero_sum_fenwick[start + zi + 1] = active_weight[id];
                    }
                    ++zi;
                }
            }
            if (!fixed_values) fenwick_build(zero_count_fenwick, start, mid[d]);
            fenwick_build(zero_sum_fenwick, start, mid[d]);
            cur.swap(nxt);
        }

        if (fixed_values) leaf_count_fenwick.clear();
        else leaf_count_fenwick.assign(slot_count + 1, 0);
        leaf_sum_fenwick.assign(slot_count + 1, U());
        for (int i = 0; i < slot_count; ++i) {
            int id = cur[i];
            leaf_position[id] = i;
            if (active[id]) {
                if (!fixed_values) leaf_count_fenwick[i + 1] = 1;
                leaf_sum_fenwick[i + 1] = active_weight[id];
            }
        }
        if (!fixed_values) fenwick_build(leaf_count_fenwick, 0, slot_count);
        fenwick_build(leaf_sum_fenwick, 0, slot_count);

        base_sum_fenwick.assign(n + 1, U());
        for (int i = 0; i < n; ++i) base_sum_fenwick[i + 1] = w[i];
        fenwick_build(base_sum_fenwick, 0, n);

        value_candidates.clear();
        value_candidates.shrink_to_fit();
        built = true;
    }

    void add_slot(int slot, int count_delta, const U &sum_delta) {
        const int *positions = update_position.data() + update_offset[slot];
        int xi = slot_value_index[slot];
        unsigned zero_mask = (~(unsigned)xi) & ((1U << lg) - 1);
        while (zero_mask) {
            int shift = 31 - __builtin_clz(zero_mask);
            int d = lg - 1 - shift;
            int p = *positions++;
            if (count_delta != 0) {
                fenwick_add_count_sum(
                        zero_count_fenwick, zero_sum_fenwick,
                        row_offset[d], mid[d], p, count_delta, sum_delta);
            }
            else {
                fenwick_add(
                        zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);
            }
            zero_mask ^= 1U << shift;
        }
        int p = leaf_position[slot];
        if (count_delta != 0) {
            fenwick_add_count_sum(
                    leaf_count_fenwick, leaf_sum_fenwick,
                    0, slot_count, p, count_delta, sum_delta);
        }
        else {
            fenwick_add(leaf_sum_fenwick, 0, slot_count, p, sum_delta);
        }
    }

    void add_slot_sum(int slot, const U &sum_delta) {
        const int *positions = update_position.data() + update_offset[slot];
        int xi = slot_value_index[slot];
        unsigned zero_mask = (~(unsigned)xi) & ((1U << lg) - 1);
        while (zero_mask) {
            int shift = 31 - __builtin_clz(zero_mask);
            int d = lg - 1 - shift;
            int p = *positions++;
            fenwick_add(
                    zero_sum_fenwick, row_offset[d], mid[d], p, sum_delta);
            zero_mask ^= 1U << shift;
        }
        int p = leaf_position[slot];
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
        fenwick_add(base_sum_fenwick, 0, n, k, delta);
        add_slot_sum(current_slot[k], delta);
        weights[k] = w;
    }

    void add_weight(int k, const U &delta) {
        assert(built && 0 <= k && k < n);
        fenwick_add(base_sum_fenwick, 0, n, k, delta);
        add_slot_sum(current_slot[k], delta);
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
        fenwick_add(base_sum_fenwick, 0, n, k, w - weights[k]);
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
                sum = fenwick_range(base_sum_fenwick, 0, l, r);
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
                if (fixed_values) {
                    if constexpr (need_count) res.count += r0 - l0;
                    if constexpr (need_sum) {
                        res.sum += fenwick_range(
                                zero_sum_fenwick, row_offset[d], l0, r0);
                    }
                }
                else {
                    if constexpr (need_count && need_sum) {
                        CountSum part = fenwick_range_count_sum(
                                zero_count_fenwick, zero_sum_fenwick,
                                row_offset[d], l0, r0);
                        res.count += part.count;
                        res.sum += part.sum;
                    }
                    else {
                        if constexpr (need_count) {
                            res.count += fenwick_range(
                                    zero_count_fenwick, row_offset[d], l0, r0);
                        }
                        if constexpr (need_sum) {
                            res.sum += fenwick_range(
                                    zero_sum_fenwick, row_offset[d], l0, r0);
                        }
                    }
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
        return count_sum_less_index(l, r, lower_bound_value(x));
    }

    CountSum count_sum_less_equal(int l, int r, const T &x) const {
        return count_sum_less_index(l, r, upper_bound_value(x));
    }

    int count_less(int l, int r, const T &x) const {
        return count_sum_less_index_internal<true, false>(
                l, r, lower_bound_value(x)).count;
    }

    int count_less_equal(int l, int r, const T &x) const {
        return count_sum_less_index_internal<true, false>(
                l, r, upper_bound_value(x)).count;
    }

    U sum_less(int l, int r, const T &x) const {
        return count_sum_less_index_internal<false, true>(
                l, r, lower_bound_value(x)).sum;
    }

    U sum_less_equal(int l, int r, const T &x) const {
        return count_sum_less_index_internal<false, true>(
                l, r, upper_bound_value(x)).sum;
    }

    pair<U, U> sum_less_index_pair(int l, int r, int first_xi, int second_xi) const {
        assert(built && 0 <= l && l <= r && r <= n);
        if (l >= r) return {U(), U()};
        int value_count = (int)vals.size();
        if (first_xi <= 0 || first_xi >= value_count ||
            second_xi <= 0 || second_xi >= value_count) {
            return {
                    count_sum_less_index_internal<false, true>(l, r, first_xi).sum,
                    count_sum_less_index_internal<false, true>(l, r, second_xi).sum
            };
        }

        int first_l = offset[l], first_r = offset[r];
        int second_l = first_l, second_r = first_r;
        U first_sum = U(), second_sum = U();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            int first_l1, first_r1;
            rank1_pair(bit_data, pref_data, first_l, first_r, first_l1, first_r1);
            int first_l0 = first_l - first_l1;
            int first_r0 = first_r - first_r1;
            if ((first_xi >> shift) & 1) {
                first_sum += fenwick_range(
                        zero_sum_fenwick, row_offset[d], first_l0, first_r0);
                first_l = mid[d] + first_l1;
                first_r = mid[d] + first_r1;
            }
            else {
                first_l = first_l0;
                first_r = first_r0;
            }

            int second_l1, second_r1;
            rank1_pair(bit_data, pref_data, second_l, second_r, second_l1, second_r1);
            int second_l0 = second_l - second_l1;
            int second_r0 = second_r - second_r1;
            if ((second_xi >> shift) & 1) {
                second_sum += fenwick_range(
                        zero_sum_fenwick, row_offset[d], second_l0, second_r0);
                second_l = mid[d] + second_l1;
                second_r = mid[d] + second_r1;
            }
            else {
                second_l = second_l0;
                second_r = second_r0;
            }

            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return {first_sum, second_sum};
    }

    Cursor range_cursor(int l, int r) const {
        assert(built && 0 <= l && l <= r && r <= n);
        return Cursor(this, 0, offset[l], offset[r], 0,
                      {r - l, fenwick_range(base_sum_fenwick, 0, l, r)});
    }

    Children split(const Cursor &cur) const {
        assert(cur.owner_ == this);
        assert(!cur.is_leaf());

        const auto *row = bit.data() + cur.depth_ * blocks;
        const int *row_pref = pref.data() + cur.depth_ * (blocks + 1);
        int l1, r1;
        rank1_pair(row, row_pref, cur.l_, cur.r_, l1, r1);
        int l0 = cur.l_ - l1;
        int r0 = cur.r_ - r1;

        CountSum low;
        if (fixed_values) {
            low = {
                    r0 - l0,
                    fenwick_range(
                            zero_sum_fenwick, row_offset[cur.depth_], l0, r0)
            };
        }
        else {
            low = fenwick_range_count_sum(
                    zero_count_fenwick, zero_sum_fenwick,
                    row_offset[cur.depth_], l0, r0);
        }
        CountSum high{
                cur.all_.count - low.count,
                cur.all_.sum - low.sum
        };

        int next_depth = cur.depth_ + 1;
        int prefix = cur.value_index_ << 1;
        return {
                Cursor(this, next_depth, l0, r0, prefix, low),
                Cursor(this, next_depth,
                       mid[cur.depth_] + l1, mid[cur.depth_] + r1,
                       prefix | 1, high)
        };
    }

    U sum_k_smallest(int l, int r, int k) const {
        assert(built && 0 <= l && l <= r && r <= n);
        assert(0 <= k && k <= r - l);
        if (k == 0) return U();
        if (k == r - l) {
            return fenwick_range(base_sum_fenwick, 0, l, r);
        }

        l = offset[l];
        r = offset[r];
        U res = U();
        const auto *bit_data = bit.data();
        const int *pref_data = pref.data();
        for (int d = 0; d < lg; ++d) {
            int l1, r1;
            rank1_pair(bit_data, pref_data, l, r, l1, r1);
            int l0 = l - l1, r0 = r - r1;
            int zero_count = fixed_values ? r0 - l0 :
                    fenwick_range(zero_count_fenwick, row_offset[d], l0, r0);
            if (k < zero_count) {
                l = l0;
                r = r0;
            }
            else {
                res += fenwick_range(zero_sum_fenwick, row_offset[d], l0, r0);
                k -= zero_count;
                if (k == 0) return res;
                l = mid[d] + l1;
                r = mid[d] + r1;
            }
            bit_data += blocks;
            pref_data += blocks + 1;
        }

        if (fixed_values) {
            return res + fenwick_range(leaf_sum_fenwick, 0, l, l + k);
        }
        int before = fenwick_prefix(leaf_count_fenwick, 0, l);
        int end = fenwick_lower_bound(
                leaf_count_fenwick, 0, slot_count, before + k);
        return res + fenwick_range(leaf_sum_fenwick, 0, l, end);
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
        if (fixed_values) {
            if constexpr (need_count) count = r - l;
            if constexpr (need_sum) {
                sum = fenwick_range(leaf_sum_fenwick, 0, l, r);
            }
            return {count, sum};
        }
        if constexpr (need_count && need_sum) {
            return fenwick_range_count_sum(
                    leaf_count_fenwick, leaf_sum_fenwick, 0, l, r);
        }
        if constexpr (need_count) count = fenwick_range(leaf_count_fenwick, 0, l, r);
        if constexpr (need_sum) sum = fenwick_range(leaf_sum_fenwick, 0, l, r);
        return {count, sum};
    }

    CountSum count_sum_equal(int l, int r, const T &x) const {
        assert(built);
        int xi = lower_bound_value(x);
        if (xi == (int)vals.size() || !equivalent(vals[xi], x)) return {0, U()};
        return count_sum_equal_internal<true, true>(l, r, xi);
    }

    int freq(int l, int r, const T &x) const {
        assert(built);
        int xi = lower_bound_value(x);
        if (xi == (int)vals.size() || !equivalent(vals[xi], x)) return 0;
        return count_sum_equal_internal<true, false>(l, r, xi).count;
    }

    U sum_equal(int l, int r, const T &x) const {
        assert(built);
        int xi = lower_bound_value(x);
        if (xi == (int)vals.size() || !equivalent(vals[xi], x)) return U();
        return count_sum_equal_internal<false, true>(l, r, xi).sum;
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
        int lower_xi = lower_bound_value(lower);
        int upper_xi = lower_bound_value(upper);
        auto sums = sum_less_index_pair(l, r, lower_xi, upper_xi);
        return sums.second - sums.first;
    }
};

/**
 * @brief 動的重み付きWavelet Matrix(Dynamic Weighted Wavelet Matrix)
 */
