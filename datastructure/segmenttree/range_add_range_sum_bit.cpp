#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_RANGE_ADD_RANGE_SUM_BIT_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_RANGE_ADD_RANGE_SUM_BIT_CPP

#include "binaryindexedtree.cpp"

template<class T>
class RangeAddRangeSumBIT {
    struct Coefficients {
        T intercept, slope, offset;

        Coefficients(int value = 0) : intercept(value), slope(value), offset(value) {}
        Coefficients(T slope, T intercept, T offset)
            : intercept(intercept), slope(slope), offset(offset) {}

        Coefficients &operator+=(const Coefficients &other) {
            slope += other.slope;
            intercept += other.intercept;
            offset += other.offset;
            return *this;
        }
    };
    int n;
    BIT<Coefficients> bit;

    static long long triangle(int k) {
        return 1LL * k * (k - 1) / 2;
    }

    static vector<Coefficients> differences(const vector<T> &values) {
        vector<Coefficients> result(values.size());
        for (int i = 0; i < (int)values.size(); ++i) {
            T delta = values[i] - (i == 0 ? T(0) : values[i - 1]);
            result[i] = {T(0), delta, delta * i};
        }
        return result;
    }

public:
    explicit RangeAddRangeSumBIT(int n) : n(n), bit(n) {}

    explicit RangeAddRangeSumBIT(const vector<T> &values)
        : n(values.size()), bit(differences(values)) {}

    void add(int l, int r, T x) {
        add(l, r, T(0), x);
    }

    void add(int l, int r, T a, T b) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        bit.add(l, {a, b, a * triangle(l) + b * l});
        if (r < n) {
            bit.add(r, {T(0) - a, T(0) - b, T(0) - (a * triangle(r) + b * r)});
        }
    }

    T sum(int r) {
        assert(0 <= r && r <= n);
        auto coefficients = bit.sum(r);
        return coefficients.slope * triangle(r) + coefficients.intercept * r - coefficients.offset;
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
