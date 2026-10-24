#ifndef FIRIEXP_LIBRARY_STRING_COUNT_WORDS_CPP
#define FIRIEXP_LIBRARY_STRING_COUNT_WORDS_CPP

#include "dfa.cpp"
#include "../fps/linear_recurrence.cpp"

namespace count_words_detail {
struct CompressedTransitions {
    vector<size_t> offset;
    vector<pair<int, int>> edges;
};

template<int W>
CompressedTransitions compress(const DFA<W>& a) {
    int s = a.next.size(), samples = min(s, 16);
    vector<int> count(s);
    size_t sampled_edges = 0, sampled_unique = 0;
    for (int i = 0; i < samples; ++i) {
        int v = 1LL * i * s / samples;
        for (int to : a.next[v]) if (to != -1) {
            ++sampled_edges;
            if (count[to] != i + 1) {
                count[to] = i + 1;
                ++sampled_unique;
            }
        }
    }
    if (sampled_edges == 0 || sampled_unique * 4 > sampled_edges * 3) return {};
    fill(count.begin(), count.end(), 0);
    CompressedTransitions result;
    result.offset.reserve(s + 1);
    result.offset.push_back(0);
    vector<int> touched;
    touched.reserve(min(s, W));
    size_t original_edges = 0;
    for (const auto& row : a.next) {
        touched.clear();
        for (int to : row) if (to != -1) {
            ++original_edges;
            if (count[to]++ == 0) touched.push_back(to);
        }
        for (int to : touched) {
            result.edges.emplace_back(to, count[to]);
            count[to] = 0;
        }
        result.offset.push_back(result.edges.size());
    }
    if (result.edges.size() * 4 > original_edges * 3) return {};
    return result;
}

template<bool SaveSequence, int W>
auto solve(const DFA<W>& a, ll n) {
    int s = (int)a.next.size();
    ll terms = min(n, 2LL * s - 1) + 1;
    vector<unsigned> dp(s);
    vector<unsigned long long> next(s);
    vector<mint> sequence;
    vector<int> active{a.initial}, touched;
    sequence.reserve(terms);
    dp[a.initial] = 1;
    unsigned long long total = bool(a.accept[a.initial]);
    int width = min<unsigned long long>(W, numeric_limits<unsigned long long>::max() / (ntt_mod - 1) / (s + 1ULL));
    bool consider_compression = W > 4 && width == W && terms > 32;
    CompressedTransitions compressed;
    for (ll len = 0; len < terms; ++len) {
        sequence.push_back(mint::raw(total % ntt_mod));
        if (active.empty()) break;
        if (len + 1 == terms) break;
        if (consider_compression && active.size() >= size_t(max(8, s / 8))) {
            consider_compression = false;
            if (terms - len > 32) compressed = compress(a);
        }
        bool sparse = active.size() < size_t(s) / 4 && width == W;
        touched.clear();
        if (!compressed.offset.empty()) {
            if (sparse) {
                for (int v : active) {
                    for (size_t i = compressed.offset[v]; i < compressed.offset[v + 1]; ++i) {
                        auto [to, multiplicity] = compressed.edges[i];
                        if (next[to] == 0) touched.push_back(to);
                        next[to] += (unsigned long long)dp[v] * multiplicity;
                    }
                    dp[v] = 0;
                }
            } else {
                for (int v : active) {
                    for (size_t i = compressed.offset[v]; i < compressed.offset[v + 1]; ++i) {
                        auto [to, multiplicity] = compressed.edges[i];
                        next[to] += (unsigned long long)dp[v] * multiplicity;
                    }
                }
            }
        } else if (sparse) {
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
    if constexpr (SaveSequence) {
        return sequence;
    } else {
        if (n < (ll)sequence.size()) return sequence[n];
        if ((ll)sequence.size() < terms) return mint(0);
        return linear_recurrence(sequence, n);
    }
}
}

template<int W>
mint count_words(const DFA<W>& a, ll n) {
    assert(n >= 0);
    if (a.initial == -1) return mint(0);
    if (n == 0) return mint(bool(a.accept[a.initial]));
    if (none_of(a.accept.begin(), a.accept.end(), [](char x) { return x; })) return mint(0);
    int s = (int)a.next.size();
    if (s == 1) {
        int degree = 0;
        for (int to : a.next[0]) degree += to != -1;
        return mint(degree).pow(n);
    }
    return count_words_detail::solve<false>(a, n);
}

template<int W>
class DFAWordCounter {
    vector<mint> initial;
    poly numerator, denominator;

public:
    explicit DFAWordCounter(const DFA<W>& a) {
        if (a.initial == -1) return;
        if (none_of(a.accept.begin(), a.accept.end(), [](char x) { return x; })) return;
        int s = (int)a.next.size();
        if (s == 1) {
            int degree = 0;
            for (int to : a.next[0]) degree += to != -1;
            initial = {mint(1)};
            denominator = poly(vector<mint>{mint(1), -mint(degree)});
            return;
        }
        initial = count_words_detail::solve<true>(a, 2LL * s - 1);
        if ((ll)initial.size() < 2LL * s) return;
        auto coefficients = berlekamp_massey(initial);
        int k = (int)coefficients.size();
        if (k == 0) return;
        denominator = poly(k + 1);
        denominator[0] = 1;
        for (int i = 0; i < k; ++i) denominator[i + 1] = -coefficients[i];
        if (k > 1) {
            numerator = (poly(vector<mint>(initial.begin(), initial.begin() + k)) * denominator).cut(k);
        }
    }

    mint count(ll n) const {
        assert(n >= 0);
        if (n < (ll)initial.size()) return initial[n];
        if (denominator.size() == 0) return mint(0);
        if (denominator.size() == 2) return initial[0] * (-denominator[1]).pow(n);
        return nth_term(numerator, denominator, n);
    }
};

#endif

/**
 * @brief 有限状態DPの長さNの文字列数
 */
