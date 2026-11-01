#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_G"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/range_add_range_sum_bit.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    RangeAddRangeSumBIT<long long> bit(n);
    while (q--) {
        int type, l, r;
        in.read(type, l, r);
        --l;
        if (type == 0) {
            long long x;
            in.read(x);
            bit.add(l, r, x);
        } else {
            out.println(bit.sum(l, r));
        }
    }
}
