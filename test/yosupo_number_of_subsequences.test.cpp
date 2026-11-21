#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/modular/modint_base.cpp"
#include "../string/count_distinct_subsequences.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    vector<int> a(n);
    sc.read(a);
    pr.println(count_distinct_subsequences<modint<998244353>>(a).val);
}
