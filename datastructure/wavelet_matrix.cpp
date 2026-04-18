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
        bit.assign(lg * blocks, 0);
        pref.assign(lg * (blocks + 1), 0);
        vector<int> nxt(n);

        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {
            auto *row = bit.data() + d * blocks;
            auto *row_pref = pref.data() + d * (blocks + 1);
            int zero_cnt = 0;
            for (int i = 0; i < n; ++i) {
                int x = cur[i];
                int b = (x >> shift) & 1;
                if (b) row[i >> 6] |= 1ULL << (i & 63);
                else ++zero_cnt;
            }
            mid[d] = zero_cnt;
            for (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);

            int zi = 0, oi = zero_cnt;
            for (int i = 0; i < n; ++i) {
                int x = cur[i];
                if ((x >> shift) & 1) nxt[oi++] = x;
                else nxt[zi++] = x;
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

    int count_less_index(int l, int r, int xi) const {
        if (xi <= 0 || l >= r || n == 0) return 0;
        if (xi >= (int)vals.size()) return r - l;

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
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return res;
    }

    int count_less(int l, int r, const T &x) const {
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_less_index(l, r, xi);
    }

    int count_equal_index(int l, int r, int xi) const {
        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size()) return 0;

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
            bit_data += blocks;
            pref_data += blocks + 1;
        }
        return r - l;
    }

    vector<pair<int, int>> top_k_freq_index(int l, int r, int k) const {
        if (k <= 0 || l >= r || n == 0) return {};

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
            rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);
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
        return vals[idx];
    }

    T kth_largest(int l, int r, int k) const {
        return kth_smallest(l, r, r - l - 1 - k);
    }

    bool prev_value(int l, int r, const T &upper, T &res) const {
        int cnt = count_less(l, r, upper);
        if (cnt == 0) return false;
        res = kth_smallest(l, r, cnt - 1);
        return true;
    }

    bool next_value(int l, int r, const T &lower, T &res) const {
        int cnt = count_less(l, r, lower);
        if (cnt == r - l) return false;
        res = kth_smallest(l, r, cnt);
        return true;
    }
};

/**
 * @brief Wavelet Matrix
 */
