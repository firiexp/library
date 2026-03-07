#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#include "../datastructure/wavelet_matrix.cpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    WaveletMatrix<int> wm(a);
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << wm.freq(l, r, x) << '\n';
    }
    return 0;
}
