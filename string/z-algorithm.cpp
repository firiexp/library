#ifndef FIRIEXP_LIBRARY_STRING_Z_ALGORITHM_CPP
#define FIRIEXP_LIBRARY_STRING_Z_ALGORITHM_CPP

namespace z_algorithm_detail {

template<class Sequence>
vector<int> z_array(const Sequence& s) {
    int n = (int)s.size();
    vector<int> res(n);
    if (n == 0) return res;
    res[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) res[i] = min(r - i, res[i - l]);
        while (i + res[i] < n && s[res[i]] == s[i + res[i]]) ++res[i];
        if (r < i + res[i]) {
            l = i;
            r = i + res[i];
        }
    }
    return res;
}

template<class Sequence>
vector<int> match(const Sequence& pattern, const Sequence& text) {
    int m = (int)pattern.size(), n = (int)text.size();
    auto z = z_array(pattern);
    vector<int> res(n);
    for (int i = 0, l = 0, r = 0; i < n; ++i) {
        if (i < r) res[i] = min(r - i, z[i - l]);
        while (res[i] < m && res[i] < n - i && pattern[res[i]] == text[i + res[i]]) ++res[i];
        if (r < i + res[i]) {
            l = i;
            r = i + res[i];
        }
    }
    return res;
}

}

vector<int> Z_algorithm(const string& s) {
    return z_algorithm_detail::z_array(s);
}

vector<int> z_match(const string& pattern, const string& text) {
    return z_algorithm_detail::match(pattern, text);
}

template<class T>
vector<int> z_match(const vector<T>& pattern, const vector<T>& text) {
    return z_algorithm_detail::match(pattern, text);
}

#endif

/**
 * @brief Z-Algorithm
 */
