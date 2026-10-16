#ifndef FIRIEXP_LIBRARY_STRING_COUNT_WORDS_CPP
#define FIRIEXP_LIBRARY_STRING_COUNT_WORDS_CPP

#include "dfa.cpp"
#include "../fps/linear_recurrence.cpp"

template<int W>
mint count_words(const DFA<W>& a, ll n) {
    assert(n >= 0);
    if (a.initial == -1) return mint(0);
    if (n == 0) return mint(bool(a.accept[a.initial]));
    if (none_of(a.accept.begin(), a.accept.end(), [](char x) { return x; })) return mint(0);
    int s = (int)a.next.size();
    if (s == 1) {
        if (!a.accept[0]) return mint(0);
        int degree = 0;
        for (int to : a.next[0]) degree += to != -1;
        return mint(degree).pow(n);
    }
    ll terms = min(n, 2LL * s - 1) + 1;
    vector<unsigned> dp(s);
    vector<unsigned long long> next(s);
    vector<mint> sequence;
    vector<int> active{a.initial}, touched;
    sequence.reserve(terms);
    dp[a.initial] = 1;
    unsigned long long total = bool(a.accept[a.initial]);
    int width = min<unsigned long long>(W, numeric_limits<unsigned long long>::max() / (ntt_mod - 1) / (s + 1ULL));
    for (ll len = 0; len < terms; ++len) {
        sequence.push_back(mint::raw(total % ntt_mod));
        if (len == n) return sequence.back();
        if (active.empty()) return mint(0);
        if (len + 1 == terms) break;
        bool sparse = active.size() < size_t(s) / 4 && width == W;
        touched.clear();
        if (sparse) {
            for (int v : active) {
                for (int to : a.next[v]) if (to != -1) {
                    if (next[to] == 0) touched.push_back(to);
                    next[to] += dp[v];
                }
                dp[v] = 0;
            }
        } else if (width == W) {
            for (int v : active) {
                for (int to : a.next[v]) if (to != -1) next[to] += dp[v];
            }
        } else {
            for (int first = 0; first < W;) {
                int last = first + min(width, W - first);
                for (int v : active) {
                    for (int c = first; c < last; ++c) {
                        int to = a.next[v][c];
                        if (to != -1) next[to] += dp[v];
                    }
                }
                first = last;
                if (first != W) for (auto& value : next) value %= ntt_mod;
            }
        }
        active.clear();
        total = 0;
        auto finish = [&](int v) {
            dp[v] = next[v] % ntt_mod;
            next[v] = 0;
            if (dp[v]) active.push_back(v);
            if (a.accept[v]) total += dp[v];
        };
        if (sparse) {
            for (int v : touched) finish(v);
        } else {
            for (int v = 0; v < s; ++v) finish(v);
        }
    }
    return linear_recurrence(sequence, n);
}

#endif

/**
 * @brief 有限状態DPの長さNの文字列数
 */
