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

    vector<T> fa(n * w), fb(n * w), fc(n * w);
    for (int s = 0; s < n; ++s) {
        int base = s * w;
        fa[base + pc[s]] = a[s];
        fb[base + pc[s]] = b[s];
    }

    for (int i = 0; i < lg; ++i) {
        for (int s = 0; s < n; ++s) {
            if (((s >> i) & 1) == 0) {
                int t = s | (1 << i);
                int sb = s * w, tb = t * w;
                for (int k = 0; k <= pc[s]; ++k) {
                    fa[tb + k] += fa[sb + k];
                    fb[tb + k] += fb[sb + k];
                }
            }
        }
    }
    for (int s = 0; s < n; ++s) {
        int base = s * w;
        int lim = min(lg, pc[s] * 2);
        for (int k = 0; k <= lim; ++k) {
            for (int i = 0; i <= k; ++i) {
                if (i <= pc[s] && k - i <= pc[s]) {
                    fc[base + k] += fa[base + i] * fb[base + k - i];
                }
            }
        }
    }
    for (int i = 0; i < lg; ++i) {
        for (int s = 0; s < n; ++s) {
            if (((s >> i) & 1) == 0) {
                int t = s | (1 << i);
                int sb = s * w, tb = t * w;
                int lim = min(lg, pc[s] * 2);
                for (int k = 0; k <= lim; ++k) {
                    fc[tb + k] -= fc[sb + k];
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
