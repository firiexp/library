#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/point_set_range_frequency.cpp"

int main() {
    PointSetRangeFrequency<long long> empty({});
    assert(empty.size() == 0);
    assert(empty.freq(0, 0, 1) == 0);
    vector<long long> a{LLONG_MIN, 7, 7, LLONG_MAX};
    PointSetRangeFrequency<long long> rf(a);
    auto check = [&] {
        assert(rf.size() == (int)a.size());
        for (int l = 0; l <= (int)a.size(); ++l) {
            for (int r = l; r <= (int)a.size(); ++r) {
                for (long long x : {LLONG_MIN, -1LL, 7LL, 99LL, LLONG_MAX}) {
                    assert(rf.freq(l, r, x) == count(a.begin() + l, a.begin() + r, x));
                }
            }
        }
        for (int i = 0; i < (int)a.size(); ++i) assert(rf.get(i) == a[i]);
    };
    check();
    for (auto [p, x] : vector<pair<int, long long>>{{1, 7}, {0, 99}, {3, LLONG_MIN}, {2, -1}}) {
        rf.set(p, x);
        a[p] = x;
        check();
    }
    PointSetRangeFrequency<string> words({"a", "bb", "a"});
    words.set(0, words.get(1));
    assert(words.freq(0, 3, "bb") == 2);
    assert(words.freq(0, 3, "a") == 1);

    mt19937 rng(406);
    for (int tc = 0; tc < 200; ++tc) {
        int n = 1 + rng() % 80;
        vector<long long> values(n);
        for (auto& x : values) x = int(rng() % 11) - 5;
        PointSetRangeFrequency<long long> tree(values);
        int last = 0;
        for (int step = 0; step < 500; ++step) {
            if (rng() % 2 == 0) {
                int p = rng() % n;
                long long x = step % 5 == 0 ? values[p] : (long long)rng() + last;
                tree.set(p, x);
                values[p] = x;
                assert(tree.get(p) == x);
            } else {
                int l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);
                long long x = rng() % 2 ? values[rng() % n] : -10LL;
                last = tree.freq(l, r, x);
                assert(last == count(values.begin() + l, values.begin() + r, x));
            }
        }
    }
}
