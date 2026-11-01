#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../math/modular/modint_base.cpp"
#include "../datastructure/wavelet_matrix/weighted_wavelet_matrix.cpp"
#include "../datastructure/wavelet_matrix/static_range_distinct_sum.cpp"
#include "../datastructure/wavelet_matrix/weighted_wavelet_matrix.cpp"

template<class U, class T, class F>
void check(const vector<T> &a, F weight) {
    int calls = 0;
    const StaticRangeDistinctSum<T, U> distinct(a, [&](const T &value) {
        ++calls;
        return weight(value);
    });
    int n = a.size(), built_calls = calls;
    vector<pair<int, int>> queries;
    for (int l = 0; l <= n; ++l)
        for (int r = l; r <= n; ++r) queries.emplace_back(l, r);
    mt19937 rng(n);
    shuffle(queries.begin(), queries.end(), rng);
    for (auto [l, r] : queries) {
        set<T> seen(a.begin() + l, a.begin() + r);
        U expected{};
        for (const T &value : seen) expected += weight(value);
        assert(distinct.sum(l, r) == expected);
    }
    assert(calls == built_calls);
    if (n == 0) assert(calls == 0);
}

struct Key {
    int value, id;
    bool operator<(const Key &other) const { return value < other.value; }
};

int main() {
    auto weight = [](int x) { return 1LL * x * x * x - 4; };
    check<ll>(vector<int>{}, weight);
    check<ll>(vector<string>{"", "abc", "a", "abc", "", "ab"},
              [](const string &s) { return (ll)s.size() - 2; });
    check<ll>(vector<Key>{{1, 0}, {-2, 1}, {1, 2}, {3, 3}, {-2, 4}},
              [](const Key &x) { return x.value; });
    for (int n : {1, 2, 63, 64, 65, 127, 128, 129}) {
        check<ll>(vector<int>(n, -2), weight);
        vector<int> a(n);
        iota(a.begin(), a.end(), -n / 2);
        check<ll>(a, weight);
        for (int i = 0; i < n; ++i) a[i] = i % 5 - 2;
        check<ll>(a, weight);
        check<modint<7>>(a, weight);
    }
    mt19937 rng(324);
    for (int tc = 0; tc < 600; ++tc) {
        vector<int> a(rng() % 45);
        for (int &x : a) x = int(rng() % 15) - 7;
        check<ll>(a, weight);
    }
    vector<int> large(4097);
    for (int &x : large) x = rng() % 200;
    const StaticRangeDistinctSum<int, ll> distinct(large, weight);
    for (int q = 0; q < 500; ++q) {
        int l = rng() % (large.size() + 1), r = rng() % (large.size() + 1);
        if (l > r) swap(l, r);
        set<int> seen(large.begin() + l, large.begin() + r);
        ll expected = 0;
        for (int x : seen) expected += weight(x);
        assert(distinct.sum(l, r) == expected);
    }
}
