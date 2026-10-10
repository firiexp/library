#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/wavelet_matrix.cpp"

template<class T>
T kth(const WaveletMatrix<T> &wm, const vector<pair<int, int>> &ranges, int k) {
    vector<typename WaveletMatrix<T>::Cursor> cursors;
    for (auto [l, r] : ranges) cursors.push_back(wm.range_cursor(l, r));
    while (!cursors[0].is_leaf()) {
        vector<typename WaveletMatrix<T>::Children> children;
        int low = 0;
        for (const auto &cur : cursors) {
            children.push_back(wm.split(cur));
            low += children.back().low.count();
        }
        for (int i = 0; i < (int)cursors.size(); ++i)
            cursors[i] = k < low ? children[i].low : children[i].high;
        if (k >= low) k -= low;
    }
    for (const auto &cur : cursors) if (!cur.empty()) return cur.value();
    abort();
}

template<class T>
void check_leaves(const WaveletMatrix<T> &wm, int l, int r, const vector<T> &values) {
    using Cursor = typename WaveletMatrix<T>::Cursor;
    auto visit = [&](auto &&self, Cursor cur) -> vector<T> {
        assert(cur.empty() == (cur.count() == 0));
        if (cur.is_leaf()) {
            if (cur.empty()) return {};
            return vector<T>(cur.count(), cur.value());
        }
        auto [low, high] = wm.split(cur);
        assert(low.count() + high.count() == cur.count());
        auto a = self(self, low), b = self(self, high);
        a.insert(a.end(), b.begin(), b.end());
        return a;
    };
    vector<T> expected(values.begin() + l, values.begin() + r);
    sort(expected.begin(), expected.end());
    assert(visit(visit, wm.range_cursor(l, r)) == expected);
}

void self_check() {
    WaveletMatrix<int> empty;
    assert(empty.range_cursor(0, 0).empty() && empty.range_cursor(0, 0).is_leaf());
    mt19937 rng(27);
    for (int n : {0, 1, 2, 3, 5, 17, 63, 64, 65, 127, 128, 129}) {
        for (int mode = 0; mode < 3; ++mode) {
            vector<long long> v(n);
            for (int i = 0; i < n; ++i) {
                v[i] = mode == 0 ? -7 : mode == 1 ? int(rng() % 13) - 6 : (i & 1 ? LLONG_MAX - i : LLONG_MIN + i);
            }
            WaveletMatrix<long long> wm(v);
            check_leaves(wm, 0, n, v);
            check_leaves(wm, n, n, v);
            for (int tc = 0; tc < 100; ++tc) {
                vector<pair<int, int>> ranges;
                vector<long long> expected;
                for (int j = 0, count = 1 + rng() % 4; j < count; ++j) {
                    int l = rng() % (n + 1), r = rng() % (n + 1);
                    if (l > r) swap(l, r);
                    ranges.emplace_back(l, r);
                    expected.insert(expected.end(), v.begin() + l, v.begin() + r);
                }
                sort(expected.begin(), expected.end());
                for (int k = 0; k < (int)expected.size(); ++k) assert(kth(wm, ranges, k) == expected[k]);
            }
            vector<long long> vals = v;
            sort(vals.begin(), vals.end());
            vals.erase(unique(vals.begin(), vals.end()), vals.end());
            vector<int> idx(n);
            for (int i = 0; i < n; ++i) idx[i] = lower_bound(vals.begin(), vals.end(), v[i]) - vals.begin();
            wm.build_from_index(idx, vals);
            check_leaves(wm, 0, n, v);
            auto copy = wm;
            check_leaves(copy, 0, n, v);
            auto moved = move(copy);
            check_leaves(moved, 0, n, v);
            wm.build({});
            assert(wm.range_cursor(0, 0).empty());
        }
    }
    vector<string> words{"b", "a", "c", "a"};
    WaveletMatrix<string> strings(words);
    check_leaves(strings, 0, 4, words);
    assert(kth(strings, {{0, 3}, {1, 4}}, 3) == "b");
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
