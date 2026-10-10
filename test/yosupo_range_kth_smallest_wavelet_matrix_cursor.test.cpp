#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/wavelet_matrix.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<int> v(n);
    for (int &x : v) in.read(x);
    WaveletMatrix<int> wm(v);
    while (q--) {
        int l, r, k;
        in.read(l, r, k);
        int m = l + (r - l) / 2;
        auto a = wm.range_cursor(l, m), b = wm.range_cursor(m, r);
        while (!a.is_leaf()) {
            auto x = wm.split(a), y = wm.split(b);
            int low = x.low.count() + y.low.count();
            if (k < low) {
                a = x.low;
                b = y.low;
            } else {
                k -= low;
                a = x.high;
                b = y.high;
            }
        }
        out.println(a.empty() ? b.value() : a.value());
    }
}
