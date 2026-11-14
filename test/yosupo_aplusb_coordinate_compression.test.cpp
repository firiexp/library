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

struct Key {
    int key;
    bool operator<(const Key& other) const { return key < other.key; }
};

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
    check<double>({0.5, -1.5, 3.25, 0.5}, {-2, -1.5, -1, 0, 0.5, 1, 3.25, 4});
    check<Key>({ {2}, {1}, {2}, {0}}, { {-1}, {0}, {1}, {2}, {3}});

    mt19937 rng(825);
    for (int tc = 0; tc < 100; ++tc) {
        vector<int> input(rng() % 50);
        for (int& x : input) x = (int)(rng() % 21) - 10;
        vector<int> queries{-11, 0, 11};
        for (int i = 0; i < 12; ++i) queries.push_back((int)(rng() % 25) - 12);
        check(input, queries);
    }
}
