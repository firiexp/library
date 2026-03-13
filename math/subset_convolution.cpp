template<class T>
vector<T> subset_convolution(vector<T> a, vector<T> b){
    int n = 1;
    while (n < (int)a.size() || n < (int)b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);
    int lg = 0;
    while ((1 << lg) < n) ++lg;
    int w = lg + 1;
    vector<int> pc(n);
    for (int s = 1; s < n; ++s) pc[s] = pc[s >> 1] + (s & 1);
    vector<int> lim2(w);
    for (int k = 0; k < w; ++k) lim2[k] = min(lg, k << 1);

    vector<T> fa(n * w), fb(n * w), fc(n * w);
    for (int s = 0; s < n; ++s) {
        int base = s * w;
        fa[base + pc[s]] = a[s];
        fb[base + pc[s]] = b[s];
    }

    for (int i = 0; i < lg; ++i) {
        int step = 1 << i;
        int span = step << 1;
        for (int block = 0; block < n; block += span) {
            for (int j = 0; j < step; ++j) {
                int s = block + j;
                int t = s + step;
                T *as = fa.data() + s * w;
                T *at = fa.data() + t * w;
                T *bs = fb.data() + s * w;
                T *bt = fb.data() + t * w;
                for (int k = 0, lim = pc[s]; k <= lim; ++k) {
                    at[k] += as[k];
                    bt[k] += bs[k];
                }
            }
        }
    }
    for (int s = 0; s < n; ++s) {
        const T *as = fa.data() + s * w;
        const T *bs = fb.data() + s * w;
        T *cs = fc.data() + s * w;
        int p = pc[s];
        int lim = lim2[p];
        for (int k = 0; k <= lim; ++k) {
            int l = max(0, k - p);
            int r = min(k, p);
            T sum = 0;
            for (int i = l; i <= r; ++i) {
                sum += as[i] * bs[k - i];
            }
            cs[k] = sum;
        }
    }
    for (int i = 0; i < lg; ++i) {
        int step = 1 << i;
        int span = step << 1;
        for (int block = 0; block < n; block += span) {
            for (int j = 0; j < step; ++j) {
                int s = block + j;
                int t = s + step;
                T *cs = fc.data() + s * w;
                T *ct = fc.data() + t * w;
                for (int k = 0, lim = lim2[pc[s]]; k <= lim; ++k) {
                    ct[k] -= cs[k];
                }
            }
        }
    }

    vector<T> c(n);
    for (int s = 0; s < n; ++s) {
        c[s] = fc[s * w + pc[s]];
    }
    return c;
}

/**
 * @brief 部分集合畳み込み(Subset Convolution)
 */
