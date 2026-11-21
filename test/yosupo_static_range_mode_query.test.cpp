#define PROBLEM "https://judge.yosupo.jp/problem/static_range_mode_query"

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/static_range_mode.cpp"
#include "../util/fastio.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<int> a(n);
    sc.read(a);
    const StaticRangeMode<int> mode(move(a));
    while (q--) {
        int l, r;
        sc.read(l, r);
        auto [value, freq] = mode.query(l, r);
        pr.println(value, freq);
    }
}
