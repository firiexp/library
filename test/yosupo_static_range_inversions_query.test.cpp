#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include <algorithm>
#include <vector>

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/binaryindexedtree.cpp"
#include "../util/mo.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) sc.read(a[i]);
    vector<int> xs = a;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
    }

    vector<Query> qs(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        sc.read(l, r);
        qs[i] = Query(l, r, i);
    }
    sort(qs.begin(), qs.end());

    BIT<int> bit((int)xs.size());
    vector<long long> ans(q);
    long long inv = 0;
    int l = 0, r = 0, len = 0;

    auto add_left = [&](int idx) {
        int x = a[idx];
        inv += bit.sum(x);
        bit.add(x, 1);
        ++len;
    };
    auto add_right = [&](int idx) {
        int x = a[idx];
        inv += len - bit.sum(x + 1);
        bit.add(x, 1);
        ++len;
    };
    auto erase_left = [&](int idx) {
        int x = a[idx];
        inv -= bit.sum(x);
        bit.add(x, -1);
        --len;
    };
    auto erase_right = [&](int idx) {
        int x = a[idx];
        inv -= len - bit.sum(x + 1);
        bit.add(x, -1);
        --len;
    };

    for (auto qu : qs) {
        while (qu.l < l) add_left(--l);
        while (r < qu.r) add_right(r++);
        while (l < qu.l) erase_left(l++);
        while (qu.r < r) erase_right(--r);
        ans[qu.no] = inv;
    }
    for (auto x : ans) pr.println(x);
    return 0;
}
