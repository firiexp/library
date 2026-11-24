#ifndef FIRIEXP_LIBRARY_STRING_COUNT_DISTINCT_SUBSEQUENCES_CPP
#define FIRIEXP_LIBRARY_STRING_COUNT_DISTINCT_SUBSEQUENCES_CPP

template<class T>
T count_distinct_subsequences(string_view s) {
    vector<T> last(256, T(0));
    T total(1);
    for (unsigned char c : s) {
        T next = total + total - last[c];
        last[c] = total;
        total = next;
    }
    return total - T(1);
}

template<class Count, class T>
Count count_distinct_subsequences(const vector<T>& a) {
    unordered_map<T, Count> last;
    Count total(1);
    for (const T& x : a) {
        Count& previous = last.try_emplace(x, 0).first->second;
        Count next = total + total - previous;
        previous = total;
        total = next;
    }
    return total - Count(1);
}

#endif

/**
 * @brief 相異なる部分列の個数
 */
