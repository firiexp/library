#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"

#include <algorithm>
#include <type_traits>
#include <vector>
using namespace std;

#include "../datastructure/weighted_wavelet_matrix.cpp"
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
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) in.read(a[i]);

    WeightedWaveletMatrix<long long, long long> wm(a, a);
    while (q--) {
        int l, r;
        long long x;
        in.read(l);
        in.read(r);
        in.read(x);
        auto res = wm.count_sum_less_equal(l, r, x);
        out.println(res.count, res.sum);
    }
    return 0;
}
