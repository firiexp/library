#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_STATIC_RANGE_DISTINCT_CPP

#include "wavelet_matrix.cpp"

template<class T>
class StaticRangeDistinct {
    WaveletMatrix<int> previous;
    vector<int> boundaries;

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
        bool repeated = false;
        for (int i = 1; i < n; ++i) {
            if (!(values[order[i - 1]] < values[order[i]])) {
                prev[order[i]] = order[i - 1];
                repeated = true;
            }
        }
        if (!repeated) return;
        boundaries.assign(n + 1, 0);
        for (int p : prev) if (p >= 0) boundaries[p + 1] = 1;
        vector<int> vals{-1};
        for (int l = 0; l <= n; ++l) {
            if (boundaries[l]) vals.push_back(l - 1);
            boundaries[l] = vals.size();
        }
        for (int &p : prev) p = p < 0 ? 0 : boundaries[p];
        previous.build_from_index(prev, vals);
    }

    int count(int l, int r) const {
        if (boundaries.empty()) return r - l;
        return previous.count_less_index(l, r, boundaries[l]);
    }
};

#endif

/**
 * @brief 静的区間の種類数
 */
