namespace subset_convolution_detail {
template<class T>
constexpr unsigned firiexp_canonical_modulus(const T *) { return 0; }
}

template<class T>
vector<T> subset_convolution(vector<T> a, vector<T> b){
    using subset_convolution_detail::firiexp_canonical_modulus;
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

    vector<T> fa(n * w), fb(n * w);
    for (int s = 0; s < n; ++s) {
        int base = s * w;
        fa[base + pc[s]] = a[s];
        fb[base + pc[s]] = b[s];
    }

    auto for_each_block = [&](auto visit) {
        for (int end = 2; end <= n; end += 2) {
            for (int step = 1; step < (end & -end); step *= 2) {
                visit(end - 2 * step, step);
            }
        }
    };
    for_each_block([&](int block, int step) {
        int lower = pc[block];
        for (int j = 0; j < step; ++j) {
            int s = block + j;
            int t = s + step;
            T *as = fa.data() + s * w;
            T *at = fa.data() + t * w;
            T *bs = fb.data() + s * w;
            T *bt = fb.data() + t * w;
            for (int k = lower, lim = pc[s]; k <= lim; ++k) {
                at[k] += as[k];
                bt[k] += bs[k];
            }
        }
    });
    for (int s = 0; s < n; ++s) {
        T *as = fa.data() + s * w;
        const T *bs = fb.data() + s * w;
        int p = pc[s];
        int lim = lim2[p];
        for (int k = lim; k >= p; --k) {
            int l = k - p, r = p;
            if constexpr (firiexp_canonical_modulus(static_cast<const T *>(nullptr)) == 998244353) {
                constexpr int batch = 18;
                unsigned long long sum = 0;
                int i = l;
                while (r - i + 1 > batch) {
                    for (int end = i + batch; i < end; ++i) {
                        sum += 1ULL * as[i].val * bs[k - i].val;
                    }
                    sum %= 998244353;
                }
                for (; i <= r; ++i) {
                    sum += 1ULL * as[i].val * bs[k - i].val;
                }
                as[k] = T::raw(sum % 998244353);
            } else {
                T sum = 0;
                for (int i = l; i <= r; ++i) sum += as[i] * bs[k - i];
                as[k] = sum;
            }
        }
    }
    for_each_block([&](int block, int step) {
        for (int j = 0; j < step; ++j) {
            int s = block + j;
            int t = s + step;
            T *cs = fa.data() + s * w;
            T *ct = fa.data() + t * w;
            for (int k = pc[t], lim = lim2[pc[s]]; k <= lim; ++k) {
                ct[k] -= cs[k];
            }
        }
    });

    vector<T> c(n);
    for (int s = 0; s < n; ++s) {
        c[s] = fa[s * w + pc[s]];
    }
    return c;
}

/**
 * @brief 部分集合畳み込み(Subset Convolution)
 */
