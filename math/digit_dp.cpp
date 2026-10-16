#ifndef FIRIEXP_LIBRARY_MATH_DIGIT_DP_CPP
#define FIRIEXP_LIBRARY_MATH_DIGIT_DP_CPP

#include "../string/dfa.cpp"

namespace digit_dp_detail {

template<class T, bool Sum>
auto run(const string& lower, const string& upper, const DFA<10>& a) {
    using Value = conditional_t<Sum, pair<T, T>, T>;
    const Value zero = []() -> Value {
        if constexpr (Sum) return {T(0), T(0)};
        else return T(0);
    }();
    auto count = [](Value& x) -> T& {
        if constexpr (Sum) return x.first;
        else return x;
    };
    auto empty = [](const Value& x) {
        if constexpr (Sum) return x.first == T(0) && x.second == T(0);
        else return x == T(0);
    };
    assert(!lower.empty() && !upper.empty());
    if (a.initial == -1) return zero;
    string_view l(lower), r(upper);
    while (l.size() > 1 && l.front() == '0') l.remove_prefix(1);
    while (r.size() > 1 && r.front() == '0') r.remove_prefix(1);
    if (l.size() > r.size() || (l.size() == r.size() && l > r)) return zero;
    size_t s = a.next.size();
    array<Value, 4> zeros{zero, zero, zero, zero};
    vector<array<Value, 4>> dp(s + 1, zeros), next(s + 1, zeros);
    count(dp[s][3]) = T(1);
    for (size_t i = 0; i < r.size(); ++i) {
        int ld = i < r.size() - l.size() ? 0 : l[i - (r.size() - l.size())] - '0';
        int rd = r[i] - '0';
        fill(next.begin(), next.end(), zeros);
        for (int tight = 0; tight < 4; ++tight) {
            int low = tight & 1 ? ld : 0;
            int high = tight & 2 ? rd : 9;
            for (size_t v = 0; v <= s; ++v) {
                auto& from = dp[v][tight];
                if (empty(from)) continue;
                for (int d = low; d <= high; ++d) {
                    int to = v == s && d == 0 ? (int)s : a.next[v == s ? a.initial : v][d];
                    if (to == -1) continue;
                    int flags = ((tight & 1) && d == ld) | (((tight & 2) && d == rd) << 1);
                    auto& dest = next[to][flags];
                    count(dest) += count(from);
                    if constexpr (Sum) dest.second += from.second * T(10) + from.first * T(d);
                }
            }
        }
        dp.swap(next);
    }
    Value result = zero;
    int zero_state = a.next[a.initial][0];
    for (size_t v = 0; v <= s; ++v) {
        bool accepted = v == s ? zero_state != -1 && a.accept[zero_state] : a.accept[v];
        if (!accepted) continue;
        for (auto& value : dp[v]) {
            count(result) += count(value);
            if constexpr (Sum) result.second += value.second;
        }
    }
    return result;
}

}

template<class T>
T digit_count(const string& lower, const string& upper, const DFA<10>& a) {
    return digit_dp_detail::run<T, false>(lower, upper, a);
}

template<class T>
pair<T, T> digit_count_sum(const string& lower, const string& upper, const DFA<10>& a) {
    return digit_dp_detail::run<T, true>(lower, upper, a);
}

#endif

/**
 * @brief 上下限付き桁DPの個数と総和
 */
