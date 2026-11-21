#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/combinatorics/stirling_first_row.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    auto row = stirling_first_row(n);
    for (int k = 0; k <= n; ++k) {
        pr.print(row[k].val);
        pr.print(k == n ? '\n' : ' ');
    }
}
