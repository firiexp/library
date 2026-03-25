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

    vector<long long> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());

    WeightedWaveletMatrix<long long, long long> wm;
    wm.build_from_index(idx, vals, a);
    while (q--) {
        int l, r;
        long long x;
        in.read(l);
        in.read(r);
        in.read(x);
        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
        auto res = wm.count_sum_less_index(l, r, xi);
        out.println(res.count, res.sum);
    }
    return 0;
}
