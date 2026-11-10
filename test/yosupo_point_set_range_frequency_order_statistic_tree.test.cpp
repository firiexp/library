#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/point_set_range_frequency.cpp"
#include "../util/fastio.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<int> a(n);
    for (int& x : a) sc.read(x);
    PointSetRangeFrequency<int> rf(move(a));
    while (q--) {
        int type;
        sc.read(type);
        if (type == 0) {
            int p, x;
            sc.read(p, x);
            rf.set(p, x);
        } else {
            int l, r, x;
            sc.read(l, r, x);
            pr.println(rf.freq(l, r, x));
        }
    }
}
