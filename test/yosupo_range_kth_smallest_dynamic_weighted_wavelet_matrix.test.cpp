#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/dynamic_weighted_wavelet_matrix.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<int> values(n);
    for (int &x : values) in.read(x);
    DynamicWeightedWaveletMatrix<int, long long> wm(values, vector<long long>(n));
    while (q--) {
        int l, r, k;
        in.read(l, r, k);
        out.println(wm.kth_smallest(l, r, k));
    }
}
