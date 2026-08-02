#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include <algorithm>
#include <type_traits>
#include <vector>
using namespace std;

#include "../datastructure/wavelet_matrix.cpp"
#include <cstdio>
#include <cstring>
#include <string>

#include <charconv>
#include "../util/fastio.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n);
    in.read(q);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) in.read(a[i]);

    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());

    WaveletMatrix<int> wm;
    wm.build_from_index(idx, vals);
    while (q--) {
        int l, r, x;
        in.read(l);
        in.read(r);
        in.read(x);
        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        if (xi == (int)vals.size() || vals[xi] != x) out.println(0);
        else out.println(wm.count_equal_index(l, r, xi));
    }
    return 0;
}
