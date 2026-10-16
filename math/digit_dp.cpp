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
    if (none_of(a.accept.begin(), a.accept.end(), [](char x) { return x; })) return zero;
    string_view l(lower), r(upper);
    while (l.size() > 1 && l.front() == '0') l.remove_prefix(1);
    while (r.size() > 1 && r.front() == '0') r.remove_prefix(1);
    if (l.size() > r.size() || (l.size() == r.size() && l > r)) return zero;
    int s = (int)a.next.size();
    vector<Value> dp(s, zero), next(s, zero);
    array<Value, 4> border{zero, zero, zero, zero};
    array<int, 4> path{-1, -1, -1, s};
    count(border[3]) = T(1);
    bool loose = false;
    vector<int> last;
    if constexpr (Sum) {
        last.assign(s, -1);
        for (int v = 0; v < s; ++v) {
            for (int d = 0; d < 10; ++d) if (a.next[v][d] != -1) last[v] = d;
        }
    }
    for (size_t i = 0; i < r.size(); ++i) {
        int ld = i < r.size() - l.size() ? 0 : l[i - (r.size() - l.size())] - '0';
        int rd = r[i] - '0';
        if (loose) fill(next.begin(), next.end(), zero);
        for (int v = 0; loose && v < s; ++v) {
            const auto& from = dp[v];
            if (empty(from)) continue;
            if constexpr (Sum) {
                if (last[v] == -1) continue;
                T sum = from.second * T(10);
                for (int d = 0; d <= last[v]; ++d) {
                    int to = a.next[v][d];
                    if (to != -1) {
                        next[to].first += from.first;
                        next[to].second += sum;
                    }
                    if (d != last[v]) sum += from.first;
                }
            } else {
                for (int to : a.next[v]) if (to != -1) next[to] += from;
            }
        }
        array<Value, 4> next_border{zero, zero, zero, zero};
        array<int, 4> next_path{-1, -1, -1, -1};
        for (int tight = 1; tight < 4; ++tight) {
            int v = path[tight];
            if (v == -1) continue;
            int low = tight & 1 ? ld : 0;
            int high = tight & 2 ? rd : 9;
            for (int d = low; d <= high; ++d) {
                int to = v == s && d == 0 ? s : a.next[v == s ? a.initial : v][d];
                if (to == -1) continue;
                int flags = ((tight & 1) && d == ld) | (((tight & 2) && d == rd) << 1);
                Value value = border[tight];
                if constexpr (Sum) value.second = value.second * T(10) + T(d);
                if (flags) {
                    next_path[flags] = to;
                    next_border[flags] = value;
                } else {
                    assert(to != s);
                    loose = true;
                    count(next[to]) += count(value);
                    if constexpr (Sum) next[to].second += value.second;
                }
            }
        }
        dp.swap(next);
        path = next_path;
        border = next_border;
    }
    Value result = zero;
    int zero_state = a.next[a.initial][0];
    for (int v = 0; v < s; ++v) if (a.accept[v]) {
        count(result) += count(dp[v]);
        if constexpr (Sum) result.second += dp[v].second;
    }
    for (int tight = 1; tight < 4; ++tight) {
        int v = path[tight];
        if (v == s) v = zero_state;
        if (v == -1 || !a.accept[v]) continue;
        count(result) += count(border[tight]);
        if constexpr (Sum) result.second += border[tight].second;
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
