#ifndef FIRIEXP_LIBRARY_STRING_COUNT_WORDS_CPP
#define FIRIEXP_LIBRARY_STRING_COUNT_WORDS_CPP

#include "dfa.cpp"
#include "../fps/linear_recurrence.cpp"

template<int W>
mint count_words(const DFA<W>& a, ll n) {
    assert(n >= 0);
    if (a.initial == -1) return mint(0);
    int s = (int)a.next.size();
    ll terms = min(n, 2LL * s - 1) + 1;
    vector<mint> dp(s), next(s), sequence;
    sequence.reserve(terms);
    dp[a.initial] = 1;
    for (ll len = 0; len < terms; ++len) {
        mint total = 0;
        for (int v = 0; v < s; ++v) if (a.accept[v]) total += dp[v];
        sequence.push_back(total);
        if (len == n) return total;
        if (len + 1 == terms) break;
        fill(next.begin(), next.end(), mint(0));
        for (int v = 0; v < s; ++v) {
            if (dp[v] == mint(0)) continue;
            for (int to : a.next[v]) if (to != -1) next[to] += dp[v];
        }
        dp.swap(next);
    }
    return linear_recurrence(sequence, n);
}

#endif

/**
 * @brief 有限状態DPの長さNの文字列数
 */
