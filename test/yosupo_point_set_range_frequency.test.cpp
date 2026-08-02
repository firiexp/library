#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../datastructure/dynamic_weighted_wavelet_matrix.cpp"
#include <charconv>
#include "../util/fastio.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<int> a(n);
    for (int &x : a) sc.read(x);

    struct Query {
        int type, a, b, c;
    };
    vector<Query> queries;
    queries.reserve(q);

    DynamicWeightedWaveletMatrix<int, int> wm(n);
    for (int i = 0; i < q; ++i) {
        int type;
        sc.read(type);
        if (type == 0) {
            int k, x;
            sc.read(k, x);
            wm.add_value_candidate(k, x);
            queries.push_back({type, k, x, 0});
        }
        else {
            int l, r, x;
            sc.read(l, r, x);
            queries.push_back({type, l, r, x});
        }
    }

    wm.build(a, vector<int>(n, 0));
    for (const Query &query : queries) {
        if (query.type == 0) {
            bool ok = wm.set_value(query.a, query.b);
            assert(ok);
        }
        else {
            pr.println(wm.freq(query.a, query.b, query.c));
        }
    }
    return 0;
}
