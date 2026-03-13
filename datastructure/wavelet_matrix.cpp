template <class T>
struct WaveletMatrix {
    int n, lg, blocks;
    vector<int> mid;
    vector<unsigned long long> bit;
    vector<int> pref;
    vector<T> vals;

    WaveletMatrix() : n(0), lg(0), blocks(0) {}
    explicit WaveletMatrix(const vector<T> &v) { build(v); }

    void build(const vector<T> &v) {
        n = (int)v.size();
        vals = v;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        if (vals.empty()) {
            lg = 0;
            blocks = 0;
            mid.clear();
            bit.clear();
            pref.clear();
            return;
        }

        int m = (int)vals.size();
        lg = 0;
        while ((1 << lg) < m) lg++;
        if (lg == 0) lg = 1;
        blocks = (n + 63) >> 6;

        vector<int> cur(n);
        for (int i = 0; i < n; ++i) {
            cur[i] = (int)(lower_bound(vals.begin(), vals.end(), v[i]) - vals.begin());
        }

        mid.assign(lg, 0);
        bit.assign(lg * blocks, 0);
        pref.assign(lg * (blocks + 1), 0);
        vector<int> nxt(n);

        for (int d = 0; d < lg; ++d) {
            int shift = lg - 1 - d;
            auto *row = bit.data() + d * blocks;
            auto *row_pref = pref.data() + d * (blocks + 1);
            int zero_cnt = 0;
            for (int i = 0; i < n; ++i) {
                int b = (cur[i] >> shift) & 1;
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

    int rank1(int d, int r) const {
        int base = d * blocks;
        int pref_base = d * (blocks + 1);
        int block = r >> 6;
        int ret = pref[pref_base + block];
        int rem = r & 63;
        if (rem) ret += __builtin_popcountll(bit[base + block] & ((1ULL << rem) - 1));
        return ret;
    }

    int rank0(int d, int r) const {
        return r - rank1(d, r);
    }

    int count_less_index(int l, int r, int xi) const {
        if (xi <= 0 || l >= r || n == 0) return 0;
        if (xi >= (int)vals.size()) return r - l;

        int res = 0;
        for (int d = 0; d < lg; ++d) {
            int shift = lg - 1 - d;
            int b = (xi >> shift) & 1;
            int l0 = rank0(d, l), r0 = rank0(d, r);
            if (b) {
                res += r0 - l0;
                l = mid[d] + rank1(d, l);
                r = mid[d] + rank1(d, r);
            }
            else {
                l = l0;
                r = r0;
            }
        }
        return res;
    }

    int count_less(int l, int r, const T &x) const {
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_less_index(l, r, xi);
    }

    int range_freq(int l, int r, const T &lower, const T &upper) const {
        if (lower >= upper || l >= r) return 0;
        return count_less(l, r, upper) - count_less(l, r, lower);
    }

    int freq(int l, int r, const T &x) const {
        int li = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        int ri = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
        return count_less_index(l, r, ri) - count_less_index(l, r, li);
    }

    T kth_smallest(int l, int r, int k) const {
        int idx = 0;
        for (int d = 0; d < lg; ++d) {
            int l0 = rank0(d, l), r0 = rank0(d, r);
            int z = r0 - l0;
            idx <<= 1;
            if (k < z) {
                l = l0;
                r = r0;
            }
            else {
                k -= z;
                idx |= 1;
                l = mid[d] + rank1(d, l);
                r = mid[d] + rank1(d, r);
            }
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
