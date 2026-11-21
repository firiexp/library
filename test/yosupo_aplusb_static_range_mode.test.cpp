#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/static_range_mode.cpp"

template<class T>
void check(const vector<T> &a) {
    const StaticRangeMode<T> mode(a);
    for (int l = int(a.size()) - 1; l >= 0; --l) {
        map<T, int> count;
        int expected = 0;
        for (int r = l + 1; r <= int(a.size()); ++r) {
            expected = max(expected, ++count[a[r - 1]]);
            auto [value, freq] = mode.query(l, r);
            assert(freq == expected && count.at(value) == expected);
        }
    }
}

int main() {
    check(vector<int>{});
    check(vector<string>{"red", "blue", "green", "blue", "red", "green", "green"});
    check(vector<long long>{LLONG_MIN, LLONG_MAX, LLONG_MAX, 0, LLONG_MIN});
    for (int n : {1, 15, 16, 17, 63, 64, 65}) {
        vector<int> a(n, -7);
        check(a);
        iota(a.begin(), a.end(), -n);
        check(a);
        for (int i = 0; i < n; ++i) a[i] = i % 3;
        check(a);
    }
    vector<int> a(7);
    for (int mask = 0; mask < 2187; ++mask) {
        int digits = mask;
        for (int &x : a) {
            x = digits % 3;
            digits /= 3;
        }
        check(a);
    }
    mt19937 rng(562);
    for (int trial = 0; trial < 250; ++trial) {
        vector<int> values(1 + rng() % 70);
        int kinds = 1 + rng() % values.size();
        for (int &x : values) x = rng() % kinds;
        check(values);
    }
}
