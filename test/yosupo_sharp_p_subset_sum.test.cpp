#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/combinatorics/subset_sum_counts.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, t;
    in.read(n, t);
    vector<int> weights(n);
    for (auto& x : weights) in.read(x);
    auto result = subset_sum_counts(weights, t);
    for (int s = 1; s <= t; ++s) {
        if (s > 1) out.print(' ');
        out.print(result[s].val);
    }
    out.println();
}
