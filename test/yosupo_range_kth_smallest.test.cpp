#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <algorithm>
#include <type_traits>
#include <vector>
using namespace std;

#include "../datastructure/wavelet_matrix.cpp"
#include <cstdio>
#include <cstring>
#include <string>

#include "../util/fastio.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n);
    in.read(q);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) in.read(a[i]);

    WaveletMatrix<int> wm(a);
    while (q--) {
        int l, r, k;
        in.read(l);
        in.read(r);
        in.read(k);
        out.println(wm.kth_smallest(l, r, k));
    }
    return 0;
}
