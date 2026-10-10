#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/interval_set.cpp"

void check(const IntervalSet<int>& st, const set<int>& points) {
    vector<pair<int, int>> expected;
    for (int x : points) {
        if (expected.empty() || expected.back().second != x) expected.emplace_back(x, x + 1);
        else ++expected.back().second;
    }
    vector<pair<int, int>> actual;
    for (auto seg : st) actual.emplace_back(seg.l, seg.r);
    assert(actual == expected);
    assert(st.size() == (int)expected.size());
    assert(st.empty() == points.empty());
    assert(st.total_length() == (long long)points.size());
    for (int x = -65; x <= 65; ++x) {
        assert(st.contains(x) == bool(points.count(x)));
        int mex = x;
        while (points.count(mex)) ++mex;
        assert(st.mex(x) == mex);
    }
}

void update(IntervalSet<int>& st, set<int>& points, bool insert, int l, int r) {
    if (insert) {
        for (int x = l; x < r; ++x) points.insert(x);
        auto seg = st.insert(l, r);
        if (l >= r) assert(seg.l == l && seg.r == l);
        else {
            int a = l, b = r;
            while (points.count(a - 1)) --a;
            while (points.count(b)) ++b;
            assert(seg.l == a && seg.r == b);
        }
    } else {
        int removed = 0;
        for (int x = l; x < r; ++x) removed += points.erase(x);
        assert(st.erase(l, r) == removed);
    }
    int covered = 0;
    for (int x = l; x < r; ++x) covered += points.count(x);
    assert(st.covered_length(l, r) == covered);
    check(st, points);
}

int main() {
    IntervalSet<int> st;
    set<int> points;
    const vector<tuple<bool, int, int>> fixed = {
        {false, 0, 10}, {true, 0, 0}, {true, 10, 0}, {true, 0, 10},
        {true, 2, 8}, {true, 0, 10}, {true, 10, 20}, {true, -10, 0},
        {false, -10, -9}, {false, 19, 20}, {false, -3, 4}, {true, -3, 4},
        {false, 0, 0}, {false, 10, 0}, {false, -60, 60}, {true, -20, -10},
        {true, 0, 10}, {true, 20, 30}, {false, -15, 25}, {false, -60, 60},
        {true, 0, 1}
    };
    for (auto [insert, l, r] : fixed) update(st, points, insert, l, r);
    mt19937 rng(141);
    for (int step = 0; step < 100000; ++step) {
        int l = int(rng() % 129) - 64, r = int(rng() % 129) - 64;
        if (l > r) swap(l, r);
        update(st, points, rng() % 2, l, r);
    }
    IntervalSet<long long, __int128_t> wide;
    wide.insert(LLONG_MIN, LLONG_MAX);
    __int128_t length = (__int128_t)LLONG_MAX - LLONG_MIN;
    assert(wide.total_length() == length);
    assert(wide.erase(-1, 1) == 2);
    assert(wide.total_length() == length - 2);
    wide.insert(-1, 1);
    assert(wide.total_length() == length);
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
