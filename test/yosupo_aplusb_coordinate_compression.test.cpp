#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../util/coordinate_compression.cpp"
#include "../datastructure/segmenttree/segtree.cpp"

struct Sum {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

template<class T>
void check(const vector<T>& input, const vector<T>& probes) {
    const CoordinateCompression<T> cc(input);
    set<T> distinct(input.begin(), input.end());
    vector<T> expected(distinct.begin(), distinct.end());
    int m = (int)expected.size();
    assert(cc.size() == m);
    for (int i = 0; i < m; ++i) {
        assert(!(cc.value(i) < expected[i]) && !(expected[i] < cc.value(i)));
        assert(cc.index(cc.value(i)) == i);
    }
    for (const T& x : input) {
        int i = cc.index(x);
        assert(0 <= i && i < m);
        assert(!(cc.value(i) < x) && !(x < cc.value(i)));
    }
    for (const T& x : probes) {
        int less = 0, less_equal = 0, index = -1;
        for (int i = 0; i < m; ++i) {
            less += expected[i] < x;
            less_equal += !(x < expected[i]);
            if (!(expected[i] < x) && !(x < expected[i])) index = i;
        }
        assert(cc.lower_bound(x) == less);
        assert(cc.upper_bound(x) == less_equal);
        assert(cc.index(x) == index);
    }

    SegmentTree<Sum> seg(m);
    vector<long long> weights(m);
    for (int i = 0; i < (int)input.size(); ++i) weights[cc.index(input[i])] += i + 1;
    for (int i = 0; i < m; ++i) seg.set(i, weights[i]);
    seg.build();
    for (const T& low : probes) {
        for (const T& high : probes) {
            array<pair<int, int>, 4> ranges{
                cc.range(low, high), cc.range_closed(low, high),
                cc.range_open(low, high), cc.range_open_closed(low, high)
            };
            for (int mode = 0; mode < 4; ++mode) {
                bool closed_left = mode < 2, closed_right = mode % 2;
                auto contains = [&](const T& x) {
                    return (closed_left ? !(x < low) : low < x)
                        && (closed_right ? !(high < x) : x < high);
                };
                auto [l, r] = ranges[mode];
                assert(0 <= l && l <= r && r <= m);
                int start = 0;
                for (int i = 0; i < m; ++i) {
                    start += closed_left ? expected[i] < low : !(low < expected[i]);
                    assert((l <= i && i < r) == contains(expected[i]));
                }
                assert(l == start);
                long long sum = 0;
                for (int i = 0; i < (int)input.size(); ++i) {
                    if (contains(input[i])) sum += i + 1;
                }
                assert(seg.query(l, r) == sum);
            }
        }
    }
}

template<class T>
void check_radix() {
    mt19937_64 rng(481);
    for (int n : {8191, 8192, 8193, 65535, 65536, 65537, 100000}) {
        for (int mode = 0; mode < 7; ++mode) {
            vector<T> input(n);
            for (T& x : input) {
                if (mode == 1) x = T(3);
                else if (mode == 2) x = T(rng() % 17);
                else if (mode == 3) x = T(numeric_limits<T>::max() - T(rng() % 16));
                else if (mode == 4) x = T(numeric_limits<T>::lowest() + T(rng() % 16));
                else x = T(rng());
            }
            if (mode == 0) {
                input[0] = numeric_limits<T>::lowest();
                input[1] = numeric_limits<T>::max();
            }
            if (mode == 5) sort(input.begin(), input.end());
            if (mode == 6) sort(input.rbegin(), input.rend());
            vector<T> expected = input;
            sort(expected.begin(), expected.end());
            expected.erase(unique(expected.begin(), expected.end()), expected.end());
            const CoordinateCompression<T> cc(move(input));
            assert(cc.size() == (int)expected.size());
            for (int i = 0; i < cc.size(); ++i) assert(cc.value(i) == expected[i]);
            vector<T> probes{numeric_limits<T>::lowest(), numeric_limits<T>::max(), T(0), T(1)};
            for (int i = 0; i < 8; ++i) {
                probes.push_back(T(rng()));
                probes.push_back(expected[rng() % expected.size()]);
            }
            for (T low : probes) {
                int l = lower_bound(expected.begin(), expected.end(), low) - expected.begin();
                int u = upper_bound(expected.begin(), expected.end(), low) - expected.begin();
                assert(cc.lower_bound(low) == l);
                assert(cc.upper_bound(low) == u);
                assert(cc.index(low) == (l < u ? l : -1));
                for (T high : probes) {
                    int r = lower_bound(expected.begin(), expected.end(), high) - expected.begin();
                    int v = upper_bound(expected.begin(), expected.end(), high) - expected.begin();
                    assert(cc.range(low, high) == make_pair(l, max(l, r)));
                    assert(cc.range_closed(low, high) == make_pair(l, max(l, v)));
                    assert(cc.range_open(low, high) == make_pair(u, max(u, r)));
                    assert(cc.range_open_closed(low, high) == make_pair(u, max(u, v)));
                }
            }
        }
    }
}

int main() {
    vector<int> probes{-5, -3, -2, -1, 0, 1, 2, 3, 4, 5, 7};
    vector<int> alphabet{-3, -1, 0, 2, 4};
    for (int mask = 0; mask < (1 << (int)alphabet.size()); ++mask) {
        vector<int> input;
        for (int i = 0; i < (int)alphabet.size(); ++i) {
            if (mask >> i & 1) {
                input.push_back(alphabet[i]);
                input.push_back(alphabet[i]);
            }
        }
        check(input, probes);
        reverse(input.begin(), input.end());
        check(input, probes);
    }
    check<int>({40, 10, 20, 20, 100}, {9, 10, 15, 20, 30, 40, 100, 101});
    check<int>({INT_MIN, INT_MAX, INT_MIN}, {INT_MIN, INT_MIN + 1, -1, 0, 1, INT_MAX - 1, INT_MAX});
    check<long long>({LLONG_MIN, LLONG_MAX, 0, LLONG_MIN},
                     {LLONG_MIN, LLONG_MIN + 1, -1, 0, 1, LLONG_MAX - 1, LLONG_MAX});
    check<unsigned long long>({0, ULLONG_MAX, 1, ULLONG_MAX}, {0, 1, 2, ULLONG_MAX - 1, ULLONG_MAX});
    check_radix<signed char>();
    check_radix<unsigned char>();
    check_radix<short>();
    check_radix<unsigned short>();
    check_radix<int>();
    check_radix<unsigned>();
    check_radix<long long>();
    check_radix<unsigned long long>();

    mt19937 rng(825);
    for (int tc = 0; tc < 100; ++tc) {
        vector<int> input(rng() % 50);
        for (int& x : input) x = (int)(rng() % 21) - 10;
        vector<int> queries{-11, 0, 11};
        for (int i = 0; i < 12; ++i) queries.push_back((int)(rng() % 25) - 12);
        check(input, queries);
    }
}
