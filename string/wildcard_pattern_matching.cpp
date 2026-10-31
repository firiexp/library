#ifndef FIRIEXP_LIBRARY_STRING_WILDCARD_PATTERN_MATCHING_CPP
#define FIRIEXP_LIBRARY_STRING_WILDCARD_PATTERN_MATCHING_CPP

#include "../math/convolution/integer_convolution.cpp"

namespace wildcard_pattern_matching_detail {
template<class Transform>
bool filter_matches(const string &text, const string &pattern, char wildcard,
                    const Transform &transform, vector<int> &result) {
    using mint = typename Transform::mint;
    int n = (int)text.size(), m = (int)pattern.size(), size = 1;
    while (size < n + m - 1) size <<= 1;
    vector<mint> a(size), b(size), score(size);
    for (int power = 1; power <= 3; ++power) {
        fill(a.begin() + n, a.end(), mint(0));
        fill(b.begin() + m, b.end(), mint(0));
        for (int i = 0; i < n; ++i) {
            unsigned int value = text[i] == wildcard ? 0 : (unsigned char)text[i] + 1;
            unsigned int x = value;
            for (int k = 1; k < power; ++k) x *= value;
            a[i] = mint::raw(x);
        }
        for (int i = 0; i < m; ++i) {
            unsigned int value = pattern[i] == wildcard ? 0 : (unsigned char)pattern[i] + 1;
            unsigned int x = value;
            for (int k = 1; k < 4 - power; ++k) x *= value;
            b[m - 1 - i] = mint::raw(x);
        }
        transform.ntt(a, false);
        transform.ntt(b, false);
        for (int i = 0; i < size; ++i) {
            mint product = a[i] * b[i];
            if (power == 2) score[i] -= product + product;
            else score[i] += product;
        }
    }
    transform.ntt(score, true);
    bool any = false;
    for (int i = 0; i <= n - m; ++i) {
        result[i] &= score[i + m - 1].val == 0;
        any |= result[i] != 0;
    }
    return any;
}
}

vector<int> wildcard_pattern_matching(const string& text, const string& pattern, char wildcard = '*') {
    int n = (int)text.size(), m = (int)pattern.size();
    if (m > n) return {};
    if (m == 0) return vector<int>(n + 1, 1);
    assert((long long)n + m - 1 <= (1 << 21));
    if (all_of(pattern.begin(), pattern.end(), [&](char c) { return c == wildcard; }))
        return vector<int>(n - m + 1, 1);
    if (min(m, n - m + 1) <= 16) {
        vector<int> result(n - m + 1, 1);
        for (int i = 0; i <= n - m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (text[i + j] == wildcard || pattern[j] == wildcard || text[i + j] == pattern[j]) continue;
                result[i] = 0;
                break;
            }
        }
        return result;
    }
    if (n + m - 1 >= 128) {
        vector<int> result(n - m + 1, 1);
        if (!wildcard_pattern_matching_detail::filter_matches(text, pattern, wildcard, BoundedConvolution::internal::ntt1(), result))
            return result;
        wildcard_pattern_matching_detail::filter_matches(text, pattern, wildcard, BoundedConvolution::internal::ntt2(), result);
        return result;
    }
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
