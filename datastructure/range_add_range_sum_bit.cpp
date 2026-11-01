#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_RANGE_ADD_RANGE_SUM_BIT_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_RANGE_ADD_RANGE_SUM_BIT_CPP

#include "binaryindexedtree.cpp"

template<class T>
class RangeAddRangeSumBIT {
    int n;
    BIT<T> slope, intercept, offset;

    static long long triangle(int k) {
        return 1LL * k * (k - 1) / 2;
    }

    static vector<T> differences(const vector<T> &values, bool weight) {
        vector<T> result(values.size());
        for (int i = 0; i < (int)values.size(); ++i) {
            T delta = values[i] - (i == 0 ? T(0) : values[i - 1]);
            result[i] = weight ? delta * i : delta;
        }
        return result;
    }

public:
    explicit RangeAddRangeSumBIT(int n) : n(n), slope(n), intercept(n), offset(n) {}

    explicit RangeAddRangeSumBIT(const vector<T> &values)
        : n(values.size()), slope(n), intercept(differences(values, false)), offset(differences(values, true)) {}

    void add(int l, int r, T x) {
        add(l, r, T(0), x);
    }

    void add(int l, int r, T a, T b) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        slope.add(l, a);
        intercept.add(l, b);
        offset.add(l, a * triangle(l) + b * l);
        if (r < n) {
            slope.add(r, T(0) - a);
            intercept.add(r, T(0) - b);
            offset.add(r, T(0) - (a * triangle(r) + b * r));
        }
    }

    T sum(int r) {
        assert(0 <= r && r <= n);
        return slope.sum(r) * triangle(r) + intercept.sum(r) * r - offset.sum(r);
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return T(0);
        return sum(r) - sum(l);
    }
};

#endif

/**
 * @brief 一次関数加算・区間和BIT
 */
