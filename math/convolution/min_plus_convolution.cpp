using namespace std;

template<class T, bool WithArgmin = false, class F>
vector<T> min_plus_convolution_monotone(int n, int m, F f, vector<int> *argmin = nullptr) {
    vector<T> res(n + m - 1);
    auto dfs = [&](auto &&self, int left, int right, int opt_left, int opt_right) -> void {
        if (left > right) return;
        int mid = (left + right) >> 1;
        int from = max(opt_left, max(0, mid - (m - 1)));
        int to = min(opt_right, min(n - 1, mid));
        int best = from;
        T best_value = f(mid, from);
        for (int i = from + 1; i <= to; ++i) {
            T value = f(mid, i);
            if (value < best_value) {
                best = i;
                best_value = value;
            }
        }
        res[mid] = best_value;
        if constexpr (WithArgmin) (*argmin)[mid] = best;
        self(self, left, mid - 1, opt_left, best);
        self(self, mid + 1, right, best, opt_right);
    };
    dfs(dfs, 0, n + m - 2, 0, n - 1);
    return res;
}

template<class T>
vector<T> min_plus_convolution_arbitrary_convex(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int n = a.size(), m = b.size();
    return min_plus_convolution_monotone<T>(n, m, [&](int k, int i) {
        return a[i] + b[k - i];
    });
}

template<class T>
vector<T> min_plus_convolution_convex_arbitrary(const vector<T> &a, const vector<T> &b) {
    return min_plus_convolution_arbitrary_convex(b, a);
}

template<class T, bool WithArgmin>
vector<T> min_plus_convolution_convex_convex_internal(const vector<T> &a, const vector<T> &b, vector<int> *argmin) {
    if (a.empty() || b.empty()) return {};
    int n = a.size(), m = b.size();
    vector<T> res(n + m - 1);
    int i = 0, j = 0;
    res[0] = a[0] + b[0];
    if constexpr (WithArgmin) (*argmin)[0] = 0;
    for (int k = 1; k < n + m - 1; ++k) {
        if (i == n - 1) {
            ++j;
        } else if (j == m - 1) {
            ++i;
        } else if (a[i + 1] + b[j] < a[i] + b[j + 1]) {
            ++i;
        } else {
            ++j;
        }
        res[k] = a[i] + b[j];
        if constexpr (WithArgmin) (*argmin)[k] = i;
    }
    return res;
}

template<class T>
vector<T> min_plus_convolution_convex_convex(const vector<T> &a, const vector<T> &b) {
    return min_plus_convolution_convex_convex_internal<T, false>(a, b, nullptr);
}

template<class T>
struct MinPlusConvolutionResult {
    vector<T> value;
    vector<int> argmin;
};

template<class T>
MinPlusConvolutionResult<T> min_plus_convolution_arbitrary_convex_with_argmin(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int n = a.size(), m = b.size();
    MinPlusConvolutionResult<T> res;
    res.argmin.resize(n + m - 1);
    res.value = min_plus_convolution_monotone<T, true>(n, m, [&](int k, int i) {
        return a[i] + b[k - i];
    }, &res.argmin);
    return res;
}

template<class T>
MinPlusConvolutionResult<T> min_plus_convolution_convex_arbitrary_with_argmin(const vector<T> &a, const vector<T> &b) {
    auto res = min_plus_convolution_arbitrary_convex_with_argmin(b, a);
    for (int k = 0; k < (int)res.argmin.size(); ++k) res.argmin[k] = k - res.argmin[k];
    return res;
}

template<class T>
MinPlusConvolutionResult<T> min_plus_convolution_convex_convex_with_argmin(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    MinPlusConvolutionResult<T> res;
    res.argmin.resize(a.size() + b.size() - 1);
    res.value = min_plus_convolution_convex_convex_internal<T, true>(a, b, &res.argmin);
    return res;
}

/**
 * @brief min-plus畳み込み(Min-Plus Convolution)
 */
