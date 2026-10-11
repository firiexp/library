#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../datastructure/wavelet_matrix.cpp"
#include "../datastructure/static_range_distinct.cpp"
#include "../datastructure/wavelet_matrix.cpp"

template<class T>
void check(const vector<T>& a) {
    const StaticRangeDistinct<T> distinct(a);
    int n = a.size();
    for (int l = 0; l <= n; ++l) {
        set<T> seen;
        assert(distinct.count(l, l) == 0);
        for (int r = l + 1; r <= n; ++r) {
            seen.insert(a[r - 1]);
            assert(distinct.count(l, r) == (int)seen.size());
        }
    }
    mt19937 rng(n);
    for (int i = 0; i < 100; ++i) {
        int l = rng() % (n + 1), r = rng() % (n + 1);
        if (l > r) swap(l, r);
        set<T> seen(a.begin() + l, a.begin() + r);
        assert(distinct.count(l, r) == (int)seen.size());
    }
}

struct Key {
    int value, id;
    bool operator<(const Key& other) const { return value < other.value; }
};

void self_check() {
    check(vector<ll>{});
    check(vector<ll>{LLONG_MIN, LLONG_MAX, LLONG_MIN, 0, -1, 1LL << 50});
    check(vector<string>{"", "abc", "ab", "abc", "", "a"});
    check(vector<Key>{{1, 0}, {2, 1}, {1, 2}, {3, 3}, {2, 4}});
    for (int n : {1, 2, 63, 64, 65, 127, 128, 129}) {
        check(vector<int>(n, 7));
        vector<int> a(n);
        iota(a.begin(), a.end(), 0);
        check(a);
        for (int i = 0; i < n; ++i) a[i] = i % 7;
        check(a);
    }
    mt19937 rng(158);
    for (int tc = 0; tc < 2000; ++tc) {
        vector<ll> a(rng() % 61);
        for (auto& x : a) x = (int(rng() % 17) - 8) * (1LL << 40);
        auto original = a;
        check(a);
        assert(a == original);
    }
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
