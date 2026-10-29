#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/partition_numbers.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    auto p = partition_numbers(n);
    for (int i = 0; i <= n; ++i) {
        pr.print(p[i].val);
        pr.print(i == n ? '\n' : ' ');
    }
}
