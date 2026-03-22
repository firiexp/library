#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include <algorithm>
#include <vector>
using namespace std;

#include "../datastructure/wavelet_matrix.cpp"
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

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
        int l, r, x;
        in.read(l);
        in.read(r);
        in.read(x);
        out.println(wm.freq(l, r, x));
    }
    return 0;
}
