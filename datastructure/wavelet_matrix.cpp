template <class T>
struct WaveletMatrix {
    int n, lg;
    vector<int> mid;
    vector<vector<int>> bit;
    vector<T> vals;

    WaveletMatrix() : n(0), lg(0) {}
    explicit WaveletMatrix(const vector<T> &v) { build(v); }

    void build(const vector<T> &v) {
        n = (int)v.size();
        vals = v;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        if (vals.empty()) {
            lg = 0;
            mid.clear();
            bit.clear();
            return;
        }

        int m = (int)vals.size();
        lg = 0;
        while ((1 << lg) < m) lg++;
        if (lg == 0) lg = 1;

        vector<int> cur(n);
        for (int i = 0; i < n; ++i) {
            cur[i] = (int)(lower_bound(vals.begin(), vals.end(), v[i]) - vals.begin());
        }

        mid.assign(lg, 0);
        bit.assign(lg, vector<int>(n + 1, 0));

        for (int d = 0; d < lg; ++d) {
            int shift = lg - 1 - d;
            vector<int> zero, one;
            zero.reserve(n);
            one.reserve(n);
            for (int i = 0; i < n; ++i) {
                int b = (cur[i] >> shift) & 1;
                bit[d][i + 1] = bit[d][i] + b;
                if (b) one.push_back(cur[i]);
                else zero.push_back(cur[i]);
            }
            mid[d] = (int)zero.size();
            cur.clear();
            cur.insert(cur.end(), zero.begin(), zero.end());
            cur.insert(cur.end(), one.begin(), one.end());
        }
    }

    int rank0(int d, int r) const {
        return r - bit[d][r];
    }

    int rank1(int d, int r) const {
        return bit[d][r];
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
