#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_SUM_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_SUM_CPP

#include "weighted_wavelet_matrix.cpp"

template<class T, class U>
class StaticRangeDistinctSum {
    int n;
    WeightedWaveletMatrix<int, U> previous;
    vector<int> boundaries;
    vector<U> prefix;

public:
    template<class F>
    StaticRangeDistinctSum(const vector<T> &values, F weight) : n(values.size()) {
        vector<int> order(n), prev(n, -1);
        vector<U> weights(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            if (values[a] < values[b]) return true;
            if (values[b] < values[a]) return false;
            return a < b;
        });
        bool repeated = false;
        for (int i = 0; i < n; ++i) {
            weights[i] = weight(values[i]);
            if (i && !(values[order[i - 1]] < values[order[i]])) {
                prev[order[i]] = order[i - 1];
                repeated = true;
            }
        }
        if (!repeated) {
            prefix.assign(n + 1, U());
            for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + weights[i];
            return;
        }
        boundaries.assign(n + 1, 0);
        for (int p : prev) if (p >= 0) boundaries[p + 1] = 1;
        vector<int> vals{-1};
        for (int l = 0; l <= n; ++l) {
            if (boundaries[l]) vals.push_back(l - 1);
            boundaries[l] = vals.size();
        }
        for (int &p : prev) p = p < 0 ? 0 : boundaries[p];
        previous.build_from_index(prev, vals, weights);
    }

    U sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (boundaries.empty()) return prefix[r] - prefix[l];
        return previous.count_sum_less_index(l, r, boundaries[l]).sum;
    }
};

#endif

/**
 * @brief 静的区間の重複を除いた値の重み和
 */
