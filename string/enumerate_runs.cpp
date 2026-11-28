#ifndef FIRIEXP_LIBRARY_STRING_ENUMERATE_RUNS_CPP
#define FIRIEXP_LIBRARY_STRING_ENUMERATE_RUNS_CPP

#include "suffix_array_query.cpp"

struct Run {
    int period, l, r;
};

vector<Run> enumerate_runs(const string& s) {
    int n = (int)s.size();
    if (n <= 1) return {};
    SuffixArrayQuery forward(s), backward(string(s.rbegin(), s.rend()));
    vector<Run> result;
    vector<int> stack;
    stack.reserve(n);
    for (int order = 0; order < 2; ++order) {
        auto less = [&](int i, int k) {
            if (order == 0) return forward.suffix_rank(i) < forward.suffix_rank(k);
            int common = s[i] == s[k] ? forward.lce(i, k) : 0;
            return k + common < n && (unsigned char)s[i + common] > (unsigned char)s[k + common];
        };
        stack.clear();
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && less(i, stack.back())) stack.pop_back();
            int j = stack.empty() ? n : stack.back();
            int period = j - i;
            int left = backward.lce(n - i, n - j);
            int right = forward.lce(i, j);
            if (left + right >= period) result.push_back({period, i - left, j + right});
            stack.push_back(i);
        }
    }
    sort(result.begin(), result.end(), [](const Run& a, const Run& b) {
        return tie(a.period, a.l, a.r) < tie(b.period, b.l, b.r);
    });
    result.erase(unique(result.begin(), result.end(), [](const Run& a, const Run& b) {
        return tie(a.period, a.l, a.r) == tie(b.period, b.l, b.r);
    }), result.end());
    return result;
}

#endif

/**
 * @brief 文字列のrun列挙
 */
