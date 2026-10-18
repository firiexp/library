#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/mo.cpp"

void check_sum_and_distinct() {
    mt19937 rng(227);
    for (int tc = 0; tc < 300; ++tc) {
        int n = rng() % 101, count = rng() % 201;
        vector<int> a(n), freq(16);
        for (int &value : a) value = rng() % 16;
        vector<Query> queries;
        vector<pair<int, int>> expected;
        for (int i = 0; i < count; ++i) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            if (tc % 4 == 1) l = 0;
            if (tc % 4 == 2) r = n;
            if (tc % 4 == 3) l = r = n / 2;
            queries.emplace_back(l, r, -i - 1);
            set<int> distinct(a.begin() + l, a.begin() + r);
            expected.emplace_back(accumulate(a.begin() + l, a.begin() + r, 0), distinct.size());
        }
        int width = tc % 3 == 0 ? 1 : tc % 3 == 1 ? 7 : INT_MAX;
        int sum = 0, distinct = 0, previous = -1;
        vector<int> seen(count);
        auto add = [&](int i) {
            sum += a[i];
            distinct += freq[a[i]]++ == 0;
        };
        auto erase = [&](int i) {
            sum -= a[i];
            distinct -= --freq[a[i]] == 0;
        };
        Query::B = width;
        mo_solve(n, queries, add, add, erase, erase, [&](int no) {
            int i = -no - 1;
            assert(make_pair(sum, distinct) == expected[i]);
            if (previous != -1) assert(!(queries[i] < queries[previous]));
            previous = i;
            ++seen[i];
        }, width);
        for (int value : seen) assert(value == 1);
        assert(Query::bucket_size == width);
    }
}

int main() {
    check_sum_and_distinct();
    mt19937 rng(87);
    for (int tc = 0; tc < 10000; ++tc) {
        int n = rng() % 31, q = rng() % 41;
        vector<int> a(n);
        for (int& x : a) x = rng() % 10;
        vector<Query> qs;
        vector<int> expected(q), seen(q);
        for (int i = 0; i < q; ++i) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            qs.emplace_back(l, r, 3 * i + 7);
            for (int j = l; j < r; ++j)
                for (int k = j + 1; k < r; ++k) expected[i] += a[j] > a[k];
        }
        shuffle(qs.begin(), qs.end(), rng);
        auto original = qs;
        Query::bucket_size = 7;
        int l = 0, r = 0, inv = 0;
        auto add_left = [&](int i) {
            assert(i == l - 1);
            for (int j = l; j < r; ++j) inv += a[i] > a[j];
            --l;
        };
        auto add_right = [&](int i) {
            assert(i == r);
            for (int j = l; j < r; ++j) inv += a[j] > a[i];
            ++r;
        };
        auto erase_left = [&](int i) {
            assert(l < r && i == l);
            ++l;
            for (int j = l; j < r; ++j) inv -= a[i] > a[j];
        };
        auto erase_right = [&](int i) {
            assert(l < r && i == r - 1);
            --r;
            for (int j = l; j < r; ++j) inv -= a[j] > a[i];
        };
        auto output = [&](int no) {
            assert((no - 7) % 3 == 0);
            int id = (no - 7) / 3;
            assert(0 <= id && id < q);
            assert(inv == expected[id]);
            ++seen[id];
        };
        int width = tc % 3 == 0 ? 0 : tc % 3 == 1 ? 1 : n + 2;
        mo_solve(n, qs, add_left, add_right, erase_left, erase_right, output, width);
        assert(Query::bucket_size == 7);
        assert(qs.size() == original.size());
        for (int i = 0; i < q; ++i) {
            assert(seen[i] == 1);
            assert(tie(qs[i].l, qs[i].r, qs[i].no) == tie(original[i].l, original[i].r, original[i].no));
        }
    }
}
