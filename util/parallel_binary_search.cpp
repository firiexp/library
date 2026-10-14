#ifndef FIRIEXP_LIBRARY_UTIL_PARALLEL_BINARY_SEARCH_CPP
#define FIRIEXP_LIBRARY_UTIL_PARALLEL_BINARY_SEARCH_CPP

template<class Reset, class Apply, class Check>
vector<int> parallel_binary_search(int m, int q, Reset reset, Apply apply, Check check) {
    if (q == 0) return {};
    vector<int> lo(q, -1), hi(q, m + 1), head(m + 1), next(q);
    while (true) {
        fill(head.begin(), head.end(), -1);
        int last = -1;
        for (int i = 0; i < q; ++i) {
            if (lo[i] + 1 == hi[i]) continue;
            int mid = lo[i] + ((long long)hi[i] - lo[i]) / 2;
            next[i] = head[mid];
            head[mid] = i;
            last = max(last, mid);
        }
        if (last == -1) break;
        reset();
        for (int t = 0; t <= last; ++t) {
            if (t) apply(t - 1);
            for (int i = head[t]; i != -1; i = next[i]) {
                if (check(i)) hi[i] = t;
                else lo[i] = t;
            }
        }
    }
    return hi;
}

#endif

/**
 * @brief 並列二分探索
 */
