#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../datastructure/wavelet_matrix/static_range_distinct.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<ll> a(n);
    for (auto& x : a) in.read(x);
    StaticRangeDistinct<ll> distinct(a);
    while (q--) {
        int l, r;
        in.read(l, r);
        out.println(distinct.count(l, r));
    }
}
