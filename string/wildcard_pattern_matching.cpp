#ifndef FIRIEXP_LIBRARY_STRING_WILDCARD_PATTERN_MATCHING_CPP
#define FIRIEXP_LIBRARY_STRING_WILDCARD_PATTERN_MATCHING_CPP

#include "../math/integer_convolution.cpp"

vector<int> wildcard_pattern_matching(const string& text, const string& pattern, char wildcard = '*') {
    int n = (int)text.size(), m = (int)pattern.size();
    if (m > n) return {};
    if (m == 0) return vector<int>(n + 1, 1);
    assert((long long)n + m - 1 <= (1 << 21));
    vector<unsigned int> a(n), b(m), ap(n), bp(m);
    for (int i = 0; i < n; ++i)
        a[i] = text[i] == wildcard ? 0 : (unsigned char)text[i] + 1;
    for (int i = 0; i < m; ++i)
        b[m - 1 - i] = pattern[i] == wildcard ? 0 : (unsigned char)pattern[i] + 1;
    vector<long long> score(n - m + 1);
    for (int power = 1; power <= 3; ++power) {
        for (int i = 0; i < n; ++i) {
            ap[i] = a[i];
            for (int k = 1; k < power; ++k) ap[i] *= a[i];
        }
        for (int i = 0; i < m; ++i) {
            bp[i] = b[i];
            for (int k = 1; k < 4 - power; ++k) bp[i] *= b[i];
        }
        auto c = BoundedConvolution::convolution_u64(ap, bp);
        int sign = power == 2 ? -2 : 1;
        for (int i = 0; i <= n - m; ++i) score[i] += sign * (long long)c[i + m - 1];
    }
    vector<int> result(n - m + 1);
    for (int i = 0; i <= n - m; ++i) result[i] = score[i] == 0;
    return result;
}

#endif

/**
 * @brief ワイルドカード付きパターン照合
 */
