#ifndef FIRIEXP_LIBRARY_STRING_KTH_WORD_CPP
#define FIRIEXP_LIBRARY_STRING_KTH_WORD_CPP

#include "dfa.cpp"

template<int W>
optional<vector<int>> kth_word(const DFA<W>& a, int n, unsigned long long k) {
    assert(n >= 0);
    if (a.initial == -1) return nullopt;
    using Count = __uint128_t;
    size_t s = a.next.size(), layers = (size_t)n + 1;
    assert(s <= vector<Count>().max_size() / layers);
    Count cap = (Count)k + 1;
    vector<Count> dp(layers * s);
    for (size_t v = 0; v < s; ++v) dp[v] = a.accept[v] ? 1 : 0;
    for (int len = 0; len < n; ++len) {
        size_t previous = (size_t)len * s, current = previous + s;
        for (size_t v = 0; v < s; ++v) {
            Count count = 0;
            for (int to : a.next[v]) if (to != -1) {
                count = min(cap, count + dp[previous + to]);
            }
            dp[current + v] = count;
        }
    }
    if (dp[(size_t)n * s + a.initial] <= (Count)k) return nullopt;
    vector<int> result;
    result.reserve(n);
    int v = a.initial;
    Count rank = k;
    for (int len = n; len > 0; --len) {
        for (int c = 0; c < W; ++c) {
            int to = a.next[v][c];
            if (to == -1) continue;
            Count count = dp[(size_t)(len - 1) * s + to];
            if (rank >= count) rank -= count;
            else {
                result.push_back(c);
                v = to;
                break;
            }
        }
    }
    return result;
}

#endif

/**
 * @brief 有限オートマトンの辞書順k番目の文字列
 */
