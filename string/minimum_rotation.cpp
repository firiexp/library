#ifndef FIRIEXP_LIBRARY_STRING_MINIMUM_ROTATION_CPP
#define FIRIEXP_LIBRARY_STRING_MINIMUM_ROTATION_CPP

namespace minimum_rotation_detail {

template<class Less>
int find(size_t n, Less less) {
    assert(n <= (size_t)numeric_limits<int>::max());
    size_t i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        size_t a = i + k, b = j + k;
        if (a >= n) a -= n;
        if (b >= n) b -= n;
        if (less(a, b)) {
            j += k + 1;
            if (i == j) ++j;
        } else if (less(b, a)) {
            i += k + 1;
            if (i == j) ++i;
        } else {
            ++k;
            continue;
        }
        k = 0;
    }
    return (int)min(i, j);
}

}

int minimum_rotation_index(const string& s) {
    return minimum_rotation_detail::find(s.size(), [&](size_t i, size_t j) {
        return (unsigned char)s[i] < (unsigned char)s[j];
    });
}

template<class T>
int minimum_rotation_index(const vector<T>& s) {
    return minimum_rotation_detail::find(s.size(), [&](size_t i, size_t j) {
        return s[i] < s[j];
    });
}

#endif

/**
 * @brief 最小巡回シフト
 */
