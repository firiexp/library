#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_CPP

#include "wavelet_matrix.cpp"

template<class T>
class StaticRangeDistinct {
    WaveletMatrix<int> previous;

public:
    explicit StaticRangeDistinct(const vector<T>& values) {
        int n = values.size();
        vector<int> order(n), prev(n, -1);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            if (values[a] < values[b]) return true;
            if (values[b] < values[a]) return false;
            return a < b;
        });
        for (int i = 1; i < n; ++i) {
            if (!(values[order[i - 1]] < values[order[i]])) prev[order[i]] = order[i - 1];
        }
        previous.build(prev);
    }

    int count(int l, int r) const {
        return previous.count_less(l, r, l);
    }
};

#endif

/**
 * @brief 静的区間の種類数
 */
