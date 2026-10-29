#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/stirling_second_row.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    auto row = stirling_second_row(n, n);
    for (int i = 0; i <= n; ++i) {
        pr.print(row[i].val);
        pr.print(i == n ? '\n' : ' ');
    }
}
