#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_SUM_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_SUM_CPP

#include "weighted_wavelet_matrix.cpp"

template<class T, class U>
class StaticRangeDistinctSum {
    WeightedWaveletMatrix<int, U> previous;

public:
    template<class F>
    StaticRangeDistinctSum(const vector<T> &values, F weight) {
        int n = values.size();
        vector<int> order(n), prev(n, -1);
        vector<U> weights(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            if (values[a] < values[b]) return true;
            if (values[b] < values[a]) return false;
            return a < b;
        });
        for (int i = 0; i < n; ++i) {
            weights[i] = weight(values[i]);
            if (i && !(values[order[i - 1]] < values[order[i]]))
                prev[order[i]] = order[i - 1];
        }
        previous.build(prev, weights);
    }

    U sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= previous.n);
        return previous.sum_less(l, r, l);
    }
};

#endif

/**
 * @brief 静的区間の重複を除いた値の重み和
 */
