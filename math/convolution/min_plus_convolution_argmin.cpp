#include "min_plus_convolution.cpp"

template<class T>
struct MinPlusArgmin {
    vector<T> value;
    vector<int> argmin;
};

template<class T>
MinPlusArgmin<T> min_plus_argmin_arbitrary_convex(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int n = a.size(), m = b.size();
    MinPlusArgmin<T> res;
    res.argmin.resize(n + m - 1);
    res.value = min_plus_convolution_monotone<T, true>(n, m, [&](int k, int i) {
        return a[i] + b[k - i];
    }, &res.argmin);
    return res;
}

template<class T>
MinPlusArgmin<T> min_plus_argmin_convex_arbitrary(const vector<T> &a, const vector<T> &b) {
    auto res = min_plus_argmin_arbitrary_convex(b, a);
    for (int k = 0; k < (int)res.argmin.size(); ++k) res.argmin[k] = k - res.argmin[k];
    return res;
}

template<class T>
MinPlusArgmin<T> min_plus_argmin_convex_convex(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    MinPlusArgmin<T> res;
    res.argmin.resize(a.size() + b.size() - 1);
    res.value = min_plus_convolution_convex_convex_internal<T, true>(a, b, &res.argmin);
    return res;
}

/**
 * @brief 添字取得付きmin-plus畳み込み
 */
