#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../util/mo.cpp"

int main() {
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
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
