#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/interval_map.cpp"
#include "../datastructure/interval_map.cpp"

using Run = tuple<long long, long long, int>;

vector<Run> clipped_runs(const vector<int> &a, int l, int r) {
    vector<Run> result;
    for (int begin = l; begin < r;) {
        int end = begin + 1;
        while (end < r && a[end] == a[begin]) ++end;
        result.emplace_back(begin, end, a[begin]);
        begin = end;
    }
    return result;
}

void check_intervals(const IntervalMap<int> &intervals, const vector<int> &a, int l, int r) {
    vector<Run> actual;
    intervals.for_each_interval(l, r, [&](long long begin, long long end, auto &value) {
        static_assert(is_same_v<decltype(value), const int &>);
        actual.emplace_back(begin, end, value);
        assert(intervals.get(begin) == value && intervals.get(end - 1) == value);
    });
    assert(actual == clipped_runs(a, l, r));
}

void check(const vector<int> &initial, const vector<tuple<int, int, int>> &operations) {
    int n = initial.size();
    IntervalMap<int> intervals(initial), reference(n, 0);
    for (auto [l, r, value] : clipped_runs(initial, 0, n)) reference.assign(l, r, value);
    vector<int> a = initial;
    vector<long long> counts(5);
    for (int value : a) ++counts[value];
    long long pairs = 0;
    for (long long count : counts) pairs += count * (count - 1) / 2;
    check_intervals(intervals, a, 0, n);
    for (int i = 0; i < n; ++i) assert(intervals.get(i) == a[i]);
    auto change = [&](int color, long long delta) {
        pairs -= counts[color] * (counts[color] - 1) / 2;
        counts[color] += delta;
        pairs += counts[color] * (counts[color] - 1) / 2;
    };
    for (auto [l, r, color] : operations) {
        check_intervals(intervals, a, 0, n);
        check_intervals(intervals, a, l, r);
        check_intervals(intervals, a, l, l);
        check_intervals(intervals, a, r, r);
        vector<Run> removed;
        intervals.assign(l, r, color, [&](long long begin, long long end, const int &old) {
            removed.emplace_back(begin, end, old);
            change(old, begin - end);
        });
        assert(removed == clipped_runs(a, l, r));
        vector<Run> reference_removed;
        reference.assign(l, r, color, [&](long long begin, long long end, const int &old) {
            reference_removed.emplace_back(begin, end, old);
        });
        assert(removed == reference_removed);
        change(color, r - l);
        fill(a.begin() + l, a.begin() + r, color);
        vector<long long> expected_counts(5);
        for (int i = 0; i < n; ++i) {
            assert(intervals.get(i) == a[i]);
            ++expected_counts[a[i]];
        }
        assert(counts == expected_counts);
        long long expected_pairs = 0;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) expected_pairs += a[i] == a[j];
        assert(pairs == expected_pairs);
        check_intervals(intervals, a, 0, n);
        check_intervals(reference, a, 0, n);
        check_intervals(intervals, a, l, r);
    }
}

struct Value {
    int value;
    explicit Value(int value) : value(value) {}
    bool operator==(const Value &other) const { return value == other.value; }
};

int main() {
    check({}, {{0, 0, 1}, {0, 0, 0}});
    check({0}, {{0, 1, 1}, {0, 1, 1}, {1, 1, 2}, {0, 1, 0}});
    check(vector<int>(10), {{2, 8, 1}, {4, 6, 2}, {4, 6, 1}, {2, 8, 0}, {0, 10, 0},
               {0, 3, 2}, {7, 10, 2}, {3, 7, 2}, {0, 10, 3}, {0, 0, 0}, {10, 10, 0}});
    check(vector<int>(100, 3), {{20, 80, 3}, {0, 20, 2}, {80, 100, 2}, {20, 80, 2}});
    check({0, 1, 2, 3, 4}, {{0, 5, 2}, {1, 4, 1}});
    vector<int> long_runs(1000, 1);
    fill(long_runs.begin() + 200, long_runs.begin() + 800, 2);
    check(long_runs, {{199, 801, 2}, {0, 1000, 1}});
    mt19937 rng(323);
    for (int trial = 0; trial < 200; ++trial) {
        int n = rng() % 50;
        vector<tuple<int, int, int>> operations;
        for (int i = 0; i < 200; ++i) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            operations.emplace_back(l, r, rng() % 5);
        }
        check(vector<int>(n), operations);
        vector<int> initial(n);
        for (int &value : initial) value = rng() % 5;
        check(initial, operations);
    }
    vector<Value> values{Value(1), Value(1), Value(2), Value(3), Value(3)};
    IntervalMap<Value> from_values(values);
    values.clear();
    vector<Run> generic_runs;
    from_values.assign(1, 4, Value(2), [&](long long l, long long r, const Value &value) {
        generic_runs.emplace_back(l, r, value.value);
    });
    assert((generic_runs == vector<Run>{{1, 2, 1}, {2, 3, 2}, {3, 4, 3}}));
    assert(from_values.get(0).value == 1 && from_values.get(4).value == 3);
    for (int i = 1; i < 4; ++i) assert(from_values.get(i).value == 2);
    IntervalMap<Value> empty_values(vector<Value>{});
    empty_values.assign(0, 0, Value(1));
    empty_values.for_each_interval(0, 0, [](long long, long long, const Value &) { assert(false); });
    IntervalMap<Value> generic(LLONG_MAX, Value(1));
    generic.assign(1, LLONG_MAX - 1, Value(2));
    vector<Run> large_runs;
    as_const(generic).for_each_interval(0, LLONG_MAX, [&](long long l, long long r, const Value &value) {
        large_runs.emplace_back(l, r, value.value);
    });
    assert((large_runs == vector<Run>{{0, 1, 1}, {1, LLONG_MAX - 1, 2}, {LLONG_MAX - 1, LLONG_MAX, 1}}));
    generic.assign(0, 1, generic.get(1));
    generic.assign(LLONG_MAX - 1, LLONG_MAX, Value(2));
    int calls = 0;
    generic.assign(0, LLONG_MAX, Value(3), [&](long long l, long long r, const Value &old) {
        assert(l == 0 && r == LLONG_MAX && old.value == 2);
        ++calls;
    });
    assert(calls == 1 && generic.get(0).value == 3 && generic.get(LLONG_MAX - 1).value == 3);
}
