#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../math/prime/totient_mobius_sum.cpp"

int main() {
    Scanner sc;
    Printer pr;
    long long n;
    sc.read(n);
    TotientMobiusSum sums(n, min(n, 1000000LL));
    pr.println((int)(sums.get(n).first % 998244353));
}
