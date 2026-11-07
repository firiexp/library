#ifndef FIRIEXP_LIBRARY_STRING_DFA_KTH_WORD_CPP
#define FIRIEXP_LIBRARY_STRING_DFA_KTH_WORD_CPP

#include "kth_word.cpp"

template<int W>
class DFAKthWord {
    DFA<W> automaton;
    int max_length;
    unsigned long long max_rank;
    vector<kth_word_detail::Count> dp;

public:
    DFAKthWord(const DFA<W>& a, int max_length, unsigned long long max_rank = ULLONG_MAX)
        : automaton(a), max_length(max_length), max_rank(max_rank),
          dp(kth_word_detail::build(automaton, max_length, max_rank)) {}

    optional<vector<int>> kth(int n, unsigned long long k) const {
        assert(0 <= n && n <= max_length && k <= max_rank);
        return kth_word_detail::restore(automaton, dp, n, k);
    }
};

#endif

/**
 * @brief 前計算付きの辞書順k番目の受理文字列
 */
